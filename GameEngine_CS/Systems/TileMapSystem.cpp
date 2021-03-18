#include "TileMapSystem.h"

TileMapSystem::TileMapSystem() = default;

void TileMapSystem::tick(ECS::World* world, float deltaTime)
{
	Engine::GetInstance().world->each<TileMap>(
		[&](ECS::Entity* entity, ECS::ComponentHandle<struct TileMap> tileMap) -> void
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				addTileOnClick(true, tileMap);
				std::cout << entity->getEntityId() << " is the entity id.\n";
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				addTileOnClick(false, tileMap);
				std::cout << entity->getEntityId() << " is the entity id. Without collison \n";
			}

			if (ButtonMap::GetMap()["SAVE"]->bClicked){
				tileMap->saveTileMap_O("tilemap_test.txt");
				ButtonMap::GetMap()["SAVE"]->bClicked = false;
				std::cout << "Tile map Saved\n";
			}

			if (ButtonMap::GetMap()["LOAD"]->bClicked) {
				tileMap->loadTileMap_O("tilemap_test.txt");
				ButtonMap::GetMap()["LOAD"]->bClicked = false;
				std::cout << "Tile map loaded\n";
			}
		}
	);
}

void TileMapSystem::addTileOnClick(bool bHasCollision, ECS::ComponentHandle<TileMap> tileMap)
{
	/* 
	* reference for window pointer that is used below to determine active cursor
	* position for adding tiles
	*/

	sf::RenderWindow* window = Engine::GetInstance().window;
	sf::Vector2f mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	sf::Vector2i mousePosGrid(static_cast<int>(mousePosView.x / tileMap->gridSizeF), static_cast<int>(mousePosView.y / tileMap->gridSizeF));

	tileMap->addTile(mousePosGrid.x, mousePosGrid.y, 0, bHasCollision);
}

TileMapSystem::~TileMapSystem() = default;
