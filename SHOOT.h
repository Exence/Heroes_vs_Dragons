#pragma once


class SHOOT
{
private: bool fly = false;
public:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;
	SHOOT() {}
	void set(Texture& image) {
		sprite.setTexture(image);
		rect = FloatRect(32, 32, 37, 37);
		sprite.setColor(Color(255, 255, 255, 0));
		dx = dy = 0;
		currentFrame = 0;

	}

	void shoot(HERO& hero, ENEMY& enemy, float time, Text& attackDamage) {
		currentFrame += time * 0.005;
		std::ostringstream ss;
		ss << "-" << enemy.makeDamage();
		attackDamage.setString(ss.str());
		attackDamage.setPosition(hero.rect.left + 5 - offsetX, hero.rect.top + 10 - offsetY - int(currentFrame) * 5);

		switch (enemy.getType())
		{
		case 1: {
			switch (int(currentFrame))
			{
			case 0: {
				enemy.sprite.setTextureRect(IntRect(62, 62, 62, 62));
				if (!fly) {
					enemy.sprite.setPosition(enemy.rect.left - offsetX, enemy.rect.top - offsetY - 62);
					fly = true;
				}
				break;
			}
			case 1: {
				enemy.sprite.setTextureRect(IntRect(62 * 2, 62, 48, 62));
				break;
			}
			case 2: {
				enemy.sprite.setTextureRect(IntRect(175, 62, 62, 62));
				break;
			}
			case 3: {
				sprite.setColor(Color(255, 255, 255, 255));
				sprite.setTextureRect(IntRect(58, 125, 30, 62));
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY);
				break;
			}
			case 4: {
				sprite.setTextureRect(IntRect(84, 125, 26, 62));
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY);
				break;
			}
			case 5: {
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY);
				sprite.setTextureRect(IntRect(108, 125, 30, 62));
				hero.sprite.setTextureRect(IntRect(380, 640, 32, 36));
				break;
			}
			case 6: {
				sprite.setTextureRect(IntRect(139, 125, 30, 62));
				hero.takeDamageSound.play();
				break;
			}
			case 7: {
				sprite.setTextureRect(IntRect(170, 125, 30, 62));
				hero.sprite.setTextureRect(IntRect(418, 640, 36, 36));
				break;
			}
			case 8: {
				sprite.setTextureRect(IntRect(194, 125, 28, 62));

				break;
			}
			default:
				break;
			}


