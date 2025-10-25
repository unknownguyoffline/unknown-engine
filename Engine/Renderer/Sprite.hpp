#pragma once
#include <memory>
#include "Types.hpp"
#include <Assets/Image.hpp>
#include "Texture.hpp"

namespace Unknown
{
	struct Sprite
	{
		std::shared_ptr<Texture> texture;
		Transform transform;

		void Load(const char* filename);
	};
}
