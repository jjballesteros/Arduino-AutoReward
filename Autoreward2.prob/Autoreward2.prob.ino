// Code for the infrared beam-triggered double reward system is shown below.
// Shared first on 05.11.2017 by jesusjballesteros in forum.arduino.cc
// Feel free to modify, share and use it. Acknowledgements and feedback are always welcome.

// 08.10.2017 Autoreward2.prob is a modification of the original Autoreward2 project. 

#include <Keypad.h>

//Main INPUT/OUTPUT system
const int RightValve = 10;          // Right Valve ctrl connected to digital pin 10
const int LeftValve = 9;            // Left Valve ctrl connected to digital pin 13
const int RightLED = 12;            // Left LED anode connected to digital pin 11
const int LeftLED = 11;             // Right LED anode connected to digital pin 12
const int irRightPin = 7;           // Right IR connected to digital pin 4
const int irLeftPin = 8;            // Left IR connected to digital pin 2
byte irRightSensor = 0;             // will read the value from the right IR
byte irLeftSensor = 0;              // will read the value from the left IR
byte alternate = 0;                 // variable to alternate between arms


//Keyboard implementation (8 keys using 5 DIG INPUTS. Can be upgraded!)

const byte rows = 4;                 // two rows
const byte cols = 3;                 // three columns
byte rowPins[rows] = {2, 6, 13, 1};  // row pinout of the keypad
byte colPins[cols] = {3, 4, 5};      // column pinout of the keypad
char keys[rows][cols] = {            // Names each element of the Keypad matrix
  {'1', '2', '3',},
  {'4', '5', '6',},
  {'7', '8', '9',},
  {'#', '0', '*',},
};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
char key;               // Stores the ASCII value of pressed key
byte menu;              // Stores the numerical value of pressed key (ASCII - 48)
char reset;             // Used to reset the software (Back to WAITING state)
byte randNumber;        // Stores a self generated ramdom number 
byte FailCounter;       // Counts #failed reward attemps by chance. It limits it to 3 consecutive ones. Makes it 'Pseudoramdom' for behavioral porpouses

//Implementing different STATES.
// Defined Protocols, add here additional ones inside brackets { } separated by commas ,

enum state {HABITUATION, TRAINING_R, TRAINING_L, PROB75R, PROB50R, PROB25R, PROB75L, PROB50L, PROB25L, WAITING, FILLandCLEAN} current_state = WAITING;      

      //I define short press 1 = HABITUATION
      //         short press 2 = TRAINING_R
      //         short press 3 = TRAINING_L
      //         short press 4 = PROB75R
      //         short press 5 = PROB50R
      //         short press 6 = PROB25R
      //         short press 7 = PROB75L
      //         short press 8 = PROB50L
      //         short press 9 = PROB25L
      //         short press 0 = FILLandCLEAN

      //         TRAINING for alternating arm has been disabled. Use Autoreward2 code for it.

//Initialize values
void setup() {

  Serial.begin(9600);
  keypad.setHoldTime(500);           // Default is 1000mS
  keypad.setDebounceTime(250);       // Default is 50mS

  pinMode(irRightPin, INPUT);        // declare right IR sensor as input
  pinMode(irLeftPin, INPUT);         // declare left IR sensor as input
  pinMode(RightLED, OUTPUT);         // declare Right LED pin as output
  pinMode(LeftLED, OUTPUT);          // declare Left LED pin as output
  pinMode(RightValve, OUTPUT);       // declare Right Valve pin as output
  pinMode(LeftValve, OUTPUT);        // declare Left Valve pin as output
  pinMode(LED_BUILTIN, OUTPUT);      // using in_build led (DIG13)

  digitalWrite(irRightPin, HIGH);    // turn on the right IR
  digitalWrite(irLeftPin, HIGH);     // turn on the left IR
  digitalWrite(RightLED, LOW);       // turn off the left LED
  digitalWrite(LeftLED, LOW);        // turn off the left LED
}

