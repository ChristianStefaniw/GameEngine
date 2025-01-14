#include "RenderingSystem.h"
#include "../Interface/States.h"

RenderingSystem::RenderingSystem(void)
{

}

RenderingSystem::~RenderingSystem(void)
{
}

void RenderingSystem::tick(ECS::World* world, float detlaTime)
{
	if (!States::GetPausedState())
	{
		// Clear before drawing all textures
		Engine::GetInstance().window->clear();

		world->each<Transform, Sprite2D>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Sprite2D> sprite
				) -> void {
					// Add a texture to the unordered map
					if (textureMap.count(sprite->texturePath) < 1) {
						textureMap[sprite->texturePath] = LoadTexture(sprite->texturePath);
					}

					// If no texture is found, add it
					if (sprite->picture.getTexture() == nullptr) {
						sprite->picture.setTexture(*textureMap[sprite->texturePath]);
						sprite->width = sprite->picture.getGlobalBounds().width;
						sprite->height = sprite->picture.getGlobalBounds().height;
					}

					// Update and draw to the screen
					sprite->picture.setPosition(transform->xPos, transform->yPos);
					Engine::GetInstance().window->draw(sprite->picture);
			}
		);

		world->each<TileMap>(
			[&](ECS::Entity* entity, ECS::ComponentHandle<TileMap> tileMap) -> void {
				/*
				* Look through each tile and render onto the engine's window instance
				* note that this is looping through a vector which stores a vector, which stores
				* the tile value
				*/

				for (auto& x: tileMap->map) {
					for (auto& y : x) {
						for (auto& z : y) {
							if (z != nullptr) {
								sf::RenderWindow* winRef = Engine::GetInstance().window;
								winRef->draw(z->shape);
								if (z->getCollision()) {
									tileMap->collisionBox.setPosition(z->getPosition());
									winRef->draw(tileMap->collisionBox);

								}
							}
						}
					}
				}
			}
		);

		// Display updates
		Engine::GetInstance().window->display();
	}
}

sf::Texture* RenderingSystem::LoadTexture(std::string textureFile)
{
	sf::Texture* _textureRef = new sf::Texture();

	// if the texture is not found
	if (!_textureRef->loadFromFile(textureFile)) {
		std::cerr << "Unable to load image " << textureFile << ".\nIs this image in the correct directory?" << std::endl;
		system("Pause");

		exit(EXIT_FAILURE);
	}

	return _textureRef;
}
