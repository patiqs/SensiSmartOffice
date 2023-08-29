#ifdef WEB
#include "Web.h"
#include <WebServer.h>

WebServer *server;
String Map(SignalType st);

Web::Web() {}

void Web::begin()
{
  server = new WebServer(80);
  server->on("/", std::bind(&Web::handle_root, this));
  server->begin();
  Serial.println("HTTP server started");
}

void Web::commitMeasures()
{
  server->handleClient();
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
void Web::handle_root()
{
  String response = HTMLHeader;

  std::vector<MeasureRecord>::iterator itRecord;
  for (itRecord = _measures.begin(); itRecord != _measures.end(); itRecord++)
  {
    String s = itRecord->DeviceName + " > " + Map(itRecord->Type) + " : ";
    if (itRecord->sVal == "")
    {
      s += itRecord->fVal;
    }
    else
    {
      s += itRecord->sVal;
    }
    Serial.println(s.c_str());
    response += "<p>" + s + "</p>";
  }

  response += HtmlFooter;

  server->send(200, "text/html", response.c_str());
}

void Web::pushMeasure(MeasureRecord measure)
{
  _measures.push_back(measure);
}

void Web::pushMeasures(std::vector<MeasureRecord> measures)
{
  _measures.insert(_measures.end(), measures.begin(), measures.end());
}

String Map(SignalType st)
{
  switch (st)
  {
  case SignalType::HCHO_PARTS_PER_BILLION:
    return "Formaldehyde";
  case SignalType::TEMPERATURE_DEGREES_CELSIUS:
    return "Temperature";
  case SignalType::RELATIVE_HUMIDITY_PERCENTAGE:
    return "Humidity";
  default:
    return "Undefined";
  }
}

#endif /* WEB */
