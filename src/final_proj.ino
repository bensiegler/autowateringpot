#include "string.h"
#include "PietteTech_DHT.h"
#include <cstring>
#include "timers/RepeatableTrigger.h"

using namespace Timing;

/*
 * Project Final Project: Auto Watering Pot
 * Description: This class defines the core functionality of all sensors
 * and pumps on the pot. 
 * Author: Benjamin Siegler
 * Date: May 8th 2022
 */

#define DEFAULT_PUMP_POWER 150
#define PUMP_PWMA_PIN D2
#define PUMP_AI2_PIN D3
#define PUMP_AI1_PIN D4

#define PHOTORESISTOR_PIN A4

#define SOIL_MOISTURE_UPPER_PWR D7
#define SOIL_MOISTURE_UPPER_SIG A1
#define SOIL_MOISTURE_LOWER_PWR D8
#define SOIL_MOISTURE_LOWER_SIG A2

#define DHT_SENSOR_INPUT_PIN D5
#define DHTTYPE DHT11

#define DATA_UPDATE_DELAY 15000

PietteTech_DHT dht(DHT_SENSOR_INPUT_PIN, DHTTYPE);
RepeatableTrigger dataReadTrigger(DATA_UPDATE_DELAY, &readData, "reading data");

//abstract method definitions needed for Particle.function call
int waterToMoistureLevel(String waterToMoistureLevel);
int togglePump(String onOff);


void setup()
{
  Particle.function("waterToMoistureLevel", waterToMoistureLevel);
  Particle.function("togglePump", togglePump);

  // init pump pins
  pinMode(PUMP_PWMA_PIN, OUTPUT);
  pinMode(PUMP_AI2_PIN, OUTPUT);
  pinMode(PUMP_AI1_PIN, OUTPUT);

  // set pump "direction"
  digitalWrite(PUMP_AI1_PIN, LOW);
  digitalWrite(PUMP_AI2_PIN, HIGH);

  // init moisture sensor pins
  pinMode(SOIL_MOISTURE_UPPER_PWR, OUTPUT);
  pinMode(SOIL_MOISTURE_UPPER_SIG, INPUT);
  digitalWrite(SOIL_MOISTURE_UPPER_PWR, LOW);

  // init moisture sensor pins
  pinMode(SOIL_MOISTURE_LOWER_PWR, OUTPUT);
  pinMode(SOIL_MOISTURE_LOWER_SIG, INPUT);
  digitalWrite(SOIL_MOISTURE_LOWER_PWR, LOW);

  pinMode(DHT_SENSOR_INPUT_PIN, INPUT);
  dht.begin();
}

int pumpPWM = -1;
int temperature = -1;
int ambientHumidity = -1;
int dewPoint = -1;
int moistureUpperLevel = -1;
int moistureLowerLevel = -1;
float voltage = -1;
int ambientLight = -1;

void loop()
{
  dataReadTrigger.check();
}

void readData()
{
  voltage = analogRead(BATT) * 0.0011224;

  moistureUpperLevel = readUpperSoilMoisture();
  moistureLowerLevel = readLowerSoilMoisture();

  ambientLight = analogRead(PHOTORESISTOR_PIN);

  int result = dht.acquireAndWait(1000);
  if (result == DHTLIB_OK)
  {
    ambientHumidity = dht.getHumidity();
    temperature = dht.getFahrenheit();
    dewPoint = dht.getDewPoint();
  }
  else if (result < 0)
  {
    //report DHT Error to dashboard
    Particle.publish("createLosantEvent", "{\"name\":\"DHT Error\",\"dashboard\":\"pot dashboard\",\"severity\":\"warning\",\"message\":\"DHT ERROR!\"}");
  }
  pushData();
}

void pushData()
{
  String JSON_Data = "{\"moistureLowerLevel\":" + String(moistureLowerLevel) + "," +
                     "\"moistureUpperLevel\":" + String(moistureUpperLevel) + "," +
                     "\"ambientLight\":" + String(ambientLight) + "," +
                     "\"dewPoint\":" + String(dewPoint) + "," +
                     "\"temperature\":" + String(temperature) + "," +
                     "\"ambientHumidity\":" + String(ambientHumidity) + "," +
                     "\"batteryLevel\":" + String(voltage) + "," +
                     "\"pumpPower\":" + String(pumpPWM) + "}";

  //push the above JSON to Particle/Losant Dashboard
  Particle.publish("pushPotData", JSON_Data);
}

int togglePump(String onOff)
{
  //if bool received was true, pump needs to be turned on
  if (strncasecmp(onOff.c_str(), "true", 5) == 0)
  {
    pumpPWM = DEFAULT_PUMP_POWER;
    analogWrite(PUMP_PWMA_PIN, DEFAULT_PUMP_POWER);
  }
  else
  {
    pumpPWM = 0;
    analogWrite(PUMP_PWMA_PIN, 0);
  }
  return 0;
}

int readUpperSoilMoisture()
{
  int upper;
  //turn on power to sensor
  digitalWrite(SOIL_MOISTURE_UPPER_PWR, HIGH);
  delay(200);
  //make reading after waiting for boot
  upper = analogRead(SOIL_MOISTURE_UPPER_SIG);
  //turn off power to sensor
  digitalWrite(SOIL_MOISTURE_UPPER_PWR, LOW);
  return upper;
}

int readLowerSoilMoisture()
{
  int lower;
  //turn on power to sensor
  digitalWrite(SOIL_MOISTURE_LOWER_PWR, HIGH);
  delay(200);
  //make measurement after waiting
  lower = analogRead(SOIL_MOISTURE_LOWER_SIG);
  //turn off power to sensor
  digitalWrite(SOIL_MOISTURE_LOWER_PWR, LOW);
  return lower;
}
