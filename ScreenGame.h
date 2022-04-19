#pragma once
//#include "main.cpp"
//#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ScreenGame :
    public cScreen
{
private:
	Music music;
	Music endMusic;

	SoundBuffer bufferJump;
	SoundBuffer bufferStep;
	SoundBuffer bufferSword;
	SoundBuffer bufferEarth;
	SoundBuffer bufferFire;
	SoundBuffer bufferIce;
	SoundBuffer bufferLight;
	SoundBuffer bufferJade;
	SoundBuffer bufferHeroTakeDamage;
	SoundBuffer bufferDragonTakeDamage;
	SoundBuffer bufferBonus;

	Sound jumpSound;
	Sound stepSound;
	Sound swordSound;
	Sound earthSound;
	Sound fireSound;
	Sound iceSound;
	Sound lightSound;
	Sound jadeSound;
	Sound heroTakeDamageSound;
	Sound dragonTakeDamageSound;
	Sound bonusSound;

	Texture heroTexture;
	Texture mapTexture;
	Texture mapTextureFw;
	Texture tileSet;
	Texture dragonTexture;
	Texture dragonDialog;
	Texture heroDialog;
	Texture endGameTexture;


	Sprite mapSprite;
	Sprite mapSpriteFw;
	Sprite tile;
	Sprite dialogDragon;
	Sprite dialogHero;

	Text Health;
	Text Score;
	Text question;
	Text answer;
	Text attackDamage;
	Text gameResult;
	Text continueString;
	Text bonus;
	Text enemyName;


	//UNITS
	HERO player;

	ENEMY  earthDragon;
	ENEMY  fireDragon;
	ENEMY  iceDragon;
	ENEMY  lightDragon;
	ENEMY  jadeDragon;

	ENEMY* enemyType;

	SHOOT shoot;

	float currentFrame = 0;
	float steps = 0;


	bool isAnswerNeeded = false;
	bool play = true;
	bool scoreSaved = false;

	std::string str, solution;

	std::fstream fs;
	
public:
	

	ScreenGame(void);
	virtual int Run(RenderWindow& window);
};

void battle(HERO& hero, ENEMY& enemy, SHOOT& shoot, std::string str, Text& question, bool& isAnswerNeeded, float time)
{
	if (std::stoi(str) == enemy.getAnswer()) {
		try
		{
			hero.swordSound.play();
		}
		catch (const std::exception&)
		{
			throw;
		}
		hero.setScore(enemy.getType() * 100);
		if (hero.makeDamageToEnemy(enemy)) {
			question.setString(L"–≈ÿ» ≈Ÿ® «¿ƒ¿◊”!\n             " + enemy.getQuestion() + " = ?");
			isAnswerNeeded = true;
		}
		else
		{

			if (5 == enemy.getType()) {
				EndGame = true;
				isMusic = true;
			}
			fight = false;
		}
	}
	else
	{
		try
		{
			enemy.takeDamageSound.play();

		}
		catch (const std::exception&)
		{
			throw;
		}
		int score = abs((std::stoi(str) - enemy.getAnswer())) * 100;
		if (score > 500)
		{
			score = enemy.getType() * 100 + std::stoi(str);
		}
		hero.setScore(-score);
		
		hero.isTakingDamage = true;
		if (hero.takeDamage(enemy.makeDamage())) {
			question.setString(L"¿ –≈ÿ» ›“” «¿ƒ¿◊”!\n             " + enemy.getQuestion() + " = ?");
			isAnswerNeeded = true;
		}
		else {
			isAnswerNeeded = true;
			EndGame = true;
			isMusic = true;
		}
	}
}

bool intersects(ENEMY& enemy, HERO& hero, bool& isAnswerNeeded)
{
	if (hero.rect.intersects(enemy.rect) && enemy.isAllive() && !fight)
	{
		fight = true;
		hero.rect.left -= 32 - offsetY;
		enemy.rect.left = hero.rect.left + 101 - offsetY;
		isAnswerNeeded = true;
		hero.setCurrentEnemy(enemy.getType());
		return true;
	}
	return false;
}

