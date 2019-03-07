#include <LiquidCrystal.h> //Library for LCD Display
#include <Servo.h> //Library for controlling Servo

// Declare servo, its initial angle, and its connecting pin
int servoPin = 9;
Servo servo;
int angle = 0;

// Define const joystick pin and its according directional pins
const int JOYSTICK_PIN = 13;
const int X_PIN = 0; 
const int Y_PIN = 1; 

int counter = 0; //total number of inputs inputted
int numOfAttempts = 0; //total number of attempts
char *input[4]; 
char *pass[4] = {"Left", "Right", "Up", "Down"}; //password for lock/unlock

// Declare lcd with according pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  servo.attach(servoPin); 
  lcd.begin(16, 2);
  lcd.print("Locked");
  pinMode(JOYSTICK_PIN, INPUT);
  pinMode(8, OUTPUT);
  digitalWrite(JOYSTICK_PIN, HIGH);
  Serial.begin(9600);
}

void loop() {
  // numOfAttempts number of attempts
  if (numOfAttempts < 3) {

    // Set a counter to input passwords 
    if (counter < 4) {
      /* ===============
       * X-Pin defined as moving joystick left or right
       * Y-Pin defined as moving joystick up or down
         =============== */

      // If joystick pushed down
      if (analogRead(X_PIN) > 1000) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Down");
        Serial.print("Down");
        lcd.setCursor(0, 1);
        lcd.print(counter + 1);
        input[counter] = "Down";
        counter++;
      }

      // If joystick pushed up
      else if (analogRead(X_PIN) < 60) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Up");
        Serial.print("Up");
        lcd.setCursor(0, 1);
        lcd.print(counter + 1);
        input[counter] = "Up";
        counter++;
      }

      // If joystick pushed left
      else if (analogRead(Y_PIN) > 1000) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Left");
        Serial.print("Left");
        lcd.setCursor(0, 1);
        lcd.print(counter + 1);
        input[counter] = "Left";
        counter++;
      }

      // If joystick pushed right
      else if (analogRead(Y_PIN) < 60) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Right");
        Serial.print("Right");
        lcd.setCursor(0, 1);
        lcd.print(counter + 1);
        input[counter] = "Right";
        counter++;
      }
      delay(200);
    }

    // If all inputs inputted, check whether the password 
    else {
      if ((input[0] == pass[0]) && (input[1] == pass[1]) && (input[2] == pass[2]) && (input[3] == pass[3])) {
        lcd.clear();
        numOfAttempts = 0;
        counter = 0;
        lcd.print("Welcome home!");

        // "Unlock" servo by turning angle to 90
        if (angle == 0) {
          for (angle = 0; angle < 90; angle++)
          {
            servo.write(angle);
            delay(15);
          }
        }

        // "Lock" servo  by turning angle back to 0
        else {
          lcd.print("You are locked!");
          for (angle = 90; angle > 0; angle--)
          {
            servo.write(angle);
            delay(15);
          }
        }
      }

      // If wrong attempt
      else {
        lcd.clear();
        numOfAttempts++;
        counter -= 4;
        lcd.print("Wrong Attempt:");
        lcd.setCursor(0, 1);
        lcd.print(numOfAttempts);
      }
    }
  }

  // After three incorrect attempts, it locks permanently
  else {
    lcd.clear();
    lcd.print("AHH BAD MAN");
    lcd.setCursor(0, 1);
    lcd.print("INTRUDER!!!!!!!");
    delay(500);
    if (angle == 90) {
      for (angle = 90; angle > 0; angle--)
      {
        servo.write(angle);
        delay(15);
      }
    }
  }
}
 
