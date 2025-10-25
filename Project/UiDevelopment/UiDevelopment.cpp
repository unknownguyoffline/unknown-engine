
#include "UiDevelopment.hpp"

using namespace glm;

void UiDevelopment::OnStart()
{
    cubeMesh = Unk::Mesh::CubeMesh();
    basicMaterial.shader = BASIC_3D_SHADER;
	textRenderer.Initialize();
    textRenderer.LoadFont("Cascadia-Regular.ttf", "Cascadia", 1024);
}

void UiDevelopment::OnRenderUi()
{
    Unk::Transform transform;
	transform.scale.x = -0.5;
	transform.scale.y = 0.5;
    textRenderer.RenderText("Button", "Cascadia", transform);
}

void UiDevelopment::OnUpdate(float dt)
{
	GetRenderer()->BeginFrame(vec4(0.5), GetWindow()->GetSize());
    //GetRenderer()->Submit(cubeMesh, basicMaterial, Unk::Transform());
    OnRenderUi();
    GetRenderer()->EndFrame();
}

void UiDevelopment::OnEnd()
{
}

CREATE_APPLICATION(UiDevelopment)
