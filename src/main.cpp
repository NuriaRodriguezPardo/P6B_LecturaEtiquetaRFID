#include <Arduino.h>

#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 9 //Pin 9 para el reset del RC522
#define SS_PIN 10 //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
void setup() {
  Serial.begin(115200); //Iniciamos la comunicación serial
  SPI.begin(36, 37, 35); //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Lectura del UID");
}
void loop() {
  // Revisamos si hay nuevas tarjetas presentes
  if ( mfrc522.PICC_IsNewCardPresent()) 
  { 
    //Seleccionamos una tarjeta
    if ( mfrc522.PICC_ReadCardSerial()) 
    {
      // Enviamos serialemente su UID
      Serial.print("Card UID:");
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0"
        : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX); 
      } 
      Serial.println();
      // Terminamos la lectura de la tarjeta actual
      mfrc522.PICC_HaltA(); 
    } 
  } 
}
/*
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x1 (POWERON),boot:0xb (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce3808,len:0x44c
load:0x403c9700,len:0xbd8
load:0x403cc700,len:0x2a80
entry 0x403c98d0

TERMINAL: 
Lectura del UID
Card UID: 08 E4 3E AD
Card UID: 08 DB 76 CB
*/