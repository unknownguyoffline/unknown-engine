#pragma once
#include <Assets/Image.hpp>
#include <string>
#include <unordered_map>
#include "Texture.hpp"

namespace Unknown
{
	class TextureLibrary
	{
	public:
		void Create(const Image& image, const std::string& identifier);
		void Create(const TextureProperty& property, const std::string& identifier);
		void Load(const std::string& filename, const std::string& identifier, TextureProperty property = TextureProperty());
		void Remove(const std::string& identifier);
		Texture* Get(const std::string& identifier);
	private:
		std::unordered_map<int32_t, Texture*> mMap;
		std::hash<std::string> mHasher;
	};
}