#include <QtGui/QApplication>
#include "analogclock.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    ClockHand sechand("sechand.png", 45.0, 16.0);
    ClockHand minhand("minhand.png", 11.0, 11.0);
    ClockHand hourhand("hourhand.png", 14.0, 14.0);

    AnalogClock clock(ClockPic("clock.png",
                sechand, minhand, hourhand));
                               
    clock.show();

    return a.exec();
}

