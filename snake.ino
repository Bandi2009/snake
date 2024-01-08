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

const int MAXKIGYOHOSSZ = 64;

int kigyohossza = 3;
const unsigned KIGYOLASSUSAG = 100;
static char iranyitas = 'w';
snake kigyo[MAXKIGYOHOSSZ];
static char pi[MAXKIGYOHOSSZ];
snake kaja;
snake keresett;

bool ellenorzes (snake keresett)
{
  for (size_t i = 0; i < kigyohossza; i++)
  {
    if (kigyo[i].x == keresett.x && kigyo[i].y == keresett.y)
    {
      return true;
    }
  }
  return false;
}

snake random ()
{
  bool talaltunkemarrandomhelyet;

  while (talaltunkemarrandomhelyet =! true)
  {
    for (size_t i = 0; i < kigyohossza; i++)
    {
      snake randomkordinata;

      randomkordinata.x = random(0,7)
      randomkordinata.y = random(0,7)

      if(ellenorzes(randomkordinata) == false)
      {
        return randomkordinata;
      } 
    }
  }
}


void setup()
{
  lc.shutdown(0, false);
  lc.setIntensity(0, 0);
  lc.clearDisplay(0);
  Serial.begin(115200);
  randomSeed(analogRead(0));

  for (int i = kigyohossza - 1; i >= 0; i--)
  {
    kigyo[i].x = 4;
    kigyo[i].y = kigyohossza - 1 - i;
    pi[i] = 'w';
    lc.setLed(0, kigyo[i].x, kigyo[i].y, true);
    delay(KIGYOLASSUSAG);
  }
}

void loop()
{
  if (Serial.available())
  {
    if (iranyitas == 'w')
    {
      switch (Serial.read())
      {
      case 'a':
        iranyitas = 'a';
        break;

      case 'd':
        iranyitas = 'd';
        break;

      default:
        break;
      }
    }

    if (iranyitas == 'a')
    {
      switch (Serial.read())
      {
      case 'w':
        iranyitas = 'w';
        break;

      case 's':
        iranyitas = 's';
        break;

      default:
        break;
      }
    }

    if (iranyitas == 's')
    {
      switch (Serial.read())
      {
      case 'a':
        iranyitas = 'a';
        break;

      case 'd':
        iranyitas = 'd';
        break;

      default:
        break;
      }
    }

    if (iranyitas == 'd')
    {
      switch (Serial.read())
      {
      case 'w':
        iranyitas = 'w';
        break;

      case 's':
        iranyitas = 's';
        break;

      default:
        break;
      }
    }
  }

  lc.setLed(0, kigyo[kigyohossza - 1].x, kigyo[kigyohossza - 1].y, false);

  for (size_t i = kigyohossza - 1; i > 0; i--)
  {
    kigyo[i] = kigyo[i - 1];
  }

  switch (iranyitas)
  {
  case 'w':
    kigyo[0].y++;
    break;
  case 'a':
    kigyo[0].x--;
    break;

  case 's':
    kigyo[0].y--;
    break;

  case 'd':
    kigyo[0].x++;
    break;

  default:
    break;
  }

  if (kigyo[0].y > 7)
  {
    kigyo[0].y = 0;
  }
  if (kigyo[0].x > 7)
  {
    kigyo[0].x = 0;
  }
  if (kigyo[0].y < 0)
  {
    kigyo[0].y = 7;
  }
  if (kigyo[0].x < 0)
  {
    kigyo[0].x = 7;
  }

  lc.setLed(0, kigyo[0].x, kigyo[0].y, true);
  delay(KIGYOLASSUSAG);
}
