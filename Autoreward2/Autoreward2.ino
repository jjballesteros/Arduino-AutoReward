// Code for the infrared beam-triggered double reward system is shown below.

#include <Keypad.h>

//Main INPUT/OUTPUT system
const int RightpumpPin = 9;         // Riht PUMP anode connected to digital pin 10
const int LeftpumpPin = 10;         // Left PUMP anode connected to digital pin 13
const int RightLED = 11;            // Left LED anode connected to digital pin 11
const int LeftLED = 12;             // Right LED anode connected to digital pin 12
const int irRightPin = 6;           // right IR connected to digital pin 4
const int irLeftPin = 7;            // left IR connected to digital pin 2
byte irRightSensor = 0;             // this variable will read the value from the right sensor
byte irLeftSensor = 0;              // this variable will read the value from the left sensor
byte alternate = 0;                 // variable to alternate between R and L during TRAINING and EXPERIMENT status


//Keyboard implementation (Only for 3 keys using 4 DIG INPUTS. Can be upgraded to 8 keys by using 6 DIG INPUTS)

const byte rows = 1;              //one row
const byte cols = 3;              //four columns
byte rowPins[rows] = {5};         //connect to the row pinouts of the keypad
byte colPins[cols] = {4, 3, 2};   //connect to the column pinouts of the keypad
char keys[rows][cols] = {
  {'1', '2', '3'},
};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
char key;
byte menu;
char reset;

//Implementing different STATES. Four states for 3 keys + default. ¿Possibility of implementing HOLD status to double options without adding new keys?

enum state {HABITUATION, TRAINING, EXPERIMENT1, WAITING} current_state = WAITING;
//I define short press 1 = HABITUATION
//         short press 2 = TRAINING
//         short press 3 = EXPERIMENT1
//         hold 1 = not_def
//         hold 2 = not_def
//         hold 3 = not_def

//Initialize values
void setup() {

  Serial.begin(9600);
  keypad.setHoldTime(500);               // Default is 1000mS
  keypad.setDebounceTime(250);           // Default is 50mS

  pinMode(irRightPin, INPUT);        // declare right infrared sensor as input
  pinMode(irLeftPin, INPUT);         // declare left infrared sensor as input
  pinMode(RightLED, OUTPUT);         // declare Right LED pin as output
  pinMode(LeftLED, OUTPUT);          // declare Left LED pin as output
  pinMode(RightpumpPin, OUTPUT);     // declare Right Pump pin as output
  pinMode(LeftpumpPin, OUTPUT);      // declare Left Pump pin as output
  pinMode(LED_BUILTIN, OUTPUT);      // using in_build led (DIG13)

  digitalWrite(irRightPin, HIGH);    // turn on the right IR
  digitalWrite(irLeftPin, HIGH);     // turn on the left IR
  digitalWrite(RightLED, LOW);       // turn off the left LED
  digitalWrite(LeftLED, LOW);        // turn off the left LED
}

void loop() {

  switch (current_state) {    //Happens depending on the STATE if different from WAITING
    case WAITING:
      digitalWrite(RightLED, HIGH);              //Visual cue for WAITING state
      digitalWrite(LeftLED, HIGH);
      key = keypad.getKey();            // check for key press
      if (key != NO_KEY) {
        menu = key - 48;                // converts ASCII key (character) to menu (numerical)
        Serial.println(key);
        switch (menu) {
          case 1:        // enter the function by short pressing "1"
            {
              current_state = HABITUATION;
              for (byte x = 0; x < 1; x++) {       // Visual cue for HABITUATION state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN, LOW);
                delay(500);
              }
            }
            break;

          case 2:                  // enter the function by short pressing "2"
            {
              current_state = TRAINING;
              for (byte x = 0; x < 2; x++) {      // Visual cue for TRAINING state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN, LOW);
                delay(500);
              }
            }
            break;

          case 3:                  // enter the function by short pressing "3"
            {
              current_state = EXPERIMENT1;
              for (byte x = 0; x < 3; x++) {     // Visual cue for EXPERIMENT1 state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN, LOW);
                delay(500);
              }
            }
            break;

        }
      }
      break;

    case HABITUATION:      // During HABITUATION both IR sensors break generate water delivery, always
      digitalWrite(RightLED, LOW);
      digitalWrite(LeftLED, LOW);
      irRightSensor = digitalRead(irRightPin);   // read right IR value
      irLeftSensor = digitalRead(irLeftPin);     // read left IR value

      if (irLeftSensor == HIGH) {               // if Left IR does not detect any
        digitalWrite(LeftpumpPin, LOW);        //     Left Pump is OFF
      } else {
        LeftAction();                          // if Left IR detects some, pump ON
      }
      if (irRightSensor == HIGH) {              // if Left IR does not detect any
        digitalWrite(RightpumpPin, LOW);         //     Left Pump is OFF
      } else {
        RightAction();                         // if Left IR detects some, pump ON
      }

      reset = keypad.getKey();            // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset();
      }
      break;

    case TRAINING:       // During TRAINING alternating IR sensor break delivers water (Starting with LEFT)
      digitalWrite(RightLED, LOW);
      digitalWrite(LeftLED, LOW);
      irRightSensor = digitalRead(irRightPin);   // read right IR value
      irLeftSensor = digitalRead(irLeftPin);     // read left IR value

      if (irLeftSensor == HIGH ) {              // if Left IR does not detect any
        digitalWrite(LeftpumpPin, LOW);        //     Left Pump is OFF
      } else if ((irLeftSensor == LOW) && (alternate == 0)) {
        LeftAction();                           // if Left IR detects some AND is Left turn, pump ON
        alternate = 1;                          // Changes turn to RIGHT
      }

      if (irRightSensor == HIGH) {             // if Left IR does not detect any
        digitalWrite(RightpumpPin, LOW);      //      Left Pump is OFF
      } else if ((irRightSensor == LOW) && (alternate == 1)) {
        RightAction();                         // if Left IR detects some AND is Right turn, pump ON
        alternate = 0;                         // Change turn to RIGHT
      }

      reset = keypad.getKey();            // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset();
      }
      break;

    case EXPERIMENT1:           // NOT YET DEFINED What happen when State is EXPERIMENT 1
      digitalWrite(RightLED, LOW);
      digitalWrite(LeftLED, LOW);
      irRightSensor = digitalRead(irRightPin);   // read right IR value
      irLeftSensor = digitalRead(irLeftPin);     // read left IR value

      //
      // Here goes code to set EXPERIMENT1 conditions //
      //

      reset = keypad.getKey();            // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset();
      }
      break;
      break;
  }
}

//Special events

void LeftAction() {                 //IR triggered LeftPump
  digitalWrite(LeftpumpPin, HIGH);       // Left Pump is turned on
  digitalWrite(LeftLED, HIGH);           // and LED blinks
  delay(3000);                         //   for 2 seconds
  digitalWrite(LeftpumpPin, LOW);        // then automatically turns off
  digitalWrite(LeftLED, LOW);            // both
  delay(1000);                         // Avoids additional trigger for next 3 sec
}

void RightAction() {                //IR triggered RightPump
  digitalWrite(RightpumpPin, HIGH);      // Left Pump is turned on
  digitalWrite(RightLED, HIGH);          // and LED blinks
  delay(2000);                         //   for 2 seconds
  digitalWrite(RightpumpPin, LOW);       // then automatically turns off
  digitalWrite(RightLED, LOW);          // both
  delay(2000);                           // Avoids additional trigger for next 5 sec
}

void softReset() {                  // Reset function (taken from arduino.cc forum, user: Volkemon)
  asm volatile ("  jmp 0");
}


