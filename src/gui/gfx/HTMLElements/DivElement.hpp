#pragma once

#include <QColor>

#include "./HTMLElement.hpp"
#include "../../stylesheet/Stylesheet.hpp"

class DivElement : public HTMLElement
{
public:
    // The div will always have a parent in some form
    DivElement(std::shared_ptr<HTMLElement> parent);

protected:
    void render(QPainter* painter) override;
};

