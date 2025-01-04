[![WiFi Clock ESP32-S3 Matrix](http://img.youtube.com/vi/gyAnZwDX77I/0.jpg)](https://youtu.be/gyAnZwDX77I "WiFi Clock ESP32-S3 Matrix")

# WiFi Clock ESP32-S3 Matrix
Small WiFi Clock based on ESP32-S3 Matrix board.
Shows Time, Date, Local Weather and News.

## Parts
| Qty | Product | Description               |
| --- | ---- |---------------------------|
|1 | [ESP32-S3 Matrix](https://www.aliexpress.com/item/1005006997616303.html?spm=a2g0o.best.moretolove.18.23a12c25H9U6di&pdp_npi=4%40dis%21ILS%21%E2%82%AA45.24%21%E2%82%AA41.81%21%21%21%21%21%40213ba0c517360067943534845e2d02%2112000038992334785%21btf%21%21%21&_gl=1*19va6ew*_gcl_aw*R0NMLjE3MzU5OTQxODMuQ2p3S0NBaUExZU83QmhBVEVpd0FtMEVlLUdtMFl5U1o0Q1RiV2pZVDFmTGQ5cDllZXktc1ZWaFRMMnJlRHRMam9kaXdyUEY4TWxZN1Rob0NxSHNRQXZEX0J3RQ..*_gcl_dc*R0NMLjE3MzU5OTQxODMuQ2p3S0NBaUExZU83QmhBVEVpd0FtMEVlLUdtMFl5U1o0Q1RiV2pZVDFmTGQ5cDllZXktc1ZWaFRMMnJlRHRMam9kaXdyUEY4TWxZN1Rob0NxSHNRQXZEX0J3RQ..*_gcl_au*MTUxMjMzMjUyNC4xNzMwNTUxNTU3*_ga*MTY3ODkxNjExNC4xNzEwMDEwMzU5*_ga_VED1YSGNC7*MTczNjAwNjc5NC4xMDguMC4xNzM2MDA2Nzk0LjYwLjAuMA..) | Main board                |

## Notes
[TFT_eSPI by Bodmer](https://github.com/Bodmer/TFT_eSPI) must be installed.
TFT_eSPI config:
1. In User_Setup_Select.h file, select:
```
#include <User_Setups/Setup24_ST7789.h>
```
2. In User_Setups/Setup24_ST7789.h file, must be:
```
#define TFT_CS   -1      // Define as not used
#define TFT_DC   PIN_D2  // Data Command control pin
#define TFT_RST  PIN_D4  // TFT reset pin (could connect to NodeMCU RST, see next line)
```  

[TinyGPS](https://github.com/mikalhart/TinyGPS) must be installed.
* Tested with TinyGPS 13.

[EspSoftwareSerial](https://github.com/plerup/espsoftwareserial) must be installed.

## Connection Diagram
![Connection Diagram](Images/Connection%20Diagram.png)

## Assembled
![Connection Diagram](Images/Assembled_01.jpg)
![Connection Diagram](Images/Assembled_02.jpg)
![Connection Diagram](Images/Assembled_03.jpg)
