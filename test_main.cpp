#include <QtTest/QtTest>
#include "plotwidget.h"

class PlotTests : public QObject {
    Q_OBJECT
private slots:
    void testDefaultFunction() {
        PlotWidget plotter;
        QCOMPARE(plotter.getCurrentFunction(), QString("Sin(x)"));
    }

    void testFunctionChange() {
        PlotWidget plotter;
        plotter.setFunction("Cos(x)");
        QCOMPARE(plotter.getCurrentFunction(), QString("Cos(x)"));
    }
};

QTEST_MAIN(PlotTests)
#include "test_main.moc"
