#include"total.h"

GameStart::GameStart(QDialog* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

void GameStart::on_okButton_clicked()
{
    ok = true;
}

void GameStart::on_cancelButton_clicked()
{
    ok = false;
}