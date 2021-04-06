#ifndef _COLOR_H
#define _COLOR_H

#include <stdio.h>
#include <SDL.h>

// Type alias for RGB colors.
typedef unsigned char byte;

// HSLA
typedef struct {
    int Hue;            // Hue from 0 to 359
    float Saturation,   // Sat from 0.0 to 1.0
          Luminance,    // Lum from 0.0 to 1.0
          Alpha;        // Opacity from 0.0 to 1.0
} Color_HSLA;

// RGBA
typedef struct {
    byte Red,           // Red color channel from 0 to 255
         Green,         // Green color channel from 0 to 255
         Blue;          // Blue color channel from 0 to 255
    float Alpha;        // Opacity from 0.0 to 1.0
} Color_RGBA;

// Initialization Functions
Color_RGBA RGBA(byte, byte, byte, float);
Color_RGBA RGB(byte, byte, byte);
Color_HSLA HSLA(int, float, float, float);
Color_HSLA HSL(int, float, float);

// Conversion Functions
Color_RGBA HSLA_RGBA(Color_HSLA);
Color_HSLA RGBA_HSLA(Color_RGBA);

// Modification Functions
void modify_channels(Color_RGBA, byte, byte, byte);
void modify_hue(Color_HSLA, int);
void modify_saturation(Color_HSLA, float);
void modify_luminance(Color_HSLA, float);
void modify_alpha_rgba(Color_RGBA, float);
void modify_alpha_hsla(Color_HSLA, float);

// Generation Functions
Color_RGBA generate_rgba(void);
Color_RGBA generate_rgb(void);
Color_HSLA generate_hsla(void);
Color_HSLA generate_hsl(void);

#endif // _COLOR_H