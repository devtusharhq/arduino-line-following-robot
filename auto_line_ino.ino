/*
 * Automatic Line Follower
 * Uses IR sensors to detect and follow black line
 */

// Motor pins
int mr1 = 8;
int mr2 = 9;
int ml1 = 10;
int ml2 = 11;
int enr = 3;
int enl = 5;

// Sensor pins
int sr = 6;
int sl = 7;

// Speed settings
int normalSpeed = 120;
int turnSpeed = 150;

bool MOTOR_TEST_MODE = true;

void setup() {
  Serial.begin(9600);
  
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  pinMode(enr, OUTPUT);
  pinMode(enl, OUTPUT);
  
  pinMode(sr, INPUT);
  pinMode(sl, INPUT);
  
  Serial.println("\n===================================");
  Serial.println("LINE FOLLOWER - STARTUP");
  Serial.println("===================================");
  Serial.println("Motor pins: R(8,9,3) L(10,11,5)");
  Serial.println("Sensor pins: RIGHT=6, LEFT=7");
  
  if (MOTOR_TEST_MODE) {
    Serial.println("\nMOTOR TEST MODE - Testing each motor...");
    runMotorTest();
  } else {
    Serial.println("\nPlace robot on black line...");
    Serial.println("Starting in 3 seconds...\n");
    delay(3000);
  }
}

void loop() {
  int rightSensor = digitalRead(sr);
  int leftSensor = digitalRead(sl);
  
  Serial.print("[");
  Serial.print(millis() / 1000);
  Serial.print("s] L=");
  Serial.print(leftSensor);
  Serial.print(" R=");
  Serial.print(rightSensor);
  Serial.print(" -> ");
  
  if (leftSensor == LOW && rightSensor == LOW) {
    forward();
    Serial.println("FORWARD (both on black)");
  }
  else {
    stop();
    Serial.println("STOP (sensors not on line)");
  }
  
  delay(100);
}

void forward() {
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  analogWrite(enr, 200);
  
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  analogWrite(enl, 200);
  
  Serial.println("[MOTORS] RIGHT=200 LEFT=200");
}

void stop() {
  analogWrite(enr, 0);
  analogWrite(enl, 0);
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, LOW);
  Serial.println("[MOTORS] STOP");
}

void runMotorTest() {
  Serial.println("\n========== MOTOR TEST ==========");
  
  Serial.println("\n[1/2] RIGHT MOTOR - 3 seconds at full power");
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  analogWrite(enr, 255);
  delay(3000);
  analogWrite(enr, 0);
  Serial.println("RIGHT motor stop");
  
  delay(2000);
  
  Serial.println("\n[2/2] LEFT MOTOR - 3 seconds at full power");
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  analogWrite(enl, 255);
  delay(3000);
  analogWrite(enl, 0);
  Serial.println("LEFT motor stop");
  
  delay(2000);
  
  Serial.println("\n=== TEST COMPLETE ===");
  Serial.println("If RIGHT motor did NOT spin:");
  Serial.println("  -> Check wires on pins 8, 9 (motor pins)");
  Serial.println("  -> Check pin 3 (enable) wire to motor driver");
  Serial.println("  -> Check battery voltage (should be 5V+)");
  Serial.println("  -> Check GND is connected to Arduino GND");
  Serial.println("\nIf LEFT motor did NOT spin:");
  Serial.println("  -> Check wires on pins 10, 11 (motor pins)");
  Serial.println("  -> Check pin 5 (enable) wire to motor driver");
  Serial.println("\nNow set MOTOR_TEST_MODE = false to run line follower");
  
  while(true) {
    delay(1000);
    Serial.println("...waiting...");
  }
}