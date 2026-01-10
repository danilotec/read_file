#include <Arduino.h>
#include <LittleFS.h>

struct Config {
  char wifi_ssid[32];
  char wifi_pass[64];
  char mqtt_host[64];
  int  mqtt_port;
  int  send_interval;
  char device_id[32];
};

Config cfg;


void loadConfig() {
  File file = LittleFS.open("/configs.ini", "r");
  if (!file) {
    Serial.println("fail to open configs.ini");
    return;
  }

  while (file.available()) {
    String line = file.readStringUntil('\n');
    line.trim();

    if (line.length() == 0 || line.startsWith("#")) continue;

    int sep = line.indexOf('=');
    if (sep < 0) continue;

    String key = line.substring(0, sep);
    String value = line.substring(sep + 1);

    key.trim();
    value.trim();

    if (key == "wifi_ssid") value.toCharArray(cfg.wifi_ssid, sizeof(cfg.wifi_ssid));
    else if (key == "wifi_pass") value.toCharArray(cfg.wifi_pass, sizeof(cfg.wifi_pass));
    else if (key == "mqtt_host") value.toCharArray(cfg.mqtt_host, sizeof(cfg.mqtt_host));
    else if (key == "mqtt_port") cfg.mqtt_port = value.toInt();
    else if (key == "send_interval") cfg.send_interval = value.toInt();
    else if (key == "device_id") value.toCharArray(cfg.device_id, sizeof(cfg.device_id));
  }

  file.close();
}

/* -------- usage example ---------

void connectWiFi() {
  WiFi.begin(cfg.wifi_ssid, cfg.wifi_pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado");
}
*/

