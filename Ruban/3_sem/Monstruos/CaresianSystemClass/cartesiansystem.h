#ifndef CARTESIANSYSTEM_H
#define CARTESIANSYSTEM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <sstream>

using namespace sf;


//ALL FUNCTIONS FOR CS - USER FUNCTION INHERITORS
class UserFunc {
public:
    UserFunc() : relSolution(0) {}
    virtual double func(double x) = 0;
    void setSolution(int solution) { relSolution = solution; }
private :
    // relSolution defines how is the solution related to the function
    // -1 - smaller
    // 0 - equal
    // 1 - bigger
    int relSolution;
};

class CartesianSystem
{
public:
    CartesianSystem(std::vector<UserFunc *> calcFunc);
    void run();

private:
    void drawLineWithAffinage(const VertexArray vertices);
    void drawCoordSystem();
    void drawFunctions();

    std::vector<UserFunc *> functions;
    RenderWindow *window;
    View *view;
    double scale;
    Font textFont;
};

#endif // CARTESIANSYSTEM_H
