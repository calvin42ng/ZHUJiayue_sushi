#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN);

byte nuidPICC[4];

int idsum = 0;

void setup() { 
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
}
 
void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  if ( ! rfid.PICC_ReadCardSerial())
    return;

    //Serial.println(F("The NUID tag is:"));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println(idsum);
    idsum = 0;
    //Serial.println();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    idsum += buffer[i];
  }
}
