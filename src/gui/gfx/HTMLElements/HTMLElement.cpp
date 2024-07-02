#include "HTMLElement.hpp"

HTMLElement::HTMLElement(const std::string& type, std::optional<std::shared_ptr<HTMLElement>> parent)
:   type( type )
{
    if (parent.has_value())
    {
        this->parent = *parent;
    }
    else
    {
        this->parent = nullptr;
    }
}

void HTMLElement::addProperty(std::string key, std::string value)
{
    properties[key] = value;
}

std::string HTMLElement::getType() const
{
    return type;
}

void HTMLElement::setType(std::string t)
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
