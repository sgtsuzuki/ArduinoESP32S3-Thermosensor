// XIAO ESP32S3とMAX31855で温度計測する
// 計測した温度はXBee3を使って無線伝送する
// MAX31855 > SPI > ESP32S3 > UART > XBee3
// MAX31855( Adafruit 製モジュール)
// 
// MAX31855 CLK  >  ESP32S3-D5  
// MAX31855 CS   >  ESP32S3-D4
// MAX31855 DO   >  ESP32S3-D3
// MAX31855 GND  <  ESP32S3-GND     >  XBee3-GND(10)
// MAX31855 3Vo
// MAX31855 Vin  <  ESP32S3-3V3     >  XBee3-VCC(1)
//                  ESP32S3-D6(TX)  >  XBee3-DIN(3)
//                  ESP32S3-D7(RX)  >  XBee3-DOUT(2)

#include <Adafruit_MAX31855.h>
#include <SPI.h>

// S3ボードではGPIO1がD1なのか？そうみたい 3，4，5で通信できた
#define MAXDO     3 // 10
#define MAXCS     4 // 0
#define MAXCLK    5 // 8
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

// #define MAXCS     1
// Adafruit_MAX31855 thermocouple(MAXCS);

// XBee用のシリアルポート
HardwareSerial XBeeSerial(0);

// カウント
volatile unsigned long count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("MAX31855 test");

  XBeeSerial.begin(57600, SERIAL_8N1, -1, -1);
  XBeeSerial.println("Start Serial with MAX31855");

  pinMode(LED_BUILTIN, OUTPUT);
  bool ret = thermocouple.begin();
  delay(500);
  if ( !ret ){
    Serial.println("MAX31855 Fail");
    while(true){
      delay(500);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);

  // 熱電対摂氏温度を読み取る
  double c = thermocouple.readCelsius();
  if (isnan(c)) {
    Serial.println("Something wrong with thermocouple!");
  } else {
    XBeeSerial.print(count);
    XBeeSerial.print(",");
    XBeeSerial.println(c);
  }

  count++;
}
