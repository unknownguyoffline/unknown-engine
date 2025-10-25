#include "TextRenderer.hpp"
#include <Core/Application.hpp>
#include <print>


namespace Unk
{
	const char* vertexCode = R"(
#version 450 core
layout(location = 0)in vec2 aPosition;
layout(location = 1)in vec2 aTextureCoordinate;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 textureCoordinate;


void main()
{
	textureCoordinate = aTextureCoordinate * -1.0;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPosition, 0.0, 1.0);
}
)";


	const char* fragmentCode = R"(
#version 450 core

out vec4 outputColor;
in vec2 textureCoordinate;
uniform sampler2D texture0;

void main()
{
	outputColor = vec4(vec3(1.0), texture(texture0, textureCoordinate).r);
	if(outputColor.a < 0.9)
		discard;
}

)";

	void TextRenderer::Initialize()
	{
		mRenderer = Application::GetInstance()->GetRenderer();
		mMesh = Mesh::QuadMesh();
		mRenderer->CreateShader({ vertexCode, fragmentCode }, "text");
		mMaterial.shader = "text";
	}

	void TextRenderer::LoadFont(const char* filename, const char* identifier, uint32_t pixelSize)
	{
		if (fopen(filename, "r") == nullptr)
			std::println("file not found {}", filename);
		Font& font = mFontLibrary.Load(filename, identifier, pixelSize);
	}

	void TextRenderer::CreateFont(const Font& font, const char* identifier)
	{
		mFontLibrary.Create(font, identifier);
	}

	float TextRenderer::RenderCharacter(char ch, const char* fontName, const Transform& transform)
	{
		Glyph glyph = mFontLibrary.Get(fontName).GetGlyph(ch);

		float normalizer = (1.f / 1024.f);

		glm::vec3 position = transform.position;
		position.x += (glyph.bearing.x + (glyph.size.x * 0.5)) * -normalizer;
		position.y += ((glyph.size.y * 0.5) - (glyph.size.y - glyph.bearing.y)) * normalizer;

		Transform t;
		t.position = position;
		t.rotation = transform.rotation;
		t.scale = glm::vec3(glyph.size.x, glyph.size.y, 1.0) * normalizer * transform.scale;

		glyph.texture->Bind(0);
		mRenderer->Submit(mMesh, mMaterial, t);

		float k = glyph.bearing.x + (glyph.size.x * 0.5);

		float advance = ((float(glyph.advance / 64.f) * -normalizer) - k * -normalizer) * 2.3f;

		return advance;
	}

	void TextRenderer::RenderText(const char* string, const char* fontName, const Transform& transform)
	{
		Transform t = transform;
		size_t size = strlen(string);
		for (int i = 0; i < size; i++)
		{
			if (string[i] < 0) continue;
			Application::GetInstance()->GetRenderer()->GetRenderCommand()->DisableDepthTest();
			t.position.x += RenderCharacter(string[i], fontName, t);
			Application::GetInstance()->GetRenderer()->GetRenderCommand()->EnableDepthTest();
		}
	}
}
