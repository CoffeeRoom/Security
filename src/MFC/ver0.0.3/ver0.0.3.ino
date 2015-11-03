

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h> 

/* Drive m*/
#define MOTER_LEFT_A    4
#define MOTER_LEFT_B    5

void rotateMoterCCW(int moterA, int moterB) ;
void rotateMoterCW(int moterA, int moterB) ;
void stopMoter(int moterA, int moterB) ;

/* Set these to your desired credentials. */
const char *ssid = "fucking";
const char *password = "abcdefgh";

WiFiServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("HTTP server started");

  
  pinMode(MOTER_LEFT_A, OUTPUT);
  pinMode(MOTER_LEFT_B, OUTPUT);

  rotateMoterCW(MOTER_LEFT_A, MOTER_LEFT_B);
  Serial.println("MotorCW");
  delay(1500);
  stopMoter(MOTER_LEFT_A, MOTER_LEFT_B);
  Serial.println("MotorStop");
}

void loop() {
  WiFiClient client = server.available();
  if(!client){
      return;
  }
  
  while(client.connected() && !client.available()){
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  
  // First line of HTTP request looks like "GET /path HTTP/1.1"
  // Retrieve the "/path" part by finding the spaces
  int addr_start = req.indexOf(' ');
  int addr_end = req.indexOf(' ', addr_start + 1);
  if (addr_start == -1 || addr_end == -1) {
    Serial.print("Invalid request: ");
    Serial.println(req);
    return;
  }
  req = req.substring(addr_start + 1, addr_end);
  Serial.print("Request: ");
  Serial.println(req);
  client.flush();

  if (req == "/")
  {
      Serial.println("- connect requested: /");
  }
  else if (req=="/12345/") {
    
      Serial.println("- connect requested: ");
      int m[100];
      for (int i = 1; i < sizeof(req); i++) {
        Serial.print(req[i]);
      }Serial.println();
      
      rotateMoterCCW(MOTER_LEFT_A, MOTER_LEFT_B);
      Serial.println("MotorCCW");
      delay(300);
      stopMoter(MOTER_LEFT_A, MOTER_LEFT_B);
      Serial.println("MotorStop");
  }
  else {
    Serial.println("Not handled request");
  }
}


  // output moterA = 1, moterB = 0
void rotateMoterCCW(int moterA, int moterB) {
  digitalWrite(moterA, 1);
  digitalWrite(moterB, 0);
}

// output moterA = 0, moterB = 1
void rotateMoterCW(int moterA, int moterB) {
  digitalWrite(moterA, 0);
  digitalWrite(moterB, 1);
}

// output moterA == moterB
void stopMoter(int moterA, int moterB) {
  digitalWrite(moterA, 0);
  digitalWrite(moterB, 0);
}

  
