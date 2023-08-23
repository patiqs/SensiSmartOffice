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
<head>\
    <title>ESP32 & SFA31</title>\
    <meta http-equiv=\"refresh\" content=\"2\">\
</head>\
<body>\
<h1>Web Server with ESP32 and SFA31 &#128522;</h1>\
<p>iteration: %d</p>\
<p>error: %s</p>\
</body>\
</html>";

// Handle root url (/)
void WebClass::handle_root() {
  char message[2047];
  sprintf(message, HTML.c_str(), _iteration, _error.c_str());

  server.send(200, "text/html", message);
}

WebClass Web;