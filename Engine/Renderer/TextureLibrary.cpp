#include "TextureLibrary.hpp"

namespace Unk
{
	void TextureLibrary::Create(const Image& image, const std::string& identifier)
	{
		TextureProperty property;
		property.image = image;
		Texture* texture = Texture::Create(property);
		mMap.insert({ mHasher(identifier), texture });
	}

	void TextureLibrary::Create(const TextureProperty& property, const std::string& identifier)
	{
		Texture* texture = Texture::Create(property);
		mMap.insert({ mHasher(identifier), texture });
	}

	void TextureLibrary::Load(const std::string& filename, const std::string& identifier, TextureProperty property)
	{
		property.image.Load(filename.c_str());
		Texture* texture = Texture::Create(property);
		mMap.insert({ mHasher(identifier), texture });
	}

	void TextureLibrary::Remove(const std::string& identifier)
	{
		auto location = mMap.find(mHasher(identifier));
		if (location == mMap.end())
		{
			printf("Error: Texture not found [%s]\n", identifier.c_str());
			return;
		}
		mMap.erase(location);
	}

	Texture* TextureLibrary::Get(const std::string& identifier)
	{
		auto location = mMap.find(mHasher(identifier));
		if (location == mMap.end())
		{
			printf("Error: Texture not found [%s]\n", identifier.c_str());
			return nullptr;
		}

		return mMap[mHasher(identifier)];
	}

}
