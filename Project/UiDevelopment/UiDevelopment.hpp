#include <Engine.hpp>
#include <Renderer/TextRenderer.hpp>

class UiDevelopment : public Unk::Application
{
    Unk::Mesh cubeMesh;
    Unk::Material basicMaterial;
    Unk::TextRenderer textRenderer;
    void OnStart() override;
    void OnRenderUi();
    void OnUpdate(float dt) override;
    void OnEnd() override;
};
