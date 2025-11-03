#include "UiDevelopment.hpp"
#include <Maths/Maths.hpp>

using namespace Unknown;

void UiDevelopment::OnStart()
{
}

void UiDevelopment::OnUpdate(float dt)
{
	GetRenderer2D()->BeginFrame();
	GetRenderer2D()->PushQuadrilateral({ Transform(), Maths::HexRGBA(0xff0000ff) });
	GetRenderer2D()->EndFrame();
}

void UiDevelopment::OnEnd()
{
}

CREATE_APPLICATION(UiDevelopment)
