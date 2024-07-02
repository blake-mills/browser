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

std::shared_ptr<HTMLElement> Window::createElement(const json &elementJson, std::shared_ptr<HTMLElement> parent)
{
    std::shared_ptr<HTMLElement> element = nullptr;

    if (elementJson.contains("tag") && elementJson["type"] == "element")
    {
        std::string tag = elementJson["tag"];

        if (tag == "style")
        {
            std::string cssSource = elementJson["children"][0]["text"];
            Stylesheet::parse(cssSource);
        }

        if (tag == "html")
        {
            std::shared_ptr<RootElement> root = std::make_shared<RootElement>();
            auto window = this->centralWidget();

            root->addProperty("width", std::format("{}", (int)window->geometry().width()));
            root->addProperty("height", std::format("{}", (int)window->geometry().height()));
            element = root;
        }
        else if (tag == "body")
        {
            element = std::make_shared<BodyElement>(parent);
        }
        else if (tag == "div")
        {
            element = std::make_shared<DivElement>(parent);
        }

        if (elementJson.contains("children") && elementJson["children"].is_array())
        {
            for (const auto &childJson: elementJson["children"])
            {
                auto childElement = createElement(childJson, element);

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
        // std::cout << response->dump(4) << std::endl;
        buildDOM(*response);
    } else
    {
        // TODO: Show a default "cannot load webpage" page
        std::cerr << std::format("Cannot load this webpage: {}\n", url);
    }
}

void Window::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QSize newSize = event->size();

    // Since the DOM always has the top level root as
    // the parent, if I update the root I
    // can cascade resize events down to the children.
    if (dom != nullptr)
    {
        dom->addProperty("width", std::format("{}", (int) newSize.width()));
        dom->addProperty("height", std::format("{}", (int) newSize.height()));
    }
}

Window::~Window()
{
    // Qt automatically deletes child widgets
}