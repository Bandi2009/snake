#include <LedControl.h>

int DIN = 11;
int CS = 10;
int CLK = 13;

LedControl lc = LedControl(DIN, CLK, CS, 0);

struct snake
{
  int x;
  int y;
};
typedef struct snake snake;

const int MAXKIGXOHOSSZ = 64;

int kigyohossza = 3;
const unsigned KIGYOLASSUSAG = 500;
static char iranyitas = 'w';
snake kigyo[MAXKIGXOHOSSZ];
static char pi[MAXKIGXOHOSSZ];

void setup()
{
  lc.shutdown(0, false);
  lc.setIntensity(0, 0);
  lc.clearDisplay(0);
  Serial.begin(115200);

  for (int i = kigyohossza - 1; i >= 0; i--)
  {
    kigyo[i].x = 4;
    kigyo[i].y = 0 + kigyohossza - 1 - i;
    pi[i] = 'w';
    lc.setLed(0, kigyo[i].x, kigyo[i].y, true);
    delay(KIGYOLASSUSAG);
  }
}

void loop()
{
  if (Serial.available())
  {
    char iranyitas2 = Serial.read();

    if (iranyitas2 == 'w' | iranyitas2 == 'a' | iranyitas2 == 's' | iranyitas2 == 'd')
    {
      iranyitas = iranyitas2;
    }
  }

  lc.setLed(0, kigyo[kigyohossza - 1].x, kigyo[kigyohossza - 1].y, false);

  for (size_t i = kigyohossza - 1; i > 0; i--)
  {
    pi[i] = pi[i-1];
  }

  pi[0] = iranyitas;

  for (size_t p = 0; p < kigyohossza; p++)
  {
    switch (pi[p])
    {
    case 'w':
      kigyo[p].y++;
      break;
    case 'a':
      kigyo[p].x++;
      break;

    case 's':
      kigyo[p].y--;
      break;

    case 'd':
      kigyo[p].x--;
      break;

    default:
      break;
    }

    if (kigyo[p].y > 7)
    {
      kigyo[p].y = 0;
    }
    if (kigyo[p].x > 7)
    {
      kigyo[p].x = 0;
    }
    if (kigyo[p].y < 0)
    {
      kigyo[p].y = 7;
    }
    if (kigyo[p].x < 0)
    {
      kigyo[p].x = 7;
    }
  }
  lc.setLed(0, kigyo[0].x, kigyo[0].y, true);
  delay(KIGYOLASSUSAG);
}
