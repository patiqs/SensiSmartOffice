#include "Web.h"
#include <WebServer.h>

#include <WebServer.h>

WebServer server(80);

WebClass::WebClass(){}

void WebClass::begin(){
  server.on("/", [](){Web.handle_root();});
  server.begin();
  Serial.println("HTTP server started");
}

void WebClass::handleClient(){
    server.handleClient();
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My First Web Server with ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";

// Handle root url (/)
void WebClass::handle_root() {
  server.send(200, "text/html", HTML);
}

WebClass Web;