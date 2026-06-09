#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "comp.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QTableWidget *tableAll;
    QTableWidget *tableSearch;
    QLineEdit *nameEdit;

    QComboBox *sortArrayComboBox;
    QComboBox *sortTypeComboBox;
    QPushButton *btnApplySort;

    QComboBox *arrayComboBox;
    QPushButton *btnProcess;
    QPushButton *btnShowAll;

    COMP<Comp> cmp1;
    COMP<Comp> cmp2;
    COMP<Comp> cmp3;

    COMP<Bag> bg1;
    COMP<Bag> bg2;
    COMP<Bag> bg3;

    void fillCompTable(QTableWidget *table, const COMP<Comp> &data);
    void fillBagTable(QTableWidget *table, const COMP<Bag> &data);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onProcessClicked();
    void onShowAllClicked();
    void onShowSortClicked();
};
