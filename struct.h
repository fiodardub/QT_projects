#pragma once
#include <QString>

struct Employee {
    QString name;
    QString position;
    qint16 salary;
    QString iconPath;

    bool operator<(const Employee& other) const {
        return this->salary < other.salary;

    }

    Employee(){name =""; position =""; salary = 0 ;}

    Employee(const QString &m_name, const QString &m_position, double m_salary, const QString &m_iconPath = "")
        : name(m_name), position(m_position), salary(m_salary), iconPath(m_iconPath) {}

    QString get_name() const { return name; }
    QString get_position() const { return position; }
    double get_salary() const { return salary; }

    bool setSalary(double newSalary) {
        if (newSalary < 0) return false;
        salary = newSalary;
        return true;
    }
};
