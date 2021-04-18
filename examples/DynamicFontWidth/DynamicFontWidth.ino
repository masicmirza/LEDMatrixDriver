// This sketch shows how to use dynamic font widths with the LEDMatrixDriver library.
// Example written 2021-04-18 by Mirza Masic, https://github.com/masicmirza.

#include <LEDMatrixDriver.hpp>

// Only include one font
#include "font_condensed.h"    // Original font, but without extra spaces
//#include "font_narrow.h"       // Small/narrow font
//#include "font_wide.h"         // Original font
//#include "font_7_segment.h"    // 7 Segment font (digits only, other characters are from narrow font)

// Only un-comment one of the lines below
//#define L2R   //Left to right scroll    
//#define R2L   //Right to left scroll
#define AS    //Auto scroll if length of text > display width

// Define CS pin 
#define CS_PIN 15

// Number of 8x8 segments you are connecting
const int LEDMATRIX_SEGMENTS = 4;
const int LEDMATRIX_WIDTH    = LEDMATRIX_SEGMENTS * 8;

// The LEDMatrixDriver class instance
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, CS_PIN);

// Marquee text
char text[] = "** LED MATRIX DEMO! ** (1234567890) ++ \"ABCDEFGHIJKLMNOPQRSTUVWXYZ\" ++ <$%/=?'.@,> --";

// Marquee speed (lower nubmers = faster)
const int ANIM_DELAY = 30;

int x=0, y=0;   // start top left

void setup()
{
    Serial.begin(115200);
    delay(10);

    // init the display
    lmd.setEnabled(true);
    lmd.setIntensity(0);   // 0 = low, 10 = high
}

void loop() {
    int len = strlen(text);

    drawString(text, len, x, 0);
    
    lmd.display();

    delay(ANIM_DELAY);

    int totalBitLength = getTotalBitLength(len);

    //Scrolling
    #ifdef L2R
    //For left to right scroll
    if( ++x > LEDMATRIX_WIDTH ){
        x = -1 * totalBitLength;
    }
    #endif
    #ifdef R2L
    //For right to left scroll
    if( --x < -1 * totalBitLength ) {
        x = LEDMATRIX_WIDTH;
    }
    #endif
    #ifdef AS
    //For autoscroll (L2R) if length of text > width of screen
    if(totalBitLength >  LEDMATRIX_WIDTH) {
        if( --x < -1 * totalBitLength ) {
            x = LEDMATRIX_WIDTH;
        }
    }
    #endif
}

