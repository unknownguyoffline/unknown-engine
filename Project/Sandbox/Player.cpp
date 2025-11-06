#include "Player.hpp"
#include <Core/Macro.hpp>

using namespace Unknown;
using namespace glm;

void Player::Initialize()
{
	mRenderer = Application::GetInstance()->GetRenderer2D();
	mQuadrilateral.transform.scale = vec3(0.1, 0.2, 1.0);
}

void Player::Terminate()
{

}

void Player::Update()
{
	if (doFixedUpdate())
		FixedUpdate();
	mRenderer->PushQuadrilateral(mQuadrilateral);
}

void Player::FixedUpdate()
{
	if (GetInput().keyboard.keySpace && isOnGround())
	{
		mPhysicsComponent = PhysicsComponent();
		mPhysicsComponent.force = vec3(0, 0.03, 0);
		UNK_CLIENT_LOG("Jump");
	}
	UpdatePhysics();
}

void Player::UpdatePhysics()
{
	
	mPhysicsComponent.force.y += mPhysicsComponent.gravity;
	mPhysicsComponent.acceleration += mPhysicsComponent.force;
	mPhysicsComponent.velocity += mPhysicsComponent.acceleration;
	mPhysicsComponent.acceleration = vec3(0);
	mPhysicsComponent.force = vec3(0);
	mQuadrilateral.transform.position += mPhysicsComponent.velocity;
	if (GetFeetPosition().y < -1.f)
		mQuadrilateral.transform.position.y = (-1.f + mQuadrilateral.transform.scale.y * 0.5);
}

bool Player::doFixedUpdate(int fps)
{
	if (abs(Application::GetInstance()->GetTime().deltaTime) > 1.0f)
		return false;

	static float accumulator = 0.0f;
	accumulator += Application::GetInstance()->GetTime().deltaTime;

	if (accumulator > (1.f / float(fps)))
	{
		accumulator = 0;
		return true;
	}
	return false;
}

vec3 Player::GetFeetPosition()
{
	float x = mQuadrilateral.transform.position.x;
	float y = mQuadrilateral.transform.position.y - (mQuadrilateral.transform.scale.y * 0.5);;
	return { x, y, 0.0 };
}

WindowInput Player::GetInput()
{
	return Application::GetInstance()->GetInput();
}

bool Player::isOnGround()
{
	if (GetFeetPosition().y == -1.0f)
		return true;
	return false;
}
