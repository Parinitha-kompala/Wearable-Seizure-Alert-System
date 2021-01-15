#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);//RS,EN,D4,D5,D6,D7

char PRESSURESHOW[4];// initializing a character of size 4 for showing the result
char TEMPARATURESHOW[4];// initializing a character of size 4 for showing the temparature result
Adafruit_BMP085 bmp;
int buzzer = 13;
int vibr_Pin=7;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(vibr_Pin, INPUT); //set vibr_Pin input for measurment
  Serial.begin(9600); //init serial 9600
 // Serial.println("----------------------Vibration demo------------------------");
lcd.begin(16, 2);
// Print a logo message to the LCD.
lcd.print(" BMP180 Sensor");
lcd.setCursor(0, 1);
lcd.print("Temp. & Pressure");
lcd.setCursor(0, 2);
delay (3000);

lcd.clear();//clear display
Serial.begin(9600);
if (!bmp.begin())
{
Serial.println("ERROR");///if there is an error in communication
while (1) {}
}
}
void loop()
{
 long measurement =TP_init();
  delay(50);
 // Serial.print("measurment = ");
  Serial.println(measurement);
  if (measurement > 1000){
    tone (buzzer,9000);
 
lcd.print("Pressure= "); // print name
String PRESSUREVALUE = String(bmp.readPressure());
// convert the reading to a char array
PRESSUREVALUE.toCharArray(PRESSURESHOW, 4);
lcd.print(PRESSURESHOW);
lcd.print("hPa ");
lcd.setCursor(0, 1);
lcd.print("Temparature=");// print name

String TEMPARATUREVALUE = String(bmp.readTemperature());
// convert the reading to a char array
TEMPARATUREVALUE.toCharArray(TEMPARATURESHOW, 4);
lcd.print(TEMPARATURESHOW);
lcd.print("C ");
lcd.setCursor(0, 0);//set the cursor to column 0, line1
delay(500);
 }
  else{
    tone (buzzer,0); 
  }
}

long TP_init(){
  delay(10);
  long measurement=pulseIn (vibr_Pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}
