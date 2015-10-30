

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN		9		// 
#define SS_PIN		10		//

#define LED             5

#define MOTER_LEFT_A    7
#define MOTER_LEFT_B    6


MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance

int uid[100]; 

void rotateMoterCCW(int moterA, int moterB) ;
void rotateMoterCW(int moterA, int moterB) ;
void stopMoter(int moterA, int moterB) ;


void setup() {
  Serial.begin(57600);		// Initialize serial communications with the PC
  while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();			// Init SPI bus
  mfrc522.PCD_Init();		// Init MFRC522
  Serial.println(F("Scan PICC to see UID, type, and data blocks..."));
  
  pinMode(5,OUTPUT); // pin out for light blinking
  
  pinMode(MOTER_LEFT_A, OUTPUT);
  pinMode(MOTER_LEFT_B, OUTPUT);
}

void loop() {
  int flag = 1;
  int i = 0;
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    
    stopMoter(MOTER_LEFT_A, MOTER_LEFT_B);

    
    digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(500);
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)


    return;
  }
  
  Serial.print(F("Card UID:"));
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  } Serial.println();
  
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid[i] = mfrc522.uid.uidByte[i];
    Serial.println(uid[i]);
  }
  Serial.println();

  if (uid[0] == 4 &&
      uid[1] == 123 && 
      uid[2] == 221 &&
      uid[3] == 162&&
      uid[4] == 158 &&
      uid[5] == 51 &&
      uid[6] == 128 ) {
      Serial.println("O.K.");
      rotateMoterCCW(MOTER_LEFT_A, MOTER_LEFT_B);
      delay(1000);

    }
  
}

  // output moterA = 1, moterB = 0
void rotateMoterCCW(int moterA, int moterB) {
  digitalWrite(moterA, 1);
  digitalWrite(moterB, 0);
}

// output moterA = 0, moterB = 1
void rotateMoterCW(int moterA, int moterB) {
  digitalWrite(moterA, 0);
  digitalWrite(moterB, 1);
}

// output moterA == moterB
void stopMoter(int moterA, int moterB) {
  digitalWrite(moterA, 0);
  digitalWrite(moterB, 0);
}

  
  
  
