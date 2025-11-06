#pragma once
#include <Engine.hpp>

struct PhysicsComponent
{
	glm::vec3 velocity = glm::vec3(0);
	glm::vec3 acceleration = glm::vec3(0);
	glm::vec3 force = glm::vec3(0);
	float gravity = -0.001f;
};

class Player
{
public:
	void Initialize();
	void Terminate();
	void Update();
	void FixedUpdate();
private:
	Unknown::Ref<Unknown::Renderer2D> mRenderer;
	Unknown::Quadrilateral mQuadrilateral;
	PhysicsComponent mPhysicsComponent;
	void UpdatePhysics();
	bool doFixedUpdate(int fps = 60);
	glm::vec3 GetFeetPosition();
	Unknown::WindowInput GetInput();
	bool isOnGround();
};
