#pragma once
#include <unordered_map>
#include "Shader.hpp"

namespace Unknown
{
	struct ShaderFile
	{
		std::string vertex;
		std::string fragment;
		std::string geometry;
		std::string tessellation;
		std::string compute;
	};

	class ShaderLibrary
	{
	public:
		void Create(const ShaderSource& source, const std::string& identifier);
		void Load(const ShaderFile& files, const std::string& identifier);
		void Remove(const std::string& identifier);
		Shader* Get(const std::string& identifier);
	private:
		std::unordered_map<int32_t, Shader*> mMap;
		std::hash<std::string> mHasher;
	};
}