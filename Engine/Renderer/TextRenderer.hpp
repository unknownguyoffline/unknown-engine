#pragma once
#include <Assets/Font.hpp>
#include "FontLibrary.hpp"
#include "Renderer.hpp"

namespace Unk
{
	struct TextVertex
	{
		glm::vec4 position;
	};

	class TextRenderer
	{
	public:
		void Initialize();
		void LoadFont(const char* filename, const char* identifier, uint32_t pixelSize = 128);
		void CreateFont(const Font& font, const char* identifier);
		float RenderCharacter(char ch, const char* fontName, const Transform& transform);
		void RenderText(const char* string, const char* fontName, const Transform& transform);
	private:
		Ref<Renderer> mRenderer;
		FontLibrary mFontLibrary;
		Mesh mMesh;
		Material mMaterial;
	};
}

