#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStringList>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleCalculate();
    void handleFunctionChange(int index);
    void openSettings();

private:
    void createMenu();
    void setupUI();
    void logOperation(const QString &message);


    QComboBox *funcComboBox;
    QTextEdit *resultTextEdit;
    QCheckBox *historyCheckBox;
    QPushButton *calcButton;


    QLineEdit *inputA;
    QLineEdit *inputB;
    QLineEdit *inputC;
    QLineEdit *inputD;
    QLineEdit *inputX;


    QLabel *lblA;
    QLabel *lblB;
    QLabel *lblC;
    QLabel *lblD;
    QLabel *lblX;


    bool m_logEnabled;
    QString m_logPath;
};

#endif
