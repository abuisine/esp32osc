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

#include <Preferences.h>
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
//      udp.begin(WiFi.localIP(), inPort);

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

void setup()
{
  Serial.begin(115200);
  Serial.println("esp32osc starting ...");

  prefs.begin("settings", true);
  inPort = prefs.getUInt("inPort", SETTINGS_DEFAULT_IN_PORT);
  outPort = prefs.getUInt("outPort", SETTINGS_DEFAULT_OUT_PORT);
  outHost = prefs.getULong("outHost", SETTINGS_DEFAULT_OUT_HOST);
  oscAddress = prefs.getString("oscAddress", SETTINGS_DEFAULT_OSC_ADDRESS);

  Serial.print("inPort: "); Serial.println(inPort);
  Serial.print("outPort: "); Serial.println(outPort);
  Serial.print("outHost: "); Serial.println(outHost);
  Serial.print("oscAddress: "); Serial.println(oscAddress);

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
