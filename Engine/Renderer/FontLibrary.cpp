#include "FontLibrary.hpp"
#include <print>

namespace Unknown
{
	Font& FontLibrary::Load(const char* filename, const char* identifier, uint32_t pixelSize)
	{
		Font font;
		font.Load(filename, pixelSize);
		mMap[mHasher(identifier)] = font;
		return mMap[mHasher(identifier)];
	}

	void FontLibrary::Create(Font font, const char* identifier)
	{
		mMap[mHasher(identifier)] = font;
	}

	Font FontLibrary::Get(const char* identifier)
	{
		assert(mMap.find(mHasher(identifier)) != mMap.end());
		return mMap[mHasher(identifier)];
	}

	Font& FontLibrary::GetRef(const char* identifier)
	{
		assert(mMap.find(mHasher(identifier)) != mMap.end());
		return mMap[mHasher(identifier)];
	}
}
