#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPushButton();

private:
    Ui::MainWindow *ui;
    QLineEdit *display;
    QString currentOperation;
    double firstNum = 0;
    bool isTypingSecondNumber = false;

    void calculate();
};
#endif // MAINWINDOW_H
