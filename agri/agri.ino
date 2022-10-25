
#include <SoftwareSerial.h>
#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial ph(5,6);
DHT dht;



String pH;
long lastMsg = 0;
char msg[50];
int value = 0;
String message="";
char val[50];
String top;
  char a[20];
  char c[20];
  char b[20];
  

String getStringPartByNr(String data, char separator, int index)//PH:38.43,w:0,L:344,T:33
{
  // spliting a string and return the part nr index
  // split by separator

  int stringData = 0;        //variable to count data part nr
  String dataPart = "";      //variable to hole the return text

  for (int i = 0; i < data.length(); i++) { //Walk through the text one letter at a time

    if (data[i] == separator) {
      //Count the number of times separator character appears in the text
      stringData++;

    } else if (stringData == index) {
      //get the text when separator is the rignt one
      dataPart.concat(data[i]);

    } else if (stringData > index) {
      //return text and stop if the next separator appears - to save CPU-time
      return dataPart;
      break;

    }

  }
  //return text if this is the last part
  return dataPart;
}

void setup() {
  Serial.begin(9600);
  ph.begin(9600);
  dht.setup(8);
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();

}

void loop() {//while(1)
String t;
  if (ph.available()) {
    String rcv = ph.readString();
    //    Serial.println(rcv);
    String p = getStringPartByNr(rcv, ',', 0);
    pH = getStringPartByNr(p, ':', 1);
    Serial.print("pH: ");
    Serial.println(pH);
  }
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  //
  //  Serial.print(dht.getStatusString());
  //  Serial.print("\t");
  if (isnan(humidity) || isnan(temperature)) {
    Serial.print(" ");

  }
  else {
    Serial.print("Humidity");
    Serial.println(humidity, 1);
    t="Temperature: " + String(temperature);
  }
  int moisture = analogRead(A1);
//  Serial.println("moisture: " + String(moisture));
  String m = "moisture: " + String(moisture);
  String p = "PH: " + String(pH);
  
Serial.println(m);
Serial.println(p);
Serial.println(t);
delay(1000); 
lcd.clear();
lcd.print(m);
delay(500);
lcd.clear();
lcd.print(p);
delay(500);
lcd.clear();
lcd.print(t);
delay(500);
}
