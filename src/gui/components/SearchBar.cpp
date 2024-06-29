#include "SearchBar.hpp"

SearchBar::SearchBar(QWidget *parent)
:   QTextEdit( parent )
{}

void SearchBar::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        // Consumes the enter press as we need
        emit enterPressed();
    }
    else
    {
        // All other key presses are processed with the default handler
        QTextEdit::keyPressEvent(event);
    }
}