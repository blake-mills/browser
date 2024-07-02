#include "BodyElement.hpp"

BodyElement::BodyElement(std::shared_ptr<HTMLElement> parent)
:   HTMLElement("body", parent)
{}

void BodyElement::render(QPainter *painter)
{
    int width, height;

    std::optional<json> style = Stylesheet::get(this->type);
    if (style.has_value())
    {
        json props = (*style)["properties"];
        if (props.contains("width")) { addProperty("width", props["width"]); }
        else if (parent->getProperties().contains("width")) { addProperty("width", parent->getProperties()["width"]); }
        else
        {
            std::cerr << "No width found for body" << std::endl;
        }


        if (props.contains("height")) { addProperty("height", props["height"]); }
        else if (parent->getProperties().contains("height")) { addProperty("height", parent->getProperties()["height"]); }
        else
        {
            std::cerr << "No height found for body" << std::endl;
        }

        if (props.contains("background-color"))
        {
            std::string bgColor = props["background-color"];
            painter->setBrush(QBrush(QColor(bgColor.c_str())));
        }

        std::string wStr = (std::string)properties["width"];
        std::string hStr = (std::string)properties["height"];

        if (wStr.ends_with("em"))
        {
            width = Stylesheet::emToPx(wStr);
        }
        else
        {
            width = std::stoi((std::string)properties["width"]);
        }

        if (hStr.ends_with("em"))
        {
            height = Stylesheet::emToPx(hStr);
        }
        else
        {
            height = std::stoi((std::string)properties["height"]);
        }

        QRect rect(0, 0, width, height);
        painter->drawRect(rect);
    }
}
