#include <QApplication>

#include "View3d.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	QGLFormat format;
	format.setVersion(4, 2);
	format.setProfile(QGLFormat::CompatibilityProfile);

	View3d view(format);

    view.show();
    
    return app.exec();
}