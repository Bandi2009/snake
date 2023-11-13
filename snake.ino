#include <LedControl.h>

int DIN = 11;
int CS = 10;
int CLK = 13;

LedControl lc = LedControl(DIN, CLK, CS, 0);

void setup()
{

  lc.shutdown(0, false);
  lc.setIntensity(0, 0);
  lc.clearDisplay(0);
  Serial.begin(115200);
}

void loop()
{
  static char x = 4, y = 4;
  static char iranyitas = 'w';
  if (Serial.available())
  {
    iranyitas = Serial.read();
  }
  switch (iranyitas)
  {
  case 'w':
    y++;
    break;
  case 'a':
    x--;
    break;

  case 's':
    y--;
    break;

  case 'd':
    x++;
    break;

  default:
    y++;
    break;
  }
if (y > 7)
{
  y = 0;
}
if (x > 7)
{
  x = 0;
}
if (y < 0)
{
  y = 7;
}
if (x < 0)
{
  x = 7;
}
  lc.setLed(0, x, y, true);
  delay(500);
  lc.setLed(0, x, y, false);
}