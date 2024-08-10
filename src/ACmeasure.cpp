#include <ACmeasure.h>

UNIT_ACMEASURE sensor;

float voltage = 0,
      current = 0, 
      power = 0, 
      appower = 0, 
      kwh = 0;

char vol_str[10] = "0", 
      cur_str[10] = "0", 
      pow_str[10] = "0", 
      appow_str[10] = "0", 
      kwh_str[10] = "0";


void updateACinfor()
{
  if (sensor.getReady())
  {
    voltage = (float)(sensor.getVoltage()) / 100.0; //V
    current = (float)(sensor.getCurrent()) * 10; //mA
    power = (float)(sensor.getPower()) / 100.0; //W
    appower = (float)(sensor.getApparentPower()) / 100.0; //VA
    kwh = (float)(sensor.getKWH()) /100.0; //kW.h
  } 
  else 
  {
    voltage = 0; 
    current = 0;
    power = 0;
    appower = 0;
    kwh = 0;
  }
  sprintf(vol_str, "%0.2f", voltage);
  sprintf(cur_str, "%0.2f", current);
  sprintf(pow_str, "%0.2f", power);
  sprintf(appow_str, "%0.2f", appower);
  sprintf(kwh_str, "%0.2f", appower);
}

void setupACsensor()
{
  while (!(sensor.begin(&Wire, UNIT_ACMEASURE_ADDR, 13, 15, 100000U))) {
    M5Dial.Lcd.clear();
    M5Dial.Lcd.setCursor(100, 100);
    M5Dial.Lcd.println("no module");
  }
}

