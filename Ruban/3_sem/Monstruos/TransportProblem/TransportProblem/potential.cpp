#include "potential.h"

Potential::Potential() : value(0), set(false)
{

}

int Potential::getValue() const
{
    return value;
}

void Potential::setValue(int v)
{
    value = v;
    set = true;
}

bool Potential::defined() const
{
    return set;
}

void Potential::setSet(bool value)
{
    set = value;
}

std::ostream &operator<<(std::ostream &str, const Potential &out)
{
    if(out.set) {
        str << std::setw(9) << out.value;
    } else {
        str << "        -";
    }
    return str;
}
