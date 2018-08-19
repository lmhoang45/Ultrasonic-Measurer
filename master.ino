#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


float GetDistance()
{
  float duration, distanceCm;
   
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

int AveDistance()
{
  float tong = 0;
  for (int i = 1;i<=10;i=i+1) {
        float distance = GetDistance();
        delay(200);
        tong = tong + distance;
        delay(20);
      }
  float trungbinh = tong*0.1; trungbinh = (int) trungbinh;
  if (trungbinh>20) trungbinh = trungbinh+1;
  if (trungbinh>24) trungbinh = trungbinh+1;
  if (trungbinh>46) trungbinh = trungbinh+1;
  
  return trungbinh;
 }


void setup() {
  Wire.begin();                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  pinMode(8, OUTPUT);
  pinMode(7, INPUT);
  lcd.begin(16, 2);
}

int receiveEvent() {
  
  int x = Wire.read();    // receive byte as an integer
  return x;
}

void loop() {

  float beday = 0;
  float bengang = 0;
  for (int j = 1; j<=5; j++)
  {
    float day = 0;
    delay(80);
  day = GetDistance();
  delay(20);
  day = 57 - day;
  delay(20);
  
  if (day >= 55)
  {
    lcd.print("Sai sot!!");
    delay(1000);
    day = 0;
    lcd.clear();
    j = j-1;
  }
  else if (day <= 15)
  {
    lcd.print("Sai sot!!");
    delay(1000);
    day = 0;
    lcd.clear();
    j = j-1;
  }
  else
  {   
    lcd.print("Be day: ");
    lcd.print(day);
    delay(1000);
    lcd.clear(); 
  }
  delay(100);
  beday = beday + day;
    }
  beday = beday/5; 
  long beday1 = beday;
  
  lcd.print("Doi tu the!");
  delay(5000);
  lcd.clear();
  
  for (int k = 1; k<=5; k++)
  {
  float ngang = 0;
  delay(80);
  ngang = GetDistance();
  ngang = 57 - ngang;
  if (ngang >= 55)
  {
    lcd.print("Sai sot!!");
    delay(1000);
    ngang = 0;
    lcd.clear();
    k = k-1;
  }
  else if (ngang <= 15)
  {
    lcd.print("Sai sot!!");
    delay(1000);
    ngang = 0;
    lcd.clear();
    k = k-1;
  }
  else
  {   
    lcd.print("Ngang: ");
    lcd.print(ngang);
    delay(2000);
    lcd.clear();
  }
  delay(500);
  bengang = bengang + ngang;
  }
  bengang = bengang/5; 
  long bengang1 = bengang; 
  lcd.print("DT: ");
  lcd.print(beday);
  lcd.print("x");
  lcd.print(bengang);
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(beday1);              // sends one byte
  Wire.write(bengang1);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(4000);
  lcd.clear();
}







