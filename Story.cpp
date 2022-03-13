#include"total.h"

Story::Story(QDialog* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

void Story::AddStory(QString text)
{
    ui.textEdit->append(text);
}