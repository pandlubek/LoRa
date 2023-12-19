float readBatteryVoltage(bool printVoltage = false)
{
	pinMode(ADC_CTRL, OUTPUT);
	digitalWrite(ADC_CTRL, LOW);
	delay(10); // delay to stabilize GPIO readings
	
	int analog = analogRead(BATTERY_VOLTAGE_GPIO_NUM);
	float v = 0.00403532794741887 * analog;
	
	if (printVoltage)
	{
		Serial.println("Battery voltage: " + String(v));
	}
	
	return v;
}