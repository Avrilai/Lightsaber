#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();
SoftwareSerial mySerial(10, 11); // RX, TX
const int ledPin = 6;


void setup() {
  mma.begin();

  Serial.begin(9600);
  mySerial.begin(9600);
  mp3_set_serial(mySerial);
  delay(1);
  mp3_set_volume(25);

  mma.setRange(MMA8451_RANGE_2_G);
  mp3_play(1);
  delay(500);

  Serial.print("52");
}

void loop() {
  /* Get a new sensor event */
  sensors_event_t event;
  mma.getEvent(&event);
  /* Display the results (acceleration is measured in m/s^2) */
  //  Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
  //  Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
  //  Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
  //  Serial.println("m/s^2 ");
  //  delay(1000);

  float vol = clamp(abs(event.acceleration.x) + 25, 25, 30);
  Serial.println(vol);
  mp3_set_volume(vol);
  if (abs(event.acceleration.x) > 15 && abs(event.acceleration.y) > 15) {
    mp3_stop();
    mp3_set_volume(30);
    delay(50);
    mp3_play(3);
    Serial.println("crash");
    delay(1000);
    mp3_set_volume(25);
  } else {
    boolean play_state = digitalRead(3);
    if (play_state == HIGH) {
      mp3_play(2);
    }
  }
}

float clamp(float x, float a, float b) {
  if (x < a) return a;
  if (x > b) return b;
  return x;
}
