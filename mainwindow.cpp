#include "mainwindow.h"
#include <QHeaderView>
#include <QMessageBox>
#include <fstream>

void MainWindow::fillCompTable(QTableWidget *table, const COMP<Comp> &data) {
    table->setRowCount(0);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Наименование", "Секция", "Цена"});
    for (size_t i = 0; i < data.get_size(); ++i) {
        table->insertRow(i);
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(data[i].name)));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(data[i].section)));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(data[i].price, 'f', 2)));
    }
}

void MainWindow::fillBagTable(QTableWidget *table, const COMP<Bag> &data) {
    table->setRowCount(0);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Наименование", "Количество", "Секция"});
    for (size_t i = 0; i < data.get_size(); ++i) {
        table->insertRow(i);
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(data[i].name)));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(data[i].count)));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(data[i].section)));
    }
}

void MainWindow::onProcessClicked()
{
    std::string searchName = nameEdit->text().trimmed().toStdString();
    int choice = arrayComboBox->currentIndex() + 1;
    tableSearch->setRowCount(0);

    if (searchName.empty()) {
        QMessageBox::information(this, "Подсказка", "Введите имя товара для поиска или нажмите кнопку 'Показать весь массив'.");
        return;
    }

    switch (choice) {
    case 1: {
        COMP<Comp> res;
        for(size_t i = 0; i < cmp1.get_size(); ++i) {
            if(cmp1[i].name == searchName) res.push_back(cmp1[i]);
        }
        fillCompTable(tableSearch, res);
        break;
    }
    case 2: {
        COMP<Comp> res;
        for(size_t i = 0; i < cmp2.get_size(); ++i) {
            if(cmp2[i].name == searchName) res.push_back(cmp2[i]);
        }
        fillCompTable(tableSearch, res);
        break;
    }
    case 3: {
        COMP<Comp> res;
        for(size_t i = 0; i < cmp3.get_size(); ++i) {
            if(cmp3[i].name == searchName) res.push_back(cmp3[i]);
        }
        fillCompTable(tableSearch, res);
        break;
    }
    case 4: {
        COMP<Bag> res;
        for(size_t i = 0; i < bg1.get_size(); ++i) {
            if(bg1[i].name == searchName) res.push_back(bg1[i]);
        }
        fillBagTable(tableSearch, res);
        break;
    }
    case 5: {
        COMP<Bag> res;
        for(size_t i = 0; i < bg2.get_size(); ++i) {
            if(bg2[i].name == searchName) res.push_back(bg2[i]);
        }
        fillBagTable(tableSearch, res);
        break;
    }
    case 6: {
        COMP<Bag> res;
        for(size_t i = 0; i < bg3.get_size(); ++i) {
            if(bg3[i].name == searchName) res.push_back(bg3[i]);
        }
        fillBagTable(tableSearch, res);
        break;
    }
    }
}

void MainWindow::onShowAllClicked()
{
    int choice = arrayComboBox->currentIndex() + 1;
    tableSearch->setRowCount(0);

    switch (choice) {
    case 1: fillCompTable(tableSearch, cmp1); break;
    case 2: fillCompTable(tableSearch, cmp2); break;
    case 3: fillCompTable(tableSearch, cmp3); break;
    case 4: fillBagTable(tableSearch, bg1); break;
    case 5: fillBagTable(tableSearch, bg2); break;
    case 6: fillBagTable(tableSearch, bg3); break;
    }
}

