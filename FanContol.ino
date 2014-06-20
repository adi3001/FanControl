// CiberPlant LLC
// http://www.cyberplant.info
// Sample code for FanControl v1.0

#include <OneWire.h>
#include <LiquidCrystal.h>
#include <EEPROMVar.h>
#include <EEPROMex.h>
#include  <TimerOne.h> 

LiquidCrystal lcd(9, 10, 7, 8, 6, 5);
OneWire  ds(4);  // линия 1-Wire будет на pin 4
int led = 13;

//int addressSetTemp = 0;
int addressR = 0;
int addressPower = addressR+sizeof(int);
int addressSetTemp = addressPower+sizeof(int);

int r = EEPROM.readInt(addressR);
int SetTemp = EEPROM.readInt(addressSetTemp);
int power = EEPROM.readInt(addressPower);

char * mode[2] = {"auto", "power"};

int m=0; 

byte upPin = A2; 
byte downPin = A3;

int flag = 0; 

long previousMillis = 0;
long interval = 2000;  // delay adjustments in minutes
//_____________________POWER___________________________

volatile int i=0;               // Variable to use as a counter
volatile boolean zero_cross=0;  // Boolean to store a "switch" to tell us if we have crossed zero
int AC_pin = 3;                // Output to Opto Triac
int dim = 0;                    // Dimming level (0-128)  0 = on, 128 = 0ff
                   // counting up or down, 1=up, -1=down

int freqStep = 78;    // This is the delay-per-brightness step in microseconds.

void setup(void) {
    lcd.begin(8, 2);
 pinMode(led, OUTPUT); 
   pinMode (upPin, INPUT);
   pinMode (downPin, INPUT);
     pinMode(AC_pin, OUTPUT);                          // Set the Triac pin as output
  attachInterrupt(0, zero_cross_detect, RISING);   // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);  

}
void zero_cross_detect() {    
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i=0;
  digitalWrite(AC_pin, LOW);       // turn off TRIAC (and AC)
}                                 

// Turn on the TRIAC at the appropriate time
void dim_check() {                   
  if(zero_cross == true) {              
    if(i>=dim) {                     
      digitalWrite(AC_pin, HIGH); // turn on light       
      i=0;  // reset time step counter                         
      zero_cross = false; //reset zero cross detection
    } 
    else {
      i++; // increment time step counter                     
    }                                
  }                                  
}                
void loop(void) {

 if (digitalRead(upPin)== LOW && flag==1)                           // stabilization buttons
  {
  flag=0;
  }
   if (digitalRead(downPin)== LOW && flag==1)                           // stabilization buttons
  {
  flag=0;
  }

  // Handle pressing the menu button
  if (digitalRead(upPin)== HIGH && digitalRead(downPin)== HIGH && flag==0)
  {
  r++;           // increase the variable level menu
  flag=1;
  if (r>1)       // if the level is greater than 3
  {
  r=0;           // then back to the top
  }
  EEPROM.updateInt(addressR, r);
  r = EEPROM.readInt(addressR);
}




  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;
  
  if ( !ds.search(addr)) {

    ds.reset_search();
    delay(100);
    return;
  }


  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end
  
  delay(100);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

 
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
  data[i] = ds.read();

 }
 

  // convert the data to actual temperature

 unsigned int raw = (data[1] << 8) | data[0];
  if (type_s) {
   raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // count remain gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
 } else 
  {
   byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw << 3;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw << 2; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw << 1; // 11 bit res, 375 ms
    // default is 12 bit resolution, 750 ms conversion time
  }
 
  if (r==0)
  {
     if (digitalRead(upPin)== HIGH && flag==0)
    {
      SetTemp++;           // increase the variable level menu
  flag=1;
  if (SetTemp>60)       // if the level is greater than 3
  {
  SetTemp=60;           // then back to the top
  }
  }
      if (digitalRead(downPin)== HIGH && flag==0)
    {
      SetTemp--;           // increase the variable level menu
  flag=1;
  if (SetTemp<0)       // if the level is greater than 3
  {
  SetTemp=0;           // then back to the top
  }
  }
 if (digitalRead(upPin)== LOW && SetTemp != EEPROM.readInt(addressSetTemp))                           // stabilization buttons
  {
      EEPROM.updateInt(addressSetTemp, SetTemp);

  flag=0;
  }
  lcd.clear();
 celsius = (float)raw / 16.0;
 lcd.setCursor (0,0);
  lcd.print(mode[r]);
    lcd.setCursor (5,0);
  lcd.print(SetTemp);
 lcd.setCursor (7,0);
  lcd.print("C");
  lcd.setCursor (0,1);
  lcd.print(celsius);
  lcd.setCursor (7,1);
  lcd.print("C");
  
    unsigned long currentMillis = millis();       // for reading interval pH Delay
  if (currentMillis - previousMillis> interval)
  {  
    previousMillis = currentMillis;
  if (SetTemp>celsius)               // if the automatic mode is selected and the pH dropped
                                               // Parameter below pH Low
{

  dim++;
  if (dim>115)
  {
  dim = 115;
  }
  }
  if (SetTemp<celsius)
  {
    dim--;
    if (dim<50)
    {
    dim = 50;
    }
    }
  }
  }
  
  else if (r==1)
  {
    if (digitalRead(upPin)== HIGH && flag==0)
    {
      power++;           // increase the variable level menu
  flag=1;
  if (power>100)       // if the level is greater than 3
  {
  power=100;           // then back to the top
  }
  }
      if (digitalRead(downPin)== HIGH && flag==0)
    {
      power--;           // increase the variable level menu
  flag=1;
  if (power<0)       // if the level is greater than 3
  {
  power=0;           // then back to the top
  }
  }
 if (digitalRead(upPin)== LOW && power != EEPROM.readInt(addressPower))                           // stabilization buttons
  {
      EEPROM.updateInt(addressPower, power);

  flag=0;
  }
  
  dim = map(power, 0, 100, 115, 50);
  
  lcd.clear();
 celsius = (float)raw / 16.0;
 lcd.setCursor (0,0);
  lcd.print(mode[r]);
  lcd.setCursor (5,0);
  lcd.print(power);
  if (power<100)
  {
 lcd.setCursor (7,0);
  lcd.print("%");
  }
  lcd.setCursor (0,1);
  lcd.print(celsius);
  lcd.setCursor (7,1);
  lcd.print("C");

  }

}
