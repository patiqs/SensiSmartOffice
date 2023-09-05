#ifdef WEB
#include "Web.h"
#include <WebServer.h>

WebServer *server;
String Map(SignalType st);

void Web::begin()
{
  server = new WebServer(80);
  server->on("/", std::bind(&Web::handle_root, this));
  server->begin();
  Serial.println("HTTP server started");
}

void Web::commitMeasures()
{
}

void Web::handleNetwork()
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

  std::vector<String>::iterator itRecord;
  std::for_each(_records.begin(), _records.end(), [&](String record){response+=record;});
  _records.clear();

  response += HtmlFooter;

  server->send(200, "text/html", response.c_str());
}

void Web::visit(InfoRecord *record) {_records.push_back("<p>" + record->toString()+ "</p>");}
void Web::visit(ErrorRecord *record) {_records.push_back("<p>" + record->toString()+ "</p>");}
void Web::visit(MeasureRecord *record) {_records.push_back("<p>" + record->toString()+ "</p>");}

#endif /* WEB */
