#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

#define AMARELO 27
#define VERMELHO 26
#define VERDE 25

char LB;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32");
  Serial.println("Dispositivo iniciado");

  pinMode(AMARELO, OUTPUT);
  pinMode(VERMELHO, OUTPUT);
  pinMode(VERDE, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {  // só lê se tiver algo
    LB = (char)SerialBT.read();

    if (LB == 'Y') {
      digitalWrite(AMARELO, !digitalRead(AMARELO));
    }  
              if (LB == 'LOWY') {
              digitalWrite(AMARELO, LOW);
            }  
    if (LB == 'R') {
      digitalWrite(VERMELHO, !digitalRead(VERMELHO));
    }
             if (LB == 'LOWR') {
            digitalWrite(VERMELHO, LOW);
          }
    if (LB == 'G') {
      digitalWrite(VERDE, !digitalRead(VERDE));
    }
            if (LB == 'LOWG') {
              digitalWrite(VERDE, LOW);
            }
  }
  delay(200);
}
