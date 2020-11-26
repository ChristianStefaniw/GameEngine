#include "RenderingSystem.h"

RenderingSystem::RenderingSystem(void)
{

}

RenderingSystem::~RenderingSystem(void)
{
}

void RenderingSystem::tick(ECS::World* world, float detlaTime)
{
	world->each<Transform, Sprite2D>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<Transform> transform,
			ECS::ComponentHandle<Sprite2D> sprite
			) -> void {
				
		});
}
