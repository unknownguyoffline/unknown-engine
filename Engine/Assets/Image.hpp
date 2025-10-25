#pragma once 
#include <glm/glm.hpp>

namespace Unk
{
	struct Image
	{
		void* data = nullptr;
		glm::uvec2 size = { 0,0 };
		void Load(const char* filename, int channel = 4);
	};
}
