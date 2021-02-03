#include <Arduino.h>
#include <EEPROM.h>

#define RPM 400
#define MOTOR_ACCEL 3000
#define MOTOR_DECEL 3000

#include "DRV8825.h"
#define MOTOR_STEPS 200
#define MICROSTEPS 32
#define MODE0 D2
#define MODE1 D3
#define MODE2 D4
#define DIR D6
#define STEP D5
#define EN D1

#define LENGTH MOTOR_STEPS * MICROSTEPS * 24  //24 full rotations to go up (or down)

#define PINUP 10
#define PINDOWN D7 

DRV8825 stepper(MOTOR_STEPS, DIR, STEP, EN, MODE0, MODE1, MODE2);

struct {
  int state = 0;
} curtainState;
void moveUp() { 
  if (curtainState.state == 0) {
    stepper.enable();
    stepper.startMove(LENGTH);
    curtainState.state = 1;
    EEPROM.put(0, curtainState);
    EEPROM.commit();
  }
}

void moveDown() {
  if (curtainState.state == 1) {
    stepper.enable();
    stepper.startMove(-1*LENGTH);
    curtainState.state = 0;
    EEPROM.put(0, curtainState);
    EEPROM.commit();
  }
}

bool isMoving = false;
void checkInputs() {
  if (isMoving) { 
    return;
  }
  if (digitalRead(PINUP) == LOW && curtainState.state == 0) {
    Serial.println("Received \'up\' press!");
    moveUp();
  } else if (digitalRead(PINDOWN) == LOW && curtainState.state == 1) {
    Serial.println("Received \'down\' press!");
    moveDown();
  }
  while (digitalRead(PINUP) == LOW || digitalRead(PINDOWN) == LOW) {
      delay(1);
      ESP.wdtFeed();
  }
}

void setup() {
  ESP.wdtDisable();
  stepper.begin(RPM, MICROSTEPS);
  stepper.setEnableActiveState(LOW);
  stepper.disable();
  stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
  Serial.begin(115200);

  EEPROM.begin(10);
  EEPROM.get(0, curtainState);

  Serial.println("Program started. Current state of curtain: " + String(curtainState.state));

  pinMode(PINUP, INPUT_PULLUP);
  pinMode(PINDOWN, INPUT_PULLUP);

}

void loop() {
  ESP.wdtFeed();
  checkInputs();
  unsigned wait_time_micros = stepper.nextAction();
    if (wait_time_micros <= 0) {
        stepper.disable();
        isMoving = false;
    } else {
      isMoving = true;
    }
}