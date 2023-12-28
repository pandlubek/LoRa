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
}