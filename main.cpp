#include "anvor.cpp"
#include <QApplication>

int main(int argc,char *argv[])

{

    QApplication a(argc, argv);
    Calculator calc;
    calc.setWindowTitle("Calculator");
    calc.resize(400, 400);
    calc.show();

    return a.exec();


}
