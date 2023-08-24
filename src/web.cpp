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

  std::vector<MeasureRecord>::iterator itRecord;
  for (itRecord = _measures.begin(); itRecord != _measures.end(); itRecord++)
  {
    String s = itRecord->Name + " : ";
    if (itRecord->sVal == "")
    {
      s += itRecord->dVal;
    }
    else
    {
      s += itRecord->sVal;
    }
    Serial.println(s.c_str());
    response += "<p>" + s + "</p>";
  }

  response += HtmlFooter;

  server.send(200, "text/html", response.c_str());
}

void WebClass::pushMeasure(MeasureRecord measure)
{
  _measures.push_back(measure);
}

void WebClass::pushMeasures(std::vector<MeasureRecord> measures)
{
  _measures.insert(_measures.end(), measures.begin(), measures.end());
}

WebClass Web;