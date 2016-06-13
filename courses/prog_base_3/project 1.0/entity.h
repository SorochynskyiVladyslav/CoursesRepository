#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "level.h"
#include "view.h"
#include "tinyxml.h"
#include "tinystr.h"

using namespace sf;
using namespace std;

class Entity {
public:
	std :: vector <Object> obj;
	float dx, dy, x, y, speed, moveTimer, CurrentFrame;
	int width, height, lives;
	bool onGround, life, isMove;
	Texture texture;
	Sprite sprite;
	String name;

	Entity(Image &image, String Name, float X, float Y, int W, int H){
		x = X;
		y = Y;
		width = W;
		height = H;
		name = Name;
		moveTimer = 0;
		CurrentFrame = 0;
		speed = 0;
		dx = 0;
		dy = 0;
		onGround = false;
		isMove = false;
		life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(width / 2, height / 2);
	}

    virtual void update(float time) = 0;

	FloatRect getRect(){
		return FloatRect(x, y, width, height);
	}
};

class Player : public Entity {
public:
	enum { left, right, up, jump, stay } state;
	int Score;
    float CurrentFrame;
    SoundBuffer jumpBuffer;
    Sound jumpSound;
	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H ){
	    CurrentFrame = 0;
        Score = 0;
        state = stay;
        onGround = false;
        lives = 3;
        obj = lev.GetAllObjects();

        jumpBuffer.loadFromFile("sounds/jump.wav");
        jumpSound.setBuffer(jumpBuffer);
        if (name == "Player"){
            sprite.setTextureRect(IntRect(5, 6, 16, 38));
            sprite.setScale(1.5, 1.5);
        }
    }

    void control(){
        if (Keyboard::isKeyPressed){
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                state = left;
                speed = 0.1;
                }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                state = right;
                speed = 0.1;
                }
            if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
                state = jump;
                dy = -0.6;
                onGround = false;
                jumpSound.play();
                }
		   }
	   }

    void checkCollisionWithMap(float Dx, float Dy) {
        for (int i = 0; i<obj.size(); i++)
            if (getRect().intersects(obj[i].rect)) {
                if (obj[i].name == "solid") {
                    if (Dy>0) {
                        y = obj[i].rect.top - height;
                        dy = 0;
                        onGround = true;
                        }
                    if (Dy<0) {
                        y = obj[i].rect.top + obj[i].rect.height;
                        dy = 0;
                    }
                    if (Dx>0) {
                        x = obj[i].rect.left - width;
                    }
                    if (Dx<0) {
                        x = obj[i].rect.left + obj[i].rect.width;
                    }
                }
            }
    }

    void update(float time)
    {
        control();
        switch (state)
        {
           case right:
               dx = speed;
               if (speed != 0) {
               if (CurrentFrame > 4) CurrentFrame = 0;
               switch (int(CurrentFrame)) {
                case 0:
                    sprite.setTextureRect(IntRect(5, 6, 14, 30));
                    break;
                case 1:
                    sprite.setTextureRect(IntRect(21, 6, 16, 30));
                    break;
                case 2:
                    sprite.setTextureRect(IntRect(39, 7, 16, 29));
                    break;
                case 3:
                    sprite.setTextureRect(IntRect(57, 6, 16, 30));
                    break;
               }
               }
               else
                 sprite.setTextureRect(IntRect(5, 6, 14, 30));
               break;
           case left:
               dx = -speed;
               if (speed != 0) {
               if (CurrentFrame > 4) CurrentFrame = 0;
               switch (int(CurrentFrame)) {
                case 0:
                    sprite.setTextureRect(IntRect(19, 6, -14, 30));
                    break;
                case 1:
                    sprite.setTextureRect(IntRect(37, 6, -16, 30));
                    break;
                case 2:
                    sprite.setTextureRect(IntRect(55, 7, -16, 29));
                    break;
                case 3:
                    sprite.setTextureRect(IntRect(73, 6, -16, 30));
                    break;
               }
               }
               else
                sprite.setTextureRect(IntRect(21, 6, -17, 39));
               break;
           case up:
               break;
           case stay:
               sprite.setTextureRect(IntRect(5, 6, 14, 30));
               break;
       }
        CurrentFrame += 0.005 * time;
        x += dx*time;
        checkCollisionWithMap(dx, 0);
        y += dy*time;
        checkCollisionWithMap(0, dy);

        sprite.setPosition(x + width / 2, y + height / 2);

        if (lives == 0){
            life = false;
        }
        if (!isMove){
            speed = 0;
        }
        setPlayerCoordinateForView(x, y);
        if (life) {
            setPlayerCoordinateForView(x, y);
        }
        dy = dy + 0.0015*time;
   }
};

class Enemy : public Entity{
public:
    float deathTimer;
	Enemy(Image &image, String Name,Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H){
        obj = lvl.GetAllObjects();
        deathTimer = 0;
		if (name == "EasyEnemy"){
            lives = 1;
            sprite.setTextureRect(IntRect(0, 4, 16, 16));
            dx = 0;
            sprite.setScale(2, 2);
        }
        if (name == "MediumEnemy") {
            lives = 2;
            sprite.setTextureRect(IntRect(61, 1, 16, 23));
            dx = 0.075;
            sprite.setScale (2, 2);
        }
        if (name == "HardEnemy"){
            lives = 3;
            dx = 0.1;
            sprite.setScale(2.5, 2.5);
        }


	}

