// --- PIN CONFIGURATION ---
#define L_PWM 5   // Left Motor Speed
#define L_IN1 6   // Left Motor Direction 1
#define L_IN2 7   // Left Motor Direction 2
#define R_PWM 10  // Right Motor Speed
#define R_IN3 8   // Right Motor Direction 1
#define R_IN4 9   // Right Motor Direction 2

// --- SAFETY ---
unsigned long last_cmd_time = 0;
const unsigned long TIMEOUT_MS = 500; // Stop if no ROS 2 msg for 0.5s

void setup() {
  Serial.begin(115200); // MUST match URDF baud_rate
  
  pinMode(L_PWM, OUTPUT); pinMode(L_IN1, OUTPUT); pinMode(L_IN2, OUTPUT);
  pinMode(R_PWM, OUTPUT); pinMode(R_IN3, OUTPUT); pinMode(R_IN4, OUTPUT);
  
  stopMotors();
}

void loop() {
  if (Serial.available() > 0) {
    char start_char = Serial.read();
    
    // Check for our 'm' (motor) command
    if (start_char == 'm') {
      int left_pwm = Serial.parseInt();
      int right_pwm = Serial.parseInt();
      
      driveMotors(left_pwm, right_pwm);
      last_cmd_time = millis();
    }
  }

  // Safety Timeout
  if (millis() - last_cmd_time > TIMEOUT_MS) {
    stopMotors();
  }
}

void driveMotors(int l, int r) {
  // Left Motor
  if (l > 0) {
    digitalWrite(L_IN1, HIGH); digitalWrite(L_IN2, LOW);
  } else {
    digitalWrite(L_IN1, LOW); digitalWrite(L_IN2, HIGH);
  }
  analogWrite(L_PWM, abs(l));

  // Right Motor
  if (r > 0) {
    digitalWrite(R_IN3, HIGH); digitalWrite(R_IN4, LOW);
  } else {
    digitalWrite(R_IN3, LOW); digitalWrite(R_IN4, HIGH);
  }
  analogWrite(R_PWM, abs(r));
}

void stopMotors() {
  analogWrite(L_PWM, 0); analogWrite(R_PWM, 0);
}