#pragma once
#include <Assets/Image.hpp>
#include <string>
#include <unordered_map>
#include "Texture.hpp"
#include <Utility/Memory.hpp>

namespace Unknown
{
	class TextureLibrary
	{
	public:
		Ref<Texture> Create(const Image& image, const std::string& identifier);
		Ref<Texture> Create(const TextureProperty& property, const std::string& identifier);
		Ref<Texture> Load(const std::string& filename, const std::string& identifier, TextureProperty property = TextureProperty());
		Ref<Texture> Get(const std::string& identifier);
		void Remove(const std::string& identifier);
	private:
		std::unordered_map<int32_t, Ref<Texture>> mMap;
		std::hash<std::string> mHasher;
	};
}
