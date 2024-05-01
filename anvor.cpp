#include "anvor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QIntValidator>

Calculator::Calculator(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout();

    lineEdit = new QLineEdit(this);
    lineEdit->setValidator(new QIntValidator(this));

    vbox->addWidget(lineEdit);

    QStringList buttons = (QStringList() << "1" << "2" << "3" << "+" << "4" << "5" << "6" << "-" << "7" << "8" << "9" << "*" << "C" << "0" << "=" << "/");

    for (int i = 0; i < buttons.size(); i++) {
        QPushButton *button = new QPushButton(buttons[i], this);
        connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
        hbox->addWidget(button);

        if ((i + 1) % 4 == 0) {
            vbox->addLayout(hbox);
            hbox = new QHBoxLayout();
        }
    }

    QString styleSheet = "\
        QWidget { \
            background-color: #f0f0f0; \
    } \
        QPushButton { \
            background-color: #ffffff; \
            font-family: Courier New, sans-serif; \
            font-size: 30px; \
            font-weight: bold; \
            color: #333333; \
            border: 1px solid #cccccc; \
            margin: 0; \
            padding: 10px; \
            min-width: 80px; \
            min-height: 80px; \
    } \
        QPushButton:hover { \
            background-color: #eaeaea; \
    } \
        QPushButton:pressed { \
            background-color: #d9d9d9; \
    } \
        QLineEdit { \
            background-color: #ffffff; \
            color: #333333; \
            font-family: Courier New, sans-serif; \
            font-size: 20px; \
            font-weight: bold; \
            border: 1px solid #cccccc; \
            margin: 0; \
            padding: 10px; \
            min-height: 80px; \
    } \
        QPushButton[text='='] { \
            background-color: #b19cd9; \
            color: #ffffff; \
            border: 1px solid #9278b3; \
    } \
        QPushButton[text='C'] { \
            background-color: #ff867d; \
            color: #ffffff; \
            border: 1px solid #cc4b38; \
    } \
        QPushButton:not([text='=']):not([text='C']) { \
            font-weight: normal; /* Делаем цифры менее жирными */ \
    }";

        this->setStyleSheet(styleSheet);

    setWindowIcon(QIcon("C:\\Users\\asus\\Downloads\\IconCalc"));

}

void Calculator::buttonClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString buttonText = button->text();

    if (buttonText == "=") {
        try {
            int result = calculate(lineEdit->text());
            lineEdit->setText(QString::number(result));
            justCalculated = true;
        } catch (const std::runtime_error& e) {
            QMessageBox::warning(this, "Ошибка", e.what());
        }

    } else if (buttonText == "C") {
        lineEdit->clear();
    } else {
        if (justCalculated) {
            lineEdit->clear();
            justCalculated = false;
        }
        lineEdit->setText(lineEdit->text() + buttonText);
    }
}

int Calculator::calculate(const QString &expression) {
    QJSEngine engine;
    QJSValue result = engine.evaluate(expression);
    if (result.isNumber()) {
        double number = result.toNumber();


        if (std::isnan(number)) {
            throw std::runtime_error("Результат выражения не является числом (NaN)");
        }


        if (std::isinf(number)) {
            throw std::runtime_error("Результат выражения является бесконечностью (Infinity)");
        }


        return static_cast<int>(number);
    } else {
        throw std::runtime_error("Ошибка вычисления выражения");
    }
}
