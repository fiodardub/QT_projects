#ifndef TEST_EMPLOYEE_H
#define TEST_EMPLOYEE_H

#include <QObject>
#include <QTest>
#include "struct.h"

class TestEmployee : public QObject
{
    Q_OBJECT

private slots:
    void testInitialization();

    void testSalaryChange();
};

#endif // TEST_EMPLOYEE_H
