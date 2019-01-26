//www.elegoo.com
//2016.12.09

// Arduino pin numbers

/*void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}*/

/*void loop() {
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
  delay(500);
}
*/


#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

// Similar to F(), but for PROGMEM string pointers rather than literals
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

#define RED matrix.Color888(66,0,0,true)
#define WHITE matrix.Color888(66,66,66,true)
#define GREEN matrix.Color888(0,66,0,true)
#define BLUE matrix.Color888(0,0,66,true)
// Last parameter = 'true' enables double-buffering, for flicker-free,
// buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
// until the first call to swapBuffers().  This is normal.
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);
// Double-buffered mode consumes nearly all the RAM available on the
// Arduino Uno -- only a handful of free bytes remain.  Even the
// following string needs to go in PROGMEM:

const int SW_pin = 12; // digital pin connected to switch output
const int X_pin = 5; // analog pin connected to X output
//const int Y_pin = 1; // analog pin connected to Y output

const char str[] PROGMEM = "Adafruit 16x32 RGB LED Matrix";
int    textX   = matrix.width(),
       textMin = sizeof(str) * -12,
       hue     = 0;

unsigned __int128 bigNum = 0x000000000001E0000000C0000001E000 
int carX = 15;
int j=0 , b, b2=0;

void setup() {
  matrix.begin();
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextSize(2);
  

}

void loop() {
  byte i;
  //Serial.begin(9600);
  //int i = 0;
  //uint8_t* buff = matrix.backBuffer();
  
    
  // Clear background
  matrix.fillScreen(0);

  
  if (( carX >= 3 ) && ( analogRead(X_pin) < 50 ))
  {
    carX--;
    bigNum<<1;
  }
  if (( carX <= 25 ) && ( analogRead(X_pin) > 900 ))
  {
    carX++;
    bigNum>>1;
  }
    
 gameOver();
  
  delay(1000);
 // for (i=0; i < 511; i++)
  //  Serial.println(*buff);
    
}

void drawCar(double long * bigNum)
{

  matrix.drawFastHLine(carX,   15, 4, BLUE);
  matrix.drawFastHLine(carX+1, 14, 2, BLUE);
  matrix.drawFastHLine(carX,   13, 4, BLUE);
}

void gameOver()
{
  const char str[] PROGMEM = "YOU LOSE\n¯\\_(ツ)_/¯";
  matrix.print(F2(str));
}

