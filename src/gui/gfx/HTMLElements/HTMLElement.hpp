#pragma once

#include <QWidget>
#include <QPainter>

#include <vector>
#include <memory>
#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * This is the base abstract class for all HTMLElements
 * that will be rendered with this HTML rendering engine.
 *
 * It defines the paintEvent pure virtual function so that
 * I can enforce that all child objects will render something.
 */
class HTMLElement
{
public:
    explicit HTMLElement(const std::string& type, std::optional<std::shared_ptr<HTMLElement>> parent = std::nullopt);
    std::string getType() const;
    void setType(std::string t);
    void addChild(std::shared_ptr<HTMLElement> e);

    void addProperty(std::string key, std::string value);
    json& getProperties() { return properties; }

    json::value_type getOrDefault(json& map, std::string key, json::value_type defaultValue)
    {
        if (map.contains(key))
        {
            return map[key];
        }
        return defaultValue;
    }

    std::vector<std::shared_ptr<HTMLElement>>& getChildren();
    virtual void render(QPainter* painter) = 0;

protected:
    std::shared_ptr<HTMLElement> parent;
    std::vector<std::shared_ptr<HTMLElement>> children;
    std::string type;
    json properties = json::object();
};