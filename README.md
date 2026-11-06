# TVTest - ISDB-Tb Internacional

Fork de **TVTest** y **LibISDB** adaptado para la norma de televisión digital terrestre **ISDB-Tb (SBTVD)** utilizada en Latinoamérica (Chile, Argentina, Brasil, Perú, etc.).

<img width="2886" height="1728" alt="Captura de pantalla 2026-11-04 011627" src="https://github.com/user-attachments/assets/07e06465-f99c-42b8-9ec6-012b9d9521cf" />

---

## Características y Modificaciones Implementadas

### 1. Soporte Nativo de Audio AAC-LATM / LOAS
* **Decodificación de flujo `STREAM_TYPE_MPEG4_AUDIO` (`0x11`)**: Mapeo directo y enrutamiento a través de **Fraunhofer FDK-AAC** (`TT_MP4_LOAS`).
* Compatibilidad total con las transmisiones de audio AAC encapsulado en LATM comunes en los estándares SBTVD/ISDB-Tb en Sudamérica.

### 2. Numeración y Canales Virtuales ISDB-Tb
* En el escaneo de canales (`ChannelScan`), formateo automático de la numeración lógica de canal mayor y menor (ejemplo: `7.1 Principal`, `7.2 Secundario`, `7.31 One-Seg`) a partir del transpondedor BonDriver y los servicios detectados.
* Identificación automática de servicios móviles 1Seg (subcanal `.31`).

### 3. Sistema Multilenguaje Dinámico (`LanguageManager`)
* Selector de idioma integrado directamente en `Ajustes > General` (`TVTest.ini`).
* Soporte nativo para 4 idiomas con diccionarios extensivos (`Languages/*.ini`):
  * **Español (`es-ES`)**
  * **Portugués (`pt-BR`)**
  * **Inglés (`en-US`)**
  * **Japonés (`ja-JP`)**
* Traducción dinámica en tiempo real de todos los componentes de la interfaz:
  * Menús contextuales con atajos de teclado preservados (`Texto\tAtajo`).
  * Diálogos Win32, pestañas (`SysTabControl32`) y encabezados de listas (`SysListView32`).
  * Comandos globales, asignación de controles/ratón y descripciones emergentes (*tooltips*).
  * Pestañas y encabezados de paneles laterales e inferiores (`Info`, `Guía`, `Canales`, `Control`, `Subtít.`).
  * Barra de estado en vivo y diálogo de configuración de ítems.
  * Mensajes en pantalla (*OSD*), notificaciones y barra de título de la guía EPG.

---

## Sintonizadores y BonDrivers (Controladores)

Para que **TVTest** pueda comunicarse con tu sintonizador USB o tarjeta PCIe, se requiere una librería **BonDriver** (un archivo `.dll` junto con su correspondiente `.ini`) colocado en la misma carpeta raíz donde se encuentra `TVTest.exe`.

### Sintonizadores probados y compatibles:
* **TBS 5530** (USB DVB-S2X/S2/T2/T/C2/C/ISDB-T):
  * Compatible tanto con **`BonDriver_PX_S1UD`** como con **`BonDriver_BDA`**.
* **PLEX PX-S1UD** (v1 / v2) y dongles USB basados en chips Siano / IT9135 (como **MyGica S880 / S870**):
  * Funcionan de forma nativa con **`BonDriver_PX_S1UD`**.
* **Sintonizadores BDA Genéricos (USB / PCI / PCIe)**:
  * Compatibles mediante **`BonDriver_BDA`** (MyGica, Geniatech, TBS, AverMedia, etc.).

