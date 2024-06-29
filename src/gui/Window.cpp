#include "./Window.hpp"

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    auto *centralWidget = new QWidget(this);

    auto *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    searchBar = new SearchBar(this);
    searchBar->setPlaceholderText("https://example.com");
    searchBar->setFixedHeight(30);
    connect(searchBar, &SearchBar::enterPressed, this, &Window::handleEnterPressed);

    contentArea = new ContentArea(this);
    contentArea->setStyleSheet("background-color: white;");
    contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(searchBar);
    layout->addWidget(contentArea);

    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);
}

std::shared_ptr<HTMLElement> Window::createElement(const json &elementJson)
{
    std::shared_ptr<HTMLElement> element = nullptr;

    if (elementJson.contains("tag") && elementJson["type"] == "element")
    {
        std::string tag = elementJson["tag"];

        if (tag == "html")
        {
            element = std::make_shared<RootElement>();
        }
        else if (tag == "body")
        {
            element = std::make_shared<BodyElement>();
        }
        else if (tag == "div")
        {
            element = std::make_shared<DivElement>();
        }

        if (elementJson.contains("children") && elementJson["children"].is_array())
        {
            for (const auto &childJson: elementJson["children"])
            {
                auto childElement = createElement(childJson);

                // We can get a nullptr in the event that we don't
                // yet support the type of node that we saw in the
                // HTML. Ignore until they are supported
                if (childElement != nullptr)
                {
                    element->addChild(childElement);
                }
            }
        }
    } else if (elementJson["type"] == "text")
    {
        // TODO: Handle text nodes
    }

    return element;
}

void Window::buildDOM(const json& html)
{
    if (html.is_array() && !html.empty())
    {
        dom = createElement(html[0]);
        auto renderClosure = [&](QPainter* painter)
        {
            renderer.render(painter, dom);
        };
        contentArea->setRenderFunction(renderClosure);
        contentArea->update();
    }
}

void Window::handleEnterPressed()
{
    std::string url = this->searchBar->toPlainText().toStdString();
    if (!url.starts_with("https://"))
    {
        url = "https://" + url;
    }

    auto response = Network::get(url);
    if (response.has_value())
    {
        // TODO: build the DOM and then trigger a render of the DOM
        std::cout << response->dump(4) << std::endl;
        buildDOM(*response);
    } else
    {
        // TODO: Show a default "cannot load webpage" page
        std::cerr << std::format("Cannot load this webpage: {}\n", url);
    }
}

Window::~Window()
{
    // Qt automatically deletes child widgets
}