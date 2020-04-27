#include "../Application.h"
#include "../SpdBackend.h"
#include <QApplication>

using namespace fig;

Application<SpdBackend>* appInit(std::unique_ptr<QApplication> app);
Application<SpdBackend>* gApp();
