#include "analogclock.h"
#include <QTimer>
#include <QTime>
#include <QPainter>

AnalogClock::AnalogClock(const ClockPic &image, 
                         QWidget* parent)
        : QWidget(parent)
        , clock(image)
{
    resize(clock.face.width(), clock.face.height());

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), 
            this, SLOT(repaint()));
    timer->start(1000); // Clock repaints every second
}

void AnalogClock::paintEvent(QPaintEvent *) 
{
    QPainter painter(this);
    painter.drawImage(0, 0, clock.face);

    /** Moving the center of the coordinate system to the center
     *  of the clock face and rotating it so x axis is turned 
     *  to twelve and the y axis is turned to three
     */
    painter.translate(QPointF(clock.face.width() / 2, 
                              clock.face.height() / 2));
    painter.rotate(-90.0);

    QTime time = QTime::currentTime();

    // Painting the hour hand
    painter.save();
    painter.rotate(30.0 * (time.hour() + time.minute() / 60.0));
    painter.drawImage(clock.hourhand.place(), clock.hourhand);
    painter.restore();

    // Painting the minute hand
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawImage(clock.minhand.place(), clock.minhand);
    painter.restore();

    // Painting the second hand
    painter.rotate(6.0 * time.second());
    painter.drawImage(clock.sechand.place(), clock.sechand);
}
