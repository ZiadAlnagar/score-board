// Importing external libraries
#include <LiquidCrystal.h>

//Defining global variables
//The Step Value
int stpValue = 0;
//The Number which we Increase/Decrease
int counter = 0;
// Condition to override default arduino loop
int condition = 1;
//Variables which store Numbers in 2 digits format
char digitStpValue[5];
char digitCounter[5];

//LCD pins to Arduino
const int pin_RS = 8;
const int pin_EN = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
const int pin_BL = 10;
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

//Functions Section
//Display the Step number in 2 digits format
void display2digitsSTP() {
  //Store the Step value in integer array
  sprintf(digitStpValue, "%02d", stpValue);
  lcd.print (digitStpValue);
}
//Display the Posotive Counter Number in 2 digits
void display2digitsCounter() {
  sprintf(digitCounter, "%02d", counter);
  lcd.print (digitCounter);
}

//Display the Negative Counter Number in 2 digits
void display2digitsNegativeCounter() {
  //The Negative sign takes 1 more place (%o3d) instead of (%02d)
  sprintf(digitCounter, "%03d", counter);
  lcd.print (digitCounter);
}

//Clears specific places in the LCD
void clearLCD() {
  for (int i = 8; i < 15; ++i)
  {
    lcd.setCursor(i, 1);
    lcd.print(" ");
    lcd.setCursor(8, 1);
  }
}

//User choose and Store the Step Value
void selectStep() {
  int x;
  while (true) {
  	//Delay helps button press to be more Accurate
    delay(150);
    x = analogRead(0);
    lcd.setCursor(8, 1);
    //Right
    if (x < 60) {
      lcd.print ("Right ");
    }

    // Up
    //Increase Step Value by One and Display it
    else if (x < 200) {
      clearLCD();
      stpValue += 1;
      display2digitsSTP();
    }

    //Down
    //Decrease Step Value by One and Display it
    else if (x < 400) {
      clearLCD();
      //User can't pick Step Value below "0" because it must be a Positive Number
      if ((stpValue -= 1) < 0) {
        stpValue = 0;
      }
      display2digitsSTP();
    }

    // Left
    else if (x < 600) {
      lcd.print ("Left  ");
    }

    //Select
    else if (x < 800) {
	  //If the user wants to select a Step Value of Zero print "Invalid"
      if (stpValue == 0)
      {
        lcd.print("Invalid");
      } else {
        condition = 0;
        break;
      }
    }
  }
}

void setup() {
  //Defines the LCD Size
  lcd.begin(16, 2);
  //Code i.e. to Set Cursor on the LCD screen
  //lcd.setCursor(x, y);
  lcd.setCursor(0, 0);
  lcd.print("Enter Step Numb");
  lcd.setCursor(0, 1);
  lcd.print("Up/Down:");
  lcd.setCursor(8, 1);
  display2digitsSTP();
}

void loop() {
  //Checks if the user selected a Step Number yet
  if (condition == 1)
  {
  	//If No Redirect him to Select Step function
    selectStep();
  } else {
    //if the usr selected the Step Number Direct him to the Scoreboard
    lcd.setCursor(0, 0);
    lcd.print("Step up/down: ");
    display2digitsSTP();
    lcd.setCursor(0, 1);
    lcd.print("Number: ");
    lcd.setCursor(9, 1);
    clearLCD();
    if(counter<0){
    display2digitsNegativeCounter();}
    else display2digitsCounter();

    delay(140);
    int button = analogRead(0);
    //Step Up
    if (button < 200) {
      counter += stpValue;
      //Step Down
    } else if (button < 400) {
      counter -= stpValue;
    }

  }

}
