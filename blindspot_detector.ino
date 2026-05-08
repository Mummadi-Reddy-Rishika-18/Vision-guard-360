EXCAVATOR CODE:
// ==========================================================
// 360° EXCAVATOR BLIND-SPOT DETECTION SYSTEM
//
// Arduino UNO
// 4 HC-SR04 Sensors
// 16 LED NeoPixel Ring
// Dynamic Smart Buzzer
//
// RANGE SETTINGS:
// 0–6 cm   -> RED ALERT
// 6–12 cm  -> YELLOW ALERT
// 12–17 cm -> LOW WARNING
// >17 cm   -> NO DETECTION
// ==========================================================

#include <Adafruit_NeoPixel.h>
// ==========================================================
// SENSOR PINS
// ==========================================================
// FRONT SENSOR
#define trigFront 2
#define echoFront 3
// BACK SENSOR
#define trigBack 4
#define echoBack 5
// LEFT SENSOR
#define trigLeft 6
#define echoLeft 7
// RIGHT SENSOR
#define trigRight 8
#define echoRight 9
// ==========================================================
// OUTPUT DEVICES
// ==========================================================
// BUZZER
#define buzzerPin 10
// 16 LED RING
#define ledPin 11
#define NUM_LEDS 16
Adafruit_NeoPixel ring(NUM_LEDS, ledPin, NEO_GRB + NEO_KHZ800);
// ==========================================================
// VARIABLES
// ==========================================================
long duration;
int frontDistance;
int backDistance;
int leftDistance;
int rightDistance;

int nearestDistance;
// ==========================================================
// DISTANCE FUNCTION
// ==========================================================
int getDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 30000);
  // NO ECHO
  if (duration == 0)
  {
    return 999;
  }
  int distance = duration * 0.034 / 2;
  // FILTER INVALID VALUES
  if (distance <= 1 || distance > 17)
  {
    return 999;
  }
  return distance;
}
// ==========================================================
// SETUP
// ==========================================================
void setup()
{
  Serial.begin(9600);
  // FRONT
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  // BACK
  pinMode(trigBack, OUTPUT);
  pinMode(echoBack, INPUT);
  // LEFT
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  // RIGHT
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
  // BUZZER
  pinMode(buzzerPin, OUTPUT);
  // LED RING
  ring.begin();
  ring.show();
  Serial.println("360 Blind Spot System Started");
}
// ==========================================================
// LOOP
// ==========================================================
void loop()
{
  // ======================================================
  // READ SENSOR DISTANCES
  // ======================================================
  frontDistance = getDistance(trigFront, echoFront);
  delay(25);
  backDistance = getDistance(trigBack, echoBack);
  delay(25);
  leftDistance = getDistance(trigLeft, echoLeft);
  delay(25);
  rightDistance = getDistance(trigRight, echoRight);
  delay(25);
  // ======================================================
  // FIND NEAREST OBJECT
  // ======================================================
  nearestDistance = 999;
  if (frontDistance < nearestDistance)
    nearestDistance = frontDistance;
  if (backDistance < nearestDistance)
    nearestDistance = backDistance;
  if (leftDistance < nearestDistance)
    nearestDistance = leftDistance;
  if (rightDistance < nearestDistance)
    nearestDistance = rightDistance;
  // ======================================================
  // SEND DATA TO LAPTOP
  // ======================================================
  Serial.print(frontDistance);
  Serial.print(",");
  Serial.print(backDistance);
  Serial.print(",");
  Serial.print(leftDistance);
  Serial.print(",");
  Serial.println(rightDistance);
  // ======================================================
  // CLEAR LED RING
  // ======================================================
  ring.clear();
  // ======================================================
  // FRONT LEDs (0-3)
  // ======================================================
  if (frontDistance != 999)
  {
    for (int i = 0; i <= 3; i++)
    {
      // RED ALERT
      if (frontDistance <= 6)
      {
        ring.setPixelColor(i, ring.Color(255, 0, 0));
      }
      // YELLOW ALERT
      else if (frontDistance <= 12)
      {
        ring.setPixelColor(i, ring.Color(255, 255, 0));
      }
      // LOW WARNING
      else if (frontDistance <= 17)
      {
        ring.setPixelColor(i, ring.Color(255, 140, 0));
      }
    }
  }
  // ======================================================
  // RIGHT LEDs (4-7)
  // ======================================================
  if (rightDistance != 999)
  {
    for (int i = 4; i <= 7; i++)
    {
      if (rightDistance <= 6)
      {
        ring.setPixelColor(i, ring.Color(255, 0, 0));
      }
      else if (rightDistance <= 12)
      {
        ring.setPixelColor(i, ring.Color(255, 255, 0));
      }
      else if (rightDistance <= 17)
      {
        ring.setPixelColor(i, ring.Color(255, 140, 0));
      }
    }
  }
  // ======================================================
  // BACK LEDs (8-11)
  // ======================================================
  if (backDistance != 999)
  {
    for (int i = 8; i <= 11; i++)
    {
      if (backDistance <= 6)
      {
        ring.setPixelColor(i, ring.Color(255, 0, 0));
      }
      else if (backDistance <= 12)
      {
        ring.setPixelColor(i, ring.Color(255, 255, 0));
      }
      else if (backDistance <= 17)
      {
        ring.setPixelColor(i, ring.Color(255, 140, 0));
      }
    }
  }
  // ======================================================
  // LEFT LEDs (12-15)
  // ======================================================
  if (leftDistance != 999)
  {
    for (int i = 12; i <= 15; i++)
    {
      if (leftDistance <= 6)
      {
        ring.setPixelColor(i, ring.Color(255, 0, 0));
      }
      else if (leftDistance <= 12)
      {
        ring.setPixelColor(i, ring.Color(255, 255, 0));
      }
      else if (leftDistance <= 17)
      {
        ring.setPixelColor(i, ring.Color(255, 140, 0));
      }
    }
  }
  // ======================================================
  // NO OBJECT DETECTED
  // ======================================================
  if (nearestDistance > 17 || nearestDistance == 999)
  {
    noTone(buzzerPin);
    ring.show();
    delay(20);
    return;
  }
  // ======================================================
  // DYNAMIC WARNING SYSTEM
  // ======================================================
  int beepDelay = map(nearestDistance, 1, 17, 40, 700);
  beepDelay = constrain(beepDelay, 40, 700);
  int toneFrequency = map(nearestDistance, 1, 17, 3200, 700);
  toneFrequency = constrain(toneFrequency, 700, 3200);
  // ======================================================
  // CRITICAL WARNING
  // ======================================================
  if (nearestDistance <= 6)
  {
    tone(buzzerPin, 3200);
    delay(25);
    noTone(buzzerPin);
    delay(10);
  }
  // ======================================================
  // NORMAL WARNING
  // ======================================================
  else
  {
    tone(buzzerPin, toneFrequency);
    delay(beepDelay);
    noTone(buzzerPin);
    delay(beepDelay);
  }
  // ======================================================
  // UPDATE LED RING
  // ======================================================
  ring.show();
  delay(20);
}


