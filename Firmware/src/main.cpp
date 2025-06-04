#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "Quarto_2G";
const char *password = "24131313";
const char *mqtt_server = "192.168.1.102";

WiFiClient espClient;
PubSubClient client(espClient);

#define BUTTON_PIN 14
#define LED_PIN_GREEN 27
#define LED_PIN_YELLOW 26
#define LED_PIN_RED 25

int clickCount = 1;
unsigned long lastClickTime = 0;
const unsigned long clickDelay = 1000;

void setup_wifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi");
}

void reconnect()
{
  while (!client.connected())
  {
    if (client.connect("ESPClient"))
    {
      Serial.println("Conectado ao broker MQTT");
    }
    else
    {
      Serial.println("erro no broker");
      delay(1000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN_GREEN, OUTPUT);  // Define o pino como saída
  pinMode(LED_PIN_RED, OUTPUT);    // Define o pino como saída
  pinMode(LED_PIN_YELLOW, OUTPUT); // Define o pino como saída
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  randomSeed(esp_random()); // 🔧 Correção aqui
}

void loop()
{
  if (!client.connected())
    reconnect();
  client.loop();

  static bool lastButtonState = HIGH;
  bool buttonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && buttonState == LOW)
  {
    clickCount++;

    if (clickCount > 3)
      clickCount = 1;

    lastClickTime = millis();
  }
  lastButtonState = buttonState;

  if (clickCount > 0 && millis() - lastClickTime > clickDelay)
  {
    int valorAleatorio = 0;

    if (clickCount == 1)
    {
      valorAleatorio = random(20, 31);
      digitalWrite(LED_PIN_GREEN, HIGH);
      digitalWrite(LED_PIN_RED, LOW);
      digitalWrite(LED_PIN_YELLOW, LOW);
    }
    else if (clickCount == 2)
    {
      valorAleatorio = random(31, 76);
      digitalWrite(LED_PIN_YELLOW, HIGH);
      digitalWrite(LED_PIN_RED, LOW);
      digitalWrite(LED_PIN_GREEN, LOW);
    }
    else
    {
      valorAleatorio = random(76, 101);
      digitalWrite(LED_PIN_RED, HIGH);
      digitalWrite(LED_PIN_YELLOW, LOW);
      digitalWrite(LED_PIN_GREEN, LOW);
    }

    String mensagem = String(valorAleatorio);
    client.publish("botao/topico", mensagem.c_str());
    Serial.println("Enviado: " + mensagem);

    delay(300);
  }
}
