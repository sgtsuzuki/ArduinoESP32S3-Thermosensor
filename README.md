- XIAO ESP32S3とMAX31855で温度計測する
- 計測した温度はXBee3を使って無線伝送する
- MAX31855 > SPI > ESP32S3 > UART > XBee3
- MAX31855( Adafruit 製モジュール)
- 参考にしたサイト
  - https://wiki.seeedstudio.com/ja/xiao_esp32s3_getting_started/
- 必要なライブラリ
  - Adafruit-MAX31855-library（Adafruit_SPIDeviceも必要かも）

```
MAX31855 CLK  >  ESP32S3-D5  
MAX31855 CS   >  ESP32S3-D4
MAX31855 DO   >  ESP32S3-D3
MAX31855 GND  <  ESP32S3-GND     >  XBee3-GND(10)
MAX31855 3Vo
MAX31855 Vin  <  ESP32S3-3V3     >  XBee3-VCC(1)
                 ESP32S3-D6(TX)  >  XBee3-DIN(3)
                 ESP32S3-D7(RX)  >  XBee3-DOUT(2)
```
