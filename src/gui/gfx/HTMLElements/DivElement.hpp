#pragma once
#include "./HTMLElement.hpp"

class DivElement : public HTMLElement
{
public:
    DivElement();

protected:
    void render(QPainter* painter) override;
};

