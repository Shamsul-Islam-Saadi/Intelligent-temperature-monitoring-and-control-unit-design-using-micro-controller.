#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*I2C LCD Address = 0x3F*/
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7 , 3, POSITIVE);

/*GreenLED - AC connection, RedLED - Heater connection*/
/*designate GREENLED pin(D2) and RedLED pin(D8)*/
int GreenLED = 2;
int RedLED = 8;

/*designate pin(A0) for sensor and declare variable for temperature sensor*/
float cTemp;
int sensor = 0;
float sensorVcc = 5.0; //5v to sensor Vcc

/*designate potentiometer pin(A2) and declare variable for POT value*/
float refTemp;
int POT = 2; 

void setup() {
  //Designate pin modes for Digital pins
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  
  //prep lcd for output  
  lcd.begin(16,2);
  lcd.clear();
}

void loop() {
  delay(500); //add delay for analog read
  refTemp = analogRead(POT); //read value from Analog 1 pin - pot  
  refTemp = analogRead(POT); // take second reading for better accuracy
  
  delay(500); //add delay for analog read  
  cTemp = analogRead(sensor); // read value from Analog 0 pin - temp sensor  
  cTemp = analogRead(sensor); // take second reading for better accuracy

  /* converts values to 100 degree scale, roughly from -50 to + 50*/  
  refTemp = ((refTemp /1024)*100)-50; 
   
  /*volts to millieVolts then to proper celcius division
   * calculate current temperature
   */
  float convFactor = ((sensorVcc*1000)/1024)/10; 
  cTemp = cTemp * convFactor;

  /*produce output on screen*/
  lcd.clear(); //clear display
  /*for cTemp - sensor*/
  lcd.setCursor(0,0); //move to top left
  lcd.print("Temp: "); //temperature
  lcd.print(cTemp, 1); //round off to 1 decimal place
  lcd.print(" ");
  lcd.print((char)223); //degree sign
  lcd.print("C");
    
  /*for refTemp - pot*/
  lcd.setCursor(0,1); //move to top left
  lcd.print("Ref: "); //reference temperature
  lcd.print(refTemp, 0); //round off to integer only
  lcd.print(" ");
  lcd.print((char)223); //degree sign
  lcd.print("C");

  if(cTemp > refTemp){
    digitalWrite(GreenLED, HIGH);   
    digitalWrite(RedLED, LOW);   
  }else{
    digitalWrite(GreenLED, LOW);   
    digitalWrite(RedLED, HIGH);   
  }    
}
