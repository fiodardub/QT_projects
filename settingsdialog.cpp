#include "settingsdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setModal(true);
    setWindowTitle("Настройки логирования");

    logCheckBox = new QCheckBox("Включить запись истории в файл log.txt", this);
    pathLineEdit = new QLineEdit(this);

    QLabel *pathLabel = new QLabel("Путь к файлу лога:", this);

    okButton = new QPushButton("Сохранить", this);
    cancelButton = new QPushButton("Отмена", this);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(logCheckBox);
    mainLayout->addWidget(pathLabel);
    mainLayout->addWidget(pathLineEdit);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(okButton);
    btnLayout->addWidget(cancelButton);
    mainLayout->addLayout(btnLayout);

    connect(logCheckBox, &QCheckBox::toggled, pathLineEdit, &QLineEdit::setEnabled);
}

bool SettingsDialog::isLoggingEnabled() const { return logCheckBox->isChecked(); }
QString SettingsDialog::getLogFilePath() const { return pathLineEdit->text(); }
void SettingsDialog::setLoggingEnabled(bool enabled) { logCheckBox->setChecked(enabled); }
void SettingsDialog::setLogFilePath(const QString &path) { pathLineEdit->setText(path); }
