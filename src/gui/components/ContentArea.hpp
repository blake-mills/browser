#pragma once
#include <QWidget>
#include <functional>
#include "../gfx/HTMLElements/HTMLElement.hpp"

class ContentArea : public QWidget
{
public:
    ContentArea(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* event);
    void setRenderFunction(std::function<void(QPainter*)> renderFunc);

private:
    std::function<void(QPainter*)> renderFunction;
};


