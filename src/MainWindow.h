#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class View3d;

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
	QSize sizeHint() const;

public slots:
    void fileOpen();
    void viewZoomIn();
	void viewZoomOut();

private:
	void setupActions();
	void setupMenus();
    void setupToolBars();

    View3d* m_view3d;
    
	QAction* m_fileOpenAction;
	QAction* m_viewZoomInAction;
	QAction* m_viewZoomOutAction;

	QMenu* m_fileMenu;
	QMenu* m_viewMenu;

    QToolBar* m_fileToolBar;
    QToolBar* m_viewToolBar;

	

};

#endif // MAIN_WINDOW_H