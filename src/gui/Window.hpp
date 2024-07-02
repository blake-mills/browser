#pragma once

#include <QMainWindow>
#include <QVBoxLayout>

#include <format>

#include "../networking/Network.hpp"
#include "./components/SearchBar.hpp"
#include "gfx/HTMLElements/HTMLElement.hpp"
#include "gfx/HTMLElements/RootElement.hpp"
#include "gfx/HTMLElements/BodyElement.hpp"
#include "gfx/HTMLElements/DivElement.hpp"
#include "gfx/Renderer.hpp"
#include "components/ContentArea.hpp"


#ifdef slots
#undef slots
#endif

#include "stylesheet/Stylesheet.hpp"

#ifndef slots
#define slots Q_SLOTS
#endif

class Window
        : public QMainWindow
{
Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);

    ~Window() override;

private slots:

    void handleEnterPressed();

private:
    void buildDOM(const json &html);

    std::shared_ptr<HTMLElement> createElement(const json &elementJson, std::shared_ptr<HTMLElement> parent = nullptr);
    std::shared_ptr<HTMLElement> dom;

protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    SearchBar *searchBar;
    ContentArea *contentArea;
    Renderer renderer;
};