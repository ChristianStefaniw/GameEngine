#include "MovementSystem.h"

MovementSystem::MovementSystem(){}

MovementSystem::~MovementSystem(){}

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<InputController, Transform, Animator>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<InputController> input,
			ECS::ComponentHandle<Transform> transform,
			ECS::ComponentHandle<Animator> animator) -> void {
				if (input->bInputActive) {
					if (input->wKey) {
						transform->ySpeed = -transform->ySpeedMod;
						transform->Move();
					}
					else if (input->sKey) {
						transform->ySpeed = transform->ySpeedMod;
						transform->Move();
					} else {
						transform->ySpeed = 0;
					}

					if (input->aKey) {
						animator->bFacingRight = false;
						animator->currentRow = 1;
						transform->xSpeed = -transform->xSpeedMod;
						transform->Move();
					}
					else if (input->dKey) {
						animator->bFacingRight = true;
						animator->currentRow = 1;
						transform->xSpeed = transform->xSpeedMod;
						transform->Move();
					}
					else {
						transform->xSpeed = 0;
					}

				}
		}
	);
}