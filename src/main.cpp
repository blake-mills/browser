#include <QApplication>
#include "./gui/Window.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Window win(nullptr);
    win.resize(800, 600);
    win.show();

    return app.exec();
}