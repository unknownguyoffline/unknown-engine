#pragma once
#include <unordered_map>
#include <Assets/Font.hpp>
#include <string>

namespace Unknown
{
	class FontLibrary
	{
	public:
		Font& Load(const char* filename, const char* identifier, uint32_t pixelSize = 128);
		void Create(Font font, const char* identifier);

		Font Get(const char* identifier);
		Font& GetRef(const char* identifier);

	private:
		std::unordered_map<int32_t, Font> mMap;
		std::hash <std::string> mHasher;
	};
}