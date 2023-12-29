SSD1306Wire oled(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);

void VextON(void)
{
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);
}

void initializeDisplay()
{
  VextON();
  oled.init();
  oled.clear();
  oled.setFont(ArialMT_Plain_10);
  oled.drawString(0, 20, "Booting...");
  oled.display();
}