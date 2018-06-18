#include "ApplicationFunctions.hpp"
#include "windowshandler.hpp"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    if (!SetupApplication()) app.exit(1);

    WindowsHandler wh;

    return app.exec();
}
