#include <filesystem>
#include <string>

#include "globals.h"

namespace fig
{
std::unique_ptr<ModelLoader> modelLoader;
ImGuiLogger logger;
std::string assets_dir = std::filesystem::current_path().string() + "/assets";
}
