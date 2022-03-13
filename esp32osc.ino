/* enable Ethernet power supply with correct clock */
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12

#include <ETH.h>
#include <OSCMessage.h>

WiFiUDP udp;

static bool eth_connected = false;
const int inPort = 3333;
IPAddress outIp(192, 168, 1, 26);
const unsigned int outPort = 9999;

void WiFiEvent(WiFiEvent_t event)
{
  Serial.println("Wifi event received");
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

void testClient(const char * host, uint16_t port)
{
  Serial.print("\nconnecting to ");
  Serial.println(host);

  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }
  client.printf("GET / HTTP/1.1\r\nHost: %s\r\n\r\n", host);
  while (client.connected() && !client.available());
  while (client.available()) {
    Serial.write(client.read());
  }

  Serial.println("closing connection\n");
  client.stop();
}

#define BUTTON_PRESSED()  (!digitalRead (34))

void setup()
{
  Serial.begin(115200);
  delay(2000);

  WiFi.onEvent(WiFiEvent);
  ETH.begin();
  pinMode (34, INPUT);  // Button
}


void loop()
{
  Serial.println("I am alive !");
  if (BUTTON_PRESSED())
  {
    Serial.println("ETH Status:");
    Serial.println(ETH.linkUp());

    OSCMessage msg("/address");
    msg.add(64);

    udp.beginPacket(outIp, outPort);
    msg.send(udp); // send the bytes to the SLIP stream
    udp.endPacket();

    msg.empty();
    while (BUTTON_PRESSED());
  }
  //  if (eth_connected) {
  //    testClient("google.com", 80);
  //
  //  }
  delay(2000);
}
