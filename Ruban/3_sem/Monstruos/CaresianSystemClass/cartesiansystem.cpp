#include "cartesiansystem.h"

CartesianSystem::CartesianSystem(std::vector<UserFunc *> calcFunc) : scale(0.5f)
{
    textFont.loadFromFile("Symbola_hint.ttf");
    functions = calcFunc;
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
            int fromCenterToEdge = window->getSize().x / 2;

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
                    if((scale /= 2) < 0.05) {
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
                    buff.x += (int)(-50 * scale);
                    break;
                case Keyboard::Right:
                    buff.x += (int)(50 * scale);
                    break;
                case Keyboard::Up:
                    buff.y += (int)(-50 * scale);
                    break;
                case Keyboard::Down:
                    buff.y += (int)(50 * scale);
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }

            fromCenterToEdge *= scale;
            if(buff.x + fromCenterToEdge > 5000)
                buff.x = 5000 - fromCenterToEdge;
            if(buff.x - fromCenterToEdge < -5000)
                buff.x = -5000 + fromCenterToEdge;
            if(buff.y + fromCenterToEdge > 5000)
                buff.y = 5000 - fromCenterToEdge;
            if(buff.y - fromCenterToEdge < -5000)
                buff.y = -5000 + fromCenterToEdge;
            view->setCenter(buff);
        }

        window->setView(*view);
        window->clear(Color::White);
        drawCoordSystem();
        drawFunctions();
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

    Text text;
    text.setFont(textFont);
    text.setColor(Color::Black);
    text.setCharacterSize(14);

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
        if(i % 50 == 0) {

            std::stringstream intStr;
            intStr << (i / -10);
            text.setString(String(intStr.str()));
            text.setPosition(0, i);
            window->draw(text);

            intStr.str("");
            intStr << (i / 10);
            text.setString(String(intStr.str()));
            text.setPosition(i, 0);
            window->draw(text);

            if(i != 0) {
                RectangleShape yAxisNotch(Vector2f(6, 3));
                yAxisNotch.setPosition(-3, i - 2);
                yAxisNotch.setFillColor(axisColor);
                window->draw(yAxisNotch);

                RectangleShape xAxisNotch(Vector2f(3, 6));
                xAxisNotch.setPosition(i - 2, -3);
                xAxisNotch.setFillColor(axisColor);
                window->draw(xAxisNotch);
            }
        }
    }
}

void CartesianSystem::drawFunctions()
{
    for(int j = 0; j < functions.size(); ++j) {
        VertexArray fLine(Lines, 2);
        fLine[0].color = Color::Black;
        fLine[1].color = Color::Black;

        // f(i * 0.1) for right value and * -10 for right drawing and scaling
        fLine[1].position = Vector2f(-5000, functions[j]->func(-500) * -10);


        for(int i = -5000 + 1; i < 5000; i++) {
            fLine[0].position = fLine[1].position;
            fLine[1].position = Vector2f(i, functions[j]->func(i * 0.1) * -10);

            if(fLine[0].position.y < 500.0f || fLine[0].position.y > 500.0f)
                if(fLine[1].position.y < 500.0f || fLine[1].position.y > 500.0f)
                    window->draw(fLine);
        }
    }
}
