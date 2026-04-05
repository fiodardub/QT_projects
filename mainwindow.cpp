#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Построитель тригонометрических графиков");

    plotter = new PlotWidget(this);

    minXEdit = new QLineEdit("-6.28", this);
    maxXEdit = new QLineEdit("6.28", this);
    minYEdit = new QLineEdit("-2.0", this);
    maxYEdit = new QLineEdit("2.0", this);

    funcCombo = new QComboBox(this);
    funcCombo->addItems({"Sin(x)", "Cos(x)", "Tan(x)"});

    styleCombo = new QComboBox(this);
    styleCombo->addItems({"Сплошная", "Пунктир", "Точки"});

    lineColorCombo = new QComboBox(this);
    lineColorCombo->addItems({"Синий", "Красный", "Зеленый"});

    bgColorCombo = new QComboBox(this);
    bgColorCombo->addItems({"Белый", "Светло-серый", "Черный"});

    fontSizeCombo = new QComboBox(this);
    fontSizeCombo->addItems({"10", "12", "14", "16"});

    //fontColorCombo = new QComboBox(this);
    //fontColorCombo->addItems({"Синий", "Красный", "Зеленый"});

    thicknessSlider = new QSlider(Qt::Horizontal, this);
    thicknessSlider->setRange(1, 5);
    thicknessSlider->setValue(2);

    applyButton = new QPushButton("Построить график", this);

    logTable = new QTableWidget(0, 2, this);
    logTable->setHorizontalHeaderLabels({"Действие", "Параметры"});

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Функция:", funcCombo);
    formLayout->addRow("Мин X:", minXEdit);
    formLayout->addRow("Макс X:", maxXEdit);
    formLayout->addRow("Мин Y:", minYEdit);
    formLayout->addRow("Макс Y:", maxYEdit);
    formLayout->addRow("Цвет линии:", lineColorCombo);
    formLayout->addRow("Стиль линии:", styleCombo);
    formLayout->addRow("Цвет поля:", bgColorCombo);
    formLayout->addRow("Размер шрифта:", fontSizeCombo);
    //formLayout->addRow("Цвет шрифта:", fontColorCombo);
    formLayout->addRow("Толщина линии:", thicknessSlider);

    QVBoxLayout *leftPanel = new QVBoxLayout();
    leftPanel->addLayout(formLayout);
    leftPanel->addWidget(applyButton);
    leftPanel->addWidget(new QLabel("Лог событий (Таблица):"));
    leftPanel->addWidget(logTable);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addLayout(leftPanel, 1);
    mainLayout->addWidget(plotter, 2);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(applyButton, &QPushButton::clicked, this, &MainWindow::applyRanges);
    connect(funcCombo, &QComboBox::currentTextChanged, plotter, &PlotWidget::setFunction);

    connect(styleCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateLineSettings);
    connect(lineColorCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateLineSettings);
    connect(bgColorCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateLineSettings);
    connect(thicknessSlider, &QSlider::valueChanged, this, &MainWindow::updateLineSettings);
    connect(fontSizeCombo, &QComboBox::currentTextChanged, this, &MainWindow::updateFontSettings);
    //connect(fontColorCombo, &QComboBox::currentTextChanged, this, &MainWindow::updateFontColor);

    connect(plotter, &PlotWidget::pointClicked, this, [this](const QString &info) {
        int row = logTable->rowCount();
        logTable->insertRow(row);
        logTable->setItem(row, 0, new QTableWidgetItem("Клик мыши"));
        logTable->setItem(row, 1, new QTableWidgetItem(info));
    });
}

void MainWindow::applyRanges() {
    double minX = minXEdit->text().toDouble();
    double maxX = maxXEdit->text().toDouble();
    double minY = minYEdit->text().toDouble();
    double maxY = maxYEdit->text().toDouble();

    plotter->setXRange(minX, maxX);
    plotter->setYRange(minY, maxY);

    int row = logTable->rowCount();
    logTable->insertRow(row);
    logTable->setItem(row, 0, new QTableWidgetItem("Обновление диапазона"));
    logTable->setItem(row, 1, new QTableWidgetItem(QString("X:[%1;%2]").arg(minX).arg(maxX)));
}

void MainWindow::updateLineSettings() {
    if (styleCombo->currentIndex() == 0) plotter->setLineStyle(Qt::SolidLine);
    else if (styleCombo->currentIndex() == 1) plotter->setLineStyle(Qt::DashLine);
    else plotter->setLineStyle(Qt::DotLine);

    if (lineColorCombo->currentIndex() == 0) plotter->setLineColor(Qt::blue);
    else if (lineColorCombo->currentIndex() == 1) plotter->setLineColor(Qt::red);
    else plotter->setLineColor(Qt::darkGreen);

    if (bgColorCombo->currentIndex() == 0) plotter->setBgColor(Qt::white);
    else if (bgColorCombo->currentIndex() == 1) plotter->setBgColor(QColor(240, 240, 240));
    else plotter->setBgColor(Qt::black);

    plotter->setLineThickness(thicknessSlider->value());
}

void MainWindow::updateFontSettings() {
    int size = fontSizeCombo->currentText().toInt();
    plotter->setPlotFont(QFont("Arial", size));
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        applyRanges();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}
