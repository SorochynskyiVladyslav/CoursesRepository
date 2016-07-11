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

	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H ){
	    CurrentFrame = 0;
        Score = 0;
        state = stay;
        onGround = false;
        lives = 3;
        obj = lev.GetAllObjects();
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
        if (life)
        control();
        switch (state)
        {
           case right:
               dx = speed;
               if (speed != 0) {
               if (CurrentFrame > 3) CurrentFrame = 0;
               sprite.setTextureRect(IntRect(16*int(CurrentFrame) + 5, 6, 16, 38));
               }
               else
                 sprite.setTextureRect(IntRect(5, 6, 16, 38));
               break;
           case left:
               dx = -speed;
               if (speed != 0) {
               if (CurrentFrame > 3) CurrentFrame = 0;
               sprite.setTextureRect(IntRect(16*int(CurrentFrame) + 21, 6, -16, 38));
               }
               else
                sprite.setTextureRect(IntRect(21, 6, -16, 38));
               break;
           case up:
               if (CurrentFrame > 2) CurrentFrame = 0;
               sprite.setTextureRect(IntRect(20*int(CurrentFrame) + 210, 9, 20, 26));
               break;
           case stay:
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
	Enemy(Image &image, String Name,Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H){
        obj = lvl.GetObjects("solid");
        lives = 1;
		if (name == "EasyEnemy"){
            sprite.setTextureRect(IntRect(0, 4, width, height));
            dx = 0;
            sprite.setScale(2, 2);
        }
	}

    void checkCollisionWithMap(float Dx, float Dy)
    {
        for (int i = 0; i<obj.size(); i++)
        if (getRect().intersects(obj[i].rect))
        {
        //if (obj[i].name == "solid"){//если встретили препятствие (объект с именем solid)
            if (Dy>0)	{ y = obj[i].rect.top - height;  dy = 0; onGround = true; }
            if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
            if (Dx>0)	{ x = obj[i].rect.left - width;  dx = -0.1; sprite.scale(-1, 1); }
            if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
        //}
		}
	}

	void update(float time)
	{
		if (name == "EasyEnemy"){
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//меняет направление примерно каждые 3 сек
			checkCollisionWithMap(dx, 0);
			//x += dx*time;
			//sprite.setPosition(x + w / 2, y + h / 2);
			if (lives != 1){ life = false; }
		}
	}
};




#endif // ENTITY_H_INCLUDED
