#pragma once
#include "cScreen.h"
class ScreenAbout :
	public cScreen
{
private:
	bool crash = false;
	Texture Texture;
	Sprite menuBackground;
	Font font;
	Text titel;
	Text aboutText;
	Text continueString;

public:
	ScreenAbout(void);
	virtual int Run(RenderWindow& window);
};

void TextBlock(Text& text, String string, Color color, Font& font, int fontSize, float x, float y)
{
	text.setString(string);
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setPosition(x, y);
	text.setFillColor(color);
	text.setOutlineThickness(1.0f);
	text.setOutlineColor(Color::Black);
	text.setLineSpacing(0.7f);
}

ScreenAbout::ScreenAbout(void)
{

	if (!font.loadFromFile("resources/fonts/Gabriola.ttf"))
	{
		MessageBoxA(NULL, "������ ��������: resources/fonts/Gabriola.ttf", "������ �������� ������", MB_OKCANCEL | MB_ICONERROR);
		crash = true;
	}
	TextBlock(titel, L"� ���������", Color::Red, font, 40, 310, 50);
	TextBlock(aboutText, L"��� ������������ ����������� ������� ����������\n��� ������������� ����� ����������� '����'\n��� �������� � ���� ����������� 'Esc'\n\nExence �2022", Color::White, font, 30, 110, 120);
	
	if (!Texture.loadFromFile("resources/img/bkgStart.jpeg"))
	{
		MessageBoxA(NULL, "������ ��������: resources/img/bkgStart.jpeg", "������ �������� ��������", MB_OKCANCEL | MB_ICONERROR);
		crash = true;
	}
	menuBackground.setTexture(Texture);
	menuBackground.scale(Vector2f(1.1f, 0.95f));

}



int ScreenAbout::Run(RenderWindow& window)
{
	Event Event;
	bool Running = true;
	RectangleShape rectangle(Vector2f(595.f, 255.f));
	rectangle.setPosition(100, 125);
	rectangle.setFillColor(Color(255, 255, 255, 70));

	if (crash) { return -1; }

	while (Running)
	{

		while (window.pollEvent(Event))
		{
			// Window closed
			if (Event.type == Event::Closed)
			{
				return -1;
			}
			//Key pressed
			//if (Event.type == Event::KeyPressed)
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					return 0;
				}
				
		}
		window.clear();
		window.draw(menuBackground);
		window.draw(rectangle);
		window.draw(titel);
		window.draw(aboutText);
		window.display();
	}

	return -1;

};