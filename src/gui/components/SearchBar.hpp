#pragma once
#include <QTextEdit>
#include <QKeyEvent>

class SearchBar : public QTextEdit
{
    Q_OBJECT

public:
    explicit SearchBar(QWidget* parent = nullptr);

signals:
    void enterPressed();

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

