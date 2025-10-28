#include "TextureLibrary.hpp"

namespace Unknown
{
	Ref<Texture> TextureLibrary::Create(const Image& image, const std::string& identifier)
	{
		TextureProperty property;
		property.image = image;
		Ref<Texture> texture = Ref<Texture>(Texture::Create(property));
		mMap.insert({ mHasher(identifier), texture });
		return texture;
	}

	Ref<Texture> TextureLibrary::Create(const TextureProperty& property, const std::string& identifier)
	{
		Ref<Texture> texture = Ref<Texture>(Texture::Create(property));
		mMap.insert({ mHasher(identifier), texture });
		return texture;
	}

	Ref<Texture> TextureLibrary::Load(const std::string& filename, const std::string& identifier, TextureProperty property)
	{
		property.image.Load(filename.c_str());
		Ref<Texture> texture = Ref<Texture>(Texture::Create(property));
		mMap.insert({ mHasher(identifier), texture });
		return texture;
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

	Ref<Texture> TextureLibrary::Get(const std::string& identifier)
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
