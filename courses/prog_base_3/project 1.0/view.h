#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include <SFML/Graphics.hpp>
using namespace sf;

View view;

void setPlayerCoordinateForView(float x,float y) {
    float tempX = x;
    float tempY = y;

	if (y > 600) tempY = 600;
	if (y < 300) tempY = 300;
 	if (x < 400) tempX = 400;

    view.setCenter(tempX, tempY);
}


#endif // VIEW_H_INCLUDED
