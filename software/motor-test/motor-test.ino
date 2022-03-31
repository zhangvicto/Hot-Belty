const int motorPWM = 10;
const int motorIn1 = 23;
const int motorIn2 = 24;
int motorSpeed = 10; 

void setup() {
  pinMode(motorPWM, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  //stop motor
  analogWrite(motorPWM, 0);
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
}

void loop() {
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);

  //run motor between 75 - 255 pwm
  analogWrite(motorPWM, map(motorSpeed, 0, 100, 75, 255));
}
