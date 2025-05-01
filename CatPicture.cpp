//
//  Created by Isabelle Genson
//

#include "CatPicture.h"
#include <cmath>

void drawCircle(point loc, int size, color c, SDL_Plotter& g){
    for(double i = -size; i <= size;i+=0.1){
        for(double j = -size; j <= size; j+=0.1){
            if(i*i + j*j <= size*size){
                g.plotPixel(round(loc.x+i),round(loc.y+j),c);
            }
        }
    }

}
void drawTriangle(point p1, point p2, point p3, color c,SDL_Plotter& g){
    for (double i = 0; i <= 1; i += 0.01){
        for (double j = 0; j <= 1 - i; j += 0.01){
            int x = p1.x * (1 - i - j) + p2.x * i + p3.x * j;
            int y = p1.y * (1 - i - j) + p2.y * i + p3.y * j;
            g.plotPixel(x,y,c);
        }
    }
}
void drawEye(point center, int radius, color eyeColor, SDL_Plotter& g) {
    drawCircle(center, radius, eyeColor, g);
}

void drawLine(point p1, point p2, color c, SDL_Plotter& g) {
    int x1 = p1.x, y1 = p1.y;
    int x2 = p2.x, y2 = p2.y;

    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2 ? 1 : -1);
    int sy = (y1 < y2 ? 1 : -1);
    int err = dx - dy;

    while (true) {
        g.plotPixel(x1, y1, c);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx)  { err += dx; y1 += sy; }
    }
}
void drawCat(point center, int size, color fur, color eyeColor, color noseColor,
             color whiskerColor, color mouthColor, color tongueColor, SDL_Plotter& g) {
    drawCircle(center, size, fur, g);
        
    int earHeight = static_cast<int>(size * 1.2);
    int earBaseY = center.y - size / 2;
    point leftEarTip = {center.x - size / 2, center.y - earHeight};
    point leftEarBaseLeft = {static_cast<int>(center.x - size / 1.5), earBaseY};
    point leftEarBaseRight = {center.x, earBaseY};
    point rightEarTip = {center.x + size / 2, center.y - earHeight};
    point rightEarBaseLeft = {center.x, earBaseY};
    point rightEarBaseRight = {static_cast<int>(center.x + size / 1.5), earBaseY};
    drawTriangle(leftEarTip, leftEarBaseLeft, leftEarBaseRight, fur, g);
    drawTriangle(rightEarTip, rightEarBaseLeft, rightEarBaseRight, fur, g);
    
    point leftEye = {center.x - size/3, center.y - size/4};
    point rightEye = {center.x + size/3, center.y - size/4};
    drawEye(leftEye, size/10, eyeColor, g);
    drawEye(rightEye, size/10, eyeColor, g);

    point noseTop = {center.x, center.y};
    point noseLeft = {center.x - size/10, center.y + size/10};
    point noseRight = {center.x + size/10, center.y + size/10};
    drawTriangle(noseTop, noseLeft, noseRight, noseColor, g);

    int whiskerLength = size;
    int whiskerYOffset = size / 10;
    for (int i = 1; i <= 3; i++) {
        point leftStart = {center.x - size/4, center.y + i * whiskerYOffset};
        point leftEnd   = {leftStart.x - whiskerLength, leftStart.y};
        drawLine(leftStart, leftEnd, whiskerColor, g);
            
        point rightStart = {center.x + size/4, center.y + i * whiskerYOffset};
        point rightEnd   = {rightStart.x + whiskerLength, rightStart.y};
        drawLine(rightStart, rightEnd, whiskerColor, g);
    }
        
    point tailStart = {center.x + size / 2, center.y - size / 2};
    point tailEnd = {tailStart.x + size, tailStart.y - size};
    drawLine(tailStart, tailEnd, fur, g);
        
    point mouthCenter = {center.x, static_cast<int>(center.y + size / 2.5)};
    int mouthRadius = size / 11;
    drawCircle(mouthCenter, mouthRadius, mouthColor, g);

    point tongueCenter = {center.x, static_cast<int>(center.y + size / 2)};
    int tongueRadiusX = size / 16;
    int tongueRadiusY = size / 10;

    for (double i = -tongueRadiusX; i <= tongueRadiusX; i += 0.1) {
        for (double j = -tongueRadiusY; j <= tongueRadiusY; j += 0.1) {
            if ((i * i) / (tongueRadiusX * tongueRadiusX) +
                (j * j) / (tongueRadiusY * tongueRadiusY) <= 1) {
                g.plotPixel(round(tongueCenter.x + i), round(tongueCenter.y + j), tongueColor);
            }
        }
    }
}
