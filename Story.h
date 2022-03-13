#pragma once
#include<QDialog>
#include"ui_Story.h"

class Story :public QDialog
{
	Q_OBJECT
public:
	Story(QDialog* parent = Q_NULLPTR);
	Ui_Story ui;
	void AddStory(QString text);
};