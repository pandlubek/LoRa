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
  oled.drawString(0, 10, "SSID: " + String(WIFI_SSID));
  oled.display();
  
  while (WiFi.status() != WL_CONNECTED)
  {
    if (attempt == 60)
    {
      esp_restart();
    }
    delay(500);
    Serial.print(".");
	rescheduleDisplaySleep();
    attempt++;
  }

  Serial.print("connected\r\n");
  Serial.println("IP: " + WiFi.localIP().toString());
}

void displayWiFiInfo()
{
  oled.clear();
  if (WiFi.status() != WL_CONNECTED)
  {
	oled.drawString(0, 0, "Wi-Fi not connected!");
  }
  else
  {
    oled.drawString(0, 0, "Wi-Fi connected");
  }
  oled.drawString(0, 10, "SSID; " + String(WIFI_SSID));
  oled.drawString(0, 20, "IP: " + WiFi.localIP().toString());
  oled.display();
}