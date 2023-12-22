float getBatteryVoltage(bool printVoltage = false)
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

String getBatteryLevel(bool printBatteryLevel = false)
{
  float v = getBatteryVoltage(true);
  String level = "000";

  if (v >= 3.9)
  {
    level = "100";
  }
  else if (v >= 3.8)
  {
    level = "090";
  }
  else if (v >= 3.7)
  {
    level = "075";
  }
  else if (v >= 3.5)
  {
    level = "050";
  }
  else if (v >= 3.3)
  {
    level = "025";
  }

  if (printBatteryLevel)
  {
    Serial.println("Battery level: " + level + "%");
  }

  return level;
}