			if (currentFrame > 9) {
				sprite.setColor(Color(255, 255, 255, 0));
				currentFrame -= 9;
				enemy.sprite.setPosition(enemy.rect.left - offsetX, enemy.rect.top - offsetY + 62);
				hero.sprite.setPosition(hero.rect.left - offsetX, hero.rect.top - offsetY);
				fly = false;
				hero.isTakingDamage = false;
			}
			break;
		}
		case 2: {
			switch (int(currentFrame))
			{
			case 0: {
				enemy.sprite.setTextureRect(IntRect(62, 315, 62, 62));
				if (!fly) {
					enemy.sprite.setPosition(enemy.rect.left - offsetX, enemy.rect.top - offsetY - 62);
					fly = true;
				}
				break;
			}
			case 1: {
				enemy.sprite.setTextureRect(IntRect(62 * 2, 315, 48, 62));
				break;
			}
			case 2: {
				enemy.sprite.setTextureRect(IntRect(175, 315, 62, 62));
				break;
			}
			case 3: {
				sprite.setColor(Color(255, 255, 255, 255));
				sprite.setTextureRect(IntRect(75, 402, 15, 34));
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY + currentFrame * 15 - 62);
				break;
			}
			case 4: {
				sprite.setTextureRect(IntRect(90, 402, 18, 34));
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY + currentFrame * 15 - 62);
				break;
			}
			case 5: {
				sprite.setTextureRect(IntRect(112, 402, 32, 34));
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY + currentFrame * 15 - 62);
				hero.takeDamageSound.play();
				hero.sprite.setPosition(hero.rect.left - offsetX, hero.rect.top - 7 - offsetY);
				hero.sprite.setTextureRect(IntRect(90, 694, 40, 48));
				break;
			}
			case 6: {
				sprite.setTextureRect(IntRect(148, 402, 32, 34));
				hero.sprite.setTextureRect(IntRect(144, 632, 36, 48));
				break;
			}
			case 7: {
				sprite.setTextureRect(IntRect(184, 402, 32, 34));
				hero.sprite.setTextureRect(IntRect(180, 632, 30, 48));
				break;
			}
			case 8: {
				sprite.setColor(Color(255, 255, 255, 0));
				hero.sprite.setTextureRect(IntRect(144, 632, 36, 48));
				break;
			}
			default:
				break;
			}

			if (currentFrame > 9) {
				currentFrame -= 9;
				enemy.sprite.setPosition(enemy.rect.left - offsetX, enemy.rect.top - offsetY + 62);
				hero.sprite.setPosition(hero.rect.left - offsetX, hero.rect.top - offsetY);
				fly = false;
				hero.isTakingDamage = false;
			}
			break;
		}
		case 3: {
			switch (int(currentFrame))
			{
			case 0: {
				enemy.sprite.setTextureRect(IntRect(62, 520, 62, 62));
				if (!fly) {
					enemy.sprite.setPosition(enemy.rect.left - offsetX, enemy.rect.top - offsetY - 62);
					fly = true;
				}
				break;
			}
			case 1: {
				enemy.sprite.setTextureRect(IntRect(62 * 2, 520, 48, 62));
				break;
			}
			case 2: {
				enemy.sprite.setTextureRect(IntRect(175, 520, 62, 62));
				break;
			}
			case 3: {
				sprite.setColor(Color(255, 255, 255, 255));
				sprite.setTextureRect(IntRect(190, 584, 16, 34));
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY + currentFrame * 15 - 62);
				break;
			}
			case 4: {
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY + currentFrame * 15 - 62);
				break;
			}
			case 5: {
				sprite.setTextureRect(IntRect(154, 584, 34, 36));
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY + currentFrame * 15 - 62);
				hero.takeDamageSound.play();
				hero.sprite.setPosition(hero.rect.left - offsetX, hero.rect.top - 7 - offsetY);
				hero.sprite.setTextureRect(IntRect(288, 7, 32, 44));
				break;
			}
			case 6: {
				sprite.setTextureRect(IntRect(120, 584, 34, 36));
				hero.sprite.setTextureRect(IntRect(220, 7, 32, 44));
				break;
			}
			case 7: {
				sprite.setTextureRect(IntRect(82, 584, 36, 36));
				hero.sprite.setTextureRect(IntRect(186, 7, 32, 44));
				break;
			}
			case 8: {
				sprite.setColor(Color(255, 255, 255, 0));
				hero.sprite.setTextureRect(IntRect(254, 7, 32, 44));
				break;
			}
			default:
				break;
			}

			if (currentFrame > 9) {
				currentFrame -= 9;
				enemy.sprite.setPosition(enemy.rect.left - offsetX, enemy.rect.top - offsetY + 62);
				hero.sprite.setPosition(hero.rect.left - offsetX, hero.rect.top - offsetY);
				fly = false;
				hero.isTakingDamage = false;
			}
			break;
		}
		case 4: {
			switch (int(currentFrame))
			{
			case 0: {
				enemy.sprite.setTextureRect(IntRect(62, 742, 62, 62));
				if (!fly) {
					enemy.sprite.setPosition(enemy.rect.left - offsetX, enemy.rect.top - offsetY - 62);
					fly = true;
				}
				break;
			}
			case 1: {
				enemy.sprite.setTextureRect(IntRect(62 * 2, 742, 48, 62));
				break;
			}
			case 2: {
				enemy.sprite.setTextureRect(IntRect(175, 742, 62, 62));
				break;
			}
			case 3: {
				sprite.setColor(Color(255, 255, 255, 255));
				sprite.setTextureRect(IntRect(68, 808, 12, 34));
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY + currentFrame * 15 - 62);
				break;
			}
			case 4: {
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY + currentFrame * 15 - 62);
				break;
			}
			case 5: {
				sprite.setTextureRect(IntRect(96, 808, 12, 34));
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY + currentFrame * 15 - 62);
				hero.takeDamageSound.play();
				hero.sprite.setPosition(hero.rect.left - offsetX, hero.rect.top - 7 - offsetY);
				hero.sprite.setTextureRect(IntRect(476 + 48, 690, -48, 56));
				break;
			}
			case 6: {
				sprite.setTextureRect(IntRect(110, 808, 20, 34));
				hero.sprite.setTextureRect(IntRect(426 + 48, 690, -48, 56));
				break;
			}
			case 7: {
				sprite.setTextureRect(IntRect(130, 808, 26, 34));
				hero.sprite.setTextureRect(IntRect(476 + 48, 690, -48, 56));
				break;
			}
			case 8: {
				sprite.setTextureRect(IntRect(194, 808, 34, 34));
				hero.sprite.setTextureRect(IntRect(426 + 48, 690, -48, 56));
				break;
			}
			default:
				break;
			}

			if (currentFrame > 9) {
				currentFrame -= 9;
				sprite.setColor(Color(255, 255, 255, 0));
				enemy.sprite.setPosition(enemy.rect.left - offsetX, enemy.rect.top - offsetY + 62);
				hero.sprite.setPosition(hero.rect.left - offsetX, hero.rect.top - offsetY);
				fly = false;
				hero.isTakingDamage = false;
			}
			break;
		}
		case 5: {
			switch (int(currentFrame))
			{
			case 0: {
				enemy.sprite.setTextureRect(IntRect(62, 962, 62, 62));
				if (!fly) {
					enemy.sprite.setPosition(enemy.rect.left - offsetX, enemy.rect.top - offsetY - 62);
					fly = true;
				}
				break;
			}
			case 1: {
				enemy.sprite.setTextureRect(IntRect(62 * 2, 962, 48, 62));
				break;
			}
			case 2: {
				enemy.sprite.setTextureRect(IntRect(175, 962, 62, 62));
				break;
			}
			case 3: {
				sprite.setColor(Color(255, 255, 255, 255));
				sprite.setTextureRect(IntRect(0, 1028, 16, 32));
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY + currentFrame * 15 - 62);
				break;
			}
			case 4: {
				sprite.setTextureRect(IntRect(46, 1028, 34, 32));
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY + currentFrame * 15 - 62);
				break;
			}
			case 5: {
				sprite.setTextureRect(IntRect(116, 1028, 34, 32));
				sprite.setPosition(enemy.rect.left - currentFrame * 15 - offsetX, enemy.rect.top - offsetY + currentFrame * 15 - 62);
				hero.takeDamageSound.play();
				hero.sprite.setTextureRect(IntRect(380, 640, 32, 36));
				break;
			}
			case 6: {
				sprite.setTextureRect(IntRect(190, 1028, 34, 32));
				hero.sprite.setTextureRect(IntRect(418, 640, 36, 36));
				break;
			}
			case 7: {
				sprite.setTextureRect(IntRect(220, 1028, 34, 32));
				sprite.setColor(Color(255, 255, 255, 115));
				hero.sprite.setTextureRect(IntRect(380, 640, 32, 36));
				break;
			}
			case 8: {
				sprite.setTextureRect(IntRect(258, 1028, 34, 32));
				sprite.setColor(Color(255, 255, 255, 150));
				hero.sprite.setTextureRect(IntRect(418, 640, 36, 36));
				break;
			}
			default:
				break;
			}

			if (currentFrame > 9) {
				currentFrame -= 9;
				sprite.setColor(Color(255, 255, 255, 0));
				enemy.sprite.setPosition(enemy.rect.left - offsetX, enemy.rect.top - offsetY + 62);
				hero.sprite.setPosition(hero.rect.left - offsetX, hero.rect.top - offsetY);
				fly = false;
				hero.isTakingDamage = false;
			}
			break;
		}
		default:
			break;
		}

	}

	

	

	

	

};

