#pragma once

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using JsonControls = std::map<std::string, std::string>;

struct CoreConfig {
  int window_width;
  int window_height;
  int panel_width;
  int panel_icon_size;
  int settings_icon_size;
  bool show_log;
  double moveSpeed;
  double rotationSpeed;
  std::vector<std::pair<int, int>> screenSizes;
  JsonControls controls;
};

class Config {
 public:
  Config(const std::string& path) : _path(path) { read(); }

  void read() {
    std::fstream config(_path, std::ios::in | std::ios::out);
    config >> _json;

    std::vector<std::string> screenSizesStrs = _json["screen_sizes"];
    std::vector<std::pair<int, int>> screenSizes;
    for (auto& screenSizeStr : screenSizesStrs) {
      auto w = std::stoi(screenSizeStr.substr(0, screenSizeStr.find('x')));
      auto h = std::stoi(screenSizeStr.substr(screenSizeStr.find('x') + 1));
      screenSizes.push_back({w, h});
    }

    std::map<std::string, std::string> controlsStrs = _json["controls"];
    JsonControls jsonControls;
    for (auto [name, key] : controlsStrs) {
      jsonControls[name] = key;
    }

    _coreConfig = {.window_width = _json["window_width"],
                   .window_height = _json["window_height"],
                   .panel_width = _json["panel_width"],
                   .panel_icon_size = _json["panel_icon_size"],
                   .settings_icon_size = _json["settings_icon_size"],
                   .show_log = _json["show_log"],
                   .moveSpeed = _json["move_speed"],
                   .rotationSpeed = _json["rotation_speed"],
                   .screenSizes = screenSizes,
                   .controls = jsonControls};
  }

  std::string print() { return _json.dump(4); }

  CoreConfig get() { return _coreConfig; }

  void write(const std::string& field, int value) {
    std::fstream config(_path, std::ios::in | std::ios::out);
    std::filesystem::resize_file(_path, 0);
    config.seekp(0);
    _json[field] = value;
    config << _json.dump(4);
  }

  void write(const std::string& field, JsonControls controls) {
    std::fstream config(_path, std::ios::in | std::ios::out);
    std::filesystem::resize_file(_path, 0);
    config.seekp(0);
    _json[field] = controls;
    config << _json.dump(4);
  }

 private:
  std::filesystem::path _path;
  json _json;
  CoreConfig _coreConfig;
};
