#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include"stdio.h"
int cambien = 7;
int gtcambien;
int relay=8;
#include "DHT.h"      //gọi thư viện DHT11
const int DHTPIN = 2;       //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;  //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
DHT dht(DHTPIN, DHTTYPE);
///////////////////////////////////////
void setup() {
  Serial.begin(9600);
  dht.begin();         // Khởi động cảm biến
  lcd.init();
  lcd.backlight();
  pinMode(cambien, INPUT);
  
  pinMode(relay,OUTPUT);

  
}
////////////////////////////////////////
void loop() {
  float humidity = dht.readHumidity();    //Đọc độ ẩm
  float temperature = dht.readTemperature(); //Đọc nhiệt độ
 
  lcd.setCursor(1, 0);
  lcd.print("Nhiet do:");
  lcd.setCursor(10, 0);
  lcd.print(temperature);
  lcd.setCursor(12, 0);
  lcd.print("(C)");
  lcd.setCursor(1, 1);
  lcd.print("Do am:");
  lcd.setCursor(8, 1);
  lcd.print(humidity);
  lcd.setCursor(10, 1);
  lcd.print("(%)");
  lcd.setCursor(13, 1);
   gtcambien = digitalRead(cambien);

  Serial.print("Giá trị cảm biến: "); 
  Serial.println(gtcambien);

  if(gtcambien == 0)
  {
    Serial.println("................Có vật cản");
    //status_lights=true;
    digitalWrite(relay,HIGH);
    
    }
  else
  {
    Serial.println("................Không có vật cản");
    //status_lights=true;
    digitalWrite(relay,LOW);
  }
  
  delay(500);
}
