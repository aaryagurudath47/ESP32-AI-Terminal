// ESP32 AI Terminal - WORKING VERSION
// Uses OpenRouter API
// Next step: portfolio documentation (screenshots + case study)
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// ===== WIFI =====
const char* ssid = "Your_wifi_ID";
const char* password = "Your_wifi_Password";

// ===== API KEY =====
const char* apiKey = "Your_api_key";

// ===== PASSWORD FOR ACCESS =====
const char* accessPassword = "your_access_password";

WebServer server(80);

// ===== MEMORY =====
String lastUserMsg = "";

// ===== WEB PAGE =====
String webpage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<style>
body {
  background:#0a0a0a;
  color:#00ffcc;
  font-family:monospace;
}
.chat {
  max-width:600px;
  margin:auto;
}
.msg {
  padding:10px;
  margin:5px;
  border-radius:10px;
}
.user {
  background:#003333;
  text-align:right;
}
.bot {
  background:#001a1a;
}
</style>
</head>

<body>

<div id="login">
  <h3>Enter Password</h3>
  <input id="pass" type="password">
  <button onclick="checkPass()">Enter</button>
</div>

<div id="chatUI" style="display:none;">
  <h2>ESP32 AI Terminal</h2>
  <div class="chat" id="chat"></div>
  <input id="msg" style="width:70%">
  <button onclick="sendMsg()">Send</button>
</div>

<script>
function checkPass() {
  if(document.getElementById("pass").value === "1234") {
    document.getElementById("login").style.display = "none";
    document.getElementById("chatUI").style.display = "block";
  }
}

function addMessage(text, cls) {
  let div = document.createElement("div");
  div.className = "msg " + cls;
  div.innerText = text;
  document.getElementById("chat").appendChild(div);
}

function sendMsg() {
  let msg = document.getElementById("msg").value;

  addMessage(msg, "user");

  let typing = document.createElement("div");
  typing.className = "msg bot";
  typing.innerText = "Typing...";
  document.getElementById("chat").appendChild(typing);

  fetch("/chat?msg=" + encodeURIComponent(msg))
    .then(res => res.text())
    .then(data => {
      typing.innerText = data;
    });
}
</script>

</body>
</html>
)rawliteral";

// ===== ROOT =====
void handleRoot() {
  server.send(200, "text/html", webpage);
}

// ===== CHAT =====
void handleChat() {
  String userMsg = server.arg("msg");

  HTTPClient http;
  http.begin("https://openrouter.ai/api/v1/chat/completions");

  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(apiKey));

  String payload = "{";
  payload += "\"model\":\"openrouter/free\",";
  payload += "\"messages\":[";
  payload += "{\"role\":\"system\",\"content\":\"You are TARS, a witty, slightly sarcastic AI assistant.\"},";
  
  if (lastUserMsg != "") {
    payload += "{\"role\":\"user\",\"content\":\"Earlier I said: " + lastUserMsg + "\"},";
  }

  payload += "{\"role\":\"user\",\"content\":\"" + userMsg + "\"}";
  payload += "],";
  payload += "\"max_tokens\":40";
  payload += "}";

  int httpResponseCode = http.POST(payload);

  String reply = "";

  if (httpResponseCode > 0) {
    String fullResponse = http.getString();
    Serial.println("==== RAW RESPONSE ====");
Serial.println(fullResponse);
Serial.println("======================");

    DynamicJsonDocument doc(2048);
    deserializeJson(doc, fullResponse);

    if (doc["choices"][0]["message"]["content"]) {
      reply = doc["choices"][0]["message"]["content"].as<String>();
    } else if (doc["choices"][0]["text"]) {
      reply = doc["choices"][0]["text"].as<String>();
    } else {
      reply = "No valid response";
    }
  } else {
    reply = "HTTP request failed";
  }

  http.end();

  lastUserMsg = userMsg;

  reply.trim();

  server.send(200, "text/plain", reply);
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/chat", handleChat);

  server.begin();
}

// ===== LOOP =====
void loop() {
  server.handleClient();
}