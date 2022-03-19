#include <Servo.h>
#include <afstandssensor.h>

AfstandsSensor afstandssensor(11, 10);  // Starter afstandssensoren på ben 13 og 12.


Servo myservo;  // create servo object to control a servo
Servo colleague0;
Servo colleague1;

Servo colleagues[] = { colleague0, colleague1 };

int pos = 0;    // variable to store the servo position
boolean working = false;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  colleague0.attach(6);
  colleague1.attach(5);
  Serial.begin(9600);  // Opsætter serial kommunikation tilbage til computeren
}

void loop() {
  checkMyWorkingState();
  handleColleagueState();
}

void handleColleagueState() {
  if (Serial.available()) {
    int incomingState = Serial.read();
    //Serial.println(String(incomingState));
    //Serial.print(incomingState == 'w');
    delay(5);
    int i = Serial.read() - 48; // colleague index
    Serial.println("index");
    Serial.println(String(i));
    if (incomingState == 'w') {
      Servo colleague = colleagues[i];
      colleague.write(180);
      Serial.println("yes");
    } else if (incomingState == 'n') {
      Servo colleague = colleagues[i];
      colleague.write(0);
      Serial.println("no");
    }
    
  }
}

void checkMyWorkingState() {
  int distance = afstandssensor.afstandCM();
  if (0 < distance && distance <= 20 && working == false) {
    Serial.print("working\n");
    working = true;
    turn();
  }
  else if (21 <= distance && working == true) {
    Serial.print("notWorking\n");
    working = false;
    turn();
  }
  // Serial.println(distance);
  delay(50);
}

void turn() {
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