#include "UiDevelopment.hpp"
#include <Core/Macro.hpp>
#include <msdfgen/msdfgen.h>
#include <msdfgen/msdfgen-ext.h>
#include <Macro.hpp>
#include <stb/stb_image_write.h>

using namespace glm;

void UiDevelopment::OnStart()
{
	msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
	if(ft == nullptr)
	{
		UNK_CLIENT_ERROR("Failed to initialize freetype");
	}
	msdfgen::FontHandle* font = msdfgen::loadFont(ft, "Cascadia-Regular.ttf");
	if(font == nullptr)
	{
		UNK_CLIENT_ERROR("Failed to load font");
	}

	msdfgen::Shape shape;
	msdfgen::loadGlyph(shape, font, 'A', msdfgen::FONT_SCALING_EM_NORMALIZED);
	shape.normalize();
	msdfgen::edgeColoringSimple(shape, 3.0);
	msdfgen::Bitmap<float, 3> msdf(128,128);
	msdfgen::SDFTransformation t(msdfgen::Projection(128, msdfgen::Vector2(0.125, 0.125)), msdfgen::Range(0.125));
	msdfgen::generateMSDF(msdf, shape, t);
	msdfgen::savePng(msdf, "test.png");

	GetRenderer()->LoadShader({"basic.vert", "basic.frag"}, "basic");

	Unknown::TextureProperty property;
	property.image.Load("test.png");
	property.format = Unknown::RGBA;
	property.magFilter = Unknown::LINEAR;
	property.minFilter = Unknown::LINEAR;


	GetRenderer()->CreateTexture(property, "font");

	rectangle = Unknown::Mesh::QuadMesh();
	basicMaterial.shader = "basic";
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
