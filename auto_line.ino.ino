/*
 * Automatic Line Follower
 * Uses IR sensors to detect and follow black line
 * Clean and simple implementation
 */

// Motor pins
int mr1 = 8;   // Motor Right 1
int mr2 = 9;   // Motor Right 2
int ml1 = 10;  // Motor Left 1
int ml2 = 11;  // Motor Left 2
int enr = 3;   // Enable Right (PWM)
int enl = 5;   // Enable Left (PWM)

// Sensor pins
int sr = 6;    // Sensor Right
int sl = 7;    // Sensor Left

// Speed settings
int normalSpeed = 120;   // Speed for straight movement
int turnSpeed = 150;     // Speed for turning

void setup() {
  Serial.begin(9600);
  
  // Motor pins as output
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  
  // Sensor pins as input
  pinMode(sr, INPUT);
  pinMode(sl, INPUT);
  
  Serial.println("Line Follower Ready!");
  Serial.println("Place on black line...");
  
  delay(3000); // 3 second delay before starting
}

void loop() {
  // Read sensors (LOW = BLACK, HIGH = WHITE)
  int rightSensor = digitalRead(sr);
  int leftSensor = digitalRead(sl);
  
  // Decision logic
  if (leftSensor == LOW && rightSensor == LOW) {
    // Both on black line - GO STRAIGHT
    forward();
    Serial.println("⬆️  Both on line - FORWARD");
  }
  else if (leftSensor == LOW && rightSensor == HIGH) {
    // Left on black, Right on white - TURN LEFT
    turnLeft();
    Serial.println("⬅️  Left on line - TURN LEFT");
  }
  else if (leftSensor == HIGH && rightSensor == LOW) {
    // Left on white, Right on black - TURN RIGHT
    turnRight();
    Serial.println("➡️  Right on line - TURN RIGHT");
  }
  else {
    // Both on white - LOST LINE, STOP
    stop();
    Serial.println("⏹️  Line lost - STOPPED");
  }
  
  delay(100); // Small delay for stability
}

void forward() {
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  analogWrite(enr, normalSpeed);
  analogWrite(enl, normalSpeed);
}

void turnLeft() {
  // Slow down right motor, speed up left
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  analogWrite(enr, turnSpeed);
  analogWrite(enl, normalSpeed / 2);
}

void turnRight() {
  // Slow down left motor, speed up right
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  analogWrite(enr, normalSpeed / 2);
  analogWrite(enl, turnSpeed);
}

void stop() {
  analogWrite(enr, 0);
  analogWrite(enl, 0);
}