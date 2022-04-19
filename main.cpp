#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <fstream>


using namespace sf;

float STEPDELAY = 0.009;

int window_width = 800;
int window_height = 432;

const int H = 27;
const int W = 151;

bool EndGame = false;
bool isMusic = false;

float offsetX = 0, offsetY = 0;
bool fight = false;

char MAP_LANG[] = { '0','a','b','d','e','f','g','h','H','k','l','m','o','p','r','t','x','y','Y' };

String GAME_MAP[H] = {

"e00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000d0e0",
"00                                                                                                                                                 0000",
"e0                                                                                                                                                 d0e0",
"00                                                                                                                                                 0000",
"e0                                                                                                                                                 d0e0",
"00                                                                                                                                                 0000",
"e0                                                                                                                                                 d0e0",
"00                                                                                                                                                 0000",
"e0                                                                                                                                                 d0e0",
"00                                                                                                                                                 0000",
"e0                                   d0a0b0n0a0b0n0a0b0n0a0b0n0a0b0n0a0b0n0e0                                                                      d0e0",
"00                                   0000000000000000000000000000000000000000                                                                      0000",
"e0                                   h0H0Y0y0y0y0y0y0y0y0H0Y0y0y0y0y0y0H0Y0z0                                                                      d0e0",
"00                                   0000000000000000000000000000000000000000                                                                      0000",
"e0                       k0lm0         0000              0000          0000                                                                        d0e0",
"00                                                                                                                                                 0000",
"e0134                                                                                                                                              d0e0",
"00 2 34              c                                                                                                                             0000",
"e01 2 34            k0lm0                                                                                                            t00           d0e0",
"00                                                                                                                                   000           0000",
"e0sS    R                                                                            d0a0b0n0a0b0n0a0b0n0a0b0n0e0                    000           d0e0",
"00                                     t00                                           0000000000000000000000000000                 t00g00       t00 0000",
"e0                                     000                  d0b0n0a0b0n0e0r0000000000f0p0p0p0p0p0p0p0p0p0p0p0p0e0                 000000       000 d0e0",
"00                                     000                  00000000000000g00     g000000000000000000000000000000                 000000     w 000 0000",
"a0b0n0a0b0n0a0b0n0a0b0n0a0b0n0a0b0n0a0b0n0a0b0n0a0b0n0a0b0e0d0p0p0p0p0p0e0           f0p0p0p0p0p0p0p0p0p0p0p0p0e0d0n0a0b0n0a0b0n0a0b0n0a0b0n0a0b0n0a0e0",
"00000000000000000000000000000000000000000000000000000000000000000000000000xxxxxxxxxxx000000000000000000000000000000000000000000000000000000000000000000",
"p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0f0a0b0n0a0b0ne0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0p0e0",
};

int cBonus[H][W];
int wBonus[H][W];


#include "UNIT.h"
#include "ENEMY.h"
#include "HERO.h"
#include "SHOOT.h"
#include "cScreen.h"
#include "ScreenMenu.h"
#include "ScreenAbout.h"
#include "ScreenGame.h"
#include "ScreenScore.h"




int main()
{
	std::vector<cScreen*> Screens;
	int screen = 0;

	RenderWindow window(VideoMode(window_width, window_height), "Heroes vs Dragons");
	
	//window.setMouseCursorVisible(false);

	Image icon;
	icon.loadFromFile("resources/img/icon.png");
	window.setIcon(32, 32, icon.getPixelsPtr());
	
	ScreenMenu screenMenu;
	Screens.push_back(&screenMenu);
	ScreenGame screenGame;
	Screens.push_back(&screenGame);
	ScreenScore screenScore;
	Screens.push_back(&screenScore);
	ScreenAbout screenAbout;
	Screens.push_back(&screenAbout);
	

	while (screen >= 0)
	{
		screen = Screens[screen]->Run(window);
	}


	return 0;
}





