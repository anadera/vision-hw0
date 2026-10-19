#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // clamp if the pixel out of range
    c = c < 0 ? 0 : c >= im.c ? im.c - 1 : c;
    y = y < 0 ? 0 : y >= im.h ? im.h - 1 : y;
    x = x < 0 ? 0 : x >= im.w ? im.w - 1 : x;

    int index = c * im.w * im.h + y * im.w + x;
    return im.data[index];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if (x >= 0 && x < im.w &&
        y >= 0 && y < im.h &&
        c >= 0 && c < im.c)
    {
        int index = c * im.w * im.h + y * im.w + x;
        im.data[index] = v;
    }
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    for (int c = 0; c < im.c; ++c) {
        for (int y = 0; y < im.h; ++y) {
            for (int x = 0; x < im.w; ++x) {
                float pixel = get_pixel(im, x, y, c);
                set_pixel(copy, x, y, c, pixel);
            }
        }
    }
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    for (int y = 0; y < im.h; ++y) {
        for (int x = 0; x < im.w; ++x) {
            float r = get_pixel(im, x, y, 0);
            float g = get_pixel(im, x, y, 1);
            float b = get_pixel(im, x, y, 2);
            float scaled = 0.299 * r + 0.587 * g + .114 * b;
            set_pixel(gray, x, y, 0, scaled);
        }
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    for (int y = 0; y < im.h; ++y) {
        for (int x = 0; x < im.w; ++x) {
            float pixel = get_pixel(im, x, y, c);
            pixel = pixel + v;
            set_pixel(im, x, y, c, pixel);
        }
    }
}

void clamp_image(image im)
{
    for (int c = 0; c < im.c; ++c) {
        for (int y = 0; y < im.h; ++y) {
            for (int x = 0; x < im.w; ++x) {
                float pixel = get_pixel(im, x, y, c);
                pixel = pixel < 0 ? 0 : pixel > 1 ? 1 : pixel;
                set_pixel(im, x, y, c, pixel);
            }
        }
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
