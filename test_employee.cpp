
#include "test_employee.h"

void TestEmployee::testInitialization()
{
    Employee emp("Иван Иванов", "Разработчик", 150000.0);

    QCOMPARE(emp.get_name(), QString("Иван Иванов"));
    QCOMPARE(emp.get_position(), QString("Разработчик"));
    QCOMPARE(emp.get_salary(), 150000.0);
}

void TestEmployee::testSalaryChange()
{
    Employee emp("Пётр Петров", "Тестировщик", 80000.0);

    QVERIFY(emp.setSalary(95000.0) == true);
    QCOMPARE(emp.get_salary(), 95000.0);


    QVERIFY(emp.setSalary(-5000.0) == false);
    QCOMPARE(emp.get_salary(), 95000.0);
}
