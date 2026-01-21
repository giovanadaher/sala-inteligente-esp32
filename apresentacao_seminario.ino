#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ESP32Servo.h>

// Credenciais da rede criada pelo ESP32
const char* apssid = "ESP32_Lock";
const char* appassword = "12345678";

// DHT11
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LEDs
const int led1 = 2;
const int led2 = 4;
const int led3 = 23;

// Servo
Servo myServo;
const int servoPin = 22;

// Web server
AsyncWebServer server(80);

// HTML
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>ESP32 Lock+Lamps+DHT11</title>
<meta name="viewport" content="width=device-width, initial-scale=1"><style>
body{font-family:Arial;text-align:center;margin:20px;} .btn{padding:10px 20px;margin:5px;font-size:1em;}
</style></head>
<body>
<h1>ESP32 Automação</h1>
<div><strong>Temp:</strong> <span id="temp">--</span> °C</div>
<div><strong>Hum:</strong> <span id="hum">--</span> %</div>
<h2>Lâmpadas</h2>
<button class="btn" onclick="toggleLed(1)">Luz 1</button>
<button class="btn" onclick="toggleLed(2)">Luz 2</button>
<button class="btn" onclick="toggleLed(3)">Luz 3</button>
<h2>Fechadura</h2>
<button class="btn" onclick="toggleLock()">Abrir/Fechar</button>
<script>
setInterval(()=>{fetch('/temp').then(r=>r.text()).then(v=>document.getElementById('temp').innerText=v);
                   fetch('/hum').then(r=>r.text()).then(v=>document.getElementById('hum').innerText=v);},2000);
function toggleLed(n){fetch(`/led?num=${n}`);}
function toggleLock(){fetch('/door');}
</script>
</body></html>
)rawliteral";

void setup(){
  Serial.begin(115200);
  dht.begin();

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  myServo.attach(servoPin);
  myServo.write(0);

  // Configurar AP
  WiFi.mode(WIFI_AP);
  WiFi.softAP(apssid, appassword);
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  // Rotas HTTP
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send_P(200, "text/html", index_html);
  });
  server.on("/temp", HTTP_GET, [](AsyncWebServerRequest *req){
    float t = dht.readTemperature();
    req->send(200, "text/plain", isnan(t) ? "Erro" : String(t));
  });
  server.on("/hum", HTTP_GET, [](AsyncWebServerRequest *req){
    float h = dht.readHumidity();
    req->send(200, "text/plain", isnan(h) ? "Erro" : String(h));
  });
  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *req){
    int n = req->getParam("num")->value().toInt();
    int pin = (n==1?led1:(n==2?led2:led3));
    digitalWrite(pin, !digitalRead(pin));
    req->send(200, "text/plain", "OK");
  });
  server.on("/door", HTTP_GET, [](AsyncWebServerRequest *req){
    static bool open = false;
    myServo.write(open ? 0 : 90);
    open = !open;
    req->send(200, "text/plain", "OK");
  });
  server.begin();
}

void loop(){
  // tudo é feito via callbacks
}
