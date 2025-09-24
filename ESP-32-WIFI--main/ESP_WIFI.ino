#include <WiFi.h>
#define led 2
#define bnt_1 18
const char *ssid = "OP 02";// insira o nome da sua rede WiFi
const char *pw = "onepiece";// insira a senha da sua rede WiFi

WiFiServer server(80);
int flag_bnt1 = 0;

// Debounce do botão
int deBounce(int estado, int pino) {
  int estadoAtual = digitalRead(pino);
  if (estado != estadoAtual) {
    delay(5);
    estadoAtual = digitalRead(pino);
  }
  return estadoAtual;
}

void setup() {
  pinMode(led, OUTPUT);
  pinMode(bnt_1, INPUT_PULLUP);
  Serial.begin(115200);

  WiFi.begin(ssid, pw);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println("Conectado ao WiFi");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

if (client) {
  Serial.println("Cliente conectado!");

  while (client.connected()) {
    if (deBounce(flag_bnt1, bnt_1) == HIGH && flag_bnt1 == 0) {
      flag_bnt1 = 1;
      Serial.println("Botão pressionado, enviando comando...");
      client.print("comando PULAR\n");
      digitalWrite(led, HIGH);
    }

    // Reset da flag quando botão solto (para novo envio)
    if (deBounce(flag_bnt1, bnt_1) == LOW && flag_bnt1 == 1) {
      flag_bnt1 = 0;
      digitalWrite(led, LOW);
    }

    delay(20);
  }

  client.stop(); // Encerra conexão quando cliente desconectar
  Serial.println("Cliente desconectado.");
}}
