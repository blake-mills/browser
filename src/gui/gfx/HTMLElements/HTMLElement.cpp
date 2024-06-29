#include "HTMLElement.hpp"

HTMLElement::HTMLElement(Type type)
:   type( type )
{}

HTMLElement::Type HTMLElement::getType() const
{
    return type;
}

void HTMLElement::setType(HTMLElement::Type t)
{
    this->type = t;
}

void HTMLElement::addChild(std::shared_ptr<HTMLElement> e)
{
    children.push_back(e);
}

std::vector<std::shared_ptr<HTMLElement>> &HTMLElement::getChildren()
{
    return children;
}
