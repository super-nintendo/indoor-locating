//For safety reasons, sensitive information about IP addresses and SSID Keys have been avoided
//The variables defined as "XXXXX" will need to be setup by each developer under its own domain

//If you have difficulties obtaining your different credentials, please visit the README.md file



#include <LWiFi.h>
#include <WiFiClient.h>
#include "MCS.h"

#include <LBLE.h>
#include <LBLEPeriphral.h>

#include <PubSubClient.h>

// Assign AP ssid / password here
#define _SSID "LinkIt_Smart_7688_1B8B79"
#define _KEY  "XXXXXXXXXXX"


//MCSLiteDevice mcs("HJYw0tkLS", "17e37edfbcf9f2f88093b3d64368b63162c57dd687f7f0b7861e8a547bc25d53", "192.168.50.29", 3000);      //81
//MCSLiteDevice mcs("rJTPkKXIB", "6807bbb4435fc519da3f0f8c042ee8140bac099828094e6c096a3d92fe0747c1", "192.168.50.29", 3000);    //82
MCSLiteDevice mcs("HJOuJYXUS", "622055a1dc6e5695c8c71979523bd24693c9717e77227e2a31abc010851fa4d2", "192.168.50.29", 3000);    //83
//MCSLiteDevice mcs("ryHtkK7Ir", "1ed7fadea8fafee2d754e957d56cb520d8964f569085661b5d6fb70ed41ce22b", "192.168.50.29", 3000);    //84



MCSControllerOnOff led("led_switch");
MCSDisplayOnOff    remote("led");

#define LED_PIN 7

//Add mqttserver, username, password

char mqttServer[] = "140.XXX.XX.XX";
char Username [] = "a579ff87-XXXX-XXXX-XXXX-XXXXXXXXXXXX";
char password [] = "r:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
char clientId[] = "switch_1568117694";
char myqnapcloudHost [] = "id4c.myqnapcloud.com:8080";
char publishTopic1 [] = "RSSI";
char publishPayload [] = "Henlo there";
char subscribeTopic [] = "qiot/things/fogta/switch/ledswitch";

int mqttport = 21883;

int status = WL_IDLE_STATUS;
WiFiClient mtclient;     
PubSubClient client(mtclient);

void setup(){
  Serial.begin(115200);
  LBLE.begin();
  client.setServer(mqttServer, 1883);


  pinMode(LED_PIN, OUTPUT);
  // setup Wifi connection
  while(WL_CONNECTED != WiFi.status())
  {
    Serial.print("WiFi.begin(");
    Serial.print(_SSID);
    Serial.print(",");
    Serial.print(_KEY);
    Serial.println(")...");
    WiFi.begin(_SSID, _KEY);
    Serial.println("WiFi connected !!");
  }
    Serial.println("WiFi connected !!");


  // setup MCS connection
  mcs.addChannel(led);
  mcs.addChannel(remote);
  while(!mcs.connected())
  {
    Serial.println("MCS.connect()...");
    mcs.connect();
  }
  Serial.println("MCS connected !!");

  // read LED value from MCS server
  while(!led.valid())
  {
    Serial.println("read LED value from MCS...");
    led.value();
  }
  Serial.print("done, LED value = ");
  Serial.println(led.value());
  digitalWrite(LED_PIN, led.value() ? HIGH : LOW);

 // Initialize BLE subsystem

  Serial.println("BLE begin");
  while (!LBLE.ready()) {
    delay(100);
  }
  Serial.println("BLE ready");
//  
//  // configure our advertisement data as iBeacon.
  LBLEAdvertisementData beaconData;
  beaconData.configAsIBeacon("096C00000-DFFB-48D2-B060-D0F5A71096E0", 01, 02, -40);
  // start advertising it
  LBLEPeripheral.advertiseAsBeacon(beaconData);


}


void loop() {
  // call process() to allow background processing, add timeout to avoid high cpu usage
  Serial.print("process(");
  Serial.print(millis());
  Serial.println(")");
  mcs.process(100);
  
  // updated flag will be cleared in process(), user must check it after process() call.
  if(led.updated())
  {
    Serial.print("LED updated, new value = ");
    Serial.println(led.value());
    digitalWrite(LED_PIN, led.value() ? HIGH : LOW);
    if(!remote.set(led.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(remote.value());
    }
  }
  
  // check if need to re-connect
  while(!mcs.connected())
  {
    Serial.println("re-connect to MCS...");
    mcs.connect();
    if(mcs.connected())
      Serial.println("MCS connected !!");
  }
}

void printWifiStatus() {                     //print Wifi status
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}
