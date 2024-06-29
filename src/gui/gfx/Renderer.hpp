#pragma once

#include <QWidget>

#include <memory>
#include <iostream>


#include "./HTMLElements/HTMLElement.hpp"

class Renderer
{
public:
    Renderer();
    void render(QPainter* painter, std::shared_ptr<HTMLElement>& element);
};
