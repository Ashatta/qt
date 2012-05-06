#include "mainWindow.h"

MainWindow::MainWindow(QWidget* parent)
		: QMainWindow(parent)
		, colorIconSide(20)
		, scene(new Scene)
		, itemsToolBar(new QToolBar)
		, colorsToolBar(new QToolBar)
{
	createActions();
	createToolBars();
	createConnections();

	scene->setSceneRect(0, 0, 1000, 1000);

	view = new QGraphicsView(scene);
	view->centerOn(0, 0);
	view->setRenderHints(QPainter::Antialiasing);

	setCentralWidget(view);
}

void MainWindow::createActions()
{
	/* Every action that represents some item gets whatsThis description
	 * which will be given to the Scene as type of current item  
	 * so when creating a new item action make sure that the Scene 
	 * can recognise it by adding corresponding branch to the Scene's 
	 * drawItem() function
	 */
	QAction* rectAction = new QAction("Rect", this);
	rectAction->setWhatsThis("QGraphicsRectItem");

	QAction* ellipseAction = new QAction("Ellipse", this);
	ellipseAction->setWhatsThis("QGraphicsEllipseItem");

	itemsActions << rectAction << ellipseAction;

	foreach (QAction* actions, itemsActions)
		actions->setCheckable(true);

	lineColorAction = new ColorAction(colorIconSide, Qt::black
			, "Line color", this);
	fillColorAction = new ColorAction(colorIconSide, Qt::white
			, "Fill color", this);
}

void MainWindow::createToolBars()
{
	itemsToolBar->addActions(itemsActions);
	itemsToolBar->setFloatable(false);

	
	colorsToolBar->addAction(lineColorAction);
	colorsToolBar->addWidget(new QLabel("Line color"));

	colorsToolBar->addAction(fillColorAction);
	QLabel* fillColor = new QLabel("Fill color");
	fillColor->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	colorsToolBar->addWidget(fillColor);

	colorsToolBar->setFloatable(false);

	addToolBar(Qt::LeftToolBarArea, colorsToolBar);
	insertToolBar(colorsToolBar, itemsToolBar);
}

void MainWindow::createConnections()
{
	// When item is chosen in the itemsToolBar the Scene
	// will know about this from the MainWindow in itemChosen slot
	connect(itemsToolBar, SIGNAL(actionTriggered(QAction*))
			, this, SLOT(itemChosen(QAction*)));

	// Actions for chosing lines and fill colors are connected
	// to corresponding Scene's slots
	connect(lineColorAction, SIGNAL(colorChanged(QColor const&))
			, scene, SLOT(setPenColor(QColor const&)));
	connect(fillColorAction, SIGNAL(colorChanged(QColor const&))
			, scene, SLOT(setBrushColor(QColor const&)));

	// QColorDialog that is opened by openColorDialog slot changes
	// a color of color action given to it as a parameter
	connect(colorsToolBar, SIGNAL(actionTriggered(QAction*))
			, this, SLOT(openColorDialog(QAction*)));
}

void MainWindow::itemChosen(QAction* action)
{
	if (action->isChecked())
	{
		foreach (QAction* act, itemsActions)
			if (act != action)
				act->setChecked(false);

		scene->setItemType(action->whatsThis());
		scene->setMode(Scene::Insert);
	}
	else
	{
		scene->setItemType("");
		scene->setMode(Scene::Select);
	}
}

void MainWindow::openColorDialog(QAction* colorAction)
{
	QColorDialog colorChoice;
	// Chosen color will be given to colorAction and then - to
	// the Scene as colorAction's signal is connected to its slot
	connect(&colorChoice, SIGNAL(colorSelected(QColor const&))
			, colorAction, SLOT(changeColor(QColor const&)));

	colorChoice.exec();
}
