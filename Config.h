#ifndef CONFIG_H
#define CONFIG_H
#include <cstdio>
#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

struct CoreConfig
{
  int window_width;
  int window_height;
  int panel_width;
  int icon_size;
  bool show_log;
  double moveSpeed;
  double rotationSpeed;
};

class Config
{
public:
  Config(const std::string& path) : _path(path)
  {
    std::fstream config(path, std::ios::in | std::ios::out);
    config >> _json;
    _coreConfig = { .window_width = _json["window_width"],
                    .window_height = _json["window_height"],
                    .panel_width = _json["panel_width"],
                    .icon_size = _json["icon_size"],
                    .show_log = _json["show_log"],
                    .moveSpeed = _json["move_speed"],
                    .rotationSpeed = _json["rotation_speed"] };
    /* std::filesystem::resize_file(config_name, 0); */
    /* config.seekp(0); */
    /* j["window_height"] = 1923; */
    /* config << j.dump(4); */
  }

  std::string print()
  {
    return _json.dump(4);
  }

  CoreConfig get()
  {
    return _coreConfig;
  }

private:
  std::filesystem::path _path;
  json _json;
  CoreConfig _coreConfig;
};

#endif
