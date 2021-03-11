#pragma once

#include "Interface/Tile.h"
#include "ECS.h"
#include "Engine.h"
#include <iostream>
#include <fstream>


struct Transform {
public:
	ECS_DECLARE_TYPE;

	float xPos, yPos, rotation, xSpeed, ySpeed, xSpeedMod, ySpeedMod;

	Transform(float newX, float newY, float newXSpeed = 0.0f, float newYSpeed = 0.0f)
		: xPos(newX), yPos(newY), xSpeedMod(newXSpeed), ySpeedMod(newYSpeed)
	{
		this->rotation = 0.0f;
		this->xSpeed = 0.0f;
		this->ySpeed = 0.0f;
	}

	void UpdateSpeed(float x, float y) {
		this->xSpeed = x;
		this->ySpeed = y;
	}

	void Move() {
		// halve the speed when moving diagnolly
		if (xSpeed != 0 && ySpeed != 0) {
			xSpeed /= 2;
			ySpeed /= 2;
		}

		xPos += xSpeed;
		yPos += ySpeed;
	}
};


struct Sprite2D {
public:
	ECS_DECLARE_TYPE;

	sf::Sprite picture;
	std::string texturePath;
	int width, height;

	Sprite2D(std::string name) {
		texturePath = name;
	}
};

struct Animator{
	ECS_DECLARE_TYPE;

	int spriteWidth, spriteHeight;
	int currentColumn, currentRow;
	int totalColumns, totalRows;

	float currentTime, nextFrameTime;

	bool bFacingRight;

	Animator(int newWidth, int newHeight, float timeBetweenFrames, int newColumns, int newRows)
	{
		this->spriteWidth = newWidth;
		this->spriteHeight = newHeight;

		currentColumn = 0;
		currentRow = 0;

		this->totalColumns = newColumns;
		this->totalRows = newRows;

		this->nextFrameTime = timeBetweenFrames;

		currentTime = 0;
		
		bFacingRight = true;
	}
};

struct InputController {
public:
	ECS_DECLARE_TYPE;

	bool bInputActive;

	bool wKey, aKey, sKey, dKey;

	InputController() {
		bInputActive = true;
		wKey = false;
		aKey = false;
		sKey = false;
		dKey = false;
	}

};

struct BoxCollider {
public:
	ECS_DECLARE_TYPE;

	int leftEdge, rightEdge, topEdge, bottomEdge;

	BoxCollider() {
		leftEdge = 0;
		rightEdge = 0;
		topEdge = 0;
		bottomEdge = 0;
	}

	void Update(int xSide, int ySide, int width, int height) {
		leftEdge = xSide;
		rightEdge = xSide + width;
		topEdge = ySide;
		bottomEdge = ySide + height;
	}
};

struct Camera {
public:
	ECS_DECLARE_TYPE;

	sf::View cameraView;

	Camera(sf::Vector2f pivot) {
		cameraView.setCenter(pivot);
	}
};


struct Tag
{
	ECS_DECLARE_TYPE;

	std::vector<std::string> tagNames;

	Tag() {};

	void AddTag(std::string tag) {
		tagNames.push_back(tag);
	}
};

struct TileMap
{
public:
	ECS_DECLARE_TYPE;

	float gridSizeF;
	uint32_t gridSizeU;

	// used for rendering images in a certian order
	uint32_t layers;

	sf::Vector2u maxSize;
	sf::RectangleShape collisionBox;

	/**
	* Map structure
	* 1. Column of vectors
	* 2. Row of vectors
	* 3. Collection of tile pointers
	*/
	std::vector<std::vector<std::vector<Tile*>>> map;

	TileMap() {
		size_t x, y, z;

		this->gridSizeF = 50.0f;

		// return a value of new type, convert float to unsigned int
		this->gridSizeU = static_cast<uint32_t>(this->gridSizeF);

		// # of tiles, size of tiles determined by grid size
		this->maxSize.x = 20;
		this->maxSize.y = 20;
		this->layers = 1;
		this->map.resize(this->maxSize.x);

		for (x = 0; x < this->maxSize.x; x++) {
			this->map.push_back(std::vector<std::vector<Tile*>>());

			for (y = 0; y < this->maxSize.y; y++) {
				this->map[x].resize(this->maxSize.y);
				this->map[x].push_back(std::vector<Tile*>());

				for (z = 0; z < this->layers; z++) {
					this->map[x][y].resize(this->layers);
					this->map[x][y].push_back(nullptr);
				}
			}
		}
		
		this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
		this->collisionBox.setFillColor(sf::Color(0, 255, 0, 50));
		this->collisionBox.setOutlineColor(sf::Color::Green);
		this->collisionBox.setOutlineThickness(-1.0f);
	}

	~TileMap() {
		clear();
	}

	void addTile(const int x, const int y,
		const int z, bool bHasCollision) {
		if (x < this->maxSize.x && x >= 0 && 
			y < this->maxSize.y && y >= 0 &&
			z < this->layers && z >= 0) {

			// check if map is empty
			if (this->map[x][y][z] == nullptr) {
				this->map[x][y][z] = new Tile(x, y, this->gridSizeF, bHasCollision);
				printf("Added tile\n");
			}
			
		}
	}

