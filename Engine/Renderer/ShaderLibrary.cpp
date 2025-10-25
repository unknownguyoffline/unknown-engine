#include "ShaderLibrary.hpp"
#include <fstream>

namespace Unk
{
	static std::string readFile(const std::string& filename)
	{
		if (filename.size() == 0)
		{
			return std::string();
		}
		std::string result;

		std::ifstream input(filename);

		if (!input.is_open())
		{
			printf("Error: file not found [%s]\n", filename.c_str());
			return std::string();
		}

		input.seekg(0, std::ios::end);
		size_t size = input.tellg();
		input.seekg(0, std::ios::beg);

		result.resize(size);

		input.read(&result[0], size);

		return result;
	}

	void ShaderLibrary::Create(const ShaderSource& source, const std::string& identifier)
	{
		int hash = mHasher(identifier);

		Shader* shader = Shader::Create(source);

		mMap.insert({ hash, shader });
	}

	void ShaderLibrary::Load(const ShaderFile& files, const std::string& identifier)
	{
		assert(files.vertex.size() != 0);
		assert(files.fragment.size() != 0);



		ShaderSource source;

		source.vertex = readFile(files.vertex);
		source.fragment = readFile(files.fragment);
		source.geometry = readFile(files.geometry);
		source.tessellation = readFile(files.tessellation);
		source.compute = readFile(files.compute);

		Shader* shader = Shader::Create(source);

		if (mMap.find(mHasher(identifier)) == mMap.end())
		{
			mMap.insert({ mHasher(identifier), shader });
		}
		else
		{
			mMap[mHasher(identifier)] = shader;
		}
	}

	void ShaderLibrary::Remove(const std::string& identifier)
	{
		auto location = mMap.find(mHasher(identifier));
		if (location == mMap.end())
		{
			printf("Error: Shader not found [%s]\n", identifier.c_str());
			return;
		}
		mMap.erase(location);
	}

	Shader* ShaderLibrary::Get(const std::string& identifier)
	{
		if (mMap.find(mHasher(identifier)) == mMap.end())
		{
			printf("Error: Shader not found [%s]\n", identifier.c_str());
			return nullptr;
		}
		return mMap[mHasher(identifier)];
	}

}
