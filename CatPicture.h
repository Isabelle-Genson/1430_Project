//
//  Created by Isabelle Genson
//

#ifndef CatPicture_h
#define CatPicture_h

#include "SDL_Plotter.h"


void drawCircle(point loc, int size, color c, SDL_Plotter& g);
void drawTriangle(point p1, point p2, point p3, color c, SDL_Plotter& g);
void drawEye(point center, int radius, SDL_Plotter& g);
void drawLine(point p1, point p2, color c, SDL_Plotter& g);
void drawCat(point center, int size, color fur, color eyeColor, color noseColor,
             color whiskerColor, color mouthColor, color tongueColor, SDL_Plotter& g);

#endif /* CatPicture_h */
