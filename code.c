#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_XL 5
#define LED_C 4
#define BUZZER 2
#define SERVO 3 
MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myServo;
 
void setup() 
{
  SPI.begin();
  mfrc522.PCD_Init();
  myServo.attach(SERVO);
  myServo.write(0);
  pinMode(LED_XL, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "53 9B 33 31")
  {
    delay(500);
    digitalWrite(LED_XL, HIGH);
    delay(1500);
    digitalWrite(LED_XL, LOW);
    myServo.write(90);
    delay(2000); // Sau 2s tự động đóng cửa
    myServo.write(0);
  }else{
    delay(500);
    digitalWrite(LED_C, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(1500);
    digitalWrite(LED_C, LOW);
    digitalWrite(BUZZER, LOW);
  }
}
