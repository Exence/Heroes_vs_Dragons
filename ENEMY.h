#pragma once


class ENEMY :
    public UNIT
{

private:
	int answer;
	int type = 0;	
	int restartHealth;

public:
	FloatRect rect;
	Sprite sprite;
	Sound attackSound;
	Sound takeDamageSound;
	float currentFrame;

	ENEMY(){}	
	
	ENEMY(int health, int damage, Sound& attckSnd, Sound& takeDmgSnd, int enemyType) :UNIT(health, damage) {

		setName(L"        lvl. 1\nEarth Dragon\n       ");
		switch (enemyType)
		{
		case 1: {
			setName(L"        lvl.  1\nEarth Dragon\n       ");
			break;
		}
		case 2: {
			setName(L"        lvl. 2\nFire Dragon\n       ");
			break;
		}
		case 3: {
			setName(L"        lvl. 3\nIce Dragon\n       ");
			break;
		}
		case 4: {
			setName(L"        lvl. 4\nLight Dragon\n       ");
			break;
		}
		case 5: {
			setName(L"    lvl. ????\nJade Dragon\n     ");
			break;
		}
		default:
			break;
		}

		attackSound = attckSnd;
		takeDamageSound = takeDmgSnd;
		type = enemyType;
		restartHealth = health;
	}
	~ENEMY(){}

	void init(Sound& attckSnd, Sound& takeDmgSnd, int enemyType)
	{
		setName(L"        lvl. 1\nEarth Dragon\n       ");
		switch (enemyType)
		{
		case 1: {
			setName(L"        lvl. 1\nEarth Dragon\n       ");
			break;
		}
		case 2: {
			setName(L"        lvl. 2\nFire Dragon\n       ");
			break;
		}
		case 3: {
			setName(L"        lvl. 3\nIce Dragon\n       ");
			break;
		}
		case 4: {
			setName(L"        lvl. 4\nLight Dragon\n       ");
			break;
		}
		case 5: {
			setName(L"    lvl. ????\nJade Dragon\n     ");
			break;
		}
		default:
			break;
		}

		attackSound = attckSnd;
		takeDamageSound = takeDmgSnd;
		type = enemyType;


	}

	void set(Texture& image, int x, int y, int dmg, int hp)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 62, 62);
		currentFrame = 0;
		setDamage(dmg);
		setHealth(hp);
		restartHealth = hp;
	}

	void update(float time, bool isMakingDamageed) {
		currentFrame += time * 0.005;
		if (currentFrame > 3) currentFrame -= 3;
		switch (getType())
		{
		case 1: {
			sprite.setTextureRect(IntRect(62 * int(currentFrame) + 62, 0, 60, 60));
			break;
		}
		case 2: {
			sprite.setTextureRect(IntRect(62 * int(currentFrame) + 62, 248, 60, 60));			
			break;
		}
		case 3: {
			sprite.setTextureRect(IntRect(62 * int(currentFrame) + 62, 454, 60, 60));
			break;
		}
		case 4: {
			sprite.setTextureRect(IntRect(62 * int(currentFrame) + 62, 676, 60, 60));
			break;
		}
		case 5: {
			sprite.setTextureRect(IntRect(62 * int(currentFrame) + 62, 896, 60, 60));
			break;
		}
		default:
			sprite.setTextureRect(IntRect(62 * int(currentFrame) + 62, 0, 60, 60));
			break;
		}
		
		if (!isAllive() && !isMakingDamageed) sprite.setTextureRect(IntRect(0, 0, 1, 1));
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}

	std::string getQuestion()
	{

		std::ostringstream question;


		int a, b, c, choise, enemyType;
		srand(time(0));
		int sumRange = 50;
		switch (type)
		{
		case 1: {
			a = 1 + rand() % sumRange;
			b = 1 + rand() % sumRange;
			answer = a + b;
			question << a << " + " << b;
			break;

		}
		case 2: {
			a = 1 + rand() % sumRange;
			b = 1 + rand() % sumRange;
			if (a > b) {
				answer = a - b;
				question << a << " - " << b;
			}
			else {
				answer = b - a;
				question << b << " - " << a;
			}
			break;
		}
		case 3: {
			a = rand() % 10;
			b = rand() % 10;
			if (a < 8) { a += 2; }
			if (b < 8) { b += 2; }
			answer = a * b;
			question << a << " x " << b;
			break;
		}
		case 4: {
			a = rand() % 10;
			b = rand() % 10;
			if (a < 8) { a += 2; }
			if (b < 8) { b += 2; }
			c = a * b;
			answer = c / a;
			question << c << " : " << a;
			break;
		}
		case 5: {
			choise = 1 + rand() % 4;
			enemyType = type;
			type = choise;
			question << getQuestion();
			type = enemyType;
			break;
		}
		default:
			a = 1 + rand() % (sumRange + 1);
			b = 1 + rand() % (sumRange + 1);
			answer = a + b;
			question << a << " + " << b;

			break;
		}
		return question.str();
	}


	int getAnswer() {
		return answer;
	}

	int getType() {
		return type;
	}

	void setType(int enemyType) {
		type = enemyType;
	}

	int getRestartHealth() {
		return restartHealth;
	}
};

