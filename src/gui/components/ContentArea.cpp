#include "ContentArea.hpp"

ContentArea::ContentArea(QWidget *parent)
:   QWidget(parent)
{
    renderFunction = [](QPainter*){}; // Default function does nothing
}

void ContentArea::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    this->renderFunction(&painter);
}

void ContentArea::setRenderFunction(std::function<void(QPainter*)> renderFunc)
{
    this->renderFunction = renderFunc;
}
