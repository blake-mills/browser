#include "Renderer.hpp"

Renderer::Renderer()
{

}

void Renderer::render(QPainter* painter, std::shared_ptr<HTMLElement>& element)
{
    element->render(painter);
    for (std::shared_ptr<HTMLElement>& child : element->getChildren())
    {
        this->render(painter, child);
    }
}
