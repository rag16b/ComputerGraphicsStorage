#include "Sprite.h"		// Sprite class to reduce the clutter
#include "Helpers.h"	// OpenGL Helpers to reduce the clutter
#include <GLFW/glfw3.h>	// GLFW is necessary to handle the OpenGL context
#include <cstdint>		// to use the different types of unsigned integer types
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>		// to save and retrieve the highscore

// *** To determine colors in this project I used a decimal translation of a 32 bit integer where each 8 bits corresponded to RGBA

// Global sprite bitmaps
uint8_t* squidBitMap2 = new uint8_t[22 * 16]
{
	0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
	0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
	0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,
	0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0

};
uint8_t* alienBitMap2 = new uint8_t[22 * 16]
{
	0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
	0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
	1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,
	1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,
	1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
	1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
	1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,
	1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,
	0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
	0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
	0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
	0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0

};
uint8_t* jellyBitMap2 = new uint8_t[22 * 16]
{
	0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,
	0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,
	0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,
	0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,
	0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0
};
uint8_t* deathBitMap = new uint8_t[26 * 14]
{
	0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,
	0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,
	0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,
	0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,
	0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,
	1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,
	1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,
	0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,
	0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,
	0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,
	0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,
	0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0
};
uint8_t* ufoBitMap = new uint8_t[32 * 14]
{
	0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
	0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,
	0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,
	0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0
};
uint8_t* squidBitMap1 = new uint8_t[22 * 16]
{
	0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
	0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
	0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0
};
uint8_t* alienBitMap1 = new uint8_t[22 * 16]
{
	0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
	0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
	0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
	0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
	0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,
	0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
	1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,
	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,
	0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0
};
uint8_t* jellyBitMap1 = new uint8_t[22 * 16]
{
	0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,
	0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,
	0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,
	0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,
	0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0
};
uint8_t* playerBitMap = new uint8_t[22 * 16]
{
	0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
uint8_t* bulletBitMap = new uint8_t[3 * 10]
{
	1,1,1,
	1,1,1,
	1,1,1,
	1,1,1,
	1,1,1,
	1,1,1,
	1,1,1,
	1,1,1,
	1,1,1,
	1,1,1
};
uint8_t* lineBitMap = new uint8_t[448 * 2]
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
uint8_t* highBitMap = new uint8_t[76 * 16]
{
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1
};
uint8_t* scoreBitMap = new uint8_t[112 * 16]
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
uint8_t* zeroBitMap = new uint8_t[12 * 16]
{
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1
};
uint8_t* oneBitMap = new uint8_t[12 * 16]
{
	0,0,0,1,1,1,1,1,0,0,0,0,
	0,0,1,1,1,1,1,1,0,0,0,0,
	0,1,1,1,1,1,1,1,0,0,0,0,
	1,1,1,1,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,0,0,1,1,1,1,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1
};
uint8_t* twoBitMap = new uint8_t[12 * 16]
{
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,
	1,1,1,1,0,0,0,0,0,0,0,0,
	1,1,1,1,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1
};
uint8_t* threeBitMap = new uint8_t[12 * 16]
{
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1
};
uint8_t* fourBitMap = new uint8_t[12 * 16]
{
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1
};
uint8_t* fiveBitMap = new uint8_t[12 * 16]
{
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,
	1,1,1,1,0,0,0,0,0,0,0,0,
	1,1,1,1,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1
};
uint8_t* sixBitMap = new uint8_t[12 * 16]
{
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,
	1,1,1,1,0,0,0,0,0,0,0,0,
	1,1,1,1,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1
};
uint8_t* sevenBitMap = new uint8_t[12 * 16]
{
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1
};
uint8_t* eightBitMap = new uint8_t[12 * 16]
{
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1
};
uint8_t* nineBitMap = new uint8_t[12 * 16]
{
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,1,1,1,1
};

// Global variables
const int maxBullets = 10;
Sprite ufoSprite;
Sprite playerSprite;
Sprite bulletSprite[maxBullets];
Sprite deathSprite;
Sprite lineSprite;
Sprite highSprite;
Sprite scoreSprite;
Sprite digits[10];
int playerMove = 0;
const int mvSpd = 2;
int numBullets = 0;
bool fire = false;
bool ufoExists = true;
int score = 0;
int highscore = 0;

struct Buffer { size_t width, height; uint32_t* buffData; };
struct Player { int posX = 0, posY = 0; Sprite sprite; int life = 3; };
struct EnemyRow { Sprite spr[11]; int numLeft = 11; };

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_RIGHT) {
		if (action == GLFW_PRESS)
			playerMove += mvSpd;
		else if (action == GLFW_RELEASE)
			playerMove -= mvSpd;
	}
	else if (key == GLFW_KEY_LEFT) {
		if (action == GLFW_PRESS)
			playerMove -= mvSpd;
		else if (action == GLFW_RELEASE)
			playerMove += mvSpd;
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		fire = true;
	}
}

