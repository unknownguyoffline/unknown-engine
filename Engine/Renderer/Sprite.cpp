#include "Sprite.hpp"


namespace Unknown
{
	void Sprite::Load(const char* filename)
	{
		Image image;
		image.Load(filename);

		TextureProperty property;
		property.image = image;
		texture.reset(Texture::Create(property));

		transform.scale.x = float(image.size.x) / float(image.size.y);
		transform.scale.y = 1.f;
	}
}
