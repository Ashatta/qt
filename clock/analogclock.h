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
	ClockHand(QString const &picFile, qreal const x, qreal const y)
			: QImage(picFile)
			, mRotationCenter(x, y)
			, mPlacementPoint(-x, -y)
	{}

	QPointF rCenter() const { return mRotationCenter; }
	QPointF place() const { return mPlacementPoint; }

protected:
	QPointF mRotationCenter;
	QPointF mPlacementPoint;
};

/** ClockPic struct contains an image of clock face and
 *  three clock hands
 */
struct ClockPic
{
	QImage mFace;

	ClockHand mSecHand;
	ClockHand mMinHand;
	ClockHand mHourHand;

	ClockPic(QString const &faceFile, ClockHand const &shand
			, ClockHand const &mhand, ClockHand const &hhand)
			: mFace(faceFile)
			, mSecHand(shand)
			, mMinHand(mhand)
			, mHourHand(hhand)
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
	AnalogClock(ClockPic const &image, QWidget* parent = 0);

protected:
	/** paintEvent is called every second and repaints all
	 *  components of the clock
	 */
	void paintEvent(QPaintEvent *);

	ClockPic mClock;  ///< Image of the clock and of the three hands of it
};
