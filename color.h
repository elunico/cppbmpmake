#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

typedef uint8_t byte;

struct Color {
  byte red, green, blue;
};

extern Color const black;
extern Color const white;
extern Color const red;
extern Color const blue;
extern Color const green;
extern Color const cyan;
extern Color const magenta;
extern Color const yellow;

#endif