    void checkCollisionWithMap(float Dx, float Dy)
    {
        for (int i = 0; i < obj.size(); i++)
        if (getRect().intersects(obj[i].rect))
        {
        if (obj[i].name == "solid" || obj[i].name == "stop"){//если встретили препятствие (объект с именем solid)
            if (Dy>0)	{ y = obj[i].rect.top - height;  dy = 0; onGround = true; }
            if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
            if (Dx>0)	{
                    x = obj[i].rect.left - width;
                    if (name == "MediumEnemy")
                        dx = -0.075;
                    if (name == "HardEnemy")
                        dx = -0.1;
                    sprite.scale(-1, 1); }
            if (Dx<0)	{
                    x = obj[i].rect.left + obj[i].rect.width;
                    if (name == "MediumEnemy")
                        dx = 0.075;
                    if (name == "HardEnemy")
                        dx = 0.1;
                    sprite.scale(-1, 1); }
        }
		}
	}

	void update(float time)
	{
        CurrentFrame += 0.002 * time;
	    if (lives == 0) {
            deathTimer += 0.005 * time;
            height = 35;
	    }
	    if (deathTimer > 1)
            life = false;
		if (name == "EasyEnemy"){
            if (CurrentFrame > 2)
                CurrentFrame = 0;
            if (lives != 0) {
                switch ((int) CurrentFrame) {
                case 0:
                    sprite.setTextureRect(IntRect(0, 4, 16, 16));
                    break;
                case 1:
                    sprite.setTextureRect(IntRect(30, 4, 16, 16));
                    break;
                }
            }
		}
            if (name == "MediumEnemy") {
                if (lives == 0)
                    life = false;
                moveTimer += time;
                if (moveTimer > 5000){
                    dx *= -1;
                    sprite.scale(-1, 1);
                    moveTimer = 0;
                    }

                if (CurrentFrame > 2)
                CurrentFrame = 0;
                if (lives != 0) {
                switch ((int) CurrentFrame) {
                case 0:
                    sprite.setTextureRect(IntRect(61, 1, 16, 23));
                    break;
                case 1:
                    sprite.setTextureRect(IntRect(91, 1, 16, 24));
                    break;
                }
            }
            }

            if (name == "HardEnemy") {
                if (lives == 0)
                    life = false;
                moveTimer += time;
                if (moveTimer > 6000){
                    dx *= -1;
                    sprite.scale(-1, 1);
                    moveTimer = 0;
                    }

                if (CurrentFrame > 4)
                CurrentFrame = 0;
                if (lives != 0) {
                switch ((int) CurrentFrame) {
                case 0:
                    sprite.setTextureRect(IntRect(162, 2, 31, 31));
                    break;
                case 1:
                    sprite.setTextureRect(IntRect(201, 2, 32, 30));
                    break;
                case 2:
                    sprite.setTextureRect(IntRect(242, 2, 31, 31));
                    break;
                case 3:
                    sprite.setTextureRect(IntRect(281, 2, 32, 31));
                    break;
                }
            }
            }

			x += dx*time;
			checkCollisionWithMap(dx, 0);
			sprite.setPosition(x + width, y + height);
		}
};

class Coin : public Entity {
public:
    Coin (Image &image, String Name,Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H){
        obj = lvl.GetObjects("solid");
        sprite.setTextureRect(IntRect(7, 0, 18, 18));
    }
    void update (float time) {
        sprite.setPosition(x + 10, y + 10);
    }
};

class Exit : public Entity {
public:
    Exit (Image &image, String Name,Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H){
        //obj = lvl.GetObjects("solid");
        sprite.setTextureRect(IntRect(7, 0, 1, 1 ));
    }
    void update (float time) {
        sprite.setPosition(x + 10, y + 10);
    }
};

class Fire : public Entity {
public:
    Fire (Image &image, String Name,Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H){
        //obj = lvl.GetObjects("solid");
        sprite.setTextureRect(IntRect(7, 0, 1, 1));
    }
    void update (float time) {
        sprite.setPosition(x + 10, y + 10);
    }
};

class MovingPlatform : public Entity{//класс движущейся платформы
public:
	MovingPlatform(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H){
		sprite.setTextureRect(IntRect(0, 0, W, H));//прямоугольник
		dx = 0.08;//изначальное ускорение по Х
	}

	void update(float time)//функция обновления платформы.
	{
		x += dx * time;//реализация движения по горизонтали
		moveTimer += time;//наращиваем таймер
		if (moveTimer>2000) { dx*= -1; moveTimer = 0; }//если прошло примерно 2 сек, то меняется направление движения платформы,а таймер обнуляется
		sprite.setPosition(x+width/2, y+height/2);//задаем позицию спрайту
	}
};

#endif // ENTITY_H_INCLUDED
