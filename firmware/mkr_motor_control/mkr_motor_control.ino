// RC Tank - single motor USB serial test
// Hardware: Arduino MKR WiFi 1010 + DRV8833
// Confirmed wiring:
//   MKR pin 5 -> DRV8833 AIN1
//   MKR pin 4 -> DRV8833 AIN2
//   MKR VCC   -> DRV8833 SLP
//   MKR GND   -> DRV8833 GND

const int AIN1 = 5;
const int AIN2 = 4;

void motorForward() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
}

void motorStop() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
}

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  motorStop();
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == '1') {
      motorForward();
    } else if (command == '0') {
      motorStop();
    }
  }
}
