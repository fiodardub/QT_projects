#include "mainwindow.h"
#include "settingsdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_logEnabled(true), m_logPath("log.txt")
{
    setupUI();
    createMenu();
    handleFunctionChange(0);
}
    MainWindow::~MainWindow() {}

void MainWindow::createMenu()
{

    QMenu *fileMenu = menuBar()->addMenu("Файл");

    QAction *settingsAction = new QAction("Настройки лога...", this);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::openSettings);
    fileMenu->addAction(settingsAction);

    fileMenu->addSeparator();

    QAction *exitAction = new QAction("Выход", this);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);


    funcComboBox = new QComboBox(this);
    QStringList functions = { "y = ax + c", "y = ax^2 + bx + c", "y = ax^3 + bx^2 + cx + d" };
    funcComboBox->addItems(functions);
    mainLayout->addWidget(new QLabel("Выберите функцию для вычисления:", this));
    mainLayout->addWidget(funcComboBox);


    QHBoxLayout *inputsLayout = new QHBoxLayout();

    lblA = new QLabel("a:", this); inputA = new QLineEdit("0", this);
    lblB = new QLabel("b:", this); inputB = new QLineEdit("0", this);
    lblC = new QLabel("c:", this); inputC = new QLineEdit("0", this);
    lblD = new QLabel("d:", this); inputD = new QLineEdit("0", this);
    lblX = new QLabel("x:", this); inputX = new QLineEdit("0", this);

    inputsLayout->addWidget(lblA); inputsLayout->addWidget(inputA);
    inputsLayout->addWidget(lblB); inputsLayout->addWidget(inputB);
    inputsLayout->addWidget(lblC); inputsLayout->addWidget(inputC);
    inputsLayout->addWidget(lblD); inputsLayout->addWidget(inputD);
    inputsLayout->addWidget(lblX); inputsLayout->addWidget(inputX);
    mainLayout->addLayout(inputsLayout);


    historyCheckBox = new QCheckBox("Дублировать вывод в окно истории ниже", this);
    historyCheckBox->setChecked(true);
    mainLayout->addWidget(historyCheckBox);

    calcButton = new QPushButton("Вычислить", this);
    mainLayout->addWidget(calcButton);

    resultTextEdit = new QTextEdit(this);
    resultTextEdit->setReadOnly(true);
    mainLayout->addWidget(new QLabel("История вычислений / Результаты:", this));
    mainLayout->addWidget(resultTextEdit);


    connect(calcButton, &QPushButton::clicked, this, &MainWindow::handleCalculate);
    connect(funcComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handleFunctionChange);
}

void MainWindow::handleFunctionChange(int index)
{

    inputB->setEnabled(index >= 1); lblB->setEnabled(index >= 1);
    inputC->setEnabled(true);       lblC->setEnabled(true);
    inputD->setEnabled(index == 2); lblD->setEnabled(index == 2);
}

void MainWindow::openSettings()
{

    SettingsDialog dialog(this);
    dialog.setLoggingEnabled(m_logEnabled);
    dialog.setLogFilePath(m_logPath);

    if (dialog.exec() == QDialog::Accepted) {
        m_logEnabled = dialog.isLoggingEnabled();
        m_logPath = dialog.getLogFilePath();
    }
}

void MainWindow::handleCalculate()
{
    bool okA, okB = true, okC, okD = true, okX;

    qint64 a = inputA->text().toLongLong(&okA);
    qint64 b = 0;
    qint64 c = inputC->text().toLongLong(&okC);
    qint64 d = 0;
    qint64 x = inputX->text().toLongLong(&okX);

    int funcType = funcComboBox->currentIndex();

    if (funcType >= 1) b = inputB->text().toLongLong(&okB);
    if (funcType == 2) d = inputD->text().toLongLong(&okD);

    if (!okA || !okB || !okC || !okD || !okX) {
        QMessageBox::critical(this, "Ошибка ввода", "Сообщение о недопустимости ввода данных! Найдено нечисловое значение или переполнение qint64.");
        return;
    }

    qint64 result = 0;
    QString formulaStr;

    if (funcType == 0) {
        // y = ax + c
        result = a * x + c;
        formulaStr = QString("y = %1 * %2 + %3").arg(a).arg(x).arg(c);
    } else if (funcType == 1) {
        // y = ax^2 + bx + c
        result = a * x * x + b * x + c;
        formulaStr = QString("y = %1 * %2^2 + %3 * %2 + %4").arg(a).arg(x).arg(b).arg(c);
    } else if (funcType == 2) {
        // y = ax^3 + bx^2 + cx + d
        result = a * x * x * x + b * x * x + c * x + d;
        formulaStr = QString("y = %1 * %2^3 + %3 * %2^2 + %4 * %2 + %5").arg(a).arg(x).arg(b).arg(c).arg(d);
    }

    QString summary = QString("[%1] Формула: %2 | Результат y = %3")
                          .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
                          .arg(formulaStr)
                          .arg(result);

    if (historyCheckBox->isChecked()) {
        resultTextEdit->append(summary);
    }

    if (m_logEnabled) {
        logOperation(summary);
    }

    QMessageBox::information(this, "Результат вычислений", QString("Вычислено значение y = %1").arg(result));
}

void MainWindow::logOperation(const QString &message)
{
    QFile file(m_logPath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << message << "\n";
        file.close();
    } else {
        QMessageBox::warning(this, "Ошибка файла", "Не удалось записать лог в файл: " + m_logPath);
    }
}