### Enlaces de descarga recomendados:
* **[BonDriver_BDA (Releases con binarios precompilados)](https://github.com/tsukumijima/BonDriver_BDA/releases)**  
  *(Código fuente original: [radi-sh/BonDriver_BDA](https://github.com/radi-sh/BonDriver_BDA))*
* **BonDriver_PX_S1UD**: Recomendado para dongles USB ISDB-T y para la **TBS 5530**.
* **[BonDriver_Pipe](https://github.com/nns779/BonDriver_Pipe)**: Para recibir flujos TS mediante tuberías de red / streaming.

### Configuración de Frecuencias ISDB-Tb (Latinoamérica)
En Latinoamérica, las transmisiones de televisión digital abierta operan principalmente en la banda **UHF (canales 14 al 51: 473.143 MHz a 695.143 MHz)** y opcionalmente en **VHF Alto (canales 7 al 13: 177.143 MHz a 213.143 MHz)**, con un ancho de canal de **6 MHz** y un desplazamiento de frecuencia de **+1/7 MHz (+143 kHz)**.

El archivo de configuración `.ini` del BonDriver debe contener la tabla de sintonización adecuada. Puedes consultar o descargar un ejemplo listo para usar en:
* [`data/BonDriver_PX_S1UD.sample.ini`](data/BonDriver_PX_S1UD.sample.ini)

Ejemplo básico de canales UHF en el archivo `.ini`:
```ini
[TuningSpace00]
TuningSpaceName="UHF"
CH000=0,473.143, ,0,UHF 14
CH001=0,479.143, ,0,UHF 15
CH002=0,485.143, ,0,UHF 16
CH003=0,491.143, ,0,UHF 17
...
CH037=0,695.143, ,0,UHF 51
```

---

## Decodificadores y Renderizadores Recomendados

Para obtener la mejor calidad de imagen, estabilidad y aceleración por hardware (GPU) en video MPEG-2, H.264/AVC y H.265/HEVC, se recomienda utilizar la siguiente combinación:

* **Filtros de Decodificación:** **[LAV Filters](https://github.com/nevcairiel/lavfilters)**
  * Paquete de filtros DirectShow de código abierto basado en FFmpeg. Ofrece decodificación rápida, compatibilidad total con aceleración por hardware (D3D11 / DXVA2 copy-back) y excelente estabilidad.
  * Descargas: [LAV Filters Releases](https://github.com/nevcairiel/lavfilters/releases)

* **Renderizador de Video:** **[MPC Video Renderer](https://github.com/Aleksoid1978/VideoRenderer)** / **[FrankyRenderer](https://github.com/mryx007/FrankyRenderer)**
  * **MPC Video Renderer**: Renderizador de video moderno basado en Direct3D 11. Proporciona bajo consumo de CPU/GPU, sincronización precisa y desentrelazado de alta fidelidad para transmisiones de TV abierta ([MPC Video Renderer Releases](https://github.com/Aleksoid1978/VideoRenderer/releases)).
  * **FrankyRenderer**: Renderizador de video DirectShow (x64) de alto rendimiento impulsado por **libplacebo** y **Direct3D 11**, con soporte nativo integrado en este fork para escalado avanzado, mapeo de tonos HDR y procesamiento de imagen ([FrankyRenderer Releases](https://github.com/mryx007/FrankyRenderer/releases)).

> **Configuración en TVTest:**  
> En **Ajustes > Video**, configure:
> * **Renderizador de video:** `MPC Video Renderer`, `FrankyRenderer` (o `EVR Custom Presenter`)
> * **Decodificador de video:** `LAV Video Decoder`

---

## Compilación

* **Entorno recomendado:** Visual Studio 2022 (v143)
* **Arquitectura:** x64 / x86
* **Solución principal:** `src/TVTest.sln`

### Dependencias
* [DirectShow BaseClasses](https://github.com/Microsoft/Windows-classic-samples/tree/master/Samples/Win7Samples/multimedia/directshow/baseclasses)
* [Fraunhofer FDK AAC](https://github.com/mstorsjo/fdk-aac)
* [FAAD2](https://github.com/knik0/faad2)
* [libmad](http://www.underbit.com/products/mad/)
* [liba52](http://liba52.sourceforge.net/)
* [libjpeg](http://www.ijg.org/)
* [libpng](http://libpng.org/)
* [zlib](http://zlib.net/)

---

## Nota Original del Proyecto / Original Notice

> デジタル放送汎用視聴プログラム実装研究資料(略称 TVTest)は、パーソナルコンピュータ上において、デジタル放送の視聴を行うプログラムの実装を研究する目的で頒布される研究資料です。  
> CAS 処理は実装されていないため、一般のテレビ放送(有料/暗号化放送)を視聴することはできません。

---

## Licencia

Este proyecto se distribuye bajo la licencia **GNU General Public License v2.0 or later (GPL-2.0-or-later)**.  
Consulte [doc/License.txt](doc/License.txt) para más detalles.
