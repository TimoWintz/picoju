#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"

#include "libraries/pico_graphics/pico_graphics.hpp"
#include "libraries/stellar_unicorn/stellar_unicorn.hpp"
#include "libraries/breakout_ioexpander/breakout_ioexpander.hpp"



using namespace pimoroni;

PicoGraphics_PenRGB888 graphics(16, 16, nullptr);

StellarUnicorn stellar_unicorn;

std::string message_a = "A";
std::string message_b = "B";
std::string message_c = "C";
std::string message_d = "D";

static void draw_arrow(int direction, Color color) {
    graphics.set_pen(0, 0, 0);
    graphics.clear();
    graphics.set_pen(color.r, color.g, color.b);
    
    // Draw arrow based on direction (0=up, 1=right, 2=down, 3=left)
    switch(direction) {
        case 0: // Up arrow
            graphics.line(Point(8, 4), Point(8, 12));  // Shaft
            graphics.line(Point(8, 4), Point(4, 8));   // Left wing
            graphics.line(Point(8, 4), Point(12, 8));  // Right wing
            break;
        case 1: // Right arrow
            graphics.line(Point(4, 8), Point(12, 8));  // Shaft
            graphics.line(Point(12, 8), Point(8, 4));  // Upper wing
            graphics.line(Point(12, 8), Point(8, 12)); // Lower wing
            break;
        case 2: // Down arrow
            graphics.line(Point(8, 4), Point(8, 12));  // Shaft
            graphics.line(Point(8, 12), Point(4, 8));  // Left wing
            graphics.line(Point(8, 12), Point(12, 8)); // Right wing
            break;
        case 3: // Left arrow
            graphics.line(Point(4, 8), Point(12, 8));  // Shaft
            graphics.line(Point(4, 8), Point(8, 4));   // Upper wing
            graphics.line(Point(4, 8), Point(8, 12));  // Lower wing
            break;
    }
    stellar_unicorn.update(&graphics);
}


struct Color
{
    int r;
    int g;
    int b;
};

static void write_letter(const char* msg, Color color) {
    std::string str = msg;
    graphics.set_pen(0, 0, 0);
    graphics.clear();
    graphics.set_pen(color.r, color.g, color.b);
    graphics.text(str, Point(1, 11), 0, 2, 270);
    stellar_unicorn.update(&graphics);
}

int main()
{

    //stdio_init_all();
    stellar_unicorn.init();
    stellar_unicorn.set_brightness(0.5f);  // Set to 50% brightness
    
    std::string message = message_a;

    while (true)
    {
        bool state = true;

        if (stellar_unicorn.is_pressed(stellar_unicorn.SWITCH_BRIGHTNESS_UP))
        {
            draw_arrow(0, Color{255,0,0}); // Up arrow
        }
        else if (stellar_unicorn.is_pressed(stellar_unicorn.SWITCH_BRIGHTNESS_DOWN))
        {
            draw_arrow(2, Color{0, 255, 0}); // Down arrow
        }
        if (stellar_unicorn.is_pressed(stellar_unicorn.SWITCH_VOLUME_UP))
        {
            draw_arrow(1, Color{0, 0, 255}); // Right arrow
        }
        else if (stellar_unicorn.is_pressed(stellar_unicorn.SWITCH_VOLUME_DOWN))
        {
            draw_arrow(3, Color{0, 0, 255}); // Left arrow
        }
        
        if (stellar_unicorn.is_pressed(stellar_unicorn.SWITCH_A))
        {
           write_letter("A", Color{255,0,0});
        }
        else if (stellar_unicorn.is_pressed(stellar_unicorn.SWITCH_B))
        {
            write_letter("B", Color{0, 255, 0});
        }
        else if (stellar_unicorn.is_pressed(stellar_unicorn.SWITCH_C))
        {
            write_letter("C", Color{0, 0, 255});
        }
        else if (stellar_unicorn.is_pressed(stellar_unicorn.SWITCH_D))
        {
            write_letter("D", Color{
                                  255,
                                  255,
                                  0
                              });
        }

        stellar_unicorn.update(&graphics);

        sleep_ms(10);
    }

    return 0;
}