#pragma once

#include "HTMLElement.hpp"

class BodyElement : public HTMLElement
{
public:
    BodyElement();
    void render(QPainter* e) override;
};