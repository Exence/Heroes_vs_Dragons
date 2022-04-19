#pragma once
#include <fstream>
#include "cScreen.h"

class ScreenScore :
	public cScreen
{
private:
	bool crash = false;
	Texture Texture;
	Sprite menuBackground;
	Font font;
	Text titel;
	Text scoreText;
	Text continueString;
	

	std::fstream fs;

public:
	ScreenScore(void);
	virtual int Run(RenderWindow& window);
};


ScreenScore::ScreenScore(void)
{
	

	if (!font.loadFromFile("resources/fonts/Gabriola.ttf"))
	{
		MessageBoxA(NULL, "Ошибка загрузки: resources/fonts/Gabriola.ttf", "Ошибка загрузки шрифта", MB_OKCANCEL | MB_ICONERROR);
		crash = true;
	}
	TextBlock(titel, L"Таблица рекордов:", Color::Red, font, 35, 310, 50);
	

	if (!Texture.loadFromFile("resources/img/bkgStart.jpeg"))
	{
		MessageBoxA(NULL, "Ошибка загрузки: resources/img/bkgStart.jpeg", "Ошибка загрузки текстуры", MB_OKCANCEL | MB_ICONERROR);
		crash = true;
	}

	
	menuBackground.setTexture(Texture);
	menuBackground.scale(Vector2f(1.1f, 0.95f));
	

}



int ScreenScore::Run(RenderWindow& window)
{
	Event Event;
	bool Running = true;
	std::string name, score;

	RectangleShape rectangle(Vector2f(305.f, 320.f));
	rectangle.setPosition(260, 105);
	rectangle.setFillColor(Color(255, 255, 255, 70));

	if (crash) { return -1; }

	while (Running)
	{

		while (window.pollEvent(Event))
		{
			// Window closed
			if (Event.type == Event::Closed)
			{
				fs.close();
				return -1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				fs.close();
				return 0;
			}

		}
		window.clear();
		window.draw(menuBackground);
		window.draw(rectangle);
		window.draw(titel);
		int i = 0;
		fs.open("resources/save/save.sav", std::fstream::in | std::fstream::out | std::fstream::app);

		if (!fs.is_open())
		{
			MessageBoxA(NULL, "Ошибка загрузки: resources/save/save.sav", "Ошибка открытия файла", MB_OKCANCEL | MB_ICONERROR);
			crash = true;
		}
		
		while (!fs.eof())
		{
			name = "";
			score = "";
			fs >> name;
			if (!fs.eof())
			{
				fs >> score;
			}
			i++;
			std::ostringstream str;
			str << i << ".	" << name << "	" << score;
			TextBlock(scoreText, str.str(), Color::White, font, 25, 280, i * 30 + 80);
			if (score != "")
			{
				window.draw(scoreText);
			}			
		}
		fs.close();

		if (i == 0)
		{
			TextBlock(scoreText, L"В данной таблице пока нет результатов.", Color::White, font, 30, 150, 120);
			window.draw(scoreText);
		}

		window.display();
	}

	
	fs.close();

	return -1;

};