/* enable Ethernet power supply with correct clock */
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12

#include <ETH.h>
#include <SPIFFS.h>
#include <OSCMessage.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

WiFiUDP udp;
AsyncWebServer server(80);

static bool eth_connected = false;

static uint16_t inPort;
static uint16_t outPort;
static IPAddress outHost;
static String oscAddress;
#define SETTINGS_DEFAULT_IN_PORT 9998
#define SETTINGS_DEFAULT_OUT_PORT 9999
#define SETTINGS_DEFAULT_OUT_HOST IPAddress(192, 168, 1, 28)
#define SETTINGS_DEFAULT_OSC_ADDRESS String("esp32osc")

#define HTML_INPUT_NAME_IN_PORT "inPort"
#define HTML_INPUT_NAME_OUT_PORT "outPort"
#define HTML_INPUT_NAME_OUT_HOST "outHost"
#define HTML_INPUT_NAME_OUT_HOST_0 "outHost0"
#define HTML_INPUT_NAME_OUT_HOST_1 "outHost1"
#define HTML_INPUT_NAME_OUT_HOST_2 "outHost2"
#define HTML_INPUT_NAME_OUT_HOST_3 "outHost3"
#define HTML_INPUT_NAME_OSC_ADDRESS "oscAddress"
const char* PARAM_INPUT_1 = "inPort";

#include <Preferences.h>
#define PREFERENCES_NAMESPACE_SETTINGS "settings"
Preferences prefs;


void WiFiEvent(WiFiEvent_t event)
{
  switch (event) {
    case ARDUINO_EVENT_ETH_START:
      Serial.println("ETH Started");
      //set eth hostname here
      ETH.setHostname("esp32-ethernet");
      break;
    case ARDUINO_EVENT_ETH_CONNECTED:
      Serial.println("ETH Connected");
      break;
    case ARDUINO_EVENT_ETH_GOT_IP:
      Serial.print("ETH MAC: ");
      Serial.print(ETH.macAddress());
      Serial.print(", IPv4: ");
      Serial.print(ETH.localIP());
      if (ETH.fullDuplex()) {
        Serial.print(", FULL_DUPLEX");
      }
      Serial.print(", ");
      Serial.print(ETH.linkSpeed());
      Serial.println("Mbps");
      eth_connected = true;
      udp.begin(WiFi.localIP(), inPort);
      break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
      Serial.println("ETH Disconnected");
      eth_connected = false;
      break;
    case ARDUINO_EVENT_ETH_STOP:
      Serial.println("ETH Stopped");
      eth_connected = false;
      break;
    default:
      Serial.print("Event not recognized : ");
      Serial.println(event);
      break;
  }
}

#define BUTTON_PRESSED()  (!digitalRead (34))

String processor(const String& var)
{
  if(var == "MAC_ADDRESS")
    return ETH.macAddress();
  if(var == "IPV4")
    return ETH.localIP().toString();
  if(var == "LINK_SPEED")
    return String(ETH.linkSpeed());

  if(var == "IN_PORT")
    return String(inPort); 
  if(var == "OUT_PORT")
    return String(outPort);
  if(var == "OUT_HOST_0")
    return String(outHost[0]);
  if(var == "OUT_HOST_1")
    return String(outHost[1]);
  if(var == "OUT_HOST_2")
    return String(outHost[2]);
  if(var == "OUT_HOST_3")
    return String(outHost[3]);
  if(var == "OSC_ADDRESS")
    return oscAddress;
  return String();
}

void dumpSettings() {
  Serial.println("##### Settings #####");
  Serial.print("inPort: "); Serial.println(inPort);
  Serial.print("outPort: "); Serial.println(outPort);
  Serial.print("outHost: "); Serial.println(outHost);
  Serial.print("oscAddress: "); Serial.println(oscAddress);
  Serial.println("####################");
}

void setup()
{
  Serial.begin(115200);
  Serial.println("esp32osc starting ...");

  prefs.begin(PREFERENCES_NAMESPACE_SETTINGS, true);
  inPort = prefs.getUInt(HTML_INPUT_NAME_IN_PORT, SETTINGS_DEFAULT_IN_PORT);
  outPort = prefs.getUInt(HTML_INPUT_NAME_OUT_PORT, SETTINGS_DEFAULT_OUT_PORT);
  outHost = prefs.getULong(HTML_INPUT_NAME_OUT_HOST, SETTINGS_DEFAULT_OUT_HOST);
  oscAddress = prefs.getString(HTML_INPUT_NAME_OSC_ADDRESS, SETTINGS_DEFAULT_OSC_ADDRESS);
  prefs.end();
  
  dumpSettings();

  WiFi.onEvent(WiFiEvent);
  ETH.begin();
  pinMode (34, INPUT);  // Button

  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request){
    Serial.print("POST request received with parameters: ");
    Serial.println(request->params());
    prefs.begin(PREFERENCES_NAMESPACE_SETTINGS, false);
    if(request->hasParam(HTML_INPUT_NAME_IN_PORT, true)) {
      AsyncWebParameter* p  = request->getParam(HTML_INPUT_NAME_IN_PORT, true);
      inPort = p->value().toInt();
      prefs.putUInt(HTML_INPUT_NAME_IN_PORT, inPort);
    }
    if(request->hasParam(HTML_INPUT_NAME_OUT_PORT, true)) {
      AsyncWebParameter* p  = request->getParam(HTML_INPUT_NAME_OUT_PORT, true);
      outPort = p->value().toInt();
      prefs.putUInt(HTML_INPUT_NAME_OUT_PORT, outPort);
    }
    if(request->hasParam(HTML_INPUT_NAME_OSC_ADDRESS, true)) {
      AsyncWebParameter* p  = request->getParam(HTML_INPUT_NAME_OSC_ADDRESS, true);
      oscAddress = p->value().substring(0, 32);
      prefs.putString(HTML_INPUT_NAME_OSC_ADDRESS, oscAddress);
    }
    if(request->hasParam(HTML_INPUT_NAME_OUT_HOST_0, true)
      && request->hasParam(HTML_INPUT_NAME_OUT_HOST_1, true)
      && request->hasParam(HTML_INPUT_NAME_OUT_HOST_2, true)
      && request->hasParam(HTML_INPUT_NAME_OUT_HOST_3, true)) {
      AsyncWebParameter* p0 = request->getParam(HTML_INPUT_NAME_OUT_HOST_0, true);
      AsyncWebParameter* p1 = request->getParam(HTML_INPUT_NAME_OUT_HOST_1, true);
      AsyncWebParameter* p2 = request->getParam(HTML_INPUT_NAME_OUT_HOST_2, true);
      AsyncWebParameter* p3 = request->getParam(HTML_INPUT_NAME_OUT_HOST_3, true);
      outHost = IPAddress(
        p0->value().toInt(),
        p1->value().toInt(),
        p2->value().toInt(),
        p3->value().toInt());
      prefs.putULong(HTML_INPUT_NAME_OUT_HOST, outHost);
    }
    prefs.end();
    dumpSettings();
    request->send(200);
  });

  server.begin();
}


void loop()
{
  Serial.println("I am alive !");
  if (BUTTON_PRESSED())
  {
    Serial.println("ETH Status:");
    Serial.println(ETH.linkUp());

//    OSCMessage msg("/address");
//    msg.add(64);
//
//    udp.beginPacket(outIp, outPort);
//    msg.send(udp); // send the bytes to the SLIP stream
//    udp.endPacket();
//
//    msg.empty();
    while (BUTTON_PRESSED());
  }
  delay(2000);
}
