#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <QSlider>
#include "plotwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void applyRanges();
    void updateLineSettings();
    void updateFontSettings();
    //void updateFontColor();

private:
    PlotWidget *plotter;

    QLineEdit *minXEdit;
    QLineEdit *maxXEdit;
    QLineEdit *minYEdit;
    QLineEdit *maxYEdit;

    QComboBox *funcCombo;
    QComboBox *styleCombo;
    QComboBox *bgColorCombo;
    QComboBox *lineColorCombo;
    QComboBox *fontSizeCombo;
    //QComboBox *fontColorCombo;

    QSlider *thicknessSlider;
    QTableWidget *logTable;
    QPushButton *applyButton;
};

#endif
