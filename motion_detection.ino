
#include Adafruit_MPU6050.h
#include Adafruit_Sensor.h
#include Wire.h

 ===== User Settings =====
const int MOTION_THRESHOLD = 10;            Number of movements to trigger walking alert
const unsigned long RESET_TIME = 10000;     10 seconds of no movement = auto reset
const unsigned long DEBOUNCE_DELAY = 200;   Debounce time for motion detection (ms)
const unsigned long BUTTON_DEBOUNCE = 50;   Debounce time for reset button (ms)

const int BUZZER_PIN = 5;
const int BUTTON_PIN = 6;

 ===== State Variables =====
Adafruit_MPU6050 mpu;

int motionCounter = 0;
unsigned long lastMotionTime = 0;
unsigned long lastDetectionTime = 0;
unsigned long lastButtonTime = 0;
bool isWalking = false;

 ===== Setup =====
void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);

  Serial.println(F(========================================));
  Serial.println(F(  Najiana — Sleepwalking Detector));
  Serial.println(F(========================================));
  Serial.println(F(Initializing...));

   Initialize MPU6050 sensor
  if (!mpu.begin()) {
    Serial.println(F(ERROR MPU6050 not found!));
    Serial.println(F(Check wiring (SDA=A4, SCL=A5, INT=D2)));
    while (1) delay(10);
  }

  Serial.println(F(MPU6050 Ready!));

   ===== Motion detection settings =====
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);

   Threshold 1 = very sensitive (good for testingdemo).
   For real sleep use, raise to 3–5 to avoid false positives
   from breathing or normal position changes.
  mpu.setMotionDetectionThreshold(1);

  mpu.setMotionDetectionDuration(20);   20ms confirmed motion
  mpu.setInterruptPinLatch(true);       Latch interrupt until cleared
  mpu.setMotionInterrupt(true);

   Pin configuration
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(BUZZER_PIN, LOW);

  delay(100);
  Serial.println(F(System ready. Waiting for motion...));
  Serial.println(F(----------------------------------------));
}

 ===== Main Loop =====
void loop() {
  handleMotionDetection();
  handleButtonReset();
  handleAutoReset();
}

 ===== Motion Detection Handler (Non-blocking) =====
void handleMotionDetection() {
   Check if motion interrupt is triggered
  if (!mpu.getMotionInterruptStatus()) return;

   Debounce ignore detections that come too fast
  if (millis() - lastDetectionTime  DEBOUNCE_DELAY) return;
  lastDetectionTime = millis();

   If alarm is already active, ignore new movements
  if (isWalking) {
    Serial.println(F(Alarm active. Press button to reset.));
    return;
  }

   Valid motion detected
  motionCounter++;
  lastMotionTime = millis();

  Serial.print(F(Movement Detected - ));
  Serial.println(motionCounter);

   Check if threshold is reached and button is not pressed
   (INPUT_PULLUP HIGH = not pressed, LOW = pressed)
  if (motionCounter = MOTION_THRESHOLD && digitalRead(BUTTON_PIN) == HIGH) {
    isWalking = true;
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println(F( ALARM PERSON IS WALKING! ));
  }
}

 ===== Button Reset Handler (with debounce) =====
void handleButtonReset() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (millis() - lastButtonTime  BUTTON_DEBOUNCE) {
      lastButtonTime = millis();
      resetSystem(F(Reset by button));
    }
  }
}

 ===== Auto Reset Handler =====
 Auto-reset only works when the alarm is NOT active.
 Once the alarm is on, only the button can stop it (safety
 we don't want to stop the alarm while the person is still walking).
void handleAutoReset() {
  if (!isWalking && motionCounter  0 && motionCounter  MOTION_THRESHOLD) {
    if (millis() - lastMotionTime = RESET_TIME) {
      resetSystem(F(Auto-reset (no movement)));
    }
  }
}

 ===== System Reset Function =====
void resetSystem(const char reason) {
  motionCounter = 0;
  isWalking = false;
  lastDetectionTime = 0;        Allow next detection immediately
  digitalWrite(BUZZER_PIN, LOW);
  Serial.print(F(Reset ));
  Serial.println(reason);
  Serial.println(F(----------------------------------------));
}