// Draws one sprite
void drawSprite(Buffer* buff, Sprite& spr, size_t posX, size_t posY, uint32_t color) {
	for (size_t i = 0; i < spr.getWidth(); i++) {
		for (size_t k = 0; k < spr.getHeight(); k++)
			if (spr.getData()[k * spr.getWidth() + i] == 1)
				buff->buffData[(spr.getHeight() - 1 + posY - k) * buff->width + (posX + i)] = color;
	}
}
// Draws an array of sprites
void drawEnemyRow(Buffer* buff, EnemyRow& er, int time, int spritePosX, int spritePosY, uint8_t* bitmap1, uint8_t* bitmap2, int scr) {
	for (int i = 0; i < er.numLeft; i++)
		if (!er.spr[i].isDead()) {
			if (time > 40)
				er.spr[i].updateData(bitmap2);
			else if (time <= 40)
				er.spr[i].updateData(bitmap1);
			er.spr[i].setPos(spritePosX + (i * 35), spritePosY);
			drawSprite(buff, er.spr[i], er.spr[i].getX(), er.spr[i].getY(), 4294967295);
		}
		else if (er.spr[i].isDead() && er.spr[i].getDeathDur() > 0) {
			drawSprite(buff, deathSprite, er.spr[i].getX(), er.spr[i].getY(), 4294967295);
			er.spr[i].decDeathDur();
			if (er.spr[i].getDeathDur() == 1)
				score += scr;
		}
}
// clears buffer every frame to make sure the new one is drawn
void clearBuffer(Buffer* buff, int color) {
	int currPixel = 0;
	while (currPixel < (buff->width*buff->height))
		buff->buffData[currPixel++] = color;
}
// checks whether two sprites are overlapping
bool collision(Sprite spr1, Sprite spr2) {
	if (spr1.getX() < spr2.getX() + spr2.getWidth() && spr1.getX() + spr1.getWidth() > spr2.getX() &&
		spr1.getY() < spr2.getY() + spr2.getHeight() && spr1.getY() + spr1.getHeight() > spr2.getY()) {
		return true;
	}
	return false;
}
// checks for each row to see if an enemy is hit
void bulletEnemyHitDetect(EnemyRow& er, int i) {
	// Checking if bullet hits an alien
	for (int k = 0; k < er.numLeft; k++) {
		if (er.spr[k].isDead())
			continue;
		if (collision(er.spr[k], bulletSprite[i])) {
			er.spr[k].makeDead();
			bulletSprite[i] = bulletSprite[(numBullets--) - 1];
			continue;
		}
	}
}

