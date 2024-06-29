#include "DivElement.hpp"

DivElement::DivElement()
:   HTMLElement(HTMLElement::Type::DIV)
{}

void DivElement::render(QPainter* painter)
{
    // Enable antialiasing for smoother drawing
    painter->setRenderHint(QPainter::Antialiasing);

    // Set the brush and pen if needed
    painter->setBrush(Qt::blue);
    painter->setPen(Qt::black);

    // Define the rectangle's position and size
    QRect rect(50, 50, 200, 100); // x, y, width, height

    // Draw the rectangle
    painter->drawRect(rect);
}
