#ifndef POTENTIAL_H
#define POTENTIAL_H

#include <fstream>
#include <iomanip>

class Potential
{
public:
    Potential();
    int getValue() const;
    void setValue(int v);

    bool defined() const;
    void setSet(bool value);

    friend std::ostream &operator<<(std::ostream &str, const Potential &out);

private:
    int value;
    bool set;
};

#endif // POTENTIAL_H