int main(void) {
	// I chose this display size because it is double the original display size of space invaders...
	// Which can be seen here: https://en.wikipedia.org/wiki/Space_Invaders
	const int winWidth = 448;
	const int winHeight = 512;

	// Creating file streams
	std::ifstream fin;
	fin.open("highscore");
	// Getting high score
	int temp;
	if (fin.is_open()) {
		fin >> temp;
		highscore = temp;
		printf("Highscore: %d\n", highscore);
	}
	else
		printf("Could not open file.\n");
	fin.close();

    GLFWwindow* window;
    // Initialize the library
    if (!glfwInit())
        return -1;
    // Activate supersampling
    glfwWindowHint(GLFW_SAMPLES, 8);
    // Ensure that we get at least a 3.3 context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(winWidth, winWidth, "Space Invaders", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    GLenum err = glewInit();
    if(GLEW_OK != err) {
		// Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
	glGetError(); // pull and savely ignonre unhandled errors like GL_INVALID_ENUM
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    
	// Displaying information
    int major, minor, rev;
    major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    rev = glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION);
    printf("OpenGL version recieved: %d.%d.%d\n", major, minor, rev);
    printf("Supported OpenGL is %s\n", (const char*)glGetString(GL_VERSION));
    printf("Supported GLSL is %s\n", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Creating a buffer to display my sprites
	Buffer buff;
	buff.width = winWidth;
	buff.height = winHeight;
	buff.buffData = new uint32_t[buff.width * buff.height];
	clearBuffer(&buff, 0);

	// Dealing with buffer textures
	GLuint buffTexture;
	glGenTextures(1, &buffTexture);
	glBindTexture(GL_TEXTURE_2D, buffTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, buff.width, buff.height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, buff.buffData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Creating VAO to make a fullscreen triangle
	// This website gives an explanation of why this is useful: https://rauwendaal.net/2014/06/14/rendering-a-screen-covering-triangle-in-opengl/
	GLuint TriangleVAO;
	glGenVertexArrays(1, &TriangleVAO);

	const char* vertex_shader =
		"#version 330\n"
			"noperspective out vec2 TexCoord;"
			"void main()"
			"{"
			"    TexCoord.x = (gl_VertexID == 2)? 2.0: 0.0;"
			"    TexCoord.y = (gl_VertexID == 1)? 2.0: 0.0;"
			"    gl_Position = vec4(2.0 * TexCoord - 1.0, 0.0, 1.0);"
			"}";
	const char* fragment_shader =
		"#version 330\n"
			"uniform sampler2D buff;"
			"noperspective in vec2 TexCoord;"
			"out vec3 outColor;"
			"void main(){"
			"    outColor = texture(buff, TexCoord).rgb;"
			"}";

	// Creating a program to hold and link the vertex and fragment shader
	GLuint shader = glCreateProgram();
	//Create vertex shader
	GLuint shaderVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderVertex, 1, &vertex_shader, 0);
	glCompileShader(shaderVertex);
	glAttachShader(shader, shaderVertex);
	glDeleteShader(shaderVertex);

	//Create fragment shader
	GLuint shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderFragment, 1, &fragment_shader, 0);
	glCompileShader(shaderFragment);
	glAttachShader(shader, shaderFragment);
	glDeleteShader(shaderFragment);
	
	glLinkProgram(shader);
	glUseProgram(shader);

	GLint loc = glGetUniformLocation(shader, "buff");
	glUniform1i(loc, 0);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(TriangleVAO);

    // Register the keyboard callback
    glfwSetKeyCallback(window, key_callback);

	// Declaring enemy rows
	EnemyRow squids;
	EnemyRow aliens1;
	EnemyRow aliens2;
	EnemyRow jellys1;
	EnemyRow jellys2;
	// Initializing Sprites
	deathSprite.update(28, 14, 0, 0, deathBitMap);
	ufoSprite.update(32, 14, 0, 0, ufoBitMap);
	for (int i = 0; i < 11; i++)
		squids.spr[i].update(22, 16, 40, 0, squidBitMap1);
	for (int i = 0; i < 11; i++) {
		aliens1.spr[i].update(22, 16, 40, 0, alienBitMap1);
		aliens2.spr[i].update(22, 16, 40, 0, alienBitMap1);
	}
	for (int i = 0; i < 11; i++) {
		jellys1.spr[i].update(22, 16, 40, 0, jellyBitMap1);
		jellys2.spr[i].update(22, 16, 40, 0, jellyBitMap1);
	}
	playerSprite.update(22, 16, 0, 0, playerBitMap);
	for (int i = 0; i < maxBullets; i++)
		bulletSprite[i].update(3, 10, 0, 0, bulletBitMap);
	lineSprite.update(448, 2, 0, 0, lineBitMap);
	highSprite.update(76, 16, 0, 0, highBitMap);
	scoreSprite.update(112, 16, 0, 0, scoreBitMap);
	// Initializing digit sprites
	digits[0].update(12, 16, 0, 0, zeroBitMap);
	digits[1].update(12, 16, 0, 0, oneBitMap);
	digits[2].update(12, 16, 0, 0, twoBitMap);
	digits[3].update(12, 16, 0, 0, threeBitMap);
	digits[4].update(12, 16, 0, 0, fourBitMap);
	digits[5].update(12, 16, 0, 0, fiveBitMap);
	digits[6].update(12, 16, 0, 0, sixBitMap);
	digits[7].update(12, 16, 0, 0, sevenBitMap);
	digits[8].update(12, 16, 0, 0, eightBitMap);
	digits[9].update(12, 16, 0, 0, nineBitMap);

	// Creating player out of player struct
	Player player;
	player.posX = 210;
	player.posY = 40;
	player.sprite = playerSprite;
	
	int time = 0;
	int mvDelay = 0;
	int ufoDelay = 0;
	bool ufoIsMoving = false;
	int fireDelay = 80;	  // starts at 80 so player can fire a projectile as soon as the game starts
	int spritePosX = 40;
	bool sprDir = true;	// sprite direction. true for right, false for left
    // --------------------------------------------------------------------------MAIN LOOP OF GAME---------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window)) {
		mvDelay++;
		ufoDelay++;
		if ((time++) == 80)
			time = 0;
		glfwSwapInterval(1);
		clearBuffer(&buff, 0);

		// Move the player
		if (playerMove != 0) {
			if (player.posX + playerSprite.getWidth() + playerMove >= winWidth)
				player.posX = winWidth - playerSprite.getWidth();
			else if (player.posX + playerMove <= 0)
				player.posX = 0;
			else
				player.posX += playerMove;
		}
		// Drawing the player
		drawSprite(&buff, player.sprite, player.posX, player.posY, 16711935);
		// Drawing extra player sprites to represent lives
		if (player.life == 3)
			drawSprite(&buff, player.sprite, (10 + player.sprite.getWidth()) * 2, 10, 16711935);
		if (player.life <= 3)
			drawSprite(&buff, player.sprite, 10 + player.sprite.getWidth(), 10, 16711935);

		// Drawing enemy sprites
		drawEnemyRow(&buff, squids, time, spritePosX, 390, squidBitMap1, squidBitMap2, 30);
		drawEnemyRow(&buff, aliens1, time, spritePosX, 360, alienBitMap1, alienBitMap2, 20);
		drawEnemyRow(&buff, aliens2, time, spritePosX, 330, alienBitMap1, alienBitMap2, 20);
		drawEnemyRow(&buff, jellys1, time, spritePosX, 300, jellyBitMap1, jellyBitMap2, 10);
		drawEnemyRow(&buff, jellys2, time, spritePosX, 270, jellyBitMap1, jellyBitMap2, 10);

		// Determining enemy sprite move direction
		if (spritePosX + (11 * 35) + aliens1.spr[0].getWidth() - 30 >= winWidth)	// using aliens1.spr since all enemy sprites have the same width
			sprDir = false;
		else if (spritePosX - 10 <= 0)
			sprDir = true;
		// Moving enemy sprites side to side
		if (mvDelay == 40) {
			if (sprDir)
				spritePosX += 8;
			else if (!sprDir)
				spritePosX -= 8;
			mvDelay = 0;
		}

		// Drawing the ufo sprite
		if (ufoIsMoving == true && !ufoSprite.isDead()) {
			drawSprite(&buff, ufoSprite, ufoSprite.getX(), 450, 4278190335);
			ufoSprite.setPos(ufoSprite.getX() + 2, 450);
			if (ufoSprite.getX() + ufoSprite.getWidth() >= winWidth) {
				ufoIsMoving = false;
				ufoSprite.setPos(0, 450);
			}
		} // drawing death animation
		else if (ufoSprite.isDead() && ufoSprite.getDeathDur() > 0) {
			drawSprite(&buff, deathSprite, ufoSprite.getX(), 450, 4278190335);
			ufoSprite.decDeathDur();
			if (ufoSprite.getDeathDur() == 1)
				score += 100;
		}
		// Moving the ufo sprite every 1,000 frames
		if (ufoDelay == 1000) {
			ufoIsMoving = true;
			ufoDelay = 0;
		}

		// Drawing projectiles
		for (int i = 0; i < numBullets; i++)
			drawSprite(&buff, bulletSprite[i], bulletSprite[i].getX(), bulletSprite[i].getY(), 4294967295);
		// Moving projectiles and making sure they are shredded when leaving the screen
		for (int i = 0; i < numBullets; i++) {
			bulletSprite[i].setPos(bulletSprite[i].getX(), bulletSprite[i].getY() + 4);
			if (bulletSprite[i].getY() >= winHeight - 36 || bulletSprite[i].getY() < bulletSprite->getHeight() + 36) {	// minus 36 and plus 36 to make sure it doesn't pass the lines
				bulletSprite[i] = bulletSprite[(numBullets--) - 1];
				continue;
			}
			// Checking if bullet hits an enemy
			bulletEnemyHitDetect(squids, i);
			bulletEnemyHitDetect(aliens1, i);
			bulletEnemyHitDetect(aliens2, i);
			bulletEnemyHitDetect(jellys1, i);
			bulletEnemyHitDetect(jellys2, i);
			// Checking if a bullet hits the ufo
			if (ufoSprite.isDead())
				continue;
			if (collision(ufoSprite, bulletSprite[i])) {
				ufoSprite.makeDead();
				bulletSprite[i] = bulletSprite[(numBullets--) - 1];
				continue;
			}

		}
		// "Firing" the projectile
		if (fireDelay++ > 80) {
			if (fire == true && numBullets < maxBullets) {
				bulletSprite[numBullets++].setPos(player.posX + player.sprite.getWidth() / 2, player.posY + player.sprite.getHeight());
				fire = false;
				fireDelay = 0;
			}
		}

		// Drawing the line at the bottom
		drawSprite(&buff, lineSprite, 0, 30, 16711935);
		// Drawing the line at the top
		drawSprite(&buff, lineSprite, 0, winHeight - 30, 4294967295);
		// Drawing the score sprites
		drawSprite(&buff, scoreSprite, 10, winHeight - 22, 4294967295);
		drawSprite(&buff, digits[((score / 10) / 10) % 10], 25 + scoreSprite.getWidth(), winHeight - 22, 4294967295);
		drawSprite(&buff, digits[(score / 10) % 10], 39 + scoreSprite.getWidth(), winHeight - 22, 4294967295);
		drawSprite(&buff, digits[score % 10], 53 + scoreSprite.getWidth(), winHeight - 22, 4294967295);
		// Drawing the highscore sprites
		drawSprite(&buff, highSprite, 20 + scoreSprite.getWidth() + 60, winHeight - 22, 4294967295);
		drawSprite(&buff, scoreSprite, 20 + scoreSprite.getWidth() + 66 + highSprite.getWidth(), winHeight - 22, 4294967295);
		drawSprite(&buff, digits[((highscore / 10) / 10) % 10], 20 + scoreSprite.getWidth()*2 + 80 + highSprite.getWidth(), winHeight - 22, 4294967295);
		drawSprite(&buff, digits[(highscore / 10) % 10], 34 + scoreSprite.getWidth()*2 + 80 + highSprite.getWidth(), winHeight - 22, 4294967295);
		drawSprite(&buff, digits[highscore % 10], 48 + scoreSprite.getWidth()*2 + 80 + highSprite.getWidth(), winHeight - 22, 4294967295);
		// Capping score
		if (score > 990)
			score = 999;
		// Updating highscore
		if (score > highscore)
			highscore = score;

		glTexSubImage2D(GL_TEXTURE_2D,0,0,0,buff.width,buff.height,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,buff.buffData);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap front and back buffers
        glfwSwapBuffers(window);
		// Poll for and process events
		glfwPollEvents();

		// TESTING
		printf("Score: %d	Highscore: %d\r", score, highscore);

		// End game COULDN'T GET IT TO STOP
		/*if (squids.numLeft == 0 && aliens1.numLeft == 0 && aliens2.numLeft == 0 && jellys1.numLeft == 0 && jellys2.numLeft == 0) {
			while (!glfwWindowShouldClose(window))
			{
				// sleep
			}
		}*/

    }

	// Setting highscore
	std::ofstream fout("highscore");
	fout << highscore;
	fout.close();

	// Deallocate glfw internals
	glfwDestroyWindow(window);
    glfwTerminate();
	glDeleteVertexArrays(1, &TriangleVAO);
    return 0;
}