#include "colorAction.h"
#include <QPainter>

ColorAction::ColorAction(int const iconSide, QColor const &picColor
		, QString const &text, QObject* parent)
	: QAction(text, parent)
	, iconSize(iconSide)
	, pixmap(iconSize, iconSize)
	, color(picColor)
{
	changeColor(color);
}

void ColorAction::changeColor(QColor const &color)
{
	pixmap.fill(color);
	drawFrame();

	setIcon(QIcon(pixmap));
	emit colorChanged(color);
}

void ColorAction::drawFrame()
{
	QPainter painter(&pixmap);
	painter.drawLine(0, 0, 0, iconSize - 1);
	painter.drawLine(0, iconSize - 1, iconSize - 1, iconSize - 1);
	painter.drawLine(0, 0, iconSize - 1, 0);
	painter.drawLine(iconSize - 1, 0, iconSize - 1, iconSize - 1);
}

