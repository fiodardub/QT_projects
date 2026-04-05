#include "plotwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMenu>
#include <cmath>
#include <QPainterPath>

PlotWidget::PlotWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(400, 300);
}

void PlotWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect plotRect(40, 20, width() - 60, height() - 50);
    painter.fillRect(plotRect, bgColor);

    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
    painter.drawRect(plotRect);

    if (maxX <= minX || maxY <= minY) return;

    auto toScreenX = [&](double x) {
        return plotRect.left() + (x - minX) / (maxX - minX) * plotRect.width();
    };
    auto toScreenY = [&](double y) {
        return plotRect.bottom() - (y - minY) / (maxY - minY) * plotRect.height();
    };

    painter.setPen(QPen(Qt::gray, 1, Qt::DashLine));
    if (minX <= 0 && maxX >= 0) {
        int zeroX = toScreenX(0);
        painter.drawLine(zeroX, plotRect.top(), zeroX, plotRect.bottom());
    }
    if (minY <= 0 && maxY >= 0) {
        int zeroY = toScreenY(0);
        painter.drawLine(plotRect.left(), zeroY, plotRect.right(), zeroY);
    }

    painter.setPen(Qt::red);
    painter.setFont(axisFont);
    painter.drawText(plotRect.left() - 35, plotRect.top() + 10, QString::number(maxY, 'g', 3));
    painter.drawText(plotRect.left() - 35, plotRect.bottom() - 5, QString::number(minY, 'g', 3));
    painter.drawText(plotRect.left(), plotRect.bottom() + 15, QString::number(minX, 'g', 3));
    painter.drawText(plotRect.right() - 30, plotRect.bottom() + 15, QString::number(maxX, 'g', 3));

    painter.setPen(QPen(lineColor, lineThickness, lineStyle));

    QPainterPath path;
    bool first = true;
    int steps = plotRect.width();

    for (int i = 0; i <= steps; ++i) {
        double screenX = plotRect.left() + i;
        double x = minX + (i / static_cast<double>(steps)) * (maxX - minX);
        double y = 0;

        if (currentFunc == "Sin(x)") y = std::sin(x);
        else if (currentFunc == "Cos(x)") y = std::cos(x);
        else if (currentFunc == "Tan(x)") {
            y = std::tan(x);
            if (std::abs(y) > 50.0) { first = true; continue; }
        }

        if (y >= minY && y <= maxY) {
            double screenY = toScreenY(y);
            if (first) {
                path.moveTo(screenX, screenY);
                first = false;
            } else {
                path.lineTo(screenX, screenY);
            }
        } else {
            first = true;
        }
    }
    painter.drawPath(path);
}

void PlotWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        QMenu menu(this);
        QAction *resetBg = menu.addAction("Сбросить фон на белый");
        connect(resetBg, &QAction::triggered, this, [this]() { setBgColor(Qt::white); });
        menu.exec(event->globalPosition().toPoint());
    } else if (event->button() == Qt::LeftButton) {
        emit pointClicked(QString("Клик в точке: X=%1 Y=%2").arg(event->x()).arg(event->y()));
    }
}
