char getContactSensorStatus(bool printStatus = false)
{
  bool pinState = digitalRead(CONTACT_SENSOR_GPIO_NUM);
  
  if (pinState && CONTACT_SENSOR_TYPE || !pinState && !CONTACT_SENSOR_TYPE)
  {
    if (printStatus)
    {
      Serial.println("Contact sensor: OPEN");
    }
    return CONTACT_SENSOR_STATUS_OPEN;
  }
  else
  {
    if (printStatus)
    {
      Serial.println("Contact sensor: CLOSED");
    }
    return CONTACT_SENSOR_STATUS_CLOSED;
  }
}