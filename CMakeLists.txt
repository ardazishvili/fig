cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(JSON_BuildTests OFF CACHE INTERNAL "")
project(Fig)

add_subdirectory(third/logging/spdlog)
add_subdirectory(third/json/json)

add_library(imgui)
target_sources(imgui
  PRIVATE
  third/gui/imgui/imgui.cpp
  third/gui/imgui/imgui.h
  third/gui/imgui/imgui_demo.cpp
  third/gui/imgui/imgui_draw.cpp
  third/gui/imgui/imgui_impl_glfw.cpp
  third/gui/imgui/imgui_impl_opengl3.cpp
  third/gui/imgui/imgui_internal.h
  third/gui/imgui/imgui_widgets.cpp
  third/gui/imgui/imstb_rectpack.h
  third/gui/imgui/imstb_truetype.h
  )

add_library(fig)
target_link_libraries(fig PRIVATE imgui spdlog::spdlog nlohmann_json::nlohmann_json GLEW)
target_sources(fig
  PRIVATE
  Layer.h
  Layers.h
  Layers.cpp
  Core.h
  Core.cpp
  Log.h
  Log.cpp
  LogBackend.h
  SpdBackend.h
  SpdBackend.cpp
  Application.h
  Application.cpp
  Window.h
  Window.cpp
  GlfwWindow.h
  GlfwWindow.cpp
  GuiBackend.h
  ImGuiBackend.h
  ImGuiBackend.cpp
  EventManager.h
  EventManager.cpp
  WindowBackground.h
  WindowBackground.cpp
  SkyboxBackground.h
  SkyboxBackground.cpp
  ColorBackground.h
  ColorBackground.cpp
  SpdBackend.h
  SpdBackend.cpp
  Timer.cpp
  Timer.h
  Animation.cpp
  Animation.h
  Camera.cpp
  Camera.h
  Light.cpp
  Light.h
  Model.cpp
  Model.h
  ModelLoader.cpp
  ModelLoader.h
  Terrain.cpp
  Terrain.h
  Texture.cpp
  Texture.h
  globals.cpp
  globals.h
  # Circle.cpp
  # Circle.h
  Beam.cpp
  Beam.h
  HeightsSegment.cpp
  HeightsSegment.h
  LinesObject.cpp
  LinesObject.h
  ObstaclesSegment.cpp
  ObstaclesSegment.h
  Path.cpp
  Path.h
  RectangleShape.cpp
  RectangleShape.h
  Skybox.cpp
  Skybox.h
  Sphere.cpp
  Sphere.h
  Surface.cpp
  Surface.h
  Vertex.cpp
  Vertex.h
  events/Event.h
  events/EventFabric.h
  math/AStar.cpp
  math/AStar.h
  math/Noise.cpp
  math/Noise.h
  misc/ImGuiLog.cpp
  misc/ImGuiLog.h
  misc/ImGuiLogger.cpp
  misc/ImGuiLogger.h
  shader/PhongShader.cpp
  shader/PhongShader.h
  shader/LinesShader.cpp
  shader/LinesShader.h
  shader/SkyboxShader.cpp
  shader/SkyboxShader.h
  shader/Shader.cpp
  shader/Shader.h
  # mesh/CircleMesh.cpp
  # mesh/CircleMesh.h
  mesh/ModelMesh.cpp
  mesh/ModelMesh.h
  mesh/MainTerrainMesh.cpp
  mesh/MainTerrainMesh.h
  mesh/Mesh.cpp
  mesh/Mesh.h
  mesh/TerrainMesh.cpp
  mesh/TerrainMesh.h
  mesh/TerrainMeshSegment.cpp
  mesh/TerrainMeshSegment.h
  mesh/SphereMesh.cpp
  mesh/SphereMesh.h
  mesh/PlainMesh.cpp
  mesh/PlainMesh.h
  mesh/SubTerrainMesh.cpp
  mesh/SubTerrainMesh.h
  )

