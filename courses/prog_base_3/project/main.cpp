#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow win(sf::VideoMode(1024, 768), "Mario 0.1");

    Image heroimage;                                // create object image
    heroimage.loadFromFile("images/mario.png");     //load file into object

    Texture herotexture;                            // create texture
    heroimage.createMaskFromColor(Color(255, 255, 255));
    herotexture.loadFromImage(heroimage);           //load imge into texture


    Sprite herosprite;                              // create sprite object
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(IntRect(0,0,18,38));     // rectangle for 1 tile
    herosprite.setScale(2, 2);
    herosprite.setPosition(50, 400);
    float CurentFrame = 0;

    Clock clock;

    while (win.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        Event event;
        while (win.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                win.close();
            }
        }



        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
            CurentFrame += 0.005 * time;
            if (CurentFrame > 3) CurentFrame = 0;
            herosprite.setTextureRect(IntRect(18*int(CurentFrame) + 18, 0, -18, 38));
            herosprite.move(-0.1*time, 0);
        }
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
		    CurentFrame += 0.005 * time;
            if (CurentFrame > 3) CurentFrame = 0;
            herosprite.setTextureRect(IntRect(18*int(CurentFrame), 0, 18, 38));
            herosprite.move(0.1*time, 0);
        }
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
            CurentFrame += 0.005 * time;
            if (CurentFrame > 3) CurentFrame = 0;
            herosprite.move(0, -0.1*time);
            herosprite.setTextureRect(IntRect(20*int(CurentFrame) + 210, 9, 20, 26));
        }

        win.clear();
        win.draw(herosprite);
        win.display();
    }

    return 0;
}
