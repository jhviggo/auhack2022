#include <Servo.h>
#include <afstandssensor.h>

AfstandsSensor afstandssensor(11, 10);  // Starter afstandssensoren på ben 13 og 12.


Servo myservo;  // create servo object to control a servo
Servo colleague0;
Servo colleague1;

// array of colleagues and their working states
Servo colleagues[] = { colleague0, colleague1 };
bool states[] = { false, false };

int pos = 0;    // variable to store the servo position
bool working = false;

void setup() {
  // initialized the servos
  myservo.attach(9);
  colleague0.attach(6);
  colleague1.attach(5);
  // reset the servos position to 0
  myservo.write(0);
  colleague0.write(0);
  colleague1.write(0);
  Serial.begin(9600);  // Opsætter serial kommunikation tilbage til computeren
}

void loop() {
  checkMyWorkingState();
  handleColleagueState();
}

/**
 * Reads data from the serial port to receive data from the database (firestore)
 * about colleague working states
 */
void handleColleagueState() {
  if (Serial.available()) {
    int incomingState = Serial.read();
    delay(5);
    int i = Serial.read() - 48; // colleague index
    if (incomingState == 'w' && !states[i]) { // checks if the colleague is working and their known state is not working
      Servo colleague = colleagues[i];
      turnColleague(colleague, true);
      states[i] = true;
    } else if (incomingState == 'n' && states[i]) {
      Servo colleague = colleagues[i];
      turnColleague(colleague, false);
      states[i] = false;
    }
    
  }
}

/**
 * Checks your own working state with a distance sensor
 */
void checkMyWorkingState() {
  int distance = afstandssensor.afstandCM();
  if (0 < distance && distance <= 20 && working == false) {
    Serial.print("working\n");
    working = true;
    turnMe();
  }
  else if (21 <= distance && working == true) {
    Serial.print("notWorking\n");
    working = false;
    turnMe();
  }
  // Serial.println(distance);
  delay(50);
}

/**
 * Turns your own figure around when called, depending on global variables
 */
void turnMe() {
  if (working) {
    int pos = 180;
    while(pos > 0){ 
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);                  // waits 15ms for the servo to reach the position
      pos--;
    }
  }
  else if (!working){
    int pos = 0;
    while(pos < 180){
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);
      pos++;
    }
  }
}

/**
 * Turns the given colleague to either working or not working
 * @param servo the colleague in the list of colleagues
 * @param isWorking whether the colleague is working
 */
void turnColleague(Servo servo, bool isWorking) {
  if (isWorking) {
    int pos = 180;
    while(pos > 0){ 
      servo.write(pos);
      delay(10);
      pos--;
    }
  }
  else if (!isWorking){
    int pos = 0;
    while(pos < 180){
      servo.write(pos);
      delay(10);
      pos++;
    }
  }
}