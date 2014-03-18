/*
The sketch receives a Bluetooth Low Energy 4 connection,
then takes a direction for the Bescor MP-101 camera pan head.

This sketch is supposed to be used with the Broadway iPhone application.
*/

#include <RFduinoBLE.h>

int up = 1;
int down = 2;
int left = 3;
int right = 4;

void setup() {
  // setup the leds for output
  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);

  // this is the data we want to appear in the advertisement
  // (the deviceName length plus the advertisement length must be <= 18 bytes
  RFduinoBLE.advertisementData = "broadway";
  RFduinoBLE.begin();
}

void loop() {
  // switch to lower power mode
  RFduino_ULPDelay(INFINITE);
}

void stop() {
  digitalWrite(up, LOW);
  digitalWrite(down, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
}

void RFduinoBLE_onConnect() {
}

void RFduinoBLE_onDisconnect() {
  // stop all movement
  stop();
}

void RFduinoBLE_onReceive(char *data, int len) {
  // each transmission should contain an RGB triple
  if (len >= 1) {
    // get the ascii value
    uint8_t r = data[0];

    switch (r) {
    case 'u':
      digitalWrite(up, HIGH);
      break;
    case 'd':
      digitalWrite(down, HIGH);
      break;
    case 'l':
      digitalWrite(left, HIGH);
      break;
    case 'r':
      digitalWrite(right, HIGH);
      break;
    case 's':
      stop();
      break;
    }

    // wait 200ms for the motor to take a turn
    delay(200);
  }
}
