# -*- coding: utf-8 -*-
import sys
sys.stdout.reconfigure(encoding='utf-8')

file_path = r"F:\TVTEST PROJECT\TVTest-develop\src\ChannelScan.cpp"

with open(file_path, 'r', encoding='utf-8') as f:
    code = f.read()

# Replacement code around RemoteControlKeyID and channel naming
target = """					int RemoteControlKeyID = pAnalyzer->GetRemoteControlKeyID();
					if (RemoteControlKeyID == 0) {
						RemoteControlKeyID =
							App.NetworkDefinition.GetRemoteControlKeyID(NetworkID, ServiceID);
					}

					String Name = ServiceInfo.ServiceName;
					// ハイフンの代わりにマイナス記号(U+2212)が使われている局がある
					StringUtility::Replace(Name, L'\\u2212', L'\\uff0d');"""

replacement = """					int RemoteControlKeyID = pAnalyzer->GetRemoteControlKeyID();
					if (RemoteControlKeyID == 0) {
						RemoteControlKeyID =
							App.NetworkDefinition.GetRemoteControlKeyID(NetworkID, ServiceID);
					}

					// ISDB-Tb Internacional: si no viene RemoteControlKeyID, intentar deducir el canal mayor
					int MajorChannel = RemoteControlKeyID;
					if (MajorChannel == 0 && m_ScanChannel >= 0 && m_ScanChannel < static_cast<int>(m_BonDriverChannelList.size())) {
						const String &BonChName = m_BonDriverChannelList[m_ScanChannel];
						// Buscar primer número de canal en el nombre del transpondedor/canal BonDriver (ej: "CH 07", "7", "Canal 24", etc.)
						for (size_t c = 0; c < BonChName.length(); c++) {
							if (BonChName[c] >= L'0' && BonChName[c] <= L'9') {
								int val = 0;
								while (c < BonChName.length() && BonChName[c] >= L'0' && BonChName[c] <= L'9') {
									val = val * 10 + (BonChName[c] - L'0');
									c++;
								}
								if (val > 0)
									MajorChannel = val;
								break;
							}
						}
					}

					String Name = ServiceInfo.ServiceName;
					// ハイフンの代わりにマイナス記号(U+2212)が使われている局がある
					StringUtility::Replace(Name, L'\\u2212', L'\\uff0d');

					// Formatear numeración ISDB-Tb (ej: "7.1", "7.2", "7.31") al principio del nombre si no lo incluye
					if (MajorChannel > 0) {
						bool bIs1Seg = (ServiceInfo.ServiceType == LibISDB::SERVICE_TYPE_DATA)
							|| (ServiceIndex >= 0 && pAnalyzer->Is1SegService(ServiceIndex))
							|| (Name.find(TEXT("1Seg")) != String::npos)
							|| (Name.find(TEXT("1seg")) != String::npos)
							|| (Name.find(TEXT("ワンセグ")) != String::npos);

						int MinorChannel = bIs1Seg ? 31 : (ServiceCount + 1);

						// Formatear prefijo (ej: "7.1 ", "7.31 ")
						TCHAR szChPrefix[32];
						StringFormat(szChPrefix, TEXT("{}.{} "), MajorChannel, MinorChannel);

						// Verificar si el nombre ya comienza con dicho formato numérico para no duplicarlo
						bool bAlreadyHasPrefix = false;
						if (Name.length() >= 3 && Name[0] >= L'0' && Name[0] <= L'9') {
							size_t dotPos = Name.find(L'.');
							if (dotPos != String::npos && dotPos <= 4 && dotPos + 1 < Name.length() && Name[dotPos + 1] >= L'0' && Name[dotPos + 1] <= L'9')
								bAlreadyHasPrefix = true;
						}

						if (!bAlreadyHasPrefix) {
							Name = String(szChPrefix) + Name;
						}

						if (RemoteControlKeyID == 0) {
							RemoteControlKeyID = MajorChannel;
						}
					}"""

if target in code:
    code = code.replace(target, replacement)
    with open(file_path, 'w', encoding='utf-8') as f:
        f.write(code)
    print("ChannelScan.cpp successfully updated with ISDB-Tb numbering formatting!")
else:
    print("Target block not found in ChannelScan.cpp!")
