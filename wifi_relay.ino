/*
 * ESP8266 (WeMosD1) WiFi Relay Control
 * 
 * learnelectronics
 * 05 JUN 2017
 * 
 * www.youtube.com/c/learnelectronics
 * arduino0169@gmail.com
*/


#include <ESP8266WiFi.h>
 
const char* ssid = "Phinergy_Qadima";
const char* password = "Qadimaev2015";
 
int ledPin_1 = 2;

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
 
  pinMode(ledPin_1, OUTPUT);
  digitalWrite(ledPin_1, LOW);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value_1 = LOW;
  if (request.indexOf("/LED_1=OFF") != -1) {
    digitalWrite(ledPin_1, LOW);
    value_1 = HIGH;
  }
  if (request.indexOf("/LED_1=ON") != -1){
    digitalWrite(ledPin_1, HIGH);
    value_1 = LOW;
  }
  
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(value_1 == LOW) {
    client.print("OFF");  
  } else {
    client.print("ON");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LED_1=OFF\">here</a>  to turn relay ON<br>");
  client.println("Click <a href=\"/LED_1=ON\">here</a>  to turn relay OFF<br>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
