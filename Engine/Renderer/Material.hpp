#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Unk
{
	struct Material
	{
		std::string texture[32];
		std::string shader;
		glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	};
}