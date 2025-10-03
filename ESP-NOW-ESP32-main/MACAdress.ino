#include <WiFi.h>

void setup() {
 // configurada a taxa de transferência em 115200 bits por segundo para a transmissão serial
 Serial.begin(115200); 
 // configurar o WIFi para o Modo de estação WiFi
 WiFi.mode(WIFI_MODE_STA); 
 Serial.print("Endereço MAC: ");
 // retorna o endereço MAC do dispositivo
 Serial.println(WiFi.macAddress()); 
 // loop infinito
 while(1);
 
}
void loop() {} 