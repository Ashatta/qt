#include "scene.h"

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
		return;

	if (mode == Insert)
	{
		drawItem(mouseEvent->scenePos());
		foreach (QGraphicsItem* item, selectedItems())
			item->setSelected(false);
		return;
	}

	QGraphicsScene::mousePressEvent(mouseEvent);
}

void Scene::keyPressEvent(QKeyEvent* keyEvent)
{
	if (keyEvent->key() == Qt::Key_Delete)
		foreach (QGraphicsItem* item, selectedItems())
			removeItem(item);
}

void Scene::drawItem(QPointF const &destination)
{
	if (itemType == "QGraphicsRectItem")
	{
		QGraphicsRectItem* rect = addRect(QRectF(destination.x(), destination.y(), 100, 70)
				, pen, brush);
		rect->setFlag(QGraphicsItem::ItemIsMovable, true);
		rect->setFlag(QGraphicsItem::ItemIsSelectable, true);
	}

	else if (itemType == "QGraphicsEllipseItem")
	{
		QGraphicsEllipseItem* ellipse = addEllipse(QRectF(destination.x(), destination.y(), 100, 70)
				, pen, brush);
		ellipse->setFlag(QGraphicsItem::ItemIsMovable, true);
		ellipse->setFlag(QGraphicsItem::ItemIsSelectable, true);
	}
}

