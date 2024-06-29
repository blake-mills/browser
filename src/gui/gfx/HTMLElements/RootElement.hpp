#pragma once

#include "HTMLElement.hpp"

class RootElement : public HTMLElement
{
public:
    RootElement();
    void render(QPainter* e) override;
};