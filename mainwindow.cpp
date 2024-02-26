#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout *vLayout = new QVBoxLayout(ui->centralwidget);
    display = new QLineEdit();
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMinimumHeight(50);
    vLayout->addWidget(display);

    QGridLayout *gridLayout = new QGridLayout();
    vLayout->addLayout(gridLayout);

    QStringList buttons {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "C", "0", "=", "+"
    };

    int position = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            QPushButton *button = new QPushButton(buttons[position]);
            gridLayout->addWidget(button, i, j);
            connect(button, &QPushButton::clicked, this, &MainWindow::onPushButton);
            ++position;
        }
    }

    setFixedSize(300, 400);
}

void MainWindow::onPushButton() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString buttonText = button->text();

    if(buttonText == "C") {
        display->clear();
        firstNum = 0;
        isTypingSecondNumber = false;
    } else if(buttonText == "+" || buttonText == "-" || buttonText == "*" || buttonText == "/") {
        firstNum = display->text().toDouble();
        currentOperation = buttonText;
        isTypingSecondNumber = true;
    } else if(buttonText == "=") {
        double secondNum = display->text().toDouble();
        double result;

        if(currentOperation == "+") {
            result = firstNum + secondNum;
        } else if(currentOperation == "-") {
            result = firstNum - secondNum;
        } else if(currentOperation == "*") {
            result = firstNum * secondNum;
        } else if(currentOperation == "/") {
            if(secondNum == 0) {
                display->setText("Error");
                return;
            } else {
                result = firstNum / secondNum;
            }
        }

        display->setText(QString::number(result));
        isTypingSecondNumber = false;
    } else {
        if(isTypingSecondNumber) {
            display->clear();
            isTypingSecondNumber = false;
        }
        QString newValue = display->text() + buttonText;
        double doubleValue = newValue.toDouble();
        display->setText(QString::number(doubleValue, 'g', 15));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
