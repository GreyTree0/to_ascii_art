#ifndef ASCII_CONVERTER_H
#define ASCII_CONVERTER_H

#include "image_parser.h"

/** 
 * Takes an rgb value and converts it to an ascii character, of equal opacity.
**/
char rgb_to_ascii(color c);


/**
 * Takes a grayscale value and convertes it to an ascci character, of equal opacity.
 * Set 'noise_stength' to zero for no noise. 
**/
char grayscale_to_ascii_noise(uint8_t stregth, unsigned int noise_strength);

char grayscale_to_ascii(uint8_t stregth);

// Operates on both grayscale and rgb values, just as byte arrays of length 1 resp. 3.
char* get_ansi_color(uint8_t* color_values, bool grayscale);



#endif
