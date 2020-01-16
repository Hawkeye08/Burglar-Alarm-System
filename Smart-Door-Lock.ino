// Include required libraries

#include <LiquidCrystal_I2C.h> // Library for I2C
#include <SPI.h> // Library for Serial Peripheral Interface i.e MISO and MOSI
#include <MFRC522.h> // Library for RFID Reader
#include <NewPing.h> // Library for IR Sensor

#define TRIGGER_PIN 6 //Trigger Pin for UltraSonic
#define ECHO_PIN 5 //Echo Pin for UltraSonic
#define MAX_DISTANCE 20 //Beyond this, the Ultrasonic Sensors shows 0

// Creating instances
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address/I2C address to 0x27 for a 16 chars and 2 line display
MFRC522 mfrc522(10, 9); // MFRC522 mfrc522(SS_PIN, RST_PIN)
NewPing sonar(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE);

String tagUID = "F6 28 3A F8";  // String to store UID of tag which must disable the buzzer

void setup() {
  
  // Arduino Pin configuration
  lcd.begin();   // LCD screen
  lcd.backlight(); // LCD Backlight Swtiched On
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  lcd.clear(); // Clear the LCD
  Serial.begin(115200); // Debugging for Ultrasonic
  pinMode(2,OUTPUT); // Output Pin for Ultrasonic VCC
  pinMode(4,OUTPUT); // Output Pin for Ultrasonic GND
}

void loop() {
  int i;
  digitalWrite(2,HIGH); // Setting High for VCC
  digitalWrite(4,LOW); // Setting Low for GND
  Serial.print("Ping: "); // Debugging
  Serial.print(sonar.ping_cm()); // Debugging
  Serial.println("cm"); // Debugging
  lcd.setCursor(0, 0); // Setting print to begin from 1st Row and immediately from the left side
  lcd.print(" RFID Door Lock "); // Print for LCD ROW 1
  lcd.setCursor(0, 1); // Setting print to begin from 2nd Row and immediately from the left side
  lcd.print(" Show Your Tag "); // Print for LCD ROW 2

  if (sonar.ping_cm() > 0) // Enter the Loop when the distance is less than max distance set
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" No Tag Shown ");
      lcd.setCursor(0, 1);
      lcd.print(" Alarm Triggered ");
      for(i=0;i<5;i++) // Code for setting the buzzer in beeping mode
      {
      analogWrite(A0,255); // Analog Used for setting loudness of Buzzer
      delay(200);
      analogWrite(A0,0);
      delay(200);
      }
       lcd.clear();
 
    }
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  //Reading from the card
  String tag = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    tag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tag.toUpperCase();
  
  //Checking the card
  if (tag.substring(1) == tagUID) //change here the UID of the card/cards that you want to give access to
  {
    // If UID of tag is matched.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Correct Tag");
    lcd.setCursor(0, 1);
    lcd.print("Access Granted");
    digitalWrite(13,HIGH); // Set internal LED of Arduino UNO to light up
    delay(10000);
    digitalWrite(13,LOW);
    lcd.clear();
  }
  else
  {
    // If UID of tag is not matched.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong Tag Shown");
    lcd.setCursor(0, 1);
    lcd.print("Access Denied");
    analogWrite(A0,255);
    delay(3000);
    analogWrite(A0,0);
    lcd.clear();
  }
}
