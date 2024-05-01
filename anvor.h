#ifndef ANVOR_H
#define ANVOR_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QJSEngine>
#include <QEvent>
#include <QIcon>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <cmath>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = 0);

public slots:
    void buttonClicked();

private:
    int calculate(const QString &expression);
    QLineEdit *lineEdit;
    QString buttonText;
   // QMediaPlayer *player;
    bool justCalculated = false;

};
#endif // ANVOR_H
