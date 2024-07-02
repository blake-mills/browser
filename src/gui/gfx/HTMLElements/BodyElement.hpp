#pragma once

#include "../../stylesheet/Stylesheet.hpp"
#include "HTMLElement.hpp"

class BodyElement : public HTMLElement
{
public:
    BodyElement(std::shared_ptr<HTMLElement> parent);
    void render(QPainter* painter) override;
};