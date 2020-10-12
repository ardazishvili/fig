#ifndef GLOBALS_H
#define GLOBALS_H

#include "ModelLoader.h"
#include "misc/ImGuiLogger.h"

namespace fig
{
extern std::unique_ptr<ModelLoader> modelLoader;
extern ImGuiLogger logger;
extern bool flatView;
extern std::string assets_dir;
}

#endif
