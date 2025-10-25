#include "UiDevelopment.hpp"
#include "freetype/freetype.h"
#include <Core/Macro.hpp>

using namespace glm;

void UiDevelopment::OnStart()
{
	FT_Library library;
	if (FT_Init_FreeType(&library) != 0)
	{
		UNK_CLIENT_ERROR("Failed to initialize freetype");
	}

	FT_Face face;
	FT_New_Face(library, "C:\Users\Abhishek\Dev\unknown-engine\Project\UiDevelopment\Cascadia-Regular.ttf", 0, &face);
	FT_Set_Pixel_Sizes(face, 0, 128);
	FT_Load_Char(face, 'A', FT_LOAD_RENDER);

	rectangle = Unknown::Mesh::QuadMesh();
	basicMaterial.shader = BASIC_TEXTURE_SHADER;

	Unknown::Image image;

	image.data = face->glyph->bitmap.buffer;
	image.size.x = face->glyph->bitmap.width;
	image.size.y = face->glyph->bitmap.rows;

	Unknown::TextureProperty property;
	property.format = Unknown::R;
	property.image = image;

	GetRenderer()->CreateTexture(property, "font");

	basicMaterial.texture[0] = "font";

}

void UiDevelopment::OnRenderUi()
{
}

void UiDevelopment::OnUpdate(float dt)
{
	GetRenderer()->BeginFrame(vec4(0.1), GetWindow()->GetSize());
	GetRenderer()->Submit(rectangle, basicMaterial, Unknown::Transform());
	GetRenderer()->EndFrame();
}

void UiDevelopment::OnEnd()
{
}

CREATE_APPLICATION(UiDevelopment)
