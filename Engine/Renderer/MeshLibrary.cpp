//#include "MeshLibrary.hpp"
//#include <fstream>
//#include <Utility/Memory.hpp>
//#include <Core/Macro.hpp>
//
//static std::string readFile(const std::string& filename)
//{
//	if (filename.size() == 0)
//	{
//		return std::string();
//	}
//	std::string result;
//
//	std::ifstream input(filename);
//
//	if (!input.is_open())
//	{
//		printf("Error: file not found [%s]\n", filename.c_str());
//		return std::string();
//	}
//
//	input.seekg(0, std::ios::end);
//	size_t size = input.tellg();
//	input.seekg(0, std::ios::beg);
//
//	result.resize(size);
//
//	input.read(&result[0], size);
//
//	return result;
//}
//
//void MeshLibrary::Create(const Mesh& mesh, const std::string& identifier)
//{
//	int hash = mHasher(identifier);
//
//	Mesh* m = new Mesh(mesh);
//
//	mMap.insert({ hash, std::make_shared<Mesh>(m) });
//}
//
//void MeshLibrary::Load(const std::string& files, const std::string& identifier)
//{
//	CORE_ASSERT("not implemented yet", false);
//}
//
//void MeshLibrary::Remove(const std::string& identifier)
//{
//	int hash = mHasher(identifier);
//	auto location = mMap.find(hash);
//	CORE_ASSERT("Mesh not found", location == mMap.end());
//	mMap.erase(location);
//}
//
//Ref<Mesh> MeshLibrary::Get(const std::string& identifier)
//{
//	int hash = mHasher(identifier);
//	auto location = mMap.find(hash);
//	CORE_ASSERT("Mesh not found", location == mMap.end());
//	return mMap[hash];
//}
//
