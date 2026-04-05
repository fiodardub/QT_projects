#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QString>
#include <QColor>
#include <QFont>

class PlotWidget : public QWidget {
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = nullptr);

    void setFunction(const QString &func) { currentFunc = func; update(); }
    void setXRange(double min, double max) { minX = min; maxX = max; update(); }
    void setYRange(double min, double max) { minY = min; maxY = max; update(); }

    void setBgColor(const QColor &color) { bgColor = color; update(); }
    void setLineColor(const QColor &color) { lineColor = color; update(); }
    void setLineStyle(Qt::PenStyle style) { lineStyle = style; update(); }
    void setLineThickness(int thickness) { lineThickness = thickness; update(); }
    void setPlotFont(const QFont &font) { axisFont = font; update(); }

    QString getCurrentFunction() const { return currentFunc; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void pointClicked(const QString &info);

private:
    QString currentFunc = "Sin(x)";
    double minX = -6.28, maxX = 6.28;
    double minY = -2.0, maxY = 2.0;

    QColor bgColor = Qt::white;
    QColor lineColor = Qt::blue;
    Qt::PenStyle lineStyle = Qt::SolidLine;
    int lineThickness = 2;
    QFont axisFont = QFont("Arial", 10);
};

#endif
