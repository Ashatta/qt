#pragma once

#include <QAction>
#include <QSize>
#include <QColor>
#include <QIcon>
#include <QPixmap>

/** Class ColorAction is a QAction with convenient slots and
 *  signals for handling color changes. Appears as a square icon
 *  of a current color
 */
class ColorAction : public QAction
{
	Q_OBJECT
public:
	/** Constructor of ColorAction with given side of action's icon,
	 *  color of icon and action's text
	 */
	ColorAction(int const iconSide, QColor const &picColor
			, QString const &text, QObject* parent = 0);

public slots:
	/** Changes the color of ColorAction's pixmap to color.
	*  Emits colorChanged signal.
	*/
	void changeColor(QColor const &color);

signals:
	/// Is emitted whenever the color of ColorAction's pixmap gets changed
	void colorChanged(QColor const &color);

protected:
	/// Draws black frame around the pixmap
	void drawFrame();

private:
	int iconSize;
	QPixmap pixmap; ///< Square of color color with side equal iconSize
	QColor color; ///< Color of action's icon
};
