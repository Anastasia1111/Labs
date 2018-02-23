#ifndef CARTESIANSYSTEM_H
#define CARTESIANSYSTEM_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace sf;

class CartesianSystem
{
public:
    CartesianSystem(double(*calcFunction)(double));
    void run();

private:
    void drawLineWithAffinage(const VertexArray vertices);
    void drawCoordSystem();
    void drawFunction();

    double (*calcFunc)(double);
    RenderWindow *window;
    View *view;
    double scale;
};

#endif // CARTESIANSYSTEM_H
