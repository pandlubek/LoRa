void setupWiFi()
{
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.disconnect(true);
  delay(100);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoConnect(true);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.setSleep(false);
  delay(100);

  int attempt = 0;
  Serial.print("\r\nConnecting Wi-Fi...");
  oled.clear();
  oled.drawString(0, 0, "Connecting Wi-Fi...");
  oled.drawString(0, 10, WIFI_SSID);
  oled.display();
  
  while (WiFi.status() != WL_CONNECTED) {
    if (attempt == 60)
    {
      esp_restart();
    }
    delay(500);
    Serial.print(".");
    attempt++;
  }

  Serial.print("connected\r\n");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.println();
  
  oled.drawString(0, 20, "connected");
  oled.drawString(0, 30, "IP address: ");
  oled.drawString(0, 40, WiFi.localIP().toString());
  oled.display();
}