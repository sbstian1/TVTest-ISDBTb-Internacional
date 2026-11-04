/*
  LibISDB
  Copyright(c) 2017-2020 DBCTRADO

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/**
 @file   AACDecoder_FDK.cpp
 @brief  AAC デコーダ (FDK_AAC)
 @author DBCTRADO
*/


#include "../../../../LibISDBPrivate.hpp"


#ifdef LIBISDB_HAS_FDK_AAC


#include "AACDecoder_FDK.hpp"
#include "../../../../../Thirdparty/fdk-aac/libAACdec/include/aacdecoder_lib.h"
#include "../../../../Base/DebugDef.hpp"


#pragma comment(lib, "fdk-aac.lib")


namespace LibISDB::DirectShow
{


void AACDecoder_FDK::GetVersion(std::string *pVersion)
{
	LIB_INFO InfoList[FDK_MODULE_LAST];

	::FDKinitLibInfo(InfoList);
	::aacDecoder_GetLibInfo(InfoList);

	for (const LIB_INFO &Info : InfoList) {
		if (Info.module_id == FDK_AACDEC) {
			*pVersion = Info.versionStr;
			return;
		}
	}

	pVersion->clear();
}


AACDecoder_FDK::AACDecoder_FDK() noexcept
	: m_hDecoder(nullptr)
	, m_LastChannelConfig(0xFF)
{
}


AACDecoder_FDK::~AACDecoder_FDK()
{
	Close();
}


bool AACDecoder_FDK::Open()
{
	if (!AACDecoder::Open())
		return false;

	constexpr size_t PCM_BUFFER_SIZE = 8 * sizeof(int16_t) * 4096;
	if (m_PCMBuffer.AllocateBuffer(PCM_BUFFER_SIZE) < PCM_BUFFER_SIZE) {
		Close();
		return false;
	}

	return true;
}


void AACDecoder_FDK::Close()
{
	AACDecoder::Close();

	m_PCMBuffer.FreeBuffer();
}


bool AACDecoder_FDK::IsOpened() const
{
	return m_hDecoder != nullptr;
}


bool AACDecoder_FDK::GetChannelMap(int Channels, int *pMap) const
{
	switch (Channels) {
	case 2:
		pMap[CHANNEL_2_L] = 0;
		pMap[CHANNEL_2_R] = 1;
		break;

	case 6:
		pMap[CHANNEL_6_FL]  = 0;
		pMap[CHANNEL_6_FR]  = 1;
		pMap[CHANNEL_6_FC]  = 2;
		pMap[CHANNEL_6_LFE] = 3;
		pMap[CHANNEL_6_BL]  = 4;
		pMap[CHANNEL_6_BR]  = 5;
		break;

	default:
		return false;
	}

	return true;
}


bool AACDecoder_FDK::GetDownmixInfo(ReturnArg<DownmixInfo> Info) const
{
	if (!Info)
		return false;

	constexpr double PSQR = 1.0 / 1.4142135623730950488016887242097;

	Info->Center = PSQR;
	Info->Front  = 1.0;
	Info->Rear   = PSQR;
	Info->LFE    = 0.0;

	return true;
}


bool AACDecoder_FDK::OpenDecoder()
{
	CloseDecoder();

	// FDK AAC オープン (LATMモード時は TT_MP4_LOAS、通常時は TT_MP4_ADTS)
	const TRANSPORT_TYPE Transport = m_LATMMode ? TT_MP4_LOAS : TT_MP4_ADTS;
	m_hDecoder = ::aacDecoder_Open(Transport, 1);
	if (m_hDecoder == nullptr)
		return false;

	// デコーダのパラメータを設定
	::aacDecoder_SetParam(m_hDecoder, AAC_PCM_OUTPUT_CHANNEL_MAPPING, 1);
	::aacDecoder_SetParam(m_hDecoder, AAC_PCM_MAX_OUTPUT_CHANNELS, 6);
	::aacDecoder_SetParam(m_hDecoder, AAC_PCM_LIMITER_ENABLE, 0);
	// ABNT NBR 15602-2 (ISDB-Tb) / ARIB STD-B21 downmix profile
	::aacDecoder_SetParam(m_hDecoder, AAC_METADATA_PROFILE, AAC_MD_PROFILE_ARIB_JAPAN);
	// Energy interpolation concealment for minor bitstream errors
	::aacDecoder_SetParam(m_hDecoder, AAC_CONCEAL_METHOD, 2);

	m_LastChannelConfig = 0xFF;
	m_HasDecodedFrame = false;
	m_SyncErrorCount = 0;
	m_DecodeError = false;

	return true;
}


void AACDecoder_FDK::CloseDecoder()
{
	// ADK AAC クローズ
	if (m_hDecoder != nullptr) {
		::aacDecoder_Close(m_hDecoder);
		m_hDecoder = nullptr;
	}
}


bool AACDecoder_FDK::DecodeFrame(const ADTSFrame *pFrame, ReturnArg<DecodeFrameInfo> Info)
{
	if (m_hDecoder == nullptr) {
		return false;
	}

	// 初回フレーム解析
	if (pFrame->GetChannelConfig() != m_LastChannelConfig) {
		// チャンネル設定が変化した、デコーダリセット
		LIBISDB_TRACE(
			LIBISDB_STR("AACDecoder_FDK::DecodeFrame() Channel config changed {} -> {}\n"),
			m_LastChannelConfig,
			pFrame->GetChannelConfig());
		if (!ResetDecoder())
			return false;

		m_LastChannelConfig = pFrame->GetChannelConfig();
	}

	// デコード
	bool OK = false;
	UCHAR *p = const_cast<UCHAR *>(pFrame->GetData());
	UINT Avail = static_cast<UINT>(pFrame->GetSize());

	while (Avail > 0) {
		const UINT Size = Avail;
		AAC_DECODER_ERROR Err = ::aacDecoder_Fill(m_hDecoder, &p, &Size, &Avail);
		if (Err != AAC_DEC_OK) {
			LIBISDB_TRACE(
				LIBISDB_STR("aacDecoder_Fill() error {:#X}\n"),
				static_cast<std::underlying_type_t<AAC_DECODER_ERROR>>(Err));
			break;
		}
		p += Size - Avail;

		Err = ::aacDecoder_DecodeFrame(
			m_hDecoder,
			reinterpret_cast<INT_PCM *>(m_PCMBuffer.GetBuffer()),
			static_cast<INT>(m_PCMBuffer.GetBufferSize() / sizeof(int16_t)),
			m_DecodeError ? AACDEC_INTR : 0);
		if (Err == AAC_DEC_TRANSPORT_SYNC_ERROR || Err == AAC_DEC_NOT_ENOUGH_BITS)
			continue;

		if (Err == AAC_DEC_OK) {
			const ::CStreamInfo *pStreamInfo = ::aacDecoder_GetStreamInfo(m_hDecoder);

			m_AudioInfo.Frequency = pStreamInfo->sampleRate;
			m_AudioInfo.ChannelCount = pStreamInfo->numChannels;
			m_AudioInfo.OriginalChannelCount = pStreamInfo->numChannels;
			m_AudioInfo.DualMono = (pStreamInfo->numChannels == 2) && (m_LastChannelConfig == 0);

			Info->pData = m_PCMBuffer.GetBuffer();
			Info->SampleCount = pStreamInfo->frameSize;
			Info->Info = m_AudioInfo;
			Info->Discontinuity = m_DecodeError;

			OK = true;
			break;
		} else {
			// エラー発生
			LIBISDB_TRACE(
				LIBISDB_STR("aacDecoder_DecodeFrame() error {:#X}\n"),
				static_cast<std::underlying_type_t<AAC_DECODER_ERROR>>(Err));

			// リセットする
			//ResetDecoder();
		}
	}

	return OK;
}


namespace
{

void DetectAACTransportFormat(const uint8_t *pData, size_t DataSize, bool *pHasADTS, bool *pHasLOAS) noexcept
{
	*pHasADTS = false;
	*pHasLOAS = false;

	if (pData == nullptr || DataSize < 7)
		return;

	// Check for chained or exact ADTS frames (syncword 0xFFF, layer 00)
	for (size_t i = 0; i + 7 <= DataSize; ++i) {
		if (pData[i] == 0xFF && (pData[i + 1] & 0xF6) == 0xF0) {
			const uint8_t SFI = (pData[i + 2] & 0x3C) >> 2;
			const uint16_t FrameLen = static_cast<uint16_t>(
				((pData[i + 3] & 0x03) << 11) | (pData[i + 4] << 3) | ((pData[i + 5] & 0xE0) >> 5));
			if (SFI < 12 && FrameLen >= 7 && FrameLen <= 4096) {
				const size_t NextPos = i + FrameLen;
				if (NextPos + 3 <= DataSize) {
					if (pData[NextPos] == 0xFF && (pData[NextPos + 1] & 0xF6) == 0xF0 &&
							((pData[NextPos + 2] & 0x3C) >> 2) == SFI) {
						*pHasADTS = true;
						break;
					}
				} else if (i == 0 && FrameLen == DataSize) {
					*pHasADTS = true;
					break;
				}
			}
		}
	}

	// Check for chained or exact LOAS frames (syncword 0x2B7 -> 0x56 0xE0)
	for (size_t i = 0; i + 4 <= DataSize; ++i) {
		if (pData[i] == 0x56 && (pData[i + 1] & 0xE0) == 0xE0) {
			const uint16_t MuxLen = static_cast<uint16_t>(((pData[i + 1] & 0x1F) << 8) | pData[i + 2]);
			if (MuxLen >= 6 && MuxLen <= 4096) {
				const size_t NextPos = i + 3 + MuxLen;
				if (NextPos + 3 <= DataSize) {
					const uint16_t NextMuxLen = static_cast<uint16_t>(((pData[NextPos + 1] & 0x1F) << 8) | pData[NextPos + 2]);
					if (pData[NextPos] == 0x56 && (pData[NextPos + 1] & 0xE0) == 0xE0 &&
							NextMuxLen >= 6 && NextMuxLen <= 4096) {
						*pHasLOAS = true;
						break;
					}
				} else if (i == 0 && 3 + MuxLen == DataSize) {
					*pHasLOAS = true;
					break;
				}
			}
		}
	}
}

} // namespace


bool AACDecoder_FDK::DecodeStream(const uint8_t *pData, size_t *pDataSize, ReturnArg<DecodeFrameInfo> Info)
{
	if (m_hDecoder == nullptr || pDataSize == nullptr)
		return false;

	// Auto-detect ADTS vs LOAS/LATM before first frame or after repeated sync errors
	if (pData != nullptr && *pDataSize >= 7 && (!m_HasDecodedFrame || m_SyncErrorCount >= 6)) {
		bool HasADTS = false;
		bool HasLOAS = false;
		DetectAACTransportFormat(pData, *pDataSize, &HasADTS, &HasLOAS);
		if (m_LATMMode && HasADTS && !HasLOAS) {
			LIBISDB_TRACE(LIBISDB_STR("AACDecoder_FDK::DecodeStream Auto-switching LOAS -> ADTS\n"));
			m_LATMMode = false;
			if (!OpenDecoder())
				return false;
		} else if (!m_LATMMode && HasLOAS && !HasADTS) {
			LIBISDB_TRACE(LIBISDB_STR("AACDecoder_FDK::DecodeStream Auto-switching ADTS -> LOAS\n"));
			m_LATMMode = true;
			if (!OpenDecoder())
				return false;
		}
	}

	// First, if there is input data to feed and decoder can accept it, feed it
	if (pData != nullptr && *pDataSize > 0) {
		UCHAR *p = const_cast<UCHAR *>(pData);
		UINT Avail = static_cast<UINT>(*pDataSize);
		const UINT InSize = Avail;

		AAC_DECODER_ERROR FillErr = ::aacDecoder_Fill(m_hDecoder, &p, &InSize, &Avail);
		if (FillErr != AAC_DEC_OK) {
			LIBISDB_TRACE(
				LIBISDB_STR("AACDecoder_FDK::DecodeStream aacDecoder_Fill error {:#X}\n"),
				static_cast<std::underlying_type_t<AAC_DECODER_ERROR>>(FillErr));
		}
		// InDataPos in caller advances by how many bytes FDK-AAC consumed into its internal buffer
		*pDataSize = InSize - Avail;
	} else {
		*pDataSize = 0;
	}

	// Now try to decode a frame from the internal bitstream buffer (bounded retries on sync/parse skip)
	for (int Retry = 0; Retry < 32; ++Retry) {
		UINT FreeBytesBefore = 0;
		::aacDecoder_GetFreeBytes(m_hDecoder, &FreeBytesBefore);

		AAC_DECODER_ERROR Err = ::aacDecoder_DecodeFrame(
			m_hDecoder,
			reinterpret_cast<INT_PCM *>(m_PCMBuffer.GetBuffer()),
			static_cast<INT>(m_PCMBuffer.GetBufferSize() / sizeof(int16_t)),
			0);

		if (Err == AAC_DEC_NOT_ENOUGH_BITS) {
			// Needs more data to form an audio frame; return with SampleCount = 0
			Info->SampleCount = 0;
			return true;
		}

		if (Err == AAC_DEC_OK) {
			const ::CStreamInfo *pStreamInfo = ::aacDecoder_GetStreamInfo(m_hDecoder);
			if (pStreamInfo == nullptr || pStreamInfo->sampleRate <= 0 || pStreamInfo->frameSize <= 0 || pStreamInfo->numChannels <= 0) {
				continue;
			}

			int OutChannels = pStreamInfo->numChannels;

			// If stream has 3/4/5/7/8 channels (which AudioDecoderFilter doesn't map directly),
			// ask FDK-AAC to downmix subsequent frames to 2 channels using ABNT NBR 15602-2 profile,
			// and compact the current frame to 2 channels so no audio frame is lost.
			if (OutChannels != 1 && OutChannels != 2 && OutChannels != 6) {
				::aacDecoder_SetParam(m_hDecoder, AAC_PCM_MAX_OUTPUT_CHANNELS, 2);
				int16_t *pPCM = reinterpret_cast<int16_t *>(m_PCMBuffer.GetBuffer());
				const int FrameSize = pStreamInfo->frameSize;
				for (int i = 0; i < FrameSize; ++i) {
					const int16_t L = pPCM[i * OutChannels + 0];
					const int16_t R = (OutChannels >= 2) ? pPCM[i * OutChannels + 1] : L;
					pPCM[i * 2 + 0] = L;
					pPCM[i * 2 + 1] = R;
				}
				OutChannels = 2;
			}

			m_AudioInfo.Frequency = pStreamInfo->sampleRate;
			m_AudioInfo.ChannelCount = static_cast<uint8_t>(OutChannels);
			m_AudioInfo.OriginalChannelCount = (pStreamInfo->channelConfig > 0 && pStreamInfo->channelConfig <= 6)
				? static_cast<uint8_t>(pStreamInfo->channelConfig)
				: static_cast<uint8_t>(OutChannels);
			m_AudioInfo.DualMono = (OutChannels == 2) && (pStreamInfo->channelConfig == 0);

			Info->pData = m_PCMBuffer.GetBuffer();
			Info->SampleCount = pStreamInfo->frameSize;
			Info->Info = m_AudioInfo;
			Info->Discontinuity = m_DecodeError;
			m_DecodeError = false;
			m_HasDecodedFrame = true;
			m_SyncErrorCount = 0;

			return true;
		}

		UINT FreeBytesAfter = 0;
		::aacDecoder_GetFreeBytes(m_hDecoder, &FreeBytesAfter);

		if (Err == AAC_DEC_TRANSPORT_SYNC_ERROR || IS_DECODE_ERROR(Err)) {
			++m_SyncErrorCount;
			// Only retry if the internal bitstream buffer actually advanced
			if (FreeBytesAfter > FreeBytesBefore) {
				continue;
			}
			Info->SampleCount = 0;
			return true;
		}

		// Fatal decoder error
		LIBISDB_TRACE(
			LIBISDB_STR("AACDecoder_FDK::DecodeStream DecodeFrame fatal error {:#X}\n"),
			static_cast<std::underlying_type_t<AAC_DECODER_ERROR>>(Err));
		Info->SampleCount = 0;
		return false;
	}

	Info->SampleCount = 0;
	return true;
}


#endif // LIBISDB_HAS_FDK_AAC


} // namespace LibISDB::DirectShow
