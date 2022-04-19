#pragma once
class UNIT
{
private:
	int damage;
	int health;
	bool life = true;
	String name;
protected:
	UNIT() {}
	UNIT(int hp, int dmg) {
		health = hp;
		damage = dmg;

	}

public:
	void setDamage(int dmg) {
		damage = dmg;
	}
	int makeDamage() {
		return damage;
	}
	void setHealth(int hp) {
		health = hp;
		if (health <= 0) { life = false; }
		else
		{
			life = true;
		}
	}
	int getHealth() {
		return health;
	}

	bool isAllive() {
		return life;
	}

	bool takeDamage(int dmg) {
		setHealth(health - dmg);
		return life;
	}

	void setName(String textName)
	{
		name = textName;
	}

	String getName()
	{
		return name;
	}
};

