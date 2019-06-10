#ifndef SPRITE_H
#define SPRITE_H

#include<cstdint>

class Sprite {
	public:
		Sprite();
		Sprite(size_t, size_t, int, int, uint8_t*);
		Sprite& operator=(const Sprite&);
		void update(size_t, size_t, int, int, uint8_t*);
		void updateData(uint8_t*);
		void setPos(int, int);
		size_t getWidth();
		size_t getHeight();
		int getX();
		int getY();
		uint8_t* getData();
		bool isDead();
		void makeDead();
		int getDeathDur();
		void decDeathDur();
		
	private:
		size_t width, height;
		uint8_t* spriteData;
		int posX, posY;
		bool dead;
		int deathDuration = 15;
};

#endif
