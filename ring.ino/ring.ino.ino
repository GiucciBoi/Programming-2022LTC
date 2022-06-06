// SD Card Module
#include <SPI.h>
#include <SD.h>
#include "Adafruit_NECremote.h"
#define IRpin         4
Adafruit_NECremote remote(IRpin);

// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.
void setup() {
  Serial.begin(9600);           // Open serial communications and wait for port to open:
  while (!Serial) {
    delay(1);                   // wait for serial port to connect. Needed for native USB port only
  }
//
//  // SD Card initialisation
//  Serial.print("Initializing SD card...");
//  if (!SD.begin(10)) {
//    Serial.println("initialization failed!");
//    while (1);
//  }
//  // Real Time Clock (RTC)
//  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
//  Serial.println("initialization done.");
//  logEvent("System Initialisation...");
}

void logEvent(String dataToLog) {
  /*
     Log entries to a file on an SD card.
  */
  // Get the updated/current time
  DateTime rightNow = rtc.now();

  // Open the log file
  File logFile = SD.open("events.csv", FILE_WRITE);
  if (!logFile) {
    Serial.print("Couldn't create log file");
    abort();
  }

  // Log the event with the date, time and data
  logFile.print(rightNow.year(), DEC);
  logFile.print(",");
  logFile.print(rightNow.month(), DEC);
  logFile.print(",");
  logFile.print(rightNow.day(), DEC);
  logFile.print(",");
  logFile.print(rightNow.hour(), DEC);
  logFile.print(",");
  logFile.print(rightNow.minute(), DEC);
  logFile.print(",");
  logFile.print(rightNow.second(), DEC);
  logFile.print(",");
  logFile.print(dataToLog);

  // End the line with a return character.
  logFile.println();
  logFile.close();
  Serial.print("Event Logged: ");
  Serial.print(rightNow.year(), DEC);
  Serial.print(",");
  Serial.print(rightNow.month(), DEC);
  Serial.print(",");
  Serial.print(rightNow.day(), DEC);
  Serial.print(",");
  Serial.print(rightNow.hour(), DEC);
  Serial.print(",");
  Serial.print(rightNow.minute(), DEC);
  Serial.print(",");
  Serial.print(rightNow.second(), DEC);
  Serial.print(",");
  Serial.println(dataToLog);
}
void loop() {
  // put your main code here, to run repeatedly:
  remoteDecode();
}

void remoteDecode() {
  int c = remote.listen(5);  // seconds to wait before timing out!
  // Or you can wait 'forever' for a valid code
  //int c = remote.listen();  // Without a #, it means wait forever
  if (c >= 0) {
    switch (c) {

        Serial.println("Code is :" + c);
      // Top keys
      case 70:
        Serial.println("UP");
        break;
      case 21:
        Serial.println("DOWN");
        break;
      case 68:
        Serial.println("LEFT");

        break;
      case 67:
        Serial.println("RIGHT");
        break;
      case 64:
        Serial.println("OK");
        break;
      // Numbers
      case 22:
        Serial.println("1");
        break;
      case 25:
        Serial.println("2");
        break;
      case 13:
        Serial.println("3");
        break;
      case 12:
        Serial.println("4");
        break;
      case 24:
        Serial.println("5");
        break;
      case 94:
        Serial.println("6");
        break;
      case 8:
        Serial.println("7");
        break;
      case 28:
        Serial.println("8");
        break;
      case 90:
        Serial.println("9");
        break;
      case 82:
        Serial.println("0");
        break;

      // # and *
      case 66:
        Serial.println("*");
        break;
      case 74:
        Serial.println("#");
        break;


      // otherwise...

      default:
        Serial.println("Code is :" + c);
        break;
    }

  }
}
