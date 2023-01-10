#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>

IPAddress    apIP(42, 42, 42, 42);  // Defining a static IP address: local & gateway
                                    // Default IP in AP mode is 192.168.4.1
/* This are the WiFi access point settings.*/

// NETWORK CREDENTIALS
const char* ssid = "TacEsp8266";
const char* password = "Tac12345";
// Define a web server at port 80 for HTTP
ESP8266WebServer server(80);

// ###################################################
// initialization of global variables
// ###################################################
int directionCW = 1;
int speed = 1;
int angle = 0;
/* motor's steps per revolution */
const int stepsPerRevolution = 1052;
/* value of stepsPerRevolution: https://forum.digikey.com/t/how-many-steps-does-24byj48s-actually-have-per-revolution/6202 */
#define expander B00100000 //expander address 0x20

// ###################################################
// void handleRoot()
// ###################################################
void handleRoot() {

  int(directionCW_server) = server.arg("dir").toInt();
  int(speed_server) = server.arg("sp").toInt();
  int(angle_server) = server.arg("quantity").toInt();
 
  if (directionCW_server != 0){
    directionCW = directionCW_server;
  }
  if (speed_server != 0){
    speed = speed_server;
  }
  
  angle = angle_server;
    
 /* Dynamically generate the direction toggle link, based on its current state (CW or CCW) */
  char dirText[80];
  if (directionCW == 2) {
    strcpy(dirText, "Rotation direction is CW. <a href=\"/?dir=1\">Turn it CCW!</a>");
  } else if (directionCW == 1){
    strcpy(dirText, "Rotation direction is CCW. <a href=\"/?dir=2\">Turn it CW!</a>");
  }
  
 /* Dynamically generate link speed switching, based on the option chosen */
  char sp1Text[80];
  if (speed == 1) {
    strcpy(sp1Text, " <input type=\"radio\" id=\"stopped\" name=\"speed\" value=\"stopped\" checked>\ ");
  } else {
    strcpy(sp1Text, " <input type=\"radio\" id=\"stopped\" name=\"speed\" value=\"stopped\">\ ");
  }
  char sp2Text[80];   
  if (speed == 2) {
    strcpy(sp2Text, " <input type=\"radio\" id=\"low_speed\" name=\"speed\" value=\"low_speed\" checked>\ ");
  } else {
    strcpy(sp2Text, " <input type=\"radio\" id=\"low_speed\" name=\"speed\" value=\"low_speed\">\ ");
  }
  char sp3Text[80];   
  if (speed == 3) {
    strcpy(sp3Text, " <input type=\"radio\" id=\"high_speed\" name=\"speed\" value=\"high_speed\" checked>\ ");
  } else {
    strcpy(sp3Text, " <input type=\"radio\" id=\"high_speed\" name=\"speed\" value=\"high_speed\">\ ");
  }
  
  char html[1500];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  
// ###################################################
// html code
// ###################################################
  // Build an HTML page to display on the web-server root address
  snprintf ( html,1500,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='10'/>\
    <title>ESP8266 WiFi Network</title>\
    <style>\
      body { background-color: #ebf1f1; font-family: Arial, Helvetica, Sans-Serif; font-size: 1.5em; Color: #000000; }\
      h1 { Color: #ffffff; background-color: #336699;}\
    </style>\
  </head>\
  <body>\
    <h1>Stepper Motor Control - Final project of TAC</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <p>%s<p>\
    <p>\
      <fieldset>\
        <legend>Select the desired speed:</legend>\
        <div>\
           %s\
           <label for=\"stopped\"><a href=\"/?sp=1\">Stopped</a>\</label>\
        <\div>\</a>\
        <div>\
           %s\
           <label for=\"low_speed\"><a href=\"/?sp=2\">Low Speed</label>\
        <\div>\
        <div>\
           %s\
           <label for=\"high_speed\"><a href=\"/?sp=3\">High Speed</label>\</a>\
        <\div>\
      </fieldset>\
    <p>\
    <p>\
      <form>\
        <label for=\"quantity\">Angle (between 1 and 360):</label>\
        <input type=\"number\" id=\"quantity\" name=\"quantity\" min=\"1\" max=\"360\">\
        <input type=\"submit\" value=\"Send Request\">\
      </form>\
    </p>\
  </body>\
</html>",

    hr, min % 60, sec % 60,
    dirText,
    sp1Text,
    sp2Text,
    sp3Text
  );
  server.send ( 250, "text/html", html );
  //digitalWrite ( LED_BUILTIN, 1 );
}

// ###################################################
// void handleNotFound()
// ###################################################
void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
}

// ###################################################
// void setup()
// ###################################################
void setup() {

  delay(1000);
  Wire.begin();
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  /* set-up the custom IP address */
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
  server.on ( "/", handleRoot );
  server.on ( "/inline", []() {
      server.send ( 200, "text/plain", "this works as well" );
  } );
  server.onNotFound (handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");

}

void loop() {
  int(delaytime) = 1000;
  byte(stepPin_ON) = B00000001;
  byte(stepPin_OFF) = B00000000;
  
  server.handleClient();

  /* Set motor direction clockwise */
  if (directionCW == 1) { 
    stepPin_ON = B00000001;
    stepPin_OFF = B00000000;
  }

  /* Set motor direction counterclockwise */
  if (directionCW == 2) {
    stepPin_ON = B00000011;
    stepPin_OFF = B00000010;  
  }
  /* Low Speed */
  if (speed == 2) {
    delaytime = 1000;
  /* High Speed */
  } else if (speed == 3){
    delaytime = 500;
  }
  
  /* angle conversion */
  float(ang_01) = float(angle)/360;

  if ( (ang_01 != 0) && (speed != 1) ) {
    for(int x = 0; x < ang_01*stepsPerRevolution; x++)
    {
      expanderWrite(stepPin_ON);
      delayMicroseconds(delaytime);
      expanderWrite(stepPin_OFF);
      delayMicroseconds(delaytime);
    }
    angle = 0;
  }
  delay(1000);
}

// ###################################################
// void expanderWrite()
// ###################################################
void expanderWrite(byte _data ) {
  Wire.beginTransmission(expander);
  Wire.write(_data);
  Wire.endTransmission();
}
