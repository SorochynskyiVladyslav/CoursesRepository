#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include <SFML/Graphics.hpp>
using namespace sf;

View view;

void setPlayerCoordinateForView(float x,float y) {
    float tempX = x;
    float tempY = y;

	if (y > 624) tempY = 624;

    view.setCenter(tempX, tempY);
}


#endif // VIEW_H_INCLUDED
