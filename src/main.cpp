#include <Arduino.h>
#include <LittleFS.h>

struct Config {
  char wifi_ssid[32];
  char wifi_pass[64];
  char mqtt_host[64];
  int  mqtt_port;
  char mqtt_username[32];
  char mqtt_password[32];
  char mqtt_subscribe_topic[32];
  char mqtt_publish_topic[32];
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
    else if (key == "mqtt_username") value.toCharArray(cfg.mqtt_username, sizeof(cfg.mqtt_username));
    else if (key == "mqtt_password") value.toCharArray(cfg.mqtt_password, sizeof(cfg.mqtt_password));
    else if (key == "mqtt_publish_topic") value.toCharArray(cfg.mqtt_publish_topic, sizeof(cfg.mqtt_publish_topic));
    else if (key == "mqtt_subscribe_topic") value.toCharArray(cfg.mqtt_subscribe_topic, sizeof(cfg.mqtt_subscribe_topic));
    else if (key == "device_id") value.toCharArray(cfg.device_id, sizeof(cfg.device_id));
  }

  file.close();
}

/* -------- usage example ---------
void setup() {
  Serial.begin(115200);

  if (!LittleFS.begin(true)) {
  Serial.println("Erro ao montar LittleFS");
  return;
  }

  loadConfig();
}

void connectWiFi() {
  WiFi.begin(cfg.wifi_ssid, cfg.wifi_pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado");
}
*/

