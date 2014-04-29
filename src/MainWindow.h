//-----------------------------------------------------------------------------
//Copyright (c) 2014 Peter Lama
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "MeshManager.h"

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

	//SceneGraphBuilder m_builder;
	MeshManager m_meshManager;
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