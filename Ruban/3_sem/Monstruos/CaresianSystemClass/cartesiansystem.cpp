#include "cartesiansystem.h"

CartesianSystem::CartesianSystem(double (*calcFunction)(double)) : calcFunc(calcFunction), scale(0.5f)
{
    window = new RenderWindow(VideoMode(500, 500), "CarteSystem");
    view = new View(Vector2f(0, 0), Vector2f(500, 500));
    view->zoom(scale);
    window->setView(*view);
}

void CartesianSystem::run()
{
    while(window->isOpen()) {
        Event event;
        while(window->pollEvent(event)) {
            Vector2f buff = view->getCenter();
            switch(event.type) {
            case Event::Closed:
                window->close();
                break;
            case Event::Resized:
                view->setSize(event.size.width, event.size.height);
                view->zoom(0.5f);
                break;
            case Event::MouseWheelScrolled:
                if(event.mouseWheelScroll.delta > 0) {
                    if((scale /= 2) < 0.01) {
                        scale *= 2;
                    } else {
                        view->zoom(0.5f);
                    }
                } else {
                    if((scale *= 2) > 3.0) {
                        scale /= 2;
                    } else {
                        view->zoom(2.0f);
                    }
                }
                break;
            case Event::KeyPressed:
                switch (event.key.code) {
                case Keyboard::Left:
                    buff.x += -50;
                    if((buff.x - window->getSize().x / 2) < -5000)
                        buff.x -= -50;
                    break;
                case Keyboard::Right:
                    buff.x += 50;
                    if((buff.x + window->getSize().x / 2) > 5000)
                        buff.x -= 50;
                    break;
                case Keyboard::Up:
                    buff.y += -50;
                    if((buff.y - window->getSize().y / 2) < -5000)
                        buff.y -= -50;
                    break;
                case Keyboard::Down:
                    buff.y += 50;
                    if((buff.y + window->getSize().y / 2) > 5000)
                        buff.x -= 50;
                    break;
                default:
                    break;
                }
                view->setCenter(buff);
                break;
            default:
                break;
            }
        }
        window->setView(*view);
        window->clear(Color::White);
        drawCoordSystem();
        drawFunction();
        window->display();
    }
}


void CartesianSystem::drawCoordSystem()
{
    Color axisColor(200, 200, 200);
    RectangleShape xAxis(Vector2f(10000, 2));
    xAxis.setPosition(-5000, -1);
    xAxis.setFillColor(axisColor);
    window->draw(xAxis);

    RectangleShape yAxis(Vector2f(2, 10000));
    yAxis.setPosition(-1, -5000);
    yAxis.setFillColor(axisColor);
    window->draw(yAxis);

    VertexArray xLine(Lines, 2);
    VertexArray yLine(Lines, 2);
    xLine[0].color = axisColor;
    xLine[1].color = axisColor;
    yLine[0].color = axisColor;
    yLine[1].color = axisColor;

    for(int i = -5000; i <= 5000; i+= 10) {
        xLine[0].position = Vector2f(-5000, i);
        xLine[1].position = Vector2f(5000, i);
        yLine[0].position = Vector2f(i, -5000);
        yLine[1].position = Vector2f(i, 5000);
        window->draw(xLine);
        window->draw(yLine);
    }
}

void CartesianSystem::drawFunction()
{
    VertexArray fLine(Lines, 2);
    fLine[0].color = Color::Black;
    fLine[1].color = Color::Black;
    fLine[0].position = Vector2f(-5001, calcFunc(-500.1) * -10); // calcFunc(i * 0.1) for right value and * -10 for right drawing and scaling
    fLine[1].position = Vector2f(-5000, calcFunc(-500) * -10);


    for(int i = -5000 + 1; i < 5000; i++) {
        fLine[0].position = fLine[1].position;
        fLine[1].position = Vector2f(i, calcFunc(i * 0.1) * -10);
        if(fLine[1].position.y < 500.0f || fLine[1].position.y > 500.0f)
            window->draw(fLine);
    }
}
