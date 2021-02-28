#include "DHT.h"

#define in 8
#define DHTTYPE DHT11

DHT dht(in, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxxx test"));
  dht.begin();


}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C \n"));
  delay(2000);
}
