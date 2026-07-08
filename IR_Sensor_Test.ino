/*
 * SINGLE IR SENSOR TEST
 * Test ONE sensor at a time
 */

// ========== CHOOSE WHICH SENSOR TO TEST ==========
#define TEST_SENSOR 1  // 1 = LEFT (pin 7), 2 = RIGHT (pin 6)
// ==================================================

// IR Sensor pins
int sr = 6;    // Sensor Right (pin 6)
int sl = 7;    // Sensor Left (pin 7)

void setup() {
  Serial.begin(9600);
  
  // Set sensor pin as input
  if (TEST_SENSOR == 1) {
    pinMode(sl, INPUT);
  } else {
    pinMode(sr, INPUT);
  }
  
  delay(1000);
  
  Serial.println("\n\n======================================");
  Serial.println("SINGLE SENSOR TEST");
  Serial.println("======================================");
  
  if (TEST_SENSOR == 1) {
    Serial.println("Testing: LEFT SENSOR (Pin 7)");
  } else {
    Serial.println("Testing: RIGHT SENSOR (Pin 6)");
  }
  
  Serial.println("");
  Serial.println("EXPECTED BEHAVIOR:");
  Serial.println("  0 (LOW)  = On BLACK line ✓ CORRECT");
  Serial.println("  1 (HIGH) = On WHITE paper ✓ CORRECT");
  Serial.println("");
  Serial.println("Instructions:");
  Serial.println("1. Place sensor on WHITE paper -> expect 1");
  Serial.println("2. Then on BLACK line -> expect 0");
  Serial.println("3. If sensor shows 1 all the time = FAULTY");
  Serial.println("======================================\n");
  
  delay(2000);
}

void loop() {
  // Read sensor value
  int sensorValue;
  
  if (TEST_SENSOR == 1) {
    sensorValue = digitalRead(sl);  // LEFT SENSOR
  } else {
    sensorValue = digitalRead(sr);  // RIGHT SENSOR
  }
  
  // Display readings
  Serial.print("[");
  Serial.print(millis() / 1000);
  Serial.print("s] Value: ");
  Serial.print(sensorValue);
  Serial.print(" -> ");
  
  // Status
  if (sensorValue == LOW) {
    Serial.println("✓ BLACK LINE DETECTED (Working!)");
  } else {
    Serial.println("⚠ WHITE / NO LINE (Check placement)");
  }
  
  delay(500);
}

// Optional: Uncomment to run full 20-second diagnostic
/*
void fullDiagnostic() {
  Serial.println("\n\nStarting 20-second diagnostic...");
  long startTime = millis();
  
  while (millis() - startTime < 20000) {
    // Read sensors
    int rightValue = digitalRead(sr);
    int leftValue = digitalRead(sl);
    
    // Count readings
    if (leftValue == LOW) leftLowCount++;
    else leftHighCount++;
    if (rightValue == LOW) rightLowCount++;
    else rightHighCount++;
    
    delay(100);
  }
  
  // Print diagnostic report
  Serial.println("\n====== DIAGNOSTIC REPORT ======");
  Serial.print("LEFT sensor - LOW readings: ");
  Serial.print(leftLowCount);
  Serial.print(", HIGH readings: ");
  Serial.println(leftHighCount);
  
  Serial.print("RIGHT sensor - LOW readings: ");
  Serial.print(rightLowCount);
  Serial.print(", HIGH readings: ");
  Serial.println(rightHighCount);
  
  if (leftHighCount == 200) {
    Serial.println("\n⚠ LEFT SENSOR ISSUE: Always returns HIGH");
    Serial.println("  Possible causes:");
    Serial.println("  1. Sensor disconnected from pin 7");
    Serial.println("  2. Sensor hardware failure");
    Serial.println("  3. Wiring problem");
    Serial.println("  ACTION: Check wiring, test with multimeter");
  }
  if (rightHighCount == 200) {
    Serial.println("\n⚠ RIGHT SENSOR ISSUE: Always returns HIGH");
    Serial.println("  Possible causes:");
    Serial.println("  1. Sensor disconnected from pin 6");
    Serial.println("  2. Sensor hardware failure");
    Serial.println("  3. Wiring problem");
    Serial.println("  ACTION: Check wiring, test with multimeter");
  }
  
  Serial.println("==============================\n");
  
  // Reset and continue
  leftLowCount = 0;
  leftHighCount = 0;
  rightLowCount = 0;
  rightHighCount = 0;
  delay(5000);
  fullDiagnostic();
}
*/
