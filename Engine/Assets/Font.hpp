#pragma once
#include <freetype/freetype.h>
#include <Utility/Memory.hpp>
#include <glm/glm.hpp>
#include <Renderer/Texture.hpp>


namespace Unk
{
	struct Glyph
	{
		char charater;
		glm::vec2 size;
		glm::vec2 bearing;
		int advance;
		Ref<Texture> texture;
	};

	class Font
	{
	public:
		void Load(const char* filename, uint32_t pixelSize);
		Glyph GetGlyph(char character);
		std::vector<Glyph>& GetGlyphsRef() { return mGlyphs; }
		glm::ivec2 GetTotalSize() { return mTotalSize; }

	private:
		FT_Library mLibrary;
		FT_Face mFace;
		std::vector<Glyph> mGlyphs;
		glm::ivec2 mTotalSize = glm::ivec2(0);
	};

}