	void clear()
	{
		size_t x, y, z;

		for (x = 0; x < this->maxSize.x; x++) {
			for (y = 0; y < this->maxSize.y; y++) {
				for (z = 0; z < this->layers; z++) {
					delete this->map[x][y][z];
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}
		this->map.clear();
	}

	//void saveTileMap(std::string filePath)
	//{
	//	std::ofstream _saveFile;
	//	size_t x, y, z;

	//	_saveFile.open(filePath);

	//	if (_saveFile.is_open()) {
	//		_saveFile
	//			<< maxSize.x << " "
	//			<< maxSize.y << "\n" 
	//			<< gridSizeF << "\n" 
	//			<< layers << "\n";

	//		for (x = 0; x < this->maxSize.x; x++) {
	//			for (y = 0; y < this->maxSize.y; y++) {
	//				for (z = 0; z < this->layers; z++) {
	//					if (this->map[x][y][z] != nullptr) {
	//						_saveFile
	//							<< x << " "
	//							<< y << " "
	//							<< z << " "
	//							<< this->map[x][y][z]->toString() << " "
	//							<< "\n";
	//					}
	//				}
	//			}
	//		}

	//	}
	//	else {
	//		std::cout << "error, tilemap couldn't save to file " << filePath << "\n";
	//	}

	//	_saveFile.close();
	//}

	//void loadTileMap(std::string path) {
	//	FILE* filePath; /* File stream structure */
	//	size_t len; /* File length, used for allocating the buffer */
	//	char *buf; /* Pointer to the memory allocated to store the file contents */
	//	uint32_t layers;
	//	size_t x, y, z;
	//	bool bColliding;

	//	filePath = fopen(path.data(), "rb");
	//	if (!filePath) {
	//		fprintf(stderr, "Error: failed to open file: %s\n",
	//			strerror(errno));
	//		return;
	//	}

	//	/* Determine the file length*/
	//	fseek(filePath, 0, SEEK_CUR); /* Go to the end of file */
	//	len = ftell(filePath); /* Get the current position in the file */
	//	fseek(filePath, 0, SEEK_SET); /* Return to the start of the file */

	//	/*
	//	* Allocate a buffer of len + 1 byte to
	//	* store the contents of the file
	//	*/
	//	buf = (char *) calloc(len + 1, sizeof(char));
	//	if (!buf) {
	//		fprintf(stderr, "Error: failed to allocated buffer: %s\n", strerror(errno));
	//		return;
	//	}

	//	/* Read file's contents into buf */
	//	fread(buf, sizeof(char), len, filePath);

	//	if (!buf) {
	//		fprintf(stderr, "Error: failed to read file: %s\n", strerror(errno));
	//		return;
	//	}

	//	buf[len] = 0;
	//	fclose(filePath);

	//	layers = 0;
	//	x, y, z = 0;
	//	bColliding = false;

	//	this->maxSize.x = atof(buf); /* atof converts ASCII to a float */
	//	this->maxSize.y = atoi(&buf[sizeof(uint32_t)]);
	//	this->gridSizeF = atof(&buf[sizeof(uint32_t) * 2 + 1]);
	//	this->layers = atoi(&buf[sizeof(uint32_t)]);
	//}

	void saveTileMap_O(std::string fileName) {
		std::ofstream _saveFile;
		_saveFile.open(fileName);

		if (_saveFile.is_open()) {
			_saveFile << maxSize.x << " " << maxSize.y << "\n"
				<< gridSizeF << "\n"
				<< layers << "\n";
			for (size_t x = 0; x < this->maxSize.x; x++) {
				for (size_t y = 0; y < this->maxSize.y; y++) {
					for (size_t z = 0; z < this->layers; z++) {
						if (this->map[x][y][z] != nullptr) {
							_saveFile << x << " " << y << " " << z << " "
								<< this->map[x][y][z]->toString() << " " << "\n";

						}
					}
				}
			}
		}
		else {
			std::cout << "Error: TileMap could not be saved to file " 
				<< fileName << "\n";
		}
		_saveFile.close();
	}

	void loadTileMap_O(std::string fileName) {
		std::ifstream _loadFile;
		_loadFile.open(fileName);

		if (_loadFile.is_open()) {
			sf::Vector2f _size;
			//float _gridSizeF = 0;
			uint32_t _layers = 0;
			uint32_t _x = 0;
			uint32_t _y = 0;
			uint32_t _z = 0;
			bool _bColliding = false;

			_loadFile >> _size.x >> _size.y >> gridSizeF >> _layers;

			//this->gridSizeF = _gridSizeF;
			//this->gridSizeU = static_cast<uint32_t>(this->gridSizeF);

			this->clear();

			this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());

			for (size_t x = 0; x < this->maxSize.x; x++) {
				for (size_t y = 0; y < this->maxSize.y; y++) {

					this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

					for (size_t z = 0; z < this->layers; z++) {
						this->map[x][y].resize(this->layers, nullptr);
					}
				}
			}

			while (_loadFile >> maxSize.x >> maxSize.y >> layers >> _bColliding) {
				std::cout << maxSize.x << ", " << maxSize.y << ", " << layers << "\n";
				this->map[maxSize.x][maxSize.y][layers] = new Tile(maxSize.x, maxSize.y,
					gridSizeF, _bColliding);
			}
		}
		else {
			std::cout << "ErrorL TileMap coild not load " << fileName << "\n";
		}
		_loadFile.close();
	}
};

ECS_DEFINE_TYPE(InputController);
ECS_DEFINE_TYPE(Sprite2D);
ECS_DEFINE_TYPE(Transform);
ECS_DEFINE_TYPE(Animator);
ECS_DEFINE_TYPE(Camera);
ECS_DEFINE_TYPE(TileMap);
