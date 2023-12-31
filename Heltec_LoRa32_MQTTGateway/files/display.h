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
  oled.drawXbm(0,5,logo_width,logo_height,(const unsigned char *)logo_bits);
  oled.display();
}

unsigned long lastDisplaySleepTrigger = 0;
const int displaySleepIntervalInMiliseconds = 10 * 1000;

unsigned long s = 0;

void rescheduleDisplaySleep()
{
	lastDisplaySleepTrigger = now;
}

void putTheDisplayToSleep()
{
	if (now - lastDisplaySleepTrigger > displaySleepIntervalInMiliseconds)
	{
		oled.clear();
		oled.display();
		rescheduleDisplaySleep();
	}
}
