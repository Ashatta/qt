#include "analogclock.h"
#include <QTimer>
#include <QTime>
#include <QPainter>

AnalogClock::AnalogClock(ClockPic const &image
		, QWidget* parent)
		: QWidget(parent)
		, mClock(image)
{
	resize(mClock.mFace.width(), mClock.mFace.height());

	QTimer* timer = new QTimer(this);
	connect(timer, SIGNAL(timeout())
			, this, SLOT(repaint()));
	timer->start(1000);    // Clock repaints every second
}

void AnalogClock::paintEvent(QPaintEvent *) 
{
	QPainter painter(this);
	painter.drawImage(0, 0, mClock.mFace);

	// Moving the center of the coordinate system to the center
	// of the clock face and rotating it so x axis is turned 
	// to twelve and the y axis is turned to three
	painter.translate(QPointF(mClock.mFace.width() / 2
			, mClock.mFace.height() / 2));
	painter.rotate(-90.0);

	QTime const time = QTime::currentTime();

	// Painting the hour hand
	painter.save();
	painter.rotate(30.0 * (time.hour() + time.minute() / 60.0));
	painter.drawImage(mClock.mHourHand.place(), mClock.mHourHand);
	painter.restore();

	// Painting the minute hand
	painter.save();
	painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
	painter.drawImage(mClock.mMinHand.place(), mClock.mMinHand);
	painter.restore();

	// Painting the second hand
	painter.rotate(6.0 * time.second());
	painter.drawImage(mClock.mSecHand.place(), mClock.mSecHand);
}
