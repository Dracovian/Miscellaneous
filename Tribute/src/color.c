#include <SDL.h>
#include <math.h>

#include "pcg.h"
#include "color.h"

// Simple defines

#define max(a, b, c) ((a) <= (b) ? (b) <= (c) ? (c) : (b) : (a))
#define min(a, b, c) ((a) >= (b) ? (b) >= (c) ? (c) : (b) : (a))

// Static functions (functions not shared with the header)

static void pcg_init(random_t *rand) {
    unsigned long long seeds[2];

    entropy_getbytes((void *) seeds, sizeof(seeds));
    pcg_srandom(rand, seeds[0], seeds[1]);
}

static void random_rgba(byte *R, byte *G, byte *B, float *A) {
    random_t rand;
    pcg_init(&rand);

    *R = (byte)  pcg_boundedrand(&rand, 0, 255);
    *G = (byte)  pcg_boundedrand(&rand, 0, 255);
    *B = (byte)  pcg_boundedrand(&rand, 0, 255);
    *A = (float) pcg_boundedrand(&rand, 0, 100) / 100.0f;
}

static void random_hsla(int *H, float *S, float *L, float *A) {
    random_t rand;
    pcg_init(&rand);

    *H = (int)   pcg_boundedrand(&rand, 0, 359);
    *S = (float) pcg_boundedrand(&rand, 0, 100) / 100.0f;
    *L = (float) pcg_boundedrand(&rand, 0, 100) / 100.0f;
    *A = (float) pcg_boundedrand(&rand, 0, 100) / 100.0f;
}

// Header functions

Color_RGBA RGBA(byte Red, byte Green, byte Blue, float Alpha) {
    return (Color_RGBA) { Red, Green, Blue, Alpha };
}

Color_RGBA RGB(byte Red, byte Green, byte Blue) {
    return (Color_RGBA) { Red, Green, Blue, 1.0f };
}

Color_HSLA HSLA(int Hue, float Saturation, float Luminance, float Alpha) {
    return (Color_HSLA) { Hue, Saturation, Luminance, Alpha };
}

Color_HSLA HSL(int Hue, float Saturation, float Luminance) {
    return (Color_HSLA) { Hue, Saturation, Luminance, 1.0f };
}

Color_RGBA HSLA_RGBA(Color_HSLA Color) {
    float C = (1 - fabsf((2 * Color.Luminance) - 1)) * Color.Saturation,
          X = C * (1 - (float) labs(((Color.Hue / 60) % 2) - 1)),
          m = Color.Luminance - (C / 2.0f);

    byte R, G, B;
    R = G = B = 0;

    if (Color.Hue >= 0 && Color.Hue < 60) {
        R = roundf((C + m) * 255);
        G = roundf((X + m) * 255);
        B = 0;
    } else if (Color.Hue >= 60 && Color.Hue < 120) {
        R = roundf((X + m) * 255);
        G = roundf((C + m) * 255);
        B = 0;
    } else if (Color.Hue >= 120 && Color.Hue < 180) {
        R = 0;
        G = roundf((C + m) * 255);
        B = roundf((X + m) * 255);
    } else if (Color.Hue >= 180 && Color.Hue < 240) {
        R = 0;
        G = roundf((X + m) * 255);
        B = roundf((C + m) * 255);
    } else if (Color.Hue >= 240 && Color.Hue < 300) {
        R = roundf((X + m) * 255);
        G = 0;
        B = roundf((C + m) * 255);
    } else if (Color.Hue >= 300 && Color.Hue < 360) {
        R = roundf((C + m) * 255);
        G = 0;
        B = roundf((X + m) * 255);
    };

    if (Color.Saturation == 0.0f && Color.Luminance == 0.0f)
        R = G = B = 0;

    if (Color.Saturation == 0.0f && Color.Luminance == 1.0f)
        R = G = B = 255;

    if (Color.Saturation == 0.0f && Color.Luminance > 0.0f && Color.Luminance < 1.0f)
        R = G = B = roundf(255 * Color.Luminance);

    return (Color_RGBA) { R, G, B, Color.Alpha };
}

Color_HSLA RGBA_HSLA(Color_RGBA Color) {
    float R = (float) Color.Red   / 255.0f,
          G = (float) Color.Green / 255.0f,
          B = (float) Color.Blue  / 255.0f,
          Cmax  = max(R, G, B),
          Cmin  = min(R, G, B),
          delta = Cmax - Cmin;

    int   H = 0;
    float L = (Cmax + Cmin) / 2.0f,
          S = 0.0f;

    if (delta != 0) {
        if (L < 0.5f) S = delta / (Cmax + Cmin);
        else S = delta / (2 - delta);

        if (Cmax == R)      H = 60 * (int)(((G - B) / delta));
        else if (Cmax == G) H = 60 * (int)(((B - R) / delta) + 2);
        else if (Cmax == B) H = 60 * (int)(((R - G) / delta) + 4);
    }

    if (H < 0) H += 360;
    return (Color_HSLA) { H, S, L, Color.Alpha };
}

void modify_channels(Color_RGBA Color, byte Red, byte Green, byte Blue) {
    Color = (Color_RGBA) { Red, Green, Blue, Color.Alpha };
}

void modify_hue(Color_HSLA Color, int Hue) {
    Color = (Color_HSLA) { Hue, Color.Saturation, Color.Luminance, Color.Alpha };
}

void modify_saturation(Color_HSLA Color, float Saturation) {
    Color = (Color_HSLA) { Color.Hue, Saturation, Color.Luminance, Color.Alpha };
}

void modify_luminance(Color_HSLA Color, float Luminance) {
    Color = (Color_HSLA) { Color.Hue, Color.Saturation, Luminance, Color.Alpha };
}

void modify_alpha_rgba(Color_RGBA Color, float Alpha) {
    Color = (Color_RGBA) { Color.Red, Color.Green, Color.Blue, Alpha };
}

void modify_alpha_hsla(Color_HSLA Color, float Alpha) {
    Color = (Color_HSLA) { Color.Hue, Color.Saturation, Color.Luminance, Alpha };
}

Color_RGBA generate_rgba(void) {
    byte R, G, B;
    float A;

    random_rgba(&R, &G, &B, &A);
    return RGBA(R, G, B, A);
}

Color_RGBA generate_rgb(void) {
    byte R, G, B;
    float A;

    random_rgba(&R, &G, &B, &A);
    return RGB(R, G, B);
}

Color_HSLA generate_hsla(void) {
    float S, L, A;
    int H;

    random_hsla(&H, &S, &L, &A);
    return HSLA(H, S, L, A);
}

Color_HSLA generate_hsl(void) {
    float S, L, A;
    int H;

    random_hsla(&H, &S, &L, &A);
    return HSL(H, S, L);
}