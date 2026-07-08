// Simple Motor Control - No Sensors
int mr1=8;  // motor right 1
int mr2=9;  // motor right 2
int ml1=10; // motor left 1
int ml2=11; // motor left 2
int led=13;
int enr=3;  // enable right (PWM)
int enl=5;  // enable left (PWM)

int speed_val=150; // Speed 0-255

void setup()
{
  Serial.begin(9600);
  
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  pinMode(led, OUTPUT);
  
  Serial.println("Motor Control Ready");
  Serial.println("Commands: W=Forward, S=Backward, A=Left, D=Right, X=Stop");
}

void loop()
{
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    
    switch(cmd) {
      case 'W':
      case 'w':
        forward();
        Serial.println("Moving Forward");
        break;
      case 'S':
      case 's':
        backward();
        Serial.println("Moving Backward");
        break;
      case 'A':
      case 'a':
        left();
        Serial.println("Turning Left");
        break;
      case 'D':
      case 'd':
        right();
        Serial.println("Turning Right");
        break;
      case 'X':
      case 'x':
        stop();
        Serial.println("Stopped");
        break;
    }
  }
  
  delay(100);
}

void forward() {
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  analogWrite(enr, speed_val);
  analogWrite(enl, speed_val);
  digitalWrite(led, HIGH);
}

void backward() {
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  analogWrite(enr, speed_val);
  analogWrite(enl, speed_val);
  digitalWrite(led, HIGH);
}

void left() {
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  analogWrite(enr, speed_val);
  analogWrite(enl, speed_val);
  digitalWrite(led, HIGH);
}

void right() {
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  analogWrite(enr, speed_val);
  analogWrite(enl, speed_val);
  digitalWrite(led, HIGH);
}

void stop() {
  analogWrite(enr, 0);
  analogWrite(enl, 0);
  digitalWrite(led, LOW);
}