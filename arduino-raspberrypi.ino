#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <Arduino.h>

// Temperatures Pin Configuration

#define DHTPIN1 2     // what pin we're connected to
#define DHTPIN2 3

#define DHTTYPE1 DHT22   // DHT 22  (AM2302)
#define DHTTYPE2 DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN1, DHTTYPE1); //// Initialize DHT sensor for normal 16mhz Arduino
DHT dht2(DHTPIN2, DHTTYPE2);

// Luminosity Configuration
float lux;
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void configureSensor(void) {
  tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */
}

// Fan Heater Configuration
#define FAN 4
#define HEATER 5

String fanStatus() {
  if (FAN == HIGH) {
     return "off";
  } else {
    return "on";
  }
}

String heaterStatus() {
  if (HEATER == HIGH) {
     return "off";
  } else {
    return "on";
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting"); 
  // Initialise the luminosity sensor
  if(!tsl.begin())  {
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
  }
  configureSensor(); 
}

void loop() {
  // Green House Status
  if (Serial.readString() == "status") {
    sensors_event_t event;
    tsl.getEvent(&event); 
    if (event.light) {
      lux = event.light;
    } else {
      lux = 0;
    }
    
    String message;
    message = message + dht.readTemperature() + ":";
    message = message + dht2.readTemperature() + ":";
    message = message + dht2.readHumidity() + ":";
    message = message + dht2.readHumidity() + ":";
    message = message + lux + ":";
    message = message + fanStatus() + ":";
    message = message + heaterStatus() + ":";
    message = message + analogRead(0) + ":";
    message = message + analogRead(1) + ":";
    message = message + analogRead(2) + ":";
    message = message + analogRead(3) + ":";
    message = message + analogRead(4) + ":";
    message = message + analogRead(5) + ":";
    message = message + analogRead(6) + ":";
    message = message + analogRead(7) + ":";
    message = message + analogRead(8) + ":";
    message = message + analogRead(9) + ":";
    message = message + analogRead(10) + ":";
    
    Serial.println(message);
  }
  // Fan Actions
  if (Serial.readString() == "fan-on") {
    digitalWrite(FAN, LOW); 
  }

  if (Serial.readString() == "fan-off") {
    digitalWrite(FAN, HIGH); 
  }
  // Heater Actions
  if (Serial.readString() == "heater-on") {
    digitalWrite(HEATER, LOW); 
  }

  if (Serial.readString() == "heater-off") {
    digitalWrite(HEATER, HIGH); 
  }
}
