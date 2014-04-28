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

#include <iostream>

#include <QAction>
#include <QDir>
#include <QFileDialog>
#include <QIcon>
#include <QMenuBar>
#include <QMenu>
#include <QSize>
#include <QStatusBar>
#include <QStyle>
#include <QToolBar>

#include "View3d.h"
#include "MainWindow.h"

MainWindow::MainWindow()
{
	QGLFormat format;
	format.setVersion(3, 3);
	format.setProfile(QGLFormat::CompatibilityProfile);

    m_view3d = new View3d(format);

    setCentralWidget(m_view3d);
	
	setupActions();
	setupMenus();
    setupToolBars();

	setStatusBar(new QStatusBar);
}

QSize MainWindow::sizeHint() const
{
	return QSize(700, 700);
}

void MainWindow::fileOpen()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::home().absolutePath(), tr("*.obj"));
	if (!filename.isNull()) {
		statusBar()->showMessage(tr("Loading..."));

		m_view3d->importObjMesh(filename.toLatin1());
		m_view3d->update();

		statusBar()->showMessage(tr("Done"), 2000);
	}
}

void MainWindow::viewZoomIn()
{
	m_view3d->viewNav()->zoom(-1.0f);
	m_view3d->update();
}

void MainWindow::viewZoomOut()
{
	m_view3d->viewNav()->zoom(1.0f);
	m_view3d->update();
}

void MainWindow::setupActions()
{
	m_fileOpenAction = new QAction(QIcon(":/icons/Document-open.svg"), tr("&Open"), this);
	m_viewZoomInAction = new QAction(QIcon(":/icons/View-zoom-in.svg"), tr("Zoom In"), this);
	m_viewZoomOutAction = new QAction(QIcon(":/icons/View-zoom-out.svg"), tr("Zoom Out"), this);

	connect(m_fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpen()));
	connect(m_viewZoomInAction, SIGNAL(triggered()), this, SLOT(viewZoomIn()));
	connect(m_viewZoomOutAction, SIGNAL(triggered()), this, SLOT(viewZoomOut()));
}

void MainWindow::setupToolBars()
{
	m_fileToolBar = addToolBar(tr("File"));
	m_viewToolBar = addToolBar(tr("View"));

	m_fileToolBar->addAction(m_fileOpenAction);
	m_viewToolBar->addAction(m_viewZoomInAction);
	m_viewToolBar->addAction(m_viewZoomOutAction);
}

void MainWindow::setupMenus()
{
	m_fileMenu = menuBar()->addMenu(tr("&File"));
	m_viewMenu = menuBar()->addMenu(tr("&View"));

	m_fileMenu->addAction(m_fileOpenAction);
	m_viewMenu->addAction(m_viewZoomInAction);
	m_viewMenu->addAction(m_viewZoomOutAction);
}