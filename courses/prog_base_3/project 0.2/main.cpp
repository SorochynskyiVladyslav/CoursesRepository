#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <vector>
#include "entity.h"
#include "level.h"
#include "view.h"

using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(1024, 768), "Mario 0.1");
    view.reset(FloatRect(0, 0, 700, 600));

    Level lvl;
    lvl.LoadFromFile("lev1.tmx");

    Image heroImage;
    heroImage.loadFromFile("images/mario.png");
    heroImage.createMaskFromColor(Color(255, 255, 255));
    Image easyEnemyImage;
    easyEnemyImage.loadFromFile("images/enemies.png");

    std::list<Entity*> entities;
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator it2;
    std::vector<Object> e = lvl.GetObjects("EasyEnemy");
    for (int i = 0; i < e.size(); i++) {
        entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 15, 15));
    }

    Object player = lvl.GetObject("player");
    Player p(heroImage, "Player", lvl, player.rect.left, player.rect.top, 22, 38);

    Clock clock;

    while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (it = entities.begin(); it != entities.end();) {
                Entity *b = *it;
                b->update(time);
                if (b->life == false) {
                    it = entities.erase(it);
                    delete b;
                }
                else it++;
        }

        for (it = entities.begin(); it != entities.end(); it++) {
            if (((*it)->name == "MovingPlatform") && ((*it)->getRect().intersects(p.getRect())))
			{
				Entity *movPlat = *it;
				if (p.dy>0)
				if (p.y + p.height < movPlat->y + movPlat->height)
				{
					p.y = movPlat->y - p.height + 3;
                    p.x += movPlat->dx*time;
                    p.dy = 0;
                    p.onGround = true;
				}
			}
            if ((*it)->getRect().intersects(p.getRect())) {
                if ((*it)->name == "EasyEnemy") {
                    if ((p.dy>0) && (p.onGround == false) && (p.y + p.height < (*it)->y + (*it)->height)) {
                        (*it)->dx = 0;
                        p.dy = -0.2;
                        (*it)->lives = 0;
                    }
                    else { p.x = player.rect.left; p.y = player.rect.top;}
                }
            }
            for (it2 = entities.begin(); it2 != entities.end(); it2++) {
                if ((*it)->getRect() != (*it2)->getRect())
                if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy")){
                    (*it)->dx *= -1;
                    (*it)->sprite.scale(-1.5, 1.5);
                }
            }
        }
        p.update(time);





		window.setView(view);
		window.clear();
		lvl.Draw(window);


        for (it = entities.begin(); it != entities.end(); it++) {

            window.draw((*it)->sprite);
		}

		window.draw(p.sprite);
		window.display();
	}

    return 0;
}
