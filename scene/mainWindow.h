#pragma once

#include <QtGui>
#include "scene.h"
#include "colorAction.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	/** Constructor of class MainWindow creates actions, toolbars,
	 *  scene, sets graphics view of the scene and connects all
	 *  these objects
	 */
	MainWindow(QWidget* parent = 0);

protected:
	void createActions();
	/** Creates toolbars that are containing action for adding
	 *  new item to the scene and for changing color of item that
	 *  is to be added
	 */
	void createToolBars();
	/** Connects signals emitted by the actions to MainWindow's
	 *  and its Scene's slots
	 */
	void createConnections();

protected slots:
	/** Sets Scene to insert mode. action param is an action
	 *  for particular item that is to be inserted
	 */
	void itemChosen(QAction* action);
	/** Open ColorDialog window and connects its colorSelected signal
	 *  to colorAction's changeColor slot
	 */
	void openColorDialog(QAction* colorAction);

private:
	int const colorIconSide;  ///< Side of icon for ColorActions. Value is 20

	Scene* scene;
	QGraphicsView* view;

	QList<QAction*> itemsActions; ///< Actions to add a new item
	ColorAction* lineColorAction;
	ColorAction* fillColorAction;

	QToolBar* itemsToolBar;
	QToolBar* colorsToolBar;
};