void loop() {

  switch (current_state) {        //Happens depending on the STATE
    case WAITING:
      digitalWrite(RightLED, HIGH);     //Visual cue for WAITING state
      digitalWrite(LeftLED, HIGH);
      key = keypad.getKey();            // check for key press
      if (key != NO_KEY) {
        menu = key - 48;                // converts ASCII key (char) to menu (byte)
        Serial.println(key);
        
       switch (menu) {            //Happens depending on the PRESSED KEY
          
          case 1:                       // enter the function by short pressing "1"
            {
              current_state = HABITUATION;
              for (byte x = 0; x < 1; x++) {           // Visual cue for HABITUATION state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN, LOW);
                delay(300);
              } }
            break;

          case 2:                      // enter the function by short pressing "2"
            {
              current_state = TRAINING_R;
              for (byte x = 0; x < 2; x++) {            // Visual cue for PROB75 state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN, LOW);
                delay(300);
              } }
            break;

           case 3:                     // enter the function by short pressing "3"
            {
              current_state = TRAINING_L;
              for (byte x = 0; x < 3; x++) {            // Visual cue for TRAINING_L state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN, LOW);
                delay(300);
              } }
            break;
            
          case 4:                       // enter the function by short pressing "4"
            {
              current_state = PROB75R;
              for (byte x = 0; x < 4; x++) {            // Visual cue for PROB75R state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN, LOW);
                delay(300);
              } }
          break;
          
          case 5:                       // enter the function by short pressing "5"
            {
              current_state = PROB50R;
              for (byte x = 0; x < 5; x++) {            // Visual cue for PROB50R state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN, LOW);
                delay(300);
              } }
          break;

          case 6:                        // enter the function by short pressing "6"
            {
              current_state = PROB25R;
              for (byte x = 0; x < 6; x++) {            // Visual cue for PROB25R state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN, LOW);
                delay(300);
              } }
          break;

          case 7:                        // enter the function by short pressing "7"
            {
              current_state = PROB75L;
              for (byte x = 0; x < 7; x++) {            // Visual cue for PROB75L state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN, LOW);
                delay(300);
              } }
          break;

          case 8:                        // enter the function by short pressing "8"
            {
              current_state = PROB50L;
              for (byte x = 0; x < 8; x++) {            // Visual cue for PROB50L state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN, LOW);
                delay(300);
              } }
          break;

          case 9:                        // enter the function by short pressing "9"
            {
              current_state = PROB25L;
              for (byte x = 0; x < 9; x++) {            // Visual cue for PROB25L state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN, LOW);
                delay(300);
              } }
          break;

          case 0:                        // enter function by short pressing "0"
             {
              current_state = FILLandCLEAN;
              for (byte x = 0; x < 1; x++) {            //Visual cue for FILLandCLEAN state
                digitalWrite(LED_BUILTIN, HIGH);
                delay(2000);
                digitalWrite(LED_BUILTIN, LOW);
                delay(500);
                  } }
           break;
       }                     // Ends switch(menu)
                             // Continues switch(current_state)

    case HABITUATION:                    // During HABITUATION both IR sensors break trigger water delivery, always
      digitalWrite(RightLED, LOW);
      digitalWrite(LeftLED, LOW);
      irRightSensor = digitalRead(irRightPin);      // read right IR value
      irLeftSensor = digitalRead(irLeftPin);        // read left IR value

      if (irLeftSensor == HIGH) {                   // if Left IR does not detect any
        digitalWrite(LeftValve, LOW);               //     Left Valve is OFF
      } else {
        LeftAction(); }                              // if Left IR detects some, pump ON
        
      if (irRightSensor == HIGH) {                  // if Left IR does not detect any
        digitalWrite(RightValve, LOW);              //     Left Valve is OFF
      } else {
        RightAction();  }                             // if Left IR detects some, pump ON

      reset = keypad.getKey();                      // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset();  }
     break;

    case TRAINING_R:                  // During TRAINING_R only right IR breaks delivers water (100% times)
      digitalWrite(RightLED, LOW);
      digitalWrite(LeftLED, LOW);
      irRightSensor = digitalRead(irRightPin);       // read right IR value
      
       if (irRightSensor == HIGH) {                   // if right IR does not detect any
        digitalWrite(RightValve, LOW);                //      right Valve is OFF
       } else if (irRightSensor == LOW) {            // if right IR detects some, pump ON
        RightAction();  }

      reset = keypad.getKey();            // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset();  }
    break;

    case TRAINING_L:                  // During TRAINING_L only Left IR breaks delivers water (100% times)
      digitalWrite(RightLED, LOW);
      digitalWrite(LeftLED, LOW);
      irLeftSensor = digitalRead(irLeftPin);       // read left IR value
      
       if (irLeftSensor == HIGH) {                   // if left IR does not detect any
        digitalWrite(LeftValve, LOW);                //      Left Valve is OFF
       } else if (irLeftSensor == LOW) {            // if left IR detects some, pump ON
        LeftAction(); }

      reset = keypad.getKey();            // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset();  }
    break;
      
    case PROB75R:                                 // right IR breaks delivers water (75% times)
      digitalWrite(RightLED, LOW);
      digitalWrite(LeftLED, LOW);
      irRightSensor = digitalRead(irRightPin);    // read right IR value
      randomSeed(analogRead(0));                  // create a seed for randomization, by reading an empty Analog port noise
      randNumber = random(1, 100);                // generates a random number each time, between 1 and 100.

                                                  // Pseudoramdomization of reward
      if (irRightSensor == HIGH) {                                  // if Right IR does detects nothing
        digitalWrite(RightValve, LOW);                              //      Right Valve stays close
      } else if ((irRightSensor == LOW) && (randNumber <= 75)) {    // if Right IR detects some AND RandomNumber is equal or minor 75
        RightAction();                                              //      Right Valve Opens
      } else if (FailCounter >=3) {                                 // if has been three consecutive Fails in reward
        RightAction();                                              //      Right Valve Opens
        FailCounter = 0;                                            //      and counter resets to zero
      } else {                                                      // otherwise, means that reward MUST NOT be given 
        FailCounter++;                                              //      and it adds one to the Fail counter.
        delay(7100);                                                 //      and adds a delay equivalent to the rewarded effect.
      }
       
      reset = keypad.getKey();              // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset();  }
    break;

    case PROB50R:                                 // right IR breaks delivers water (50% times)
      digitalWrite(RightLED, LOW);
      digitalWrite(LeftLED, LOW);
      irRightSensor = digitalRead(irRightPin);    // read right IR value
      randomSeed(analogRead(0));                  // create a seed for randomization, by reading an empty Analog port noise
      randNumber = random(1, 100);                // generates a random number each time, between 1 and 100.

                                                         // Pseudoramdomization of reward
      if (irRightSensor == HIGH) {                                  // if Right IR does not detect any
        digitalWrite(RightValve, LOW);                              //      Right Valve is OFF
      } else if ((irRightSensor == LOW) && (randNumber <= 50)) {    // if Right IR detects some AND RandomNumber is equal or minor 50
        RightAction();                                              //      Right Valve Opens
      } else if (FailCounter >=3) {                                 // if has been three consecutive Fails in reward
        RightAction();                                              //      Right Valve Opens
        FailCounter = 0;                                            //      and counter resets to zero
      } else {                                                      // otherwise, means that reward MUST NOT be given 
        FailCounter++;                                              //      and it adds one to the Fail counter.
        delay(7100);                                                 //      and adds a delay equivalent to the rewarded effect.      
      }
      
      reset = keypad.getKey();            // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset();  }
    break;
      
    case PROB25R:                                 // right IR breaks delivers water (25% times)
      digitalWrite(RightLED, LOW);
      digitalWrite(LeftLED, LOW);
      irRightSensor = digitalRead(irRightPin);    // read right IR value
      randomSeed(analogRead(0));                  // create a seed for randomization, by reading an empty Analog port noise
      randNumber = random(1, 100);                // generates a random number each time, between 1 and 100.

                                                            // Pseudoramdomization of reward
      if (irRightSensor == HIGH) {                                  // if Right IR does not detect any
        digitalWrite(RightValve, LOW);                              //      Right Valve is OFF
      } else if ((irRightSensor == LOW) && (randNumber <= 25)) {    // if Right IR detects some AND RandomNumber is equal or minor 25
        RightAction();                                              //      Right Valve Opens
      } else if (FailCounter >=3) {                                 // if has been three consecutive Fails in reward
        RightAction();                                              //      Right Valve Opens
        FailCounter = 0;                                            //      and counter resets to zero
      } else {                                                      // otherwise, means that reward MUST NOT be given 
        FailCounter++;                                              //      and it adds one to the Fail counter.
        delay(7100);                                                   //      and adds a delay equivalent to the rewarded effect.      
      }
      
      reset = keypad.getKey();            // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset(); }
    break;

    case PROB75L:                                 // Left IR breaks delivers water (75% times)
      digitalWrite(RightLED, LOW);
      digitalWrite(LeftLED, LOW);
      irLeftSensor = digitalRead(irLeftPin);      // read left IR value
      randomSeed(analogRead(0));                  // create a seed for randomization, by reading an empty Analog port noise
      randNumber = random(1, 100);                // generates a random number each time, between 1 and 100.

                                                            // Pseudoramdomization of reward
      if (irLeftSensor == HIGH ) {                                  // if Left IR does not detect any
        digitalWrite(LeftValve, LOW);                               //     Left Valve is OFF
      } else if ((irLeftSensor == LOW) && (randNumber <= 75)) {     // if Left IR detects some AND is RandomNumber is equal or minor 75     
        LeftAction();                                               //      Left Valve Opens
      } else if (FailCounter >=3) {                                 // if has been three consecutive Fails in reward
        LeftAction();                                               //      Left Valve Opens
        FailCounter = 0;                                            //     and counter resets to zero
      } else {                                                      // otherwise, means that reward MUST NOT be given 
        FailCounter++;                                              //     and it adds one to the Fail counter.
        delay(7100);                                                 //      and adds a delay equivalent to the rewarded effect.      
      }

      reset = keypad.getKey();            // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset(); }
    break;

      case PROB50L:                                 // Left IR breaks delivers water (50% times)
      digitalWrite(RightLED, LOW);
      digitalWrite(LeftLED, LOW);
      irLeftSensor = digitalRead(irLeftPin);      // read left IR value
      randomSeed(analogRead(0));                  // create a seed for randomization, by reading an empty Analog port noise
      randNumber = random(1, 100);                // generates a random number each time, between 1 and 100.

                                                            // Pseudoramdomization of reward
      if (irLeftSensor == HIGH ) {                                   // if Left IR does not detect any
        digitalWrite(LeftValve, LOW);                                //     Left Valve is OFF
      } else if ((irLeftSensor == LOW) && (randNumber <= 50)) {      // if Left IR detects some AND is RandomNumber is equal or minor 50     
          LeftAction();                                              //      Left Valve Opens
      } else if (FailCounter >=3) {                                  // if has been three consecutive Fails in reward
        LeftAction();                                                //      Left Valve Opens
        FailCounter = 0;                                             //     and counter resets to zero
      } else {                                                       // otherwise, means that reward MUST NOT be given 
        FailCounter++;                                               //     and it adds one to the Fail counter.
        delay(7100);                                                 //      and adds a delay equivalent to the rewarded effect.      
      }

      reset = keypad.getKey();                  // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset();  }
    break;
      
    case PROB25L:                                 // Left IR breaks delivers water (25% times)
      digitalWrite(RightLED, LOW);
      digitalWrite(LeftLED, LOW);
      irLeftSensor = digitalRead(irLeftPin);      // read left IR value
      randomSeed(analogRead(0));                  // create a seed for randomization, by reading an empty Analog port noise
      randNumber = random(1, 100);                // generates a random number each time, between 1 and 100.

                                                            // Pseudoramdomization of reward
      if (irLeftSensor == HIGH ) {                                  // if Left IR does not detect any
        digitalWrite(LeftValve, LOW);                               //     Left Valve is OFF
      } else if ((irLeftSensor == LOW) && (randNumber <= 25)) {     // if Left IR detects some AND is RandomNumber is equal or minor 25    
         LeftAction();                                              //      Left Valve Opens
      } else if (FailCounter >=3) {                                 // if has been three consecutive Fails in reward
        LeftAction();                                               //      Left Valve Opens
        FailCounter = 0;                                            //     and counter resets to zero
      } else {                                                      // otherwise, means that reward MUST NOT be given 
        FailCounter++;                                              //     and it adds one to the Fail counter.
        delay(7100);                                                 //      and adds a delay equivalent to the rewarded effect.      
      }

      reset = keypad.getKey();                    // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset();  }
    break;
      
//      case EXPERIMENT2:                            // NOT YET DEFINED What happen when State is EXPERIMENT 2
//      digitalWrite(RightLED, LOW);
//      digitalWrite(LeftLED, LOW);
//      irRightSensor = digitalRead(irRightPin);   // read right IR value
//      irLeftSensor = digitalRead(irLeftPin);     // read left IR value
//      
//      reset = keypad.getKey();            // Any key to Reset to WAITING state
//      if (reset != NO_KEY) {
//        softReset();
//      }
//    break;

     case FILLandCLEAN:                 // During FILL/CLEAN IR sensors are not read and Valves are OPEN for 5 secs, every 2 sec
      digitalWrite(LeftValve, HIGH);         // Left Valve is turned on
      digitalWrite(LeftLED, HIGH);           // and LED blinks
      digitalWrite(RightValve, HIGH);        // Left Valve is turned on
      digitalWrite(RightLED, HIGH);          // and LED blinks
      delay(5000);
      digitalWrite(LeftValve, LOW);         // Left Valve is turned on
      digitalWrite(LeftLED, LOW);           // and LED blinks
      digitalWrite(RightValve, LOW);        // Left Valve is turned on
      digitalWrite(RightLED, LOW);          // and LED blinks
      delay(2000);
      
      reset = keypad.getKey();            // Any key to Reset to WAITING state
      if (reset != NO_KEY) {
        softReset();  }
      break;

//    case NOT_DEF:           // Add new STATES to define additional protocols (remember to add them up in STATE definition!)
//
//
//    reset = keypad.getKey();            // Any key to Reset to WAITING state
//      if (reset != NO_KEY) {
//        softReset();
//      }
//      break;
      
      
      }}}      // ENDS ALL LOOP


//Special events

void LeftAction() {                   //IR triggered LeftValve
  digitalWrite(LeftValve, HIGH);          // Left Valve is open briefly
  digitalWrite(LeftLED, HIGH);            // and LED blinks
  delay(100);
  digitalWrite(LeftValve, LOW);
  delay(2000);                            //   for 2 seconds
  digitalWrite(LeftLED, LOW);
  delay(5000);                            // Avoids additional trigger for next 5 sec
}

void RightAction() {                  //IR triggered RightValve
  digitalWrite(RightValve, HIGH);        // Right Valve is turned on
  digitalWrite(RightLED, HIGH);          // and LED blinks
  delay(100);
  digitalWrite(RightValve, LOW);
  delay(2000);                           //   for 2 seconds
  digitalWrite(RightLED, LOW);
  delay(5000);
}

void softReset() {                       // Reset function (taken from arduino.cc forum, user: Volkemon)
  asm volatile ("  jmp 0");
}

