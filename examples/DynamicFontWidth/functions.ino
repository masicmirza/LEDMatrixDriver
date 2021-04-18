// Functions

/**
 * This draws a sprite to the given position using the width and height supplied (usually 8x8)
 */
void drawSprite( char** sprite, int x, int y, int width, int height ){
  for( int iy = 0; iy < height; iy++ ) {
    for( int ix = 0; ix < width; ix++ ) {

      bool b = sprite[iy][ix] == '1';
      
      lmd.setPixel(x + ix, y + iy, b);
    }
  }
}

/**
 * This function draws a string of the given length to the given position.
 */
void drawString(char* text, int len, int x, int y ) {
  int totalLength = 0;
  
  for( int idx = 0; idx < len; idx ++ ) {
    int c = text[idx] - 32;
    String firstEl = font[c][0];
    int charLen = firstEl.length();

    // stop if char is outside visible area
    if( x + totalLength + charLen  > LEDMATRIX_WIDTH ) {
      return;
    }

    // only draw if char is visible
    if( charLen + x + totalLength > 0 ) {
      drawSprite( font[c], x + totalLength, y, charLen, 8 );
    }

    totalLength = totalLength + charLen;
  }
}

/**
 * This function returns total bit length of the string (translated from the font)
 */
int getTotalBitLength(int len) {
    int totalBitLength = 0;

    for( int idx = 0; idx < len; idx ++ ) {
        int c = text[idx] - 32;
        String firstEl = font[c][0];
        int charLen = firstEl.length();
        totalBitLength = totalBitLength + charLen;
    }

    return totalBitLength;
}