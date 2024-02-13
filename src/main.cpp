// Simple date conversions and calculations

#include <SPI.h>
#include "RTClib.h"
RTC_DS3231 rtc;

// +
#define I 8
#define II 7
#define III 6
#define IV 5

// -
#define A 11
#define B 14
#define C 15
#define D 10
#define E_I 16
#define E_F 9
#define F 12
#define G 17

// MIDDLE DOTS
#define H_P 3
#define H_M 4

class Display
{
private:
  uint8_t x = 0;

public:

  uint8_t get() {
    return this->x;
  }

  void next() {
    if (this->x == 3)
      this->x = 0;
    else
      ++this->x;
  }
};

constexpr uint8_t nOpins = 14;
uint8_t pins[nOpins] = { I, II, III, IV, A, B, C, D, E_I, E_F, F, G, H_P, H_M };

Display actualDisplay;

uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;

uint8_t hour_ones = 0;
uint8_t hour_tens = 0;
uint8_t minute_ones = 0;
uint8_t minute_tens = 0;

uint8_t digits[4];

void setPinModes();
void showAll();
void lowAll();
void disp(uint8_t di[]);

void displayOne();
void displayTwo();
void displayThree();
void displayFour();
void displayFive();
void displaySix();
void displaySeven();
void displayEight();
void displayNine();
void displayZero();

void changeMiddleDots();

void setup () {
    rtc.begin();
    setPinModes();
}

void loop () {
  DateTime now = rtc.now();

  hour = now.hour();
  minute = now.minute();

  digits[1] = hour % 10; // HOUR ONES
  digits[0] = (hour/10) % 10; // HOUR TENS

  digits[3] = minute % 10; // MINUTE ONES
  digits[2] = (minute/10) % 10; // MINUTE TENS

  if (second != now.second()) {
    changeMiddleDots();
    second = now.second();
  }

  disp(digits);
  delay(1); // 4 - 60Hz, 3 - 90Hz, 2 - 120Hz, 1 - 240Hz
}

void setPinModes() {
    for (uint8_t i = 0; i < nOpins; ++i) {
      pinMode(pins[i], OUTPUT);
      digitalWrite(pins[i], LOW);
    }
}

void lowAll() {
    for (uint8_t i = 0; i < nOpins - 2; ++i) {
      digitalWrite(pins[i], LOW);
    }
}


void disp(uint8_t di[]) {
  lowAll();
  digitalWrite(pins[actualDisplay.get()], HIGH);

  switch (di[actualDisplay.get()])
  {
  case 1:
    displayOne();
    break;
  case 2:
    displayTwo();
    break;
  case 3:
    displayThree();
    break;
  case 4:
    displayFour();
    break;
  case 5:
    displayFive();
    break;
  case 6:
    displaySix();
    break;
  case 7:
    displaySeven();
    break;
  case 8:
    displayEight();
    break;
  case 9:
    displayNine();
    break;
  case 0:
    displayZero();
    break;
  }

  actualDisplay.next();
}

void displayOne() {
    digitalWrite(A, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(F, HIGH);
    if (actualDisplay.get() == 0)
      digitalWrite(E_I, HIGH);
    else
      digitalWrite(E_F, HIGH);
}

void displayTwo() {
    digitalWrite(F, HIGH);
    digitalWrite(C, HIGH);
}

void displayThree() {
    digitalWrite(F, HIGH);
    if (actualDisplay.get() == 0)
      digitalWrite(E_I, HIGH);
    else
      digitalWrite(E_F, HIGH);
}

void displayFour() {
    digitalWrite(A, HIGH);
    if (actualDisplay.get() == 0)
      digitalWrite(E_I, HIGH);
    else
      digitalWrite(E_F, HIGH);
    digitalWrite(D, HIGH);
}

void displayFive() {
    digitalWrite(B, HIGH);
    if (actualDisplay.get() == 0)
      digitalWrite(E_I, HIGH);
    else
      digitalWrite(E_F, HIGH);
}

void displaySix() {
    digitalWrite(B, HIGH);
}

void displaySeven() {
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
    if (actualDisplay.get() == 0)
      digitalWrite(E_I, HIGH);
    else
      digitalWrite(E_F, HIGH);
    digitalWrite(D, HIGH);
}

void displayEight() {
    
}

void displayNine() {
    if (actualDisplay.get() == 0)
      digitalWrite(E_I, HIGH);
    else
      digitalWrite(E_F, HIGH);
}

void displayZero() {
  digitalWrite(G, HIGH);
}

void changeMiddleDots() {
  if (digitalRead(H_P))
    digitalWrite(H_P, LOW);
  else
    digitalWrite(H_P, HIGH);
}