void MainWindow::onShowSortClicked()
{
    int arrayChoice = sortArrayComboBox->currentIndex();
    int sortChoice = sortTypeComboBox->currentIndex();


    if (arrayChoice == 0) {
        if (sortChoice == 1) cmp1.ReverseSort();
        else cmp1.Sort();

        fillCompTable(tableAll, cmp1);
    }
    else if (arrayChoice == 1) {
        if (sortChoice == 1) cmp2.ReverseSort();
        else cmp2.Sort();

        fillCompTable(tableAll, cmp2);
    }
    else if (arrayChoice == 2) {
        if (sortChoice == 1) cmp3.ReverseSort();
        else cmp3.Sort();

        fillCompTable(tableAll, cmp3);
    }

    if (arrayChoice == 3) {
        if (sortChoice == 1) bg1.ReverseSort();
        else bg1.Sort();

        fillBagTable(tableAll, bg1);
    }
    else if (arrayChoice == 4) {
        if (sortChoice == 1) bg2.ReverseSort();
        else bg2.Sort();

        fillBagTable(tableAll, bg2);
    }
    else if (arrayChoice == 5) {
        if (sortChoice == 1) bg3.ReverseSort();
        else bg3.Sort();

        fillBagTable(tableAll, bg3);
    }

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    std::ifstream fin_cm_1("/Users/h/exammmmm/comp_1");
    std::ifstream fin_cm_2("/Users/h/exammmmm/comp_2");
    cmp1.ReadTextData(fin_cm_1); cmp2.ReadTextData(fin_cm_2);
    cmp3 = cmp1 + cmp2;
    std::ofstream fout_cmp("/Users/h/exammmmm/comp_3");
    cmp3.WriteTextData(fout_cmp);
    system("open /Users/h/exammmmm/comp_3");

    std::ifstream fin_bg_1("/Users/h/exammmmm/bag_1");
    std::ifstream fin_bg_2("/Users/h/exammmmm/bag_2");
    bg1.ReadTextData(fin_bg_1); bg2.ReadTextData(fin_bg_2);
    bg3 = bg1 + bg2;
    std::ofstream fout_bg("/Users/h/exammmmm/bag_3");
    bg3.WriteTextData(fout_bg);
    system("open /Users/h/exammmmm/bag_3");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QHBoxLayout *sortLayout = new QHBoxLayout();
    sortLayout->addWidget(new QLabel("Массив для вывода:"));

    sortArrayComboBox = new QComboBox(this);
    sortArrayComboBox->addItems({
        "1. Первый массив Comp",
        "2. Второй массив Comp",
        "3. Третий массив Comp (Объединенный)",
        "4. Первый массив Bag",
        "5. Второй массив Bag",
        "6. Третий массив Bag (Объединенный)"
    });
    sortLayout->addWidget(sortArrayComboBox);

    sortLayout->addWidget(new QLabel("Сортировка:"));
    sortTypeComboBox = new QComboBox(this);
    sortTypeComboBox->addItems({"Без сортировки (Прямая)", "Реверсивная сортировка"});
    sortLayout->addWidget(sortTypeComboBox);

    btnApplySort = new QPushButton("Показать и отсортировать", this);
    sortLayout->addWidget(btnApplySort);
    layout->addLayout(sortLayout);

    tableAll = new QTableWidget(this);
    tableAll->setColumnCount(3);
    tableAll->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(tableAll);

    layout->addLayout(sortLayout);

    QHBoxLayout *searchLayout = new QHBoxLayout();

    searchLayout->addWidget(new QLabel("Наименование:"));
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Введите имя товара...");
    searchLayout->addWidget(nameEdit);

    searchLayout->addWidget(new QLabel("Массив:"));
    arrayComboBox = new QComboBox(this);
    arrayComboBox->addItems({
        "1. Первый массив Comp", "2. Второй массив Comp", "3. Третий массив Comp",
        "4. Первый массив Bag", "5. Второй массив Bag", "6. Третий массив Bag"
    });
    searchLayout->addWidget(arrayComboBox);


    btnProcess = new QPushButton("Найти по имени", this);
    searchLayout->addWidget(btnProcess);

    btnShowAll = new QPushButton("Показать весь массив", this);
    searchLayout->addWidget(btnShowAll);

    layout->addLayout(searchLayout);

    layout->addWidget(new QLabel("<b>Результаты запроса:</b>"));
    tableSearch = new QTableWidget(this);
    tableSearch->setColumnCount(3);
    tableSearch->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(tableSearch);

    connect(btnProcess, &QPushButton::clicked, this, &MainWindow::onProcessClicked);
    connect(btnShowAll, &QPushButton::clicked, this, &MainWindow::onShowAllClicked);
    connect(btnApplySort, &QPushButton::clicked, this, &MainWindow::onShowSortClicked);

    fillCompTable(tableAll, cmp3);
    sortArrayComboBox->setCurrentIndex(2);
    resize(550, 650);
    setWindowTitle("Учет компьютерной техники и аксессуаров");
}
