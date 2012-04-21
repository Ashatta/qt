#pragma once
#include <QWidget>
#include <QPointF>

/** ClockHand is an image of clock hand that knows its
 *  rotation center and coordinates of the point there
 *  it should be places. Coordinates of rotation center
 *  is given to constructor by user
 */
class ClockHand : public QImage
{
public:
    ClockHand(const QString &picFile, qreal x, qreal y)
        : QImage(picFile)
        , rotationCenter(x, y) 
        , placementPoint(-x, -y)
    {}

    QPointF rCenter() { return rotationCenter; }
    QPointF place() { return placementPoint; }

protected:
    QPointF rotationCenter;
    QPointF placementPoint;
};

/** ClockPic struct contains an image of clock face and
 *  three clock hands
 */
struct ClockPic
{
    QImage face;

    ClockHand sechand;
    ClockHand minhand;
    ClockHand hourhand;

    ClockPic(const QString &faceFile, const ClockHand &shand,
             const ClockHand &mhand, const ClockHand &hhand)
        : face(faceFile)
        , sechand(shand)
        , minhand(mhand)
        , hourhand(hhand)
    {}
};

/** AnalogClock class as a widget that represents a simple
 *  clock with three hands and repaints itself every second
 *  synchronizing with system clock
 */
class AnalogClock : public QWidget
{
    Q_OBJECT
public:
    AnalogClock(const ClockPic &image, QWidget* parent = 0);
protected:
    ClockPic clock; ///< Image of the clock and of the three hands of it

    /** paintEvent is called every second and repaints all
     *  components of the clock
     */ 
    void paintEvent(QPaintEvent *);
};
