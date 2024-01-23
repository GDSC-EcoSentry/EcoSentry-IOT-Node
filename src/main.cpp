#include <Arduino.h>
#include <RadioLib.h>
#include "DHT.h"

#define RAIN_PIN A0
#define SOIL_PIN A1
#define DHT22_PIN 2

float tempRead();
float humidRead();
int rainRead();
int moistRead();
void radioError(int);

DHT dht22(DHT22_PIN, DHT22);

// nRF24 has the following connections:
// CS pin:    10
// IRQ pin:   9
// CE pin:    8
nRF24 radio = new Module(10, 9, 8);

// Buffer to store received messages
char msg[60];


void setup() {
  Serial.begin(9600);
  dht22.begin(); // initialize the DHT22 sensor

  // initialize nRF24 with default settings
  Serial.print(F("[nRF24] Initializing ... "));
  int state = radio.begin();
  if(state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }

  // set transmit address
  // NOTE: address width in bytes MUST be equal to the
  //       width set in begin() or setAddressWidth()
  //       methods (5 by default)
  byte addr[] = {0x01, 0x23, 0x45, 0x67, 0x89};
  Serial.print(F("[nRF24] Setting transmit pipe ... "));
  state = radio.setTransmitPipe(addr);
  if(state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }
}

void loop() {
  
  float temp = tempRead();
  float humidity = humidRead();
  int rain = rainRead();
  int moisture = moistRead();

  String message = String(temp, 2) + "," + 
                 String(humidity, 2) + "," + 
                 String(rain) + "," +
                 String(moisture);

  message.toCharArray(msg, sizeof(msg));
  Serial.print("Sending message: "); Serial.println(msg);
  int radio_code = radio.transmit(msg);
  radioError(radio_code);

  // wait a few seconds between measurements.
  delay(5000);
}

float tempRead() {
  // read temperature as Celsius
  float temp = dht22.readTemperature();

  // check if any reads failed
  if (isnan(temp)) {
    Serial.println("Failed to temp from DHT22 sensor!");
    return 0;
  } else {
    return temp;
  }
}

float humidRead() {
  // read humidity
  float humi = dht22.readHumidity();

  // check if any reads failed
  if (isnan(humi)) {
    Serial.println("Failed to humidity from DHT22 sensor!");
    return 0;
  } else {
    return humi;
  }
}

int rainRead() {
  int sensorValue = analogRead(RAIN_PIN);
  return 1023 - sensorValue;
}

int moistRead() {
  int sensorValue = 1023 - analogRead(SOIL_PIN);

  // clamp and map moisture 
  if (sensorValue < 520) sensorValue = 520;
  if (sensorValue > 820) sensorValue = 820;

  sensorValue = map(sensorValue, 520, 820, 0, 100);

  return sensorValue; // inverted because soil moisture sensor is weird
}

void radioError(int state) {
  if (state == RADIOLIB_ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("success!"));

  } else if (state == RADIOLIB_ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 32 bytes
    Serial.println(F("too long!"));

  } else if (state == RADIOLIB_ERR_ACK_NOT_RECEIVED) {
    // acknowledge from destination module
    // was not received within 15 retries
    Serial.println(F("ACK not received!"));

  } else if (state == RADIOLIB_ERR_TX_TIMEOUT) {
    // timed out while transmitting
    Serial.println(F("timeout!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }
}