#include <LedControl.h>

struct snake
{
  int x;
  int y;
};
typedef struct snake snake;

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
  snake kigyo[64];
  kigyo[0].x = 4;
  kigyo[0].y = 7;
  kigyo[1].x = 4;
  kigyo[1].y = 6;
  kigyo[2].x = 4;
  kigyo[2].y = 5;
  for (size_t i = 0; i < 3; i++)
  {
      lc.setLed(0, kigyo[i].x, kigyo[i].y, true);
  }
}

void loop()
{
  static char x = 4, y = 4;
  static char iranyitas = 'q';
  static char iranyitas2;
  if (Serial.available())
  {
    iranyitas2 = Serial.read();
  }
  if (iranyitas2 == 'w'|iranyitas2 == 'a'|iranyitas2 =='s'|iranyitas2 =='d')
  {
    iranyitas = iranyitas2;
  }
  switch (iranyitas)
  {
  case 'w':
    y++;
    break;
  case 'a':
    x++;
    break;

  case 's':
    y--;
    break;

  case 'd':
    x--;
    break;

  default:
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
