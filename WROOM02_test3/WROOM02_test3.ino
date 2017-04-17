#include "ESP8266.h"
#include <SoftwareSerial.h>
 
//Arduino UNOとESP8266をシリアルで繋いで通信。
//UNOとESP8266はSoftware Serialで通信。
 
#define SSID "KEROMIN-GUEST"
#define PASSWORD "0455659967"
#define HOST_NAME "mkbtm.jp"
#define HOST_PORT 80
 
SoftwareSerial mySerial(11, 10); /* RX:11, TX:10 */
ESP8266 wifi(mySerial);
//software serialの速度はESP8266.hで設定
 
void setup(void)
{
 Serial.begin(9600);
 //Serial.begin(57600);
 Serial.print("setup begin\r\n");
  
 Serial.print("FW Version:");
 Serial.println(wifi.getVersion().c_str());
  
 if (wifi.setOprToStationSoftAP()) {
 Serial.print("to station + softap ok\r\n");
 } else {
 Serial.print("to station + softap err\r\n");
 }
  
 if (wifi.joinAP(SSID, PASSWORD)) {
 Serial.print("Join AP success\r\n");
 Serial.print("IP:");
 Serial.println( wifi.getLocalIP().c_str()); 
 } else {
 Serial.print("Join AP failure\r\n");
 }
  
 if (wifi.disableMUX()) {
 Serial.print("single ok\r\n");
 } else {
 Serial.print("single err\r\n");
 }
  
 Serial.print("setup end\r\n");
}
  
void loop(void)
{
 uint8_t buffer[512] = {0};
  
 if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
 Serial.print("create tcp ok\r\n");
 } else {
 Serial.print("create tcp err\r\n");
 }
  
 char *hello = "GET / HTTP/1.0\r\n User-Agent: arduino\r\n\r\n";
 
 wifi.send((const uint8_t*)hello, strlen(hello));
  
 uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
 if (len > 0) {
 Serial.print("Received:[");
 for(uint32_t i = 0; i < len; i++) {
 Serial.print((char)buffer[i]);
 }
 Serial.print("]\r\n");
 }
  
 delay(5000);
}
