#pragma once
class EarthDragon :
    public ENEMY
{
public:    
    
    EarthDragon(Sound& attackSound, Sound& takeDamageSound, int type) :ENEMY(attackSound, takeDamageSound, type) {
        setType(1);
    }

    EarthDragon(int health, int damage, Sound& attckSnd, Sound& takeDamageSound, int type) :ENEMY(health, damage, attckSnd, takeDamageSound, type) {
        setType(1);
    }

    ~EarthDragon() {}

    virtual void update(float time, bool isMakingDamageed) override {
        currentFrame += time * 0.005;
        if (currentFrame > 3) currentFrame -= 3;

        sprite.setTextureRect(IntRect(62 * int(currentFrame) + 62, 0, 60, 60));

        if (!isAllive() && !isMakingDamageed) sprite.setTextureRect(IntRect(0, 0, 1, 1));


        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
    }
};
class FireDragon :
    public ENEMY
{
public:

    FireDragon(Sound& attackSound, Sound& takeDamageSound, int type) :ENEMY(attackSound, takeDamageSound, type) {
        setType(2);
    }

    FireDragon(int health, int damage, Sound& attckSnd, Sound& takeDamageSound, int type) :ENEMY(health, damage, attckSnd, takeDamageSound, type) {
        setType(2);
    }

    ~FireDragon() {}

    virtual void update(float time, bool isMakingDamageed) override {
        currentFrame += time * 0.005;
        if (currentFrame > 3) currentFrame -= 3;

        sprite.setTextureRect(IntRect(62 * int(currentFrame) + 62, 248, 60, 60));

        if (!isAllive() && !isMakingDamageed) sprite.setTextureRect(IntRect(0, 0, 1, 1));


        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
    }
};
class IceDragon :
    public ENEMY
{
public:

    IceDragon(Sound& attackSound, Sound& takeDamageSound, int type) :ENEMY(attackSound, takeDamageSound, type) {
        setType(3);
    }

    IceDragon(int health, int damage, Sound& attckSnd, Sound& takeDamageSound, int type) :ENEMY(health, damage, attckSnd, takeDamageSound, type) {
        setType(3);
    }

    ~IceDragon() {}

    virtual void update(float time, bool isMakingDamageed) override {
        currentFrame += time * 0.005;
        if (currentFrame > 3) currentFrame -= 3;

        sprite.setTextureRect(IntRect(62 * int(currentFrame) + 62, 454, 60, 60));

        if (!isAllive() && !isMakingDamageed) sprite.setTextureRect(IntRect(0, 0, 1, 1));


        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
    }
};
class LightDragon :
    public ENEMY
{
public:

    LightDragon(Sound& attackSound, Sound& takeDamageSound, int type) :ENEMY(attackSound, takeDamageSound, type) {
        setType(4);
    }

    LightDragon(int health, int damage, Sound& attckSnd, Sound& takeDamageSound, int type) :ENEMY(health, damage, attckSnd, takeDamageSound, type) {
        setType(4);
    }

    ~LightDragon() {}

    virtual void update(float time, bool isMakingDamageed) override {
        currentFrame += time * 0.005;
        if (currentFrame > 3) currentFrame -= 3;

        sprite.setTextureRect(IntRect(62 * int(currentFrame) + 62, 676, 60, 60));

        if (!isAllive() && !isMakingDamageed) sprite.setTextureRect(IntRect(0, 0, 1, 1));


        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
    }
};
class JadeDragon :
    public ENEMY
{
public:

    JadeDragon(Sound& attackSound, Sound& takeDamageSound, int type) :ENEMY(attackSound, takeDamageSound, type) {
        setType(5);
    }

    JadeDragon(int health, int damage, Sound& attckSnd, Sound& takeDamageSound, int type) :ENEMY(health, damage, attckSnd, takeDamageSound, type) {
        setType(5);
    }

    ~JadeDragon() {}

    virtual void update(float time, bool isMakingDamageed) override {
        currentFrame += time * 0.005;
        if (currentFrame > 3) currentFrame -= 3;

        sprite.setTextureRect(IntRect(62 * int(currentFrame) + 62, 896, 60, 60));

        if (!isAllive() && !isMakingDamageed) sprite.setTextureRect(IntRect(0, 0, 1, 1));


        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
    }
};
