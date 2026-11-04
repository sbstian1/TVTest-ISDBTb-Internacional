# TVTest - ISDB-Tb Internacional

Fork de **TVTest** y **LibISDB** adaptado para la norma de televisión digital terrestre **ISDB-Tb (SBTVD)** utilizada en Latinoamérica (Argentina, Brasil, Chile, Colombia, Costa Rica, Ecuador, Paraguay, Perú, Uruguay, etc.).
<img width="2886" height="1728" alt="image" src="https://github.com/user-attachments/assets/40dd585d-d163-4336-9506-13ddc99f6718" />


---

## Características y Modificaciones Implementadas

### 1. Soporte Nativo de Audio AAC-LATM / LOAS
* **Decodificación de flujo `STREAM_TYPE_MPEG4_AUDIO` (`0x11`)**: Mapeo directo y enrutamiento a través de **Fraunhofer FDK-AAC** (`TT_MP4_LOAS`).
* Compatibilidad total con las transmisiones de audio AAC encapsulado en LATM comunes en los estándares SBTVD/ISDB-Tb.

### 2. Numeración y Canales Virtuales ISDB-Tb
* En el escaneo de canales (`ChannelScan`), formateo automático de la numeración lógica de canal mayor y menor (ejemplo: `7.1 Principal`, `7.2 Secundario`, `7.31 One-Seg`) a partir del transpondedor BonDriver y los servicios detectados.
* Identificación automática de servicios 1Seg (subcanal `.31`).

### 3. Interfaz en Español
* Menús principales, paneles de opciones, diálogos de configuración, comandos de teclado y avisos traducidos al español.

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
