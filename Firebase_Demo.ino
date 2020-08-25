#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "home-66067.firebaseio.com" 
#define FIREBASE_AUTH "pQ7HGm9FRJSLJGzoyge6t8xzPZwoM4Nxmub5wIAV"
#define WIFI_SSID "RJPT"
#define WIFI_PASSWORD "rjpt_12396"

#define Relay1 14
#define Relay2 12

int rel1, rel2;

void setup() {
  Serial.begin(9600);

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("Fan", 1);
  Firebase.setString("Light", "OFF");
}
void loop() {

  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(1000);
  rel1 = Firebase.getInt("Fan") ;
  rel2 = Firebase.getString("Light").toInt();
  if (rel1 == 1)
  {
    digitalWrite(Relay1, LOW);
    Serial.println("Relay 1 ON");
  }
  if (rel1 == 0)
  {
    digitalWrite(Relay1, HIGH);
    Serial.println("Relay 1 OFF");
  }
  if (rel2 == 1)
  {
    digitalWrite(Relay1, LOW);
    Serial.println("Relay 2 ON");
  }
  if (rel2 == 0)
  {
    digitalWrite(Relay1, HIGH);
    Serial.println("Relay 2 OFF");
  }
  delay(1000);
}
