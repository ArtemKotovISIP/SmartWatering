#include <QuadDisplay2.h>
#include <TroykaLight.h>
#include <TroykaDHT.h>
#include <ArduinoJson.h>

#define BUTTON A0
#define TEMPERATURE A1
#define HUMIDITY A2
#define LIGHT A3
#define LED A4
#define PUMP A5
#define INDICATOR 8

QuadDisplay quadDisplay(INDICATOR);
TroykaLight light(LIGHT);
DHT dht(TEMPERATURE, DHT11);

int index = 1;
int change = 0;
int count = 5;
int button = 0;
int watch = 0;

void updateSensors() {
  light.read();
  dht.read();
}

int readLight() {
  return light.getLightLux();
}

int readdhtTemperature() {
  return dht.getTemperatureC();
}

int readdhtHumidity() {
  return dht.getHumidity();
}

int readHumidity() {
  return analogRead(HUMIDITY);
}

void updateLed(bool value) {
  digitalWrite(LED, value);
}

void updatePump(bool value) {
  digitalWrite(PUMP, value);
}

void illumination() {
  if (readLight() < 100) {
    updateLed(HIGH);
  } else {
    updateLed(LOW);
  }
}

void moisten() {
  if (readHumidity() < 30) {
    updatePump(HIGH);
  } else {
    updatePump(LOW);
  }
}

void updateQuadDisplay(int index) {
  switch (index) {
    case 1:
      if (change == 0) {
        quadDisplay.displayDigits(QD_h, QD_o, QD_u, QD_r);
      } else {
        quadDisplay.displayInt(watch);
      }
      break;
    
    case 2:
      if (change == 0) {
        quadDisplay.displayDigits(QD_t, QD_NONE, QD_NONE, QD_NONE);
      } else {
        quadDisplay.displayInt(readdhtTemperature());
      }
      break;
      
    case 3:
      if (change == 0) {
        quadDisplay.displayDigits(QD_h, QD_NONE, QD_NONE, QD_NONE);
      } else {
        quadDisplay.displayInt(readdhtHumidity());
      }
      break;

    case 4:
      if (change == 0) {
        quadDisplay.displayDigits(QD_d, QD_h, QD_NONE, QD_NONE);
      } else {
        quadDisplay.displayInt(readHumidity());
      }
      break;

    case 5:
      if (change == 0) {
        quadDisplay.displayDigits(QD_L, QD_NONE, QD_NONE, QD_NONE);
      } else {
        quadDisplay.displayInt(readLight());
      }
      break;
  }
}

void checkButton() {
  if (digitalRead(BUTTON) == 0) {
    if (button == 0) {
      button = 1;
      index += 1;
      if (index > count) {
        index = 1;
      }
      change = 0;
      updateQuadDisplay(index);
    }
  } else {
    if (button == 1) {
      button = 0;
    }
  }
}

void submit() {
  StaticJsonDocument<64> output;
  output["Temperature"] = readdhtTemperature();
  output["Humidity"] = readdhtHumidity();
  output["DirtHumidity"] = readHumidity();
  output["Light"] = readLight();
  serializeJson(output, Serial);
}

void broadcast() {
  if (Serial.available() > 0) {
    StaticJsonDocument<64> input;
    String record = Serial.readStringUntil('\n');
    DeserializationError error = deserializeJson(input, record);
    if (error) return;
    watch = input["watch"];
    if (input["get"] == true) {
      submit();
    }
  }
}

void setup() {
  quadDisplay.begin();
  dht.begin();
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(PUMP, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  updateSensors();
  updateQuadDisplay(index);
  if (change == 0) change = 1;
  illumination();
  moisten();
  broadcast();
  delay(1000);
}

void yield() {
  checkButton();
}
