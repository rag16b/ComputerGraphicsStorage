#include "Sprite.h"

Sprite::Sprite() {
	width = 0;
	height = 0;
	spriteData = nullptr;
	posX = 0;
	posY = 0;
	dead = false;
}

Sprite::Sprite(size_t w, size_t h, int x, int y, uint8_t* sprData) {
	width = w;
	height = h;
	spriteData = sprData;
	posX = x;
	posY = y;
}

Sprite& Sprite::operator=(const Sprite& rhs) {
	width = rhs.width;
	height = rhs.height;
	spriteData = rhs.spriteData;
	posX = rhs.posX;
	posY = rhs.posY;
	return *this;
}

void Sprite::update(size_t w, size_t h, int x, int y, uint8_t* sprData) {
	width = w;
	height = h;
	spriteData = sprData;
	posX = x;
	posY = y;
}

void Sprite::updateData(uint8_t* sprData) {
	spriteData = sprData;
}

void Sprite::setPos(int x, int y) {
	posX = x;
	posY = y;
};

size_t Sprite::getWidth() { return width; }
size_t Sprite::getHeight() { return height; }

int Sprite::getX() { return posX; }
int Sprite::getY() { return posY; }

uint8_t* Sprite::getData() { return spriteData; }

bool Sprite::isDead() { return dead; }
void Sprite::makeDead() { dead = true; }

int Sprite::getDeathDur() { return deathDuration; }
void Sprite::decDeathDur() { deathDuration--; }