void restart(HERO& hero, ENEMY& earthDragon, ENEMY& fireDragon, ENEMY& iceDragon, ENEMY& lightDragon, ENEMY& jadeDragon, Texture& dragonTexture, Music& music, Music& endMusic)
{
	earthDragon.set(dragonTexture, 50 * 16, 20 * 16, 10, 30);
	fireDragon.set(dragonTexture, 70 * 16, 18 * 16, 20, 30);
	iceDragon.set(dragonTexture, 97 * 16, 16 * 16, 30, 30);
	lightDragon.set(dragonTexture, 120 * 16, 20 * 16, 40, 30);
	jadeDragon.set(dragonTexture, 60 * 16, 6 * 16, 50, 100);
	hero.rect = FloatRect(64, 22 * 16, 37, 37);
	hero.gravity = -0.25;
	hero.setHealth(hero.getRestartHealth());
	hero.setScore(-99999);
	fight = false;
	offsetX = 0;
	offsetY = 0;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			if (cBonus[i][j] == 1) {
				GAME_MAP[i][j] = 'c';
			}
			if (wBonus[i][j] == 1) {
				GAME_MAP[i][j] = 'w';
			}
		}
	endMusic.stop();
	music.play();
	
}

void showEnemyName(ENEMY& enemy, Text& enemyName) {

	std::ostringstream ss;
	if (enemy.isAllive()) {
		ss << enemy.getHealth() << "/" << enemy.getRestartHealth();
		enemyName.setString(enemy.getName() + ss.str());
		enemyName.setPosition(enemy.sprite.getPosition().x - 10, enemy.sprite.getPosition().y - 60);
	}
	else
	{
		enemyName.setString("");
	}

}

void setText(Text& text, String newText, int fontSize)
{
	text.setString(newText);
	text.setCharacterSize(fontSize);
}

ScreenGame::ScreenGame(void)
{
	//Vector2f centerPos = Vector2f(window.getSize().x / 2, window.getSize().y / 2);


	music.openFromFile("resources/sounds/music.ogg");
	music.setLoop(true);
	music.setVolume(80.f);


	endMusic.openFromFile("resources/sounds/endGame.ogg");
	endMusic.setLoop(true);
	//endMusic.setVolume(80.f);
	//endMusic.play();

	//BUFFER

	bufferJump.loadFromFile("resources/sounds/jump.ogg");
	bufferStep.loadFromFile("resources/sounds/step.ogg");
	bufferSword.loadFromFile("resources/sounds/sword.ogg");
	bufferEarth.loadFromFile("resources/sounds/earth.ogg");
	bufferFire.loadFromFile("resources/sounds/fire.ogg");
	bufferIce.loadFromFile("resources/sounds/ice.ogg");
	bufferLight.loadFromFile("resources/sounds/light.ogg");
	bufferJade.loadFromFile("resources/sounds/jade.ogg");
	bufferHeroTakeDamage.loadFromFile("resources/sounds/heroTakeDamage.ogg");
	bufferDragonTakeDamage.loadFromFile("resources/sounds/dragonTakeDamage.ogg");
	bufferBonus.loadFromFile("resources/sounds/bonus.ogg");


	//SOUNDS
	jumpSound.setBuffer(bufferJump);
	stepSound.setBuffer(bufferStep);
	swordSound.setBuffer(bufferSword);
	earthSound.setBuffer(bufferEarth);
	fireSound.setBuffer(bufferFire);
	iceSound.setBuffer(bufferIce);
	lightSound.setBuffer(bufferLight);
	jadeSound.setBuffer(bufferJade);
	heroTakeDamageSound.setBuffer(bufferHeroTakeDamage);
	dragonTakeDamageSound.setBuffer(bufferDragonTakeDamage);
	bonusSound.setBuffer(bufferBonus);




	//TEXTURE
	heroTexture.loadFromFile("resources/img/Hero.png");
	heroTexture.setSmooth(true);


	mapTexture.loadFromFile("resources/img/background1.png");
	mapSprite.setTexture(mapTexture);
	mapSprite.setPosition(0, 0);

	mapTextureFw.loadFromFile("resources/img/background2.png");
	mapTextureFw.setRepeated(true);
	mapSpriteFw.setTexture(mapTextureFw);
	mapSpriteFw.setTextureRect(IntRect(0, 0, 3200, 400));
	mapSpriteFw.scale(Vector2f(1.0f, 1.2f));


	tileSet.loadFromFile("resources/img/MapBuild.png");
	tile.setTexture(tileSet);

	dragonTexture.loadFromFile("resources/img/Dragons.png");
	dragonTexture.setSmooth(true);

	dragonDialog.loadFromFile("resources/img/dialogDragon.png");
	dialogDragon.setTexture(dragonDialog);
	dialogDragon.setColor(Color(255, 255, 255, 150));
	dialogDragon.setTextureRect(IntRect(263, 0, -263, 145));
	dialogDragon.scale(Vector2f(0.7f, 0.7f));

	heroDialog.loadFromFile("resources/img/dialogHero.png");
	dialogHero.setTexture(heroDialog);
	dialogHero.setColor(Color(255, 255, 255, 150));
	dialogHero.setTextureRect(IntRect(0, 0, 260, 166));
	dialogHero.scale(Vector2f(0.4f, 0.3f));




	//UNITS
	player.set(150, 20, heroTexture, heroTakeDamageSound, swordSound);
	//ENEMY* enemyType;


	earthDragon.init(earthSound, dragonTakeDamageSound, 1);
	fireDragon.init(fireSound, dragonTakeDamageSound, 2);
	iceDragon.init(iceSound, dragonTakeDamageSound, 3);
	lightDragon.init(lightSound, dragonTakeDamageSound, 4);
	jadeDragon.init(jadeSound, dragonTakeDamageSound, 5);

	enemyType = &jadeDragon;

	

	//TEXT
	setText(Health, L"", 25);
	setText(Score, L"", 25);
	setText(question, L"", 20);
	setText(answer, L"", 25);
	setText(attackDamage, L"", 20);
	setText(gameResult, L"", 80);
	setText(continueString, L"◊ÚÓ·˚ Ì‡˜‡Ú¸ Á‡ÌÓ‚Ó Ì‡ÊÏËÚÂ œ–Œ¡≈À", 20);
	setText(bonus, L"", 20);
	setText(enemyName, L"", 20);
	

	
	

	
	//DragonAttack
	shoot.set(dragonTexture);

}


int ScreenGame::Run(RenderWindow& window)
{	
	
	
	endMusic.stop();
	music.play();
	Font font;
	font.loadFromFile("resources/fonts/Gabriola.ttf");
	Health.setFont(font);
	Score.setFont(font);
	question.setFont(font);
	answer.setFont(font);
	attackDamage.setFont(font);
	gameResult.setFont(font);
	continueString.setFont(font);
	bonus.setFont(font);
	enemyName.setFont(font);

	
	
	

	attackDamage.setFillColor(Color::Red);
	gameResult.setFillColor(Color::Red);
	continueString.setFillColor(Color::White);
	answer.setFillColor(Color(0, 128, 0, 255));
	answer.setStyle(Text::Bold);
	question.setFillColor(Color::Black);
	enemyName.setFillColor(Color::Green);

	Health.setLineSpacing(0.6f);
	enemyName.setLineSpacing(0.5f);
	continueString.setOutlineColor(Color::Black);
	continueString.setOutlineThickness(0.8f);
	gameResult.setOutlineColor(Color::Black);
	gameResult.setOutlineThickness(0.5f);


	Event Event;
	bool Running = true;
	bool firstRun = true;
	
	if (play)
	{
			std::string name = "";
			Text playerName(L"", font, 25);
			Text infText(L"¬‚Â‰ËÚÂ ¬‡¯Â ËÏˇ:", font, 25);
			Text infSubText(L"(ƒŒ—“”œÕŒ: [a-z],[A-Z], [0-9], ÒÔÂˆË‡Î¸Ì˚Â ÒËÏ‚ÓÎ˚, ÌÂ ·ÓÎÂÂ 15 ÒËÏ‚ÓÎÓ‚, ·ÂÁ ÔÓ·ÂÎÓ‚)", font, 18);

			infText.setPosition(80, 180);
			infSubText.setPosition(80, 250);
			playerName.setPosition(245, 180);

			//infSubText.setFillColor(Color::Red);
			infSubText.setLetterSpacing(2.5f);

			infText.setOutlineColor(Color::Black);
			infText.setOutlineThickness(1.f);
			infSubText.setOutlineColor(Color::Black);
			infSubText.setOutlineThickness(1.f);
			playerName.setOutlineColor(Color::Black);
			playerName.setOutlineThickness(1.f);
			playerName.setFillColor(Color::Green);


			while (play)
			{

				window.clear(Color::White);
				window.draw(mapSprite);
				window.draw(mapSpriteFw);


				while (window.pollEvent(Event))
				{
					if (Event.type == Event::Closed)
					{
						return -1;
					}

					if (Event.type == Event::TextEntered)
					{

						if (name.length() > 0 && Keyboard::isKeyPressed(Keyboard::BackSpace)) { name.erase(name.length() - 1, name.length()); }
						else
						{
							if (name.length() < 15)
							{
								if (Event.text.unicode >= 33 && Event.text.unicode <= 126)
								{
									name += static_cast<char>(Event.text.unicode);
								}

							}


							if (name.length() > 1 && Keyboard::isKeyPressed(Keyboard::Enter)) {

								player.setName(name);
								play = false;

							}
						}
						playerName.setString(name);
					}

				}




				window.draw(infText);
				window.draw(infSubText);
				window.draw(playerName);



				window.display();

			}



			play = false;
		restart(player, earthDragon, fireDragon, iceDragon, lightDragon, jadeDragon, dragonTexture, music, endMusic);
		
		
	}

	Clock clock;
	window.setMouseCursorVisible(false);

	while (Running)
	{
		
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time /= 800;
		//Event Event;
		
		

		if (EndGame && isMusic) {
			music.stop();
			endMusic.play();
			isMusic = false;
		}
		

		while (window.pollEvent(Event))
		{
			if (Event.type == Event::Closed)
			{
				return -1;
			}



			if (Event.type == Event::TextEntered && isAnswerNeeded)
			{

				if (str.length() > 0 && Keyboard::isKeyPressed(Keyboard::BackSpace)) { str.erase(str.length() - 1, str.length()); }
				else
				{
					if (str.length() > 2) { str = ""; }
					if (Event.text.unicode >= 48 && Event.text.unicode <= 57) {
						str += static_cast<char>(Event.text.unicode);
					}
					if (str.length() > 0 && Keyboard::isKeyPressed(Keyboard::Enter)) {
						isAnswerNeeded = false;
						solution = str;
						str = "";
					}
				}


				answer.setString(str);



			}
			if (!isAnswerNeeded) { str = ""; }

			dialogDragon.setPosition(player.rect.left - offsetX - 32, player.rect.top - offsetY - 120);
			question.setPosition(player.rect.left - offsetX - 16, player.rect.top - offsetY - 110);
			//question.setPosition(centerPos.x - question.getGlobalBounds().width / 2, centerPos.y - question.getGlobalBounds().height / 2 -10);

			dialogHero.setPosition(player.rect.left - offsetX, player.rect.top - offsetY - 40);
			answer.setPosition(player.rect.left - offsetX + 35, player.rect.top - offsetY - 43);


			if (Event.type == Event::TextEntered && EndGame)
			{
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					isAnswerNeeded = false;					
					restart(player, earthDragon, fireDragon, iceDragon, lightDragon, jadeDragon, dragonTexture, music, endMusic);
					EndGame = false;
					scoreSaved = false;
				}
			}

		}

		;


		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (!fight) {
				try
				{
					steps += time * 0.01;
					if (int(steps) == 0 && player.onGround) {
						stepSound.play();
						steps += 1;
					}
					if (steps > 5) {
						steps = 0;
					}
				}
				catch (const std::exception&)
				{
					throw;
				}


				player.dx = -0.1;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (!fight) {
				try
				{
					steps += time * 0.01;
					if (int(steps) == 0 && player.onGround) {
						stepSound.play();
						steps += 1;
					}
					if (steps > 5) {
						steps = 0;
					}
				}
				catch (const std::exception&)
				{
					throw;
				}

				player.dx = 0.1;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{

			try
			{
				if (!fight && player.onGround) { jumpSound.play(); }
			}
			catch (const std::exception&)
			{
				throw;
			}

			if (!fight && player.onGround) {
				player.dy = player.gravity;
				player.onGround = false;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape) && !firstRun) 
		{
			music.pause();
			endMusic.play();
			return 0;
		}
		
		//intersects
		if (!fight)
		{
			if (intersects(earthDragon, player, isAnswerNeeded)) {
				question.setString(L"–≈ÿ» ÃŒﬁ «¿ƒ¿◊”!\n             " + earthDragon.getQuestion() + " = ?");
				enemyType = &earthDragon;
			}
			else
			{
				if (intersects(fireDragon, player, isAnswerNeeded)) {
					question.setString(L"–≈ÿ» ÃŒﬁ «¿ƒ¿◊”!\n             " + fireDragon.getQuestion() + " = ?");
					enemyType = &fireDragon;
				}
				else
				{
					if (intersects(iceDragon, player, isAnswerNeeded)) {
						question.setString(L"–≈ÿ» ÃŒﬁ «¿ƒ¿◊”!\n             " + iceDragon.getQuestion() + " = ?");
						enemyType = &iceDragon;
					}
					else
					{
						if (intersects(lightDragon, player, isAnswerNeeded)) {
							question.setString(L"–≈ÿ» ÃŒﬁ «¿ƒ¿◊”!\n             " + lightDragon.getQuestion() + " = ?");
							enemyType = &lightDragon;
						}
						else
						{
							if (intersects(jadeDragon, player, isAnswerNeeded)) {
								question.setString(L"–≈ÿ» ÃŒﬁ «¿ƒ¿◊”!\n             " + jadeDragon.getQuestion() + " = ?");
								enemyType = &jadeDragon;
							}

						}
					}
				}


			}
		}

		///UNITS update
		if (!player.isMakingDamage && !player.isTakingDamage) {
			player.update(time, bonusSound);
			earthDragon.update(time, player.isMakingDamage);
			fireDragon.update(time, player.isMakingDamage);
			iceDragon.update(time, player.isMakingDamage);
			lightDragon.update(time, player.isMakingDamage);
			jadeDragon.update(time, player.isMakingDamage);
		}
		else
		{
			if (!player.isTakingDamage)
			{
				player.attack(*enemyType, time, attackDamage);
			}
			else
			{
				shoot.shoot(player, *enemyType, time, attackDamage);
			}


		}

		if (fight && !isAnswerNeeded) {
			battle(player, *enemyType, shoot, solution, question, isAnswerNeeded, time);
		}


		if (player.rect.left > 300) offsetX = player.rect.left - 300;
		//if (player.rect.top > 200) offsetY = player.rect.top - 200;

		window.clear(Color::White);
		if (EndGame && !player.isTakingDamage && !player.isMakingDamage)
		{
			if (!scoreSaved)
			{				
				std::string filePath = "resources/save/save.sav";
				fs.open(filePath, std::fstream::in | std::fstream::out | std::fstream::app);

				if (!fs.is_open())
				{
					MessageBoxA(NULL, "Œ¯Ë·Í‡ Á‡„ÛÁÍË: resources/save/save.sav", "Œ¯Ë·Í‡ ‰ÓÒÚÛÔ‡ Í Ù‡ÈÎÛ", MB_OKCANCEL | MB_ICONERROR);
					return 0;
				}
				else
				{

					std::string arrUsers[11];
					int arrScore[11];
					int i = 0, j = 0, num = 0;
					fs.clear();
					fs.seekg(0, std::ios::beg);

					while (!fs.eof())
					{
						if (num > 19) { break; }
						if (num % 2 == 0)
						{
							fs >> arrUsers[i];
							if (arrUsers[i] != "") { i++; }

						}
						else
						{
							fs >> arrScore[j];
							if (arrScore[j] >= 0) { j++; }
						}
						num++;
					}
					arrUsers[i] = player.getName();
					arrScore[j] = player.getScore();

					qsortRecursive(arrScore, arrUsers, i + 1);
					fs.close();
					fs.open(filePath, std::fstream::out);
					for (i = 0; i < 10; i++)
					{
						if (arrUsers[i] == "" || arrScore[i] < 0) { break; }
						fs << arrUsers[i] << std::endl;
						fs << arrScore[i] << std::endl;
					}
					fs.close();
					scoreSaved = true;
				}
			}
			


			

			if (!player.isAllive()) {
				gameResult.setString(L"¬˚ ÔÓË„‡ÎË!");
				endGameTexture.loadFromFile("resources/img/bkgLose.jpg");
				gameResult.setPosition(30, 220);
				continueString.setPosition(80, 320);				
			}
			else
			{
				gameResult.setString(L"œŒ¡≈ƒ¿!");
				endGameTexture.loadFromFile("resources/img/bkgWin.jpg");
				gameResult.setPosition(390, 10);
				continueString.setPosition(420, 110);
			}
			Sprite endGameSprite(endGameTexture);
			float xSize = window_width / 1280;
			float ySize = window_height / 720;
			endGameSprite.scale(Vector2f(0.625f, 0.6f));
			endGameSprite.setPosition(0, 0);
			window.draw(endGameSprite);
			window.draw(gameResult);
			window.draw(continueString);

			std::ostringstream sScore;
			sScore << player.getScore();
			Score.setString(L"¬‡¯ Ò˜ÂÚ: ");
			Score.setPosition(30, 150);
			Score.setFillColor(Color::White);
			Score.setOutlineThickness(1.f);
			Score.setOutlineColor(Color::Black);
			window.draw(Score);
			Score.setString(sScore.str());
			Score.setPosition(120, 150);
			Score.setFillColor(Color::Red);
			Score.setOutlineColor(Color::Black);
			window.draw(Score);
			Score.setOutlineThickness(0.f);

			EndGame = true;

		}
		else {
			if (!player.isMakingDamage || player.rect.left < 300) {
				mapSpriteFw.setPosition(0 - offsetX, 0 - offsetY);
			}
			else
			{
				mapSpriteFw.setPosition(0 - offsetX + 64, 0 - offsetY);
			}
			window.draw(mapSprite);
			window.draw(mapSpriteFw);

			for (int i = 0; i < H; i++)
				for (int j = 0; j < W; j++)
				{
					switch (GAME_MAP[i][j])
					{
					case 'p': {
						tile.setTextureRect(IntRect(224, 688, 32, 32));
						break;
					}
					case 'a': {
						tile.setTextureRect(IntRect(224, 368, 32, 32));
						break;
					}
					case 'b': {
						tile.setTextureRect(IntRect(336, 368, 32, 32));
						break;
					}
					case 'n': {
						tile.setTextureRect(IntRect(384, 368, 32, 32));
						break;
					}
					case 'k': {
						tile.setTextureRect(IntRect(528, 240, 32, 16));
						break;
					}
					case 'l': {
						tile.setTextureRect(IntRect(544, 240, 16, 16));
						break;
					}
					case 'm': {
						tile.setTextureRect(IntRect(128, 240, 32, 16));
						break;
					}
					case 'c': {
						tile.setTextureRect(IntRect(832, 896, 16, 16));
						cBonus[i][j] = 1;
						break;
					}
					case 't': {
						tile.setTextureRect(IntRect(752, 96, 48, 48));
						break;
					}
					case 'g': {
						tile.setTextureRect(IntRect(880, 96, 48, 48));
						break;
					}
					case 'S': {
						tile.setTextureRect(IntRect(952, 16, 16 * 4, 16 * 4));
						break;
					}
					case 'd': {
						tile.setTextureRect(IntRect(400, 176, 32, 32));
						break;
					}
					case 'e': {
						tile.setTextureRect(IntRect(256, 176, 32, 32));
						break;
					}
					case 'f': {
						tile.setTextureRect(IntRect(432, 320, 32, 32));
						break;
					}
					case 'x': {
						tile.setTextureRect(IntRect(749, 286, 24, 18));
						break;
					}

					case 'r': {
						tile.setTextureRect(IntRect(752, 16, 176, 16));
						break;
					}
					case 'w': {
						tile.setTextureRect(IntRect(864, 896, 16, 16));
						wBonus[i][j] = 1;
						break;
					}
					case 'h': {
						tile.setTextureRect(IntRect(576, 96, 32, 32));
						break;
					}case 'H': {
						tile.setTextureRect(IntRect(624, 80, 32, 48));
						break;
					}case 'y': {
						tile.setTextureRect(IntRect(302, 96, 32, 32));
						break;
					}case 'Y': {
						tile.setTextureRect(IntRect(32, 80, 32, 48));
						break;
					}case 'z': {
						tile.setTextureRect(IntRect(80, 96, 32, 32));
						break;
					}case 's': {
						tile.setTextureRect(IntRect(224, 736, 98, 64));
						break;
					}case 'R': {
						tile.setTextureRect(IntRect(48, 590, 32, 64));
						break;
					}case '1': {
						tile.setTextureRect(IntRect(96, 624, 32, 48));
						break;
					}case '2': {
						tile.setTextureRect(IntRect(208, 624, 32, 48));
						break;
					}case '3': {
						tile.setTextureRect(IntRect(368, 624, 32, 48));
						break;
					}case '4': {
						tile.setTextureRect(IntRect(48, 590, 32, 48));
						break;
					}

					default:
						continue;
						break;
					}


					if (!player.isMakingDamage || player.rect.left < 300) {
						tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);
					}
					else
					{
						tile.setPosition(j * 16 - offsetX + 64, i * 16 - offsetY);
					}

					window.draw(tile);
				}
				try
				{
					///UNITS draw		
					
					window.draw(earthDragon.sprite);
					showEnemyName(earthDragon, enemyName);
					window.draw(enemyName);
					window.draw(fireDragon.sprite);
					showEnemyName(fireDragon, enemyName);
					window.draw(enemyName);
					window.draw(iceDragon.sprite);
					showEnemyName(iceDragon, enemyName);
					window.draw(enemyName);
					window.draw(lightDragon.sprite);
					showEnemyName(lightDragon, enemyName);
					window.draw(enemyName);
					window.draw(jadeDragon.sprite);
					showEnemyName(jadeDragon, enemyName);
					window.draw(enemyName);
					window.draw(player.sprite);
					window.draw(shoot.sprite);
				}
				catch (const std::exception&)
				{
					return 0;
				}
			

			bonus.setPosition(player.sprite.getPosition());


			if (player.takeHealth) {
				bonus.setFillColor(Color::Green);
				bonus.setString("+50 hp");
				window.draw(bonus);
			}
			if (player.takeGravity) {
				bonus.setFillColor(Color::Magenta);
				bonus.setString("SuperJump!");
				window.draw(bonus);
			}

			if (isAnswerNeeded && !player.isMakingDamage && !player.isTakingDamage) {
				window.draw(dialogDragon); window.draw(dialogHero);  window.draw(question); window.draw(answer);
			}

			std::ostringstream sHealth, sScore;
			sHealth << player.getHealth();
						
			Health.setString(L"»Ïˇ:\n«‰ÓÓ‚¸Â:");
			Health.setPosition(30, 10);
			Health.setFillColor(Color::White);
			window.draw(Health);
			Health.setString(player.getName());
			Health.setPosition(80, 10);
			Health.setFillColor(Color(10,180,0));
			window.draw(Health);
			Health.setString(sHealth.str());
			Health.setPosition(115, 35);
			Health.setFillColor(Color(180, 0, 10));
			window.draw(Health);

			sScore << player.getScore();
			Score.setString(L"—˜ÂÚ: ");
			Score.setPosition(window_width - 110, 10);
			Score.setFillColor(Color::White);
			window.draw(Score);
			Score.setString(sScore.str());
			Score.setPosition(window_width - 55, 10);
			Score.setFillColor(Color(10, 180, 0));
			window.draw(Score);
			

			window.draw(Health);
			if (player.isMakingDamage || player.isTakingDamage) { window.draw(attackDamage); }
		}


		window.display();
		firstRun = false;
	}

	//Never reaching this point normally, but just in case, exit the windowlication
	return -1;
};




