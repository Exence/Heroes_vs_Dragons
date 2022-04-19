
class ScreenMenu :
    public cScreen
{
private:
	int alpha_max;
	int alpha_div;
	bool crash = false;
	bool playing;
	Texture Texture;
	Sprite menuBackground;
	int alpha = 0;
	Font font;
	Text startMenu;
	Text scoreMenu;
	Text aboutMenu;
	Text exitMenu;
	Text resumeMenu;
	int choise = 0;
	int fontSize = 25;

	Music menuMusic;
public:
	ScreenMenu(void);
	virtual int Run(RenderWindow& window);
};

void MenuLine(Text& menuItem, String text, Font& font, int fontSize, float x, float y)
{
	menuItem.setString(text);
	menuItem.setFont(font);
	menuItem.setCharacterSize(fontSize);
	menuItem.setPosition(x, y);
	menuItem.setOutlineThickness(1.2f);
	menuItem.setOutlineColor(Color::Black);
}

//быстрая сортировка
void qsortRecursive(int* masInt, std::string* masStr, int size) {
	int i = 0;
	int j = size - 1;

	int mid = masInt[size / 2];

	do {
		while (masInt[i] > mid) {
			i++;
		}
		while (masInt[j] < mid) {
			j--;
		}

		if (i <= j) {
			int tmpInt = masInt[i];
			std::string tmpStr = masStr[i];
			masInt[i] = masInt[j];
			masStr[i] = masStr[j];
			masInt[j] = tmpInt;
			masStr[j] = tmpStr;

			i++;
			j--;
		}
	} while (i <= j);


	if (j > 0) {
		qsortRecursive(masInt, masStr, j + 1);
	}
	if (i < size) {
		qsortRecursive(&masInt[i], &masStr[i], size - i);
	}
}

ScreenMenu::ScreenMenu(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;


	if (!menuMusic.openFromFile("resources/sounds/endGame.ogg"))
	{
		std::cerr << "Error loading: resources/sounds/endGame.ogg" << std::endl;
		crash = true;
	}
	menuMusic.setLoop(true);
	menuMusic.setVolume(90.f);
	menuMusic.play();

	if (!Texture.loadFromFile("resources/img/bkgStart.jpeg"))
	{
		std::cerr << "Error loading: resources/img/bkgStart.jpeg" << std::endl;
		menuMusic.stop();
		crash = true;
	}
	menuBackground.setTexture(Texture);
	menuBackground.scale(Vector2f(1.1f, 0.95f));
	menuBackground.setColor(Color(255, 255, 255, alpha));
	if (!font.loadFromFile("resources/fonts/Gabriola.ttf"))
	{
		std::cerr << "Error loading Gabriola.ttf" << std::endl;
		menuMusic.stop();
		crash = true;
	}
	MenuLine(startMenu, L"Новая игра", font, fontSize, 280, 100);
	MenuLine(resumeMenu, L"Продолжить", font, fontSize, 280, 100);
	MenuLine(scoreMenu, L"Таблица рекордов", font, fontSize, 280, 160);
	MenuLine(aboutMenu, L"О программе", font, fontSize, 280, 220);
	MenuLine(exitMenu, L"Выход", font, fontSize, 280, 280);

}



