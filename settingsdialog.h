#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);

    bool isLoggingEnabled() const;
    QString getLogFilePath() const;

    void setLoggingEnabled(bool enabled);
    void setLogFilePath(const QString &path);

private:
    QCheckBox *logCheckBox;
    QLineEdit *pathLineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif
