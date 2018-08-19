#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

 
float GetDistance()
{  float duration, distanceCm;
   
  digitalWrite(8, LOW);
  delayMicroseconds(70);
  digitalWrite(8, HIGH);
  delayMicroseconds(70);
  digitalWrite(8, LOW);
  
  duration = pulseIn(7, HIGH, 5000);   //5000 microseconds
 
  // convert to distance
  distanceCm = duration / 30 / 2;
  return distanceCm;
}

float AveDistance()
{
  float tong = 0;
  for (int i = 1;i<=8;i=i+1) {
        float distance = GetDistance();
        tong = tong + distance;
        delay(400);
      }
  float trungbinh = tong/8;
  if (trungbinh>10) trungbinh = trungbinh+1;
  if (trungbinh>20) trungbinh = trungbinh+1;
  if (trungbinh>45) trungbinh = trungbinh+1;
  return trungbinh;
 }
 
void setup() { 
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event 
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(7, INPUT);
  lcd.begin(8, 2);
  }

byte cao1 = 0;

void loop() {
  }

byte receiveEvent() {
  
  long x = Wire.read();    // receive byte as an integer
  long y = Wire.read();    // receive byte as an integer
  
  float cao = GetDistance();  
  delay(50);
  cao1 = 182 - cao;
  //int cao1 = cao;
  delay(500);
  float ketqua = cao1*x*y*0.385*0.000985;  
  long ketqua1 = ketqua;
  //ketqua = (int) ketqua;
    lcd.setCursor(0, 0);
    lcd.print("Cao: ");         // print the character
    lcd.print(cao1);
    lcd.print(" cm"); 
    lcd.setCursor(0, 1);
    //lcd.clear(); 
    lcd.print("Nang ");         // print the character
    lcd.print(ketqua); 
    lcd.print(" kg"); 
    delay(4000);
}
