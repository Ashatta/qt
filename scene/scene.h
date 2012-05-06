#pragma once

#include <QtGui>

/// Alpha value of items on the Scene
int const alphaValue = 200;

/** Scene class is derived from QGraphicsScene.
 *  Holds pen, brush and type of item that is to be inserted
 */
class Scene : public QGraphicsScene
{
	Q_OBJECT
public:
	/** Modes:
	 *
	 *  Select - click on the Scene selects
	 *  	an item under mouse
	 *  Insert - click on the Scene inserts
	 *  	an item depending on itemType value
	 */
	enum SceneMode { Select, Insert };

	Scene(QObject* parent = 0)
			: QGraphicsScene(parent)
			, pen(QBrush(Qt::black), 2.5)
			, brush(QColor(255, 255, 255, alphaValue))
			, itemType("")
			, mode(Select)
	{}

	void setMode(SceneMode newMode)
	{
		mode = newMode;
	}

public slots:
	void setPenColor(QColor const &color)
	{
		pen.setColor(color);
	}
	void setBrushColor(QColor const &color)
	{
		QColor brushColor(color);
		brushColor.setAlpha(alphaValue);

		brush.setColor(brushColor);
	}
	/// Sets type of item that will be drawn in mousePressEvent handler
	void setItemType(QString const &type)
	{
		itemType = type;
	}

protected:
	/** Depending on current mode mousePressEvent either inserts an item
	 *  into position of event or selects an item under mouse
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
	/// In case of typing Delete removes all selected items
	void keyPressEvent(QKeyEvent* keyEvent);

	/** Inserts a new item to the scene into destination position.
	 *  The new item type is chosen in conformity with current itemType
	 */
	void drawItem(QPointF const &destination);

private:
	QPen pen;  ///< Pen to draw a new item
	QBrush brush;  ///< Brush to draw a new item

	QString itemType;  ///< Scene adds a new item 'decoding' this string

	SceneMode mode;
};

