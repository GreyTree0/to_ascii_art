#include "ascii_converter.h"

//const char ascii_table[34] = " `.,'-~:;*+\"^_<=>!?|/\\()[]{}%&@$#";
const char ascii_table[34] = "#$@&%}{][)(\\/|?!>=<_^\"+*;:~-',.` "; 
const int table_length = 33; // 33 characters + \0

float random_noise(int min, int max);

char rgb_to_ascii(color c) {
	return ascii_table[(int) ((float) (c.r + c.b + c.g) / 765) * table_length];
}

char grayscale_to_ascii_noise(uint8_t strength, unsigned int noise_strength) {
	int noise_range = noise_strength * table_length / 30;
	float noise = random_noise(-noise_range, noise_range);	

	float scalar_value = (float) (strength + noise) / 255;
	return ascii_table[(int) (scalar_value * table_length)];
}

char grayscale_to_ascii(uint8_t strength) {
	//printf(" [%d]", strength);
	float scalar_value = (float) strength / 255;
	return ascii_table[(int) (scalar_value * table_length)];
}

#define r color_array[0]
#define g color_array[1]
#define b color_array[2]

char* get_ansi_color(uint8_t* color_array, bool grayscale) {
	
	/* List of all ansi colors:

		Basic "Darker"
		\e[0;30m 	Black
		\e[0;31m 	Red
		\e[0;32m 	Green
		\e[0;33m 	Yellow
		\e[0;34m 	Blue
		\e[0;35m 	Purple
		\e[0;36m 	Cyan
		\e[0;37m 	White
		
		Intense "Lighter"
		\e[0;90m 	Black
		\e[0;91m 	Red
		\e[0;92m 	Green
		\e[0;93m 	Yellow
		\e[0;94m 	Blue
		\e[0;95m 	Purple
		\e[0;96m 	Cyan
		\e[0;97m 	White	
			
		\e[0m 	Reset
]

	*/

	if (grayscale) {
		// Any way to optimize? "binary search"
		// Grayscale stength maoed to a grayscale ansi value.
		if (color_array[0] >= 192) return "\e[0;30m";	// Black.
		if (color_array[0] >= 128) return "\e[0;90m";	// Gray (Intence black)
		if (color_array[0] >= 64) return "\e[0;37m";	// Light gray (Basic white).
		return "\e[0;97m";								// White.

	} else {
		
		// Some algorithm to map rgb to a value between 1-how many ansi colors there are.?
		// if r > x and g, b < y then red
		// ...
		
		if (g < 150 && b < 150) {
			if (r > 155) return "\e[0;91m";
			if (r > 45) return "\e[0;31m";
		}
	}


	return "\e[0m"; 
}

#undef r
#undef g
#undef b

float random_noise(int min, int max) {
	float scalar = (float) rand() / (float) RAND_MAX;
	return min + scalar * (max - min);
}

