#ifndef CONTAINER_H
#define CONTAINER_H

#include <fstream>
#include <iomanip>

class Container
{
public:
    Container(int storing, int max);
    Container(int max = 1);
    int take(int value);
    int put(int value);
    operator int() const;

    friend std::istream &operator>>(std::istream &str, Container& inC);
    friend std::ostream &operator<<(std::ostream &str, const Container& outC);

    bool isFull();
    bool isEmpty();

    int getSize() const;
    void setSize(int value);

    int getStore() const;

private:
    int size;
    int store;
};

#endif // CONTAINER_H
