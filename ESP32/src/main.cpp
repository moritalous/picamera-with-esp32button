#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <ESPmDNS.h>

const char *ssid = "____your_ssid____";
const char *password = "____your_password____";

String localhost = "esp32";

String serverHost = "raspberrypi";
String serverPort = "8000";
String serverPath = "cgi-bin/capture.py";

const int switchPin = 32;
const int ledPin = 27;

int currentState = 0;
int beforeState = 0;

void setup()
{
  Serial.begin(115200);

  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  MDNS.begin(localhost.c_str());
}

String createUrl()
{
  IPAddress ipaddress = MDNS.queryHost(serverHost);
  Serial.println(ipaddress);
  Serial.println(ipaddress.toString());

  String url = "http://" + ipaddress.toString() + ":" + serverPort + "/" + serverPath;
  Serial.println(url);

  return url;
}

boolean isChange(int current, int before)
{
  return (current != before) && (current == 1);
}

void loop()
{
  currentState = digitalRead(switchPin);

  if (isChange(currentState, beforeState))
  {
    Serial.println("Change!!!");

    digitalWrite(ledPin, 1);

    HTTPClient http;
    String request = createUrl();
    http.begin(request.c_str());
    int httpResponseCode = http.GET();

    digitalWrite(ledPin, 0);

    Serial.println(httpResponseCode);
  }

  beforeState = currentState;
}