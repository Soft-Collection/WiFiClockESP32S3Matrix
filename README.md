[![WiFi Clock ESP32-S3 Matrix](http://img.youtube.com/vi/gyAnZwDX77I/0.jpg)](https://youtu.be/gyAnZwDX77I "WiFi Clock ESP32-S3 Matrix")

# WiFi Clock ESP32-S3 Matrix
Small WiFi Clock based on ESP32-S3 Matrix board.
Shows Time, Date, Local Weather and News.

## Parts
| Qty | Product | Description               |
| --- | ---- |---------------------------|
|1 | [ESP32-S3 Matrix](https://www.aliexpress.com/item/1005006997616303.html?spm=a2g0o.best.moretolove.18.23a12c25H9U6di&pdp_npi=4%40dis%21ILS%21%E2%82%AA45.24%21%E2%82%AA41.81%21%21%21%21%21%40213ba0c517360067943534845e2d02%2112000038992334785%21btf%21%21%21&_gl=1*19va6ew*_gcl_aw*R0NMLjE3MzU5OTQxODMuQ2p3S0NBaUExZU83QmhBVEVpd0FtMEVlLUdtMFl5U1o0Q1RiV2pZVDFmTGQ5cDllZXktc1ZWaFRMMnJlRHRMam9kaXdyUEY4TWxZN1Rob0NxSHNRQXZEX0J3RQ..*_gcl_dc*R0NMLjE3MzU5OTQxODMuQ2p3S0NBaUExZU83QmhBVEVpd0FtMEVlLUdtMFl5U1o0Q1RiV2pZVDFmTGQ5cDllZXktc1ZWaFRMMnJlRHRMam9kaXdyUEY4TWxZN1Rob0NxSHNRQXZEX0J3RQ..*_gcl_au*MTUxMjMzMjUyNC4xNzMwNTUxNTU3*_ga*MTY3ODkxNjExNC4xNzEwMDEwMzU5*_ga_VED1YSGNC7*MTczNjAwNjc5NC4xMDguMC4xNzM2MDA2Nzk0LjYwLjAuMA..) | Main board                |

## Notes
You can run commands on the device using the Arduino IDE **Serial Monitor**.
1. Use **help** to get description of all commands.
2. Use **get** to get all data in JSON format.
3. Enter the edited JSON string you have got using **get** command.
4. See your [Time Zone](https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h)
5. Validate your [JSON String](https://jsonlint.com)
6. If you want to see News, you must get Newsapi.org [API Key](https://newsapi.org)
