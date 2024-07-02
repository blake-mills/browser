#include "DivElement.hpp"

DivElement::DivElement(std::shared_ptr<HTMLElement> parent)
        : HTMLElement("div", std::make_optional(parent))
{}

void DivElement::render(QPainter *painter)
{
    int width = 0, height = 0;
    json margin = json::object();

    painter->setRenderHint(QPainter::Antialiasing);
    std::optional<json> style = Stylesheet::get(this->type);

    std::string pWidth = getOrDefault(parent->getProperties(), "width", "0");
    std::string pHeight = getOrDefault(parent->getProperties(), "height", "0");

    std::string defaultBgColor = "#FFFFFF";

    if (style.has_value())
    {
        json props = (*style)["properties"];
        addProperty("width", getOrDefault(props, "width", pWidth));
        addProperty("height", getOrDefault(props, "height", pHeight));

        std::string bgColor = getOrDefault(props, "background-color", defaultBgColor);
        painter->setBrush(QBrush(QColor(bgColor.c_str())));

        std::string wStr = (std::string) properties["width"];
        std::string hStr = (std::string) properties["height"];

        width = Stylesheet::asPx(wStr);

        // TODO: Compute the size of the children in height and then go from there
        height = Stylesheet::asPx(hStr);

        // Extract all the components and get the result as an std::vector<int>
        // so I can map them for margin.
        auto marginList = Stylesheet::forEach<int>(props, "margin", [this](const std::string &s, int index) -> int
        {
            if (s == "auto")
            {
                int pV, cV;
                json &childProps = this->getProperties();
                json &parentProps = this->parent->getProperties();

                switch (index)
                {
                    case 0:
                        return Stylesheet::computeAuto<int>(std::stoi((std::string) childProps["height"]),
                                                            std::stoi((std::string) parentProps["height"]));
                        break;
                    case 1:
                        return Stylesheet::computeAuto<int>(std::stoi((std::string) childProps["width"]),
                                                            std::stoi((std::string) parentProps["width"]));
                        break;
                    default:
                        throw std::runtime_error(std::format("Unexpected index {}", index));
                }
            }
            return Stylesheet::asPx(s);
        });

        // TODO: Implement others later
        if (marginList.size() == 2)
        {
            margin["top"] = marginList[0];
            margin["left"] = marginList[1];
        }

        painter->setPen(Qt::black);
    }

    QRect rect((int)margin["left"], (int)margin["top"], width, 250);
    painter->drawRect(rect);
}
