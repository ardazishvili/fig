#ifndef GLOBALS_H
#define GLOBALS_H

#include "Config.h"
#include "ModelLoader.h"
#include "misc/ImGuiLogger.h"

namespace fig
{
extern std::unique_ptr<ModelLoader> modelLoader;
extern ImGuiLogger logger;
extern std::string assets_dir;
}
extern Config CONFIG;

#endif