int ScreenMenu::Run(RenderWindow& window)
{
	Event Event;
	bool Running = true;
	window.setMouseCursorVisible(true);
	RectangleShape rectangle(Vector2f(180.f, 220.f));
	rectangle.setPosition(270,95);
	rectangle.setFillColor(Color(255, 255, 255, 70));

	if (crash) { return -1; }
	
	
	
	if (playing)
	{
		alpha = alpha_max;
	}

	while (Running)
	{
		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

		while (window.pollEvent(Event))
		{
			// Window closed
			if (Event.type == Event::Closed)
			{
				return -1;
			}
			if (Event.type == Event::MouseMoved)
			{
				if (startMenu.getGlobalBounds().contains(pos.x, pos.y))
				{
					choise = 0;
				}
				if (scoreMenu.getGlobalBounds().contains(pos.x, pos.y))
				{
					choise = 1;
				}
				if (aboutMenu.getGlobalBounds().contains(pos.x, pos.y))
				{
					choise = 2;
				}
				if (exitMenu.getGlobalBounds().contains(pos.x, pos.y))
				{
					choise = 3;
				}

			}


			if (Event.type == Event::MouseButtonPressed)
				if (Event.key.code == Mouse::Left)
				{
					if (choise == 0)
					{
						//Начинаем игру
						playing = true;
						menuMusic.stop();
						return 1;
					}
					if (choise == 1)
					{
						//menuMusic.stop();
						return 2;
					}
					if (choise == 2)
					{
						//menuMusic.stop();
						return 3;
					}
					else
					{
						//Выход
						menuMusic.stop();
						return -1;
					}
				}
			
			//Key pressed
			if (Event.type == Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case Keyboard::Up:
					if (choise != 0)
						choise -= 1;
					break;
				case Keyboard::Down:
					if (choise != 3)
						choise += 1;
					break;
				case Keyboard::Escape:
					if (playing)
					{
						menuMusic.stop();
						return 1;
					}
					break;
				case Keyboard::Return:
					if (choise == 0)
					{
						//Начинаем игру
						playing = true;
						menuMusic.stop();
						return 1;
					}
					if (choise == 1) 
					{
						//menuMusic.stop();
						return 2;
					}
					if (choise == 2)
					{
						//menuMusic.stop();
						return 3;
					}
					else
					{
						//Выход
						menuMusic.stop();
						return -1;
					}
					break;
				default:
					break;
				}
			}
		}
		//Плавное появление меню
		if (alpha < alpha_max)
		{
			alpha++;
		}
		menuBackground.setColor(Color(255, 255, 255, alpha / alpha_div));
		
		switch (choise)
		{
		case 0: 
		{
			startMenu.setFillColor(Color(255, 0, 0, 255));
			resumeMenu.setFillColor(Color(255, 0, 0, 255));
			scoreMenu.setFillColor(Color(255, 255, 255, 255));
			aboutMenu.setFillColor(Color(255, 255, 255, 255));
			exitMenu.setFillColor(Color(255, 255, 255, 255));			
			break;
		}
		case 1:
		{
			startMenu.setFillColor(Color(255, 255, 255, 255));
			resumeMenu.setFillColor(Color(255, 255, 255, 255));
			scoreMenu.setFillColor(Color(255, 0, 0, 255));
			aboutMenu.setFillColor(Color(255, 255, 255, 255));
			exitMenu.setFillColor(Color(255, 255, 255, 255));
			break;
		}
		case 2:
		{
			startMenu.setFillColor(Color(255, 255, 255, 255));
			resumeMenu.setFillColor(Color(255, 255, 255, 255));
			scoreMenu.setFillColor(Color(255, 255, 255, 255));
			aboutMenu.setFillColor(Color(255, 0, 0, 255));
			exitMenu.setFillColor(Color(255, 255, 255, 255));
			break;
		}
		case 3:
		{
			startMenu.setFillColor(Color(255, 255, 255, 255));
			resumeMenu.setFillColor(Color(255, 255, 255, 255));
			scoreMenu.setFillColor(Color(255, 255, 255, 255));
			aboutMenu.setFillColor(Color(255, 255, 255, 255));
			exitMenu.setFillColor(Color(255, 0, 0, 255));
			break;
		}
		default:
			break;
		}
		

		window.clear();
		window.draw(menuBackground);

		if (alpha == alpha_max)
		{
			//window.draw(rectangle);
			if (playing)
			{
				window.draw(resumeMenu);
			}
			else
			{
				window.draw(startMenu);
			}

			window.draw(scoreMenu);
			window.draw(aboutMenu);
			window.draw(exitMenu);
		}
		window.display();
	}

	menuMusic.stop();
	return -1;

};