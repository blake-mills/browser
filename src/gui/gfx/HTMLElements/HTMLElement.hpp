#pragma once

#include <QWidget>
#include <QPainter>

#include <vector>
#include <memory>
#include <iostream>

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
    enum Type
    {
        ROOT,
        DIV,
        BODY
    };

    explicit HTMLElement(Type type);
    Type getType() const;
    void setType(Type t);
    void addChild(std::shared_ptr<HTMLElement> e);
    std::vector<std::shared_ptr<HTMLElement>>& getChildren();

    virtual void render(QPainter* painter) = 0;

protected:
    std::vector<std::shared_ptr<HTMLElement>> children;

private:
    Type type;
};