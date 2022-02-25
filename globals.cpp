#include "globals.h"

#include <filesystem>
#include <string>

namespace fig {
std::unique_ptr<ModelLoader> modelLoader;
ImGuiLogger logger;
std::string assets_dir = std::filesystem::current_path().string() + "/assets";
}  // namespace fig
