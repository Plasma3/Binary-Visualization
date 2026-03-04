#include "lib/fcu_common.h"
#include "math.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"
	#include "lib/stb_image_write.h"
	#include "lib/stb_image.h"
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop

// Allocate the map in static memory
#define MAP_WIDTH 256
#define MAP_SIZE  MAP_WIDTH * MAP_WIDTH
u64 static_map[MAP_SIZE] = {0};

bool load_image_file(cchar _cptr(filename), u64 map[static MAP_SIZE])
{
	i32 width, height, comp;
	f_FOR_u32_i(MAP_SIZE)
		map[i] = 0;

	str_t remappedFileName = f_strmap_swedish2ascii(filename, f_strlen(filename));
	u8* data = stbi_load(remappedFileName, &width, &height, &comp, 0);
	f_FREE(remappedFileName);

	if (width <= 0 || height <= 0 || comp <= 0 || data == nullptr) 
		return false;
	
	printf_s("Image file recognized! A %dx%d image with %i bits per pixel\n", width, height, comp * 8);

	f_FOR_int_i_1(width * height * comp)
		map[ data[i - 1] + data[i] * MAP_WIDTH ]++;

	stbi_image_free(data);

	return true;
}
bool load_binary_file(cchar _cptr(filename), u64 map[static MAP_SIZE])
{
	FILE* file = nullptr;
	// u32c readBufferSize = kiloByte;


	// Zero out the map
	f_FOR_u32_i(MAP_SIZE)
		map[i] = 0;

	// Open the file
	str_t remappedFileName = f_strmap_swedish2ascii(filename, f_strlen(filename));
	assert(0 == fopen_s(&file, remappedFileName, "rb"));
	f_FREE(remappedFileName);

	int previousByte = fgetc(file);
	int  currentByte = 0;
	assert(previousByte != EOF); // File is empty

	// Read and enter all byte pairs into the map
	while ( EOF != (currentByte = fgetc(file)) )
	{
		assert(previousByte < MAP_WIDTH);
		assert( currentByte < MAP_WIDTH);

		// Use previousByte and currentByte as (X, Y) into the map
		map[ previousByte + currentByte * MAP_WIDTH ]++;
		previousByte = currentByte;
	}

	// Close the file
	fclose(file);

	return true;
}

bool createImageFromMap(cchar _cptr(filename), u64c map[static MAP_SIZE])
{
	// Find biggest value to determine the range
	f64 highestValue = log(0.0 + 1);
	f64  lowestValue = log(0.0 + 1);
	f_FOR_u32_i(MAP_SIZE) {
		f64 currentValue = log((f64) map[i] + 1);
		lowestValue  = f_min( lowestValue, currentValue);
		highestValue = f_max(highestValue, currentValue);
	}

	printf_s("Genrating grayscale image \"%s\" with the logaritmic range %.1f to %.1f\n", filename, lowestValue, highestValue);

	// Allocate the "image" in stack
	u8 image[MAP_SIZE] = {0};

	// For every pixel, normalize it
	f_FOR_u32_i(MAP_SIZE) {
		f64 currentValue = log((f64) map[i] + 1);
		f64 t = f_unlerp_between(lowestValue, highestValue, currentValue);
			t = f_clamp(t, 0.0, 1.0);
		u8 brightness = (u8) (t * MAP_WIDTH);

		image[i] = brightness;
	}

	return stbi_write_png(filename, MAP_WIDTH, MAP_WIDTH, 1, image, MAP_WIDTH);
}

bool tryReadFileAsImage(cchar _cptr(filename), u64 map[static MAP_SIZE])
{
	if (!load_image_file(filename, map)) return false; 

	printf_s("Successfully loaded the file as an image!\n");
	
	str_t outputFilename = "raw image visualization.png";
	assert(createImageFromMap(outputFilename, map));
	printf_s("Raw image binary visualization stored to \"%s\"!\n", outputFilename);

	return true;
}

int main(int argc, char** argv)
{
	assert(argc == 2);

	tryReadFileAsImage(argv[1], static_map);	

	assert(load_binary_file(argv[1], static_map));
	assert(createImageFromMap("result.png", static_map));
	
	assert_allFileClosed();
	return 0;
}

/**
 * TODO:
 * https://en.wikipedia.org/wiki/Hilbert_curve
 * https://www.fundza.com/algorithmic/space_filling/hilbert/basics/
 * FFMPEG?
 * 3D
 */