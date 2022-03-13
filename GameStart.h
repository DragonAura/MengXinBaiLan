#pragma once
#include<QDialog>
#include "ui_GameStart.h"
class GameStart :public QDialog
{
	Q_OBJECT
public:
	GameStart(QDialog* parent = Q_NULLPTR);
	Ui_Dialog ui;

	bool ok;

public slots:
	void on_okButton_clicked();
	void on_cancelButton_clicked();
};