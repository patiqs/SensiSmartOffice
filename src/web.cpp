#include "Web.h"
#include <WebServer.h>

WebServer server(80);

WebClass::WebClass() {}

void WebClass::begin()
{
  server.on("/", []()
            { Web.handle_root(); });
  server.begin();
  Serial.println("HTTP server started");
}

void WebClass::handleClient()
{
  server.handleClient();
}

void WebClass::setMeasure(String key, String value)
{
  _measures.push_back(std::pair<String, String>(key, value));
  Serial.println(key + ":" + value);
}

// HTML & CSS contents which display on web server
String HTMLHeader = "<!DOCTYPE html>\
<html>\
<head>\
    <title>ESP32 & SFA31</title>\
    <meta http-equiv=\"refresh\" content=\"2\">\
</head>\
<body>\
<h1>Web Server with ESP32 and SFA31 &#128522;</h1>";

String HtmlFooter = "\
</body>\
</html>";

// Handle root url (/)
void WebClass::handle_root()
{
  String response = HTMLHeader;

  std::vector<std::pair<String, String>>::iterator it;

  for (it = _measures.begin(); it != _measures.end(); it++)
  {
    response += "<p>" + it->first + " : " + it->second + "</p>";
  }

  response += HtmlFooter;

  server.send(200, "text/html", response.c_str());
}

WebClass Web;