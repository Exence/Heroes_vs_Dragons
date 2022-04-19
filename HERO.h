#pragma once



class HERO :
    public UNIT
{
private: 
	int lastDirection = 0;
	int restartHealth;
	int currentEnemy = 0;
	int score = 0;
public:
	bool takeHealth = false;
	bool takeGravity = false;
	float dx, dy;
	FloatRect rect;
	Sound takeDamageSound;
	Sound swordSound;
	bool onGround;
	Sprite sprite;

	float currentFrame = 0;
	float bonusCurrentFrame = 0;
	float attackCurrentFrame;
	float gravity = -0.25;

	bool isMakingDamage = false;
	bool isTakingDamage = false;

	HERO() {
		rect = FloatRect(32, 18 * 16, 37, 37);
	};
	
	HERO(int health, int damage, Texture& image, Sound& takeDmgSnd, Sound& swordSnd) :UNIT(health, damage) {
		

		sprite.setTexture(image);
		rect = FloatRect(32, 18 * 16, 37, 37);
		dx = dy = 0;
		currentFrame = 0;
		attackCurrentFrame = 0;
		setDamage(damage);
		restartHealth = health;
		takeDamageSound = takeDmgSnd;
		swordSound = swordSnd;

		
	}


	void set(int health, int damage, Texture& image, Sound& takeDmgSnd, Sound& swordSnd) {


		sprite.setTexture(image);
		rect = FloatRect(32, 18 * 16, 37, 37);
		dx = dy = 0;
		currentFrame = 0;
		attackCurrentFrame = 0;
		setDamage(damage);
		setHealth(health);
		restartHealth = health;
		takeDamageSound = takeDmgSnd;
		swordSound = swordSnd;


	}


	void update(float time, Sound& bonusSound) {


		if (takeHealth || takeGravity) {
			bonusCurrentFrame += 0.0025 * time;
			switch (int(bonusCurrentFrame)) {
			case 0:
			{
				if (bonusSound.getStatus() != SoundSource::Playing) { bonusSound.play(); }
				sprite.setPosition(rect.left - offsetX, rect.top - 14 - offsetY);
				sprite.setTextureRect(IntRect(158, 696, 32, 46));
				if (takeHealth) {
					sprite.setColor(Color(255, 0, 0, 230));
				}
				else
				{
					sprite.setColor(Color(90, 0, 157, 230));
				}

				break;
			}
			case 1:
			{
				sprite.setTextureRect(IntRect(190, 696, 32, 46));
				sprite.setColor(Color(255, 255, 255, 255));

				break;
			}
			case 2:
			{
				sprite.setTextureRect(IntRect(220, 696, 32, 46));
				if (takeHealth) {
					sprite.setColor(Color(255, 0, 0, 230));
				}
				else
				{
					sprite.setColor(Color(90, 0, 157, 230));
				}
				break;
			}
			case 3:
			{
				sprite.setTextureRect(IntRect(250, 696, 32, 46));
				sprite.setColor(Color(255, 255, 255, 255));
				break;
			}
			case 4:
			{
				sprite.setTextureRect(IntRect(282, 696, 32, 46));
				if (takeHealth) {
					sprite.setColor(Color(255, 0, 0, 230));
				}
				else
				{
					sprite.setColor(Color(90, 0, 157, 230));
				}
				break;
			}
			case 5:
			{
				sprite.setTextureRect(IntRect(158, 696, 32, 46));
				sprite.setColor(Color(255, 255, 255, 255));
				sprite.setPosition(rect.left - offsetX, rect.top + 14 - offsetY);
				takeHealth = false;
				takeGravity = false;
				bonusCurrentFrame = 0;
				break;
			}
			default:
			{
				bonusCurrentFrame = 0;
				break;
			}
			}
		}
		else
		{
			currentFrame += STEPDELAY * time;
			rect.left += dx * time;
			Collision(0);

			if (!onGround) {
				dy = dy + 0.0005 * time;
			}

			rect.top += dy * time;

			onGround = false;

			Collision(1);




			switch (int(currentFrame))
			{
			case 0:
			{

				if (dx > 0) { sprite.setTextureRect(IntRect(106, 107, 31, 34)); lastDirection = 0; }
				if (dx < 0) { sprite.setTextureRect(IntRect(106 + 31, 107, -31, 34)); lastDirection = 1; }
				break;
			}
			case 1:
			{
				if (dx > 0) { sprite.setTextureRect(IntRect(158, 107, 23, 34)); lastDirection = 0; }
				if (dx < 0) { sprite.setTextureRect(IntRect(158 + 23, 107, -23, 34)); lastDirection = 1; }

				break;
			}
			case 2:
			{
				if (dx > 0) { sprite.setTextureRect(IntRect(213, 107, 34, 34)); lastDirection = 0; }
				if (dx < 0) { sprite.setTextureRect(IntRect(213 + 34, 107, -34, 34)); lastDirection = 1; }
				break;
			}
			case 3:
			{
				if (dx > 0) { sprite.setTextureRect(IntRect(275, 107, 23, 34)); lastDirection = 0; }
				if (dx < 0) { sprite.setTextureRect(IntRect(275 + 23, 107, -23, 34)); lastDirection = 1; }
				break;
			}
			case 4:
			{
				if (dx > 0) { sprite.setTextureRect(IntRect(325, 107, 31, 34)); lastDirection = 0; }
				if (dx < 0) { sprite.setTextureRect(IntRect(325 + 31, 107, -31, 34)); lastDirection = 1; }
				break;
			}
			case 5:
			{
				if (dx > 0) { sprite.setTextureRect(IntRect(391, 107, 31, 34)); lastDirection = 0; }
				if (dx < 0) { sprite.setTextureRect(IntRect(391 + 31, 107, -31, 34)); lastDirection = 1; }
				break;
			}
			default:
			{
				currentFrame = 0;
				break;
			}
			}
			if (dx == 0) {
				if (lastDirection == 0)
				{
					sprite.setTextureRect(IntRect(83, 232, 40, 37));
				}
				else
				{
					sprite.setTextureRect(IntRect(83 + 40, 232, -40, 37));
				}
			}




			sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

			dx = 0;
		}




	}


	void attack(ENEMY& enemy, float time, Text& attackDamage)
	{
		attackCurrentFrame += time * 0.01;


		std::ostringstream ss;
		ss << "-" << makeDamage();
		attackDamage.setString(ss.str());
		attackDamage.setPosition(enemy.rect.left + 62 - offsetX, enemy.rect.top + 20 - offsetY - int(attackCurrentFrame) * 5);
		enemy.takeDamageSound.play();

		if (int(attackCurrentFrame) < 5) {
			sprite.setTextureRect(IntRect(int(attackCurrentFrame) * 42, 342, 42, 56));
		}
		else
			if (int(attackCurrentFrame) == 5) {
				sprite.setTextureRect(IntRect(178, 342, 42, 56));
				enemy.sprite.setColor(Color(255, 0, 0, 127));
			}
			else
				if (int(attackCurrentFrame) == 6) {
					sprite.setTextureRect(IntRect(222, 342, 46, 56));
					enemy.sprite.setColor(Color(255, 0, 0, 255));
				}
				else
					if (int(attackCurrentFrame) == 7) {
						sprite.setTextureRect(IntRect(274, 342, 64, 56));
						enemy.sprite.setColor(Color(255, 0, 0, 127));
					}
					else
						if (int(attackCurrentFrame) == 8) {
							sprite.setTextureRect(IntRect(342, 342, 48, 56));
							enemy.sprite.setColor(Color(255, 0, 0, 255));
						}
						else
							if (int(attackCurrentFrame) == 9) {
								sprite.setTextureRect(IntRect(398, 342, 46, 56));
								enemy.sprite.setColor(Color(255, 0, 0, 127));
							}
							else
								if (int(attackCurrentFrame) == 10) {
									sprite.setTextureRect(IntRect(452, 342, 46, 56));
									enemy.sprite.setColor(Color(255, 0, 0, 255));
								}
								else
									sprite.setTextureRect(IntRect(496, 342, 42, 56));
		if (attackCurrentFrame > 11) {
			attackCurrentFrame -= 11;
			isMakingDamage = false;
			rect.left -= 64;
			rect.top += 19;
			rect.height = 37;
			rect.width = 37;
			enemy.sprite.setColor(Color(255, 255, 255, 255));
		}

		if (rect.left > 300) {
			sprite.setPosition(rect.left - offsetX + 64, rect.top - offsetY);
		}
		else
		{
			sprite.setPosition(rect.left, rect.top - offsetY);
		}


	}

	bool makeDamageToEnemy(ENEMY& enemy) { //true - если противник ещё жив
		enemy.takeDamage(makeDamage());
		isMakingDamage = true;
		rect.left += 64;
		rect.top -= 19;
		rect.height = 56;
		rect.width = 64;

		return enemy.isAllive();
	}


	int getRestartHealth() {
		return restartHealth;
	}

	void Collision(int dir)
	{
		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if (GAME_MAP[i][j] == 'c')
				{
					GAME_MAP[i][j] = ' ';
					setHealth(getHealth() + 50);
					takeHealth = true;

				}

				if (strchr(MAP_LANG, (char)GAME_MAP[i][j]))
				{
					if ((dx > 0) && (dir == 0)) rect.left = j * 16 - rect.width;
					if ((dx < 0) && (dir == 0)) rect.left = j * 16 + 16;
					if ((dy > 0) && (dir == 1)) { rect.top = i * 16 - rect.height;  dy = 0;   onGround = true;}
					if ((dy < 0) && (dir == 1)) { rect.top = i * 16 + 16;   dy = 0; }
				}

				

				if (GAME_MAP[i][j] == 'w')
				{
					GAME_MAP[i][j] = ' ';
					takeGravity = true;
					gravity = -0.35;
				}

			}

	}

	void setCurrentEnemy(int enemyType) {
		currentEnemy = enemyType;
	}

	int getCurrentEnemy() {
		return currentEnemy;
	}

	//Добавляет указанное число очков к общему счету
	void setScore(int newPoints) 
	{
		score += newPoints;
		if (score < 0)
		{
			score = 0;
		}
	}

	int getScore()
	{
		return score;
	}

};

