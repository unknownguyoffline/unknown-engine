#include "Font.hpp"
#include <Assets/Image.hpp>
#include <Renderer/Texture.hpp>
#include <print>


namespace Unk
{
	void Font::Load(const char* filename, uint32_t pixelSize)
	{
		FT_Error error = FT_Init_FreeType(&mLibrary);
		FT_New_Face(mLibrary, filename, 0, &mFace);
		FT_Set_Pixel_Sizes(mFace, 0, pixelSize);
		for (char ch = 0; ch < 127; ch++)
		{
			FT_Load_Char(mFace, ch, FT_LOAD_RENDER);

			Glyph glyph;
			glyph.charater = ch;
			glyph.size = { mFace->glyph->bitmap.width, mFace->glyph->bitmap.rows };
			glyph.bearing = { mFace->glyph->bitmap_left, mFace->glyph->bitmap_top };
			glyph.advance = mFace->glyph->advance.x;
			Image image;
			image.size = glyph.size;
			image.data = new char[image.size.x * image.size.y];
			memcpy(image.data, mFace->glyph->bitmap.buffer, image.size.x * image.size.y);
			TextureProperty property;
			property.image = image;
			property.format = R;
			property.magFilter = NEAREST;
			property.minFilter = NEAREST;
			property.slot = 0;
			glyph.texture.reset(Texture::Create(property));

			mGlyphs.push_back(glyph);

			mTotalSize.x += glyph.size.x;
			if (mTotalSize.y < glyph.size.y)
				mTotalSize.y = glyph.size.y;
		}

		FT_Done_Face(mFace);
		FT_Done_FreeType(mLibrary);
	}

	Glyph Font::GetGlyph(char character)
	{
		for (int i = 0; i < mGlyphs.size(); i++)
		{
			if (mGlyphs[i].charater == character)
				return mGlyphs[i];
		}
		std::println("Glyph not found: {}", character);
	}
}
