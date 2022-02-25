#pragma once

#include "Config.h"
#include "ModelLoader.h"
#include "misc/ImGuiLogger.h"

namespace fig {
extern std::unique_ptr<ModelLoader> modelLoader;
extern ImGuiLogger logger;
extern std::string assets_dir;
}  // namespace fig
extern Config CONFIG;
