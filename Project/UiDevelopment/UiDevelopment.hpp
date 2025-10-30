#include <Engine.hpp>
#include <Renderer/TextRenderer.hpp>

class UiDevelopment : public Unknown::Application
{
    Unknown::Mesh rectangle;
    Unknown::Material basicMaterial;
    Unknown::TextRenderer textRenderer;
	Unknown::Mesh mesh;



    void OnStart() override;
    void OnRenderUi();
    void OnUpdate(float dt) override;
    void OnEnd() override;
};
