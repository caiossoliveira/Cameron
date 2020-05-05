/*
  Cameron Platform
  ESP8266 mDNS responder with AP and Station mode
  HTTP server that is accessible via http://cameron.local URL thanks to mDNS responder.
  Instructions:
  - Install host software:
    - For Linux, install Avahi (http://avahi.org/), sudo apt-get install avahi-daemon avahi-discover avahi-utils libnss-mdns mdns-scan.
    - For Windows, install Bonjour (http://www.apple.com/support/bonjour/).
    - For Mac OSX and iOS support is built in through Bonjour already.
  - Point your browser to http://cameron.local, you should see a response.
  - Recommended browser: Mozila Firefox
  - Developer: Caio Oliveira <caiossoliveira@gmail.com>.
*/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "login.h"
#include "indexPage.h"
 
WiFiServer server(80); // server: http://192.168.4.1
 
void setup() {
  const char* AP_SSID = "Cameron";
  const char* AP_PWSD = "cameron10";
  String sta_ssid = "", sta_pswd = "";
  
  Serial.begin(115200);

  ESP.eraseConfig();
  delay(50);

  login login;
  String conectionInfo = login.read();
  if(conectionInfo.compareTo("0") != 0){
    Serial.printf("\n Station mode");
    WiFi.mode(WIFI_STA);
    sta_ssid = login.getSSID(conectionInfo);
    sta_pswd = login.getPSWD(conectionInfo);

    int n = 0;
    Serial.printf("\n Connecting to %s ", sta_ssid.c_str());
    WiFi.begin(sta_ssid.c_str(), sta_pswd.c_str());
    while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
      n++;
      if(n == 100){
        n=0;
        login.clean();
        ESP.restart();
      }
    }
    Serial.printf("\n Connected to %s", sta_ssid.c_str());
    Serial.printf("\n IP address: ");
    Serial.println(WiFi.localIP());
  }
  else{
    Serial.printf("\n AP mode");
    WiFi.mode(WIFI_AP); //Connect to WiFi network
    WiFi.softAP(AP_SSID, AP_PWSD);
  }

  if(!MDNS.begin("cameron")){ 
    Serial.println("Error setting up MDNS responder!");
    while(1) {
      delay(1000);
    }
  }
  Serial.println("\n mDNS responder started");

  server.begin(); // Start TCP (HTTP) server
  Serial.printf("\n TCP server started \n\n");

  MDNS.addService("http", "tcp", 80); //Add service to MDNS-SD

  WiFi.printDiag(Serial);

}
 
void loop() {
  MDNS.update();

  WiFiClient client = server.available(); //Check if a client has connected
  if (!client){
    return;
  }
  Serial.printf("\n\n New client");

  while(client.connected() && !client.available()){ //Wait for data from client to become available
    delay(1);
  }

  String req = client.readStringUntil('\r'); // Read the first line of HTTP request
  int addr_start = req.indexOf(' '); //1º line of HTTP req is "GET /path HTTP/1.1". Retrieve the "/path" part by finding the spaces
  int addr_end = req.indexOf(' ', addr_start + 1);
  if(addr_start == -1 || addr_end == -1){
    Serial.printf("\n Invalid request: %s", req.c_str());
    return;
  }
  req = req.substring(addr_start + 1, addr_end);
  Serial.printf("\n Request: %s \n", req.c_str());
  
  client.flush();

  processRequest(req, client); //process the request
}

void processRequest(String req, WiFiClient client){
  
  String sta_ssid = "",  sta_pswd = "", command = "";
  String buf = "";
  login login;
  indexPage indexPage("");

  buf = indexPage.getPage();
  
  if((req.indexOf("/?function=") != -1) && (req.indexOf("&") != -1) && (req.indexOf("%") != -1)){
     
    sta_ssid = login.getSSID(req);
    sta_pswd = login.getPSWD(req);
    
    delay(250);

    login.clean();
    String conectionInfo = '&' + sta_ssid + '*' + sta_pswd + '%';
    login.store(conectionInfo);

    ESP.restart();
  }
  else if(req.indexOf("/?function=") != -1){
    String command = login.getCommand(req);
    Serial.print(command.c_str());
  }
  else if(req.indexOf("/") == -1){
    buf = "HTTP/1.1 404 Not Found\r\n\r\n";
  }

  client.print(buf);
  buf = "";
}
