/*
* Author: Dominic Handsborough ...
* Assignment Title: Final Project
* Assignment Description: Whack-a-mole
* Due Date: 5/7/2025
* Date Created: 4/21/2025
* Date Last Modified: 4/22/2025
*/

#include "Cat.h"
double distance(point p1, double x, double y){
	return sqrt(pow(p1.x - x, 2) + pow(p1.y - y, 2));
}

double distance(point p1, point p2){
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int random(int min, int max){
	return (rand() % (max - min + 1)) + min;
}

Cat::Cat(point pointIn) : start(pointIn), position(pointIn), timeAlive(0),
furColor(150, 75, 0),
eyeColor(0, 0, 0),
noseColor(255, 182, 193),
whiskerColor(169, 169, 169),
mouthColor(0, 0, 0),
tongueColor(255, 105, 180)
{}

void Cat::draw(SDL_Plotter& screen){
	drawCat(position, radius,
                furColor, eyeColor, noseColor,
                whiskerColor, mouthColor, tongueColor,
                screen);
}

void Cat::undraw(SDL_Plotter& screen){
	for(double i = position.x - 2 * radius; i < position.x + 2 * radius; i += 0.5){
		for(double j = position.y - 2 * radius; j < position.y + 2 * radius; j += 0.5){
			screen.plotPixel(i, j, 255, 255, 255);
		}
	}
}

void Cat::update(SDL_Plotter& screen){
	undraw(screen);
	point newPos;
	newPos.x = random(position.x - speed, position.x + speed);
	newPos.y = random(position.y - speed, position.y + speed);
	if(distance(start, newPos) < roamingDistance - 3 * radius / 2){
		position = newPos;
	}
	draw(screen);
	timeAlive++;
}

bool Cat::contains(point place){
	return (distance(position, place) < radius);
}

bool Cat::wouldOverlap(point place){
	return (distance(position, place) < 2 * roamingDistance);
}

bool Cat::isTimedOut(){
	return timeAlive > lifeSpan;
}

int Cat::kill(SDL_Plotter& screen){
	undraw(screen);
	return (isTimedOut()) ? 0 : (lifeSpan - timeAlive);
}

int Cat::getRoamingDistance(){
	return roamingDistance;
}



