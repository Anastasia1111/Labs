#include "container.h"

Container::Container(int storing, int max)
{
    store = storing;
    size = max;
}

Container::Container(int max)
{
    store = size = max;
}

int Container::take(int value) // return how many taken
{
    if(value > store) {
        int buf = store;
        store = 0;
        return buf;
    } else {
        store -= value;
        return value;
    }
}

int Container::put(int value) // return overcontaining
{
    int sub = value + store - size;
    if(sub > 0) {
        store = size;
        return sub;
    } else {
        store += value;
        return 0;
    }
}

std::istream &operator>>(std::istream &str, Container &inC)
{
    char buf;
    str >> buf;
    if(buf != '[')
        return str;
    str >> inC.store >> buf;
    if(buf != '|')
        return str;
    str >> inC.size >> buf;
    return str;
}

bool Container::isFull()
{
    return store == size;
}

bool Container::isEmpty()
{
    return store == 0;
}

int Container::getSize() const
{
    return size;
}

void Container::setSize(int value)
{
    size = value;
    if(store > size)
        store = size;
}

int Container::getStore() const
{
    return store;
}

std::ostream &operator<<(std::ostream &str, const Container &outC)
{
    str << "[" << outC.store << "|" << outC.size << "]";
    return str;
}

Container::operator int() const
{
    return store;
}
