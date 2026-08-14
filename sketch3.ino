#include <Arduino.h>

// Pin Definitions
#define TRIG_PIN 5
#define ECHO_PIN 18

// Speed of sound in cm/uS
#define SOUND_SPEED 0.0343

long duration;
float distanceCm;

unsigned long lastTime = 0;
const unsigned long timerDelay = 1000;

void setup() {
  Serial.begin(115200);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.println("==========================================");
  Serial.println(" Cloud-Connected Security Node Started ");
  Serial.println("==========================================");
}

void loop() {
  if (millis() - lastTime >= timerDelay) {
    lastTime = millis();

    // Trigger pulse creation
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    // Read pulse echo time
    duration = pulseIn(ECHO_PIN, HIGH);
    distanceCm = (duration * SOUND_SPEED) / 2.0;
    
    // Output distance to Serial Monitor
    Serial.print("Sensor Telemetry -> Distance: ");
    Serial.print(distanceCm);
    Serial.println(" cm");

    // Threshold check
    if (distanceCm < 50.0 && distanceCm > 0) {
      Serial.println("⚠️ INTRUSION DETECTED! Object within boundary ( < 50 cm )");
    }
  }
}
