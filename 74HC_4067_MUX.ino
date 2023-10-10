#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27,20,4);
//int sensorPin = A0;
//int sensorValue = 0;


//Mux control pins
int s0 = 8;
int s1 = 9;
int s2 = 10;
int s3 = 11;

//Mux in "SIG" pin
int SIG_pin = 0;


void setup(){
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);

  Serial.begin(9600);

  lcd.init(); //Khởi tạo màn hình LCD
  lcd.backlight(); //Bật đèn màn hình lCD
}


void loop(){

  //Loop through and read all 16 values
  //Reports back Value at channel 6 is: 346
  // for(int i = 0; i < 16; i ++){
  //   Serial.print("Value at channel ");
  //   Serial.print(i);
  //   Serial.print("is : ");
  //   Serial.println(readMux(i));
  //   delay(1000);
  // }
  lcd.setCursor(0, 0); 
  lcd.print(readMux(0)); 
  
  lcd.setCursor(5, 0); 
  lcd.print(readMux(1));

  lcd.setCursor(10, 0); 
  lcd.print(readMux(2));

  lcd.setCursor(15, 0); 
  lcd.print(readMux(3));
//----------------------------
  lcd.setCursor(0, 1);
  lcd.print(readMux(12));

  lcd.setCursor(5, 1); 
  lcd.print(readMux(13));

  lcd.setCursor(10, 1); 
  lcd.print(readMux(14));

  lcd.setCursor(15, 1); 
  lcd.print(readMux(15));

}


int readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int val = analogRead(SIG_pin);

  //return the value
  return val;
}