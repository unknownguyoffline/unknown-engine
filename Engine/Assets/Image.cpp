#include "Image.hpp"
#include <ThirdParty/stb/stb_image.h>


namespace Unknown
{
	
	void Image::Load(const char* filename, int channel)
	{
		FILE* fp = fopen(filename, "r");
		if (fp == nullptr)
		{
			printf("Failed to open file: %s\n", filename);
			return;
		}
		fclose(fp);
		int width, height;
		data = stbi_load(filename, &width, &height, nullptr, channel);
		size = { width, height };
	}
}
