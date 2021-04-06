#include <stdio.h>
#include "src/color.h"

int main(void) {

    /* Introduce our test HSL colors.
    **
    ** The following colors will be used for this test:
    **   - Red
    **     - RGB(255, 0, 0)
    **     - HSL(0°, 100%, 50%)
    **
    **   - Green
    **     - RGB(0, 255, 0)
    **     - HSL(120°, 100%, 50%)
    **
    **   - Blue
    **     - RGB(0, 0, 255)
    **     - HSL(240°, 100%, 50%)
    **
    **   - Black
    **     - RGB(0, 0, 0)
    **     - HSL(0°, 0%, 0%)
    **
    **   - White
    **     - RGB(255, 255, 255)
    **     - HSL(0°, 0%, 100%)
    **
    **   - Gray
    **     - RGB(128, 128, 128)
    **     - HSL(0°, 0%, 50%)
    **
    **   - Purple
    **     - RGB(128, 0, 128)
    **     - HSL(300°, 100%, 25%)
    */
    Color_HSLA Color_Red    = HSL(  0, 1.0f, 0.50f);
    Color_HSLA Color_Green  = HSL(120, 1.0f, 0.50f);
    Color_HSLA Color_Blue   = HSL(240, 1.0f, 0.50f);
    Color_HSLA Color_Black  = HSL(  0, 0.0f, 0.00f);
    Color_HSLA Color_White  = HSL(  0, 0.0f, 1.00f);
    Color_HSLA Color_Gray   = HSL(  0, 0.0f, 0.50f);
    Color_HSLA Color_Purple = HSL(300, 1.0f, 0.25f);

    /* Test our HSLA => RGBA function. */
    Color_RGBA Red    = HSLA_RGBA(Color_Red   );
    Color_RGBA Green  = HSLA_RGBA(Color_Green );
    Color_RGBA Blue   = HSLA_RGBA(Color_Blue  );
    Color_RGBA Black  = HSLA_RGBA(Color_Black );
    Color_RGBA White  = HSLA_RGBA(Color_White );
    Color_RGBA Gray   = HSLA_RGBA(Color_Gray  );
    Color_RGBA Purple = HSLA_RGBA(Color_Purple);

    /* Print out the RGB equivalent to our HSL colors. */
    fprintf(
        stdout,

        "\n     HSLA_RGBA Function Test\n"
        "  +--------+-----+-----+-----+\n"
        "  | RED    | %3u | %3u | %3u |\n"
        "  | GREEN  | %3u | %3u | %3u |\n"
        "  | BLUE   | %3u | %3u | %3u |\n"
        "  | BLACK  | %3u | %3u | %3u |\n"
        "  | WHITE  | %3u | %3u | %3u |\n"
        "  | GRAY   | %3u | %3u | %3u |\n"
        "  | PURPLE | %3u | %3u | %3u |\n"
        "  +--------+-----+-----+-----+\n\n",

        Red.Red,    Red.Green,    Red.Blue,
        Green.Red,  Green.Green,  Green.Blue,
        Blue.Red,   Blue.Green,   Blue.Blue,
        Black.Red,  Black.Green,  Black.Blue,
        White.Red,  White.Green,  White.Blue,
        Gray.Red,   Gray.Green,   Gray.Blue,
        Purple.Red, Purple.Green, Purple.Blue
    );

    /* Test our RGBA => HSLA function. */
    Color_HSLA HSLA_Red    = RGBA_HSLA(Red   );
    Color_HSLA HSLA_Green  = RGBA_HSLA(Green );
    Color_HSLA HSLA_Blue   = RGBA_HSLA(Blue  );
    Color_HSLA HSLA_Black  = RGBA_HSLA(Black );
    Color_HSLA HSLA_White  = RGBA_HSLA(White );
    Color_HSLA HSLA_Gray   = RGBA_HSLA(Gray  );
    Color_HSLA HSLA_Purple = RGBA_HSLA(Purple);

    /* Print out the HSL equivalent to our RGB colors. */
    fprintf(
        stdout,

        "    RGBA_HSLA function test          \n"
        "+--------+------+------+------+      \n"
        "| RED    | %3d° | %3.0f%% | %3.0f%% |\n"
        "| GREEN  | %3d° | %3.0f%% | %3.0f%% |\n"
        "| BLUE   | %3d° | %3.0f%% | %3.0f%% |\n"
        "| BLACK  | %3d° | %3.0f%% | %3.0f%% |\n"
        "| WHITE  | %3d° | %3.0f%% | %3.0f%% |\n"
        "| GRAY   | %3d° | %3.0f%% | %3.0f%% |\n"
        "| PURPLE | %3d° | %3.0f%% | %3.0f%% |\n"
        "+--------+------+------+------+      \n",

        HSLA_Red.Hue,    HSLA_Red.Saturation * 100.0f,    HSLA_Red.Luminance * 100.0f,
        HSLA_Green.Hue,  HSLA_Green.Saturation * 100.0f,  HSLA_Green.Luminance * 100.0f,
        HSLA_Blue.Hue,   HSLA_Blue.Saturation * 100.0f,   HSLA_Blue.Luminance * 100.0f,
        HSLA_Black.Hue,  HSLA_Black.Saturation * 100.0f,  HSLA_Black.Luminance * 100.0f,
        HSLA_White.Hue,  HSLA_White.Saturation * 100.0f,  HSLA_White.Luminance * 100.0f,
        HSLA_Gray.Hue,   HSLA_Gray.Saturation * 100.0f,   HSLA_Gray.Luminance * 100.0f,
        HSLA_Purple.Hue, HSLA_Purple.Saturation * 100.0f, HSLA_Purple.Luminance * 100.0f
    );

    return 0;
}