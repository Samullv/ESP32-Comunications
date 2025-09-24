#include <DHT.h>

#define DHTPIN 4       // tente trocar para GPIO 4 ou 23
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println("Testando DHT11...");
}

void loop() {
  delay(2000); // espera pelo sensor

  float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println("Falha ao ler o DHT11!");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" °C");
}
