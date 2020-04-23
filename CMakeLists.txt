cmake_minimum_required(VERSION 3.13)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
project(Fig)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(third/logging/spdlog)

add_library(fig)
target_link_libraries(fig PRIVATE spdlog::spdlog)
target_sources(fig
  PUBLIC
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
  events/Event.h
  events/EventFabric.h
  math/AStar.cpp
  math/AStar.h
  math/Noise.cpp
  math/Noise.h
  SpdBackend.h
  SpdBackend.cpp
  misc/ImGuiLog.cpp
  misc/ImGuiLog.h
  misc/ImGuiLogger.cpp
  misc/ImGuiLogger.h
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
  ModelMesh.cpp
  ModelMesh.h
  PhongShader.cpp
  PhongShader.h
  Shader.cpp
  Shader.h
  Terrain.cpp
  Terrain.h
  Texture.cpp
  Texture.h
  globals.cpp
  globals.h
  # Circle.cpp
  # Circle.h
  # CircleMesh.cpp
  # CircleMesh.h
  Beam.cpp
  Beam.h
  HeightsSegment.cpp
  HeightsSegment.h
  LinesObject.cpp
  LinesObject.h
  LinesShader.cpp
  LinesShader.h
  MainTerrainMesh.cpp
  MainTerrainMesh.h
  Mesh.cpp
  Mesh.h
  ObstaclesSegment.cpp
  ObstaclesSegment.h
  Path.cpp
  Path.h
  PlainMesh.cpp
  PlainMesh.h
  RectangleShape.cpp
  RectangleShape.h
  Skybox.cpp
  Skybox.h
  SkyboxShader.cpp
  SkyboxShader.h
  Sphere.cpp
  Sphere.h
  SphereMesh.cpp
  SphereMesh.h
  SubTerrainMesh.cpp
  SubTerrainMesh.h
  Surface.cpp
  Surface.h
  TerrainMesh.cpp
  TerrainMesh.h
  TerrainMeshSegment.cpp
  TerrainMeshSegment.h
  Vertex.cpp
  Vertex.h
  imgui/imgui.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_impl_glfw.cpp
  imgui/imgui_impl_opengl3.cpp
  imgui/imgui_internal.h
  imgui/imgui_widgets.cpp
  imgui/imstb_rectpack.h
  imgui/imstb_truetype.h
  )

add_executable(editor
  editor/editor.cpp
  editor/EditorApplication.h
  editor/EditorApplication.cpp
  editor/globals.h
  editor/globals.cpp
  editor/WorldLayer.h
  editor/WorldLayer.cpp
  editor/EditorEventManager.h
  editor/EditorEventManager.cpp
  editor/EditorEventFabric.h
  editor/EditorEventFabric.cpp
  editor/EditorKeyReleaseEvent.h
  editor/EditorKeyReleaseEvent.cpp
  editor/EditorGuiLayer.h
  editor/EditorGuiLayer.cpp
  editor/mainwindow.h
  editor/mainwindow.cpp
  editor/myglwidget.h
  editor/myglwidget.cpp
  )
target_include_directories(editor PRIVATE editor)
target_link_libraries(editor PRIVATE spdlog::spdlog fig glfw dl GL GLEW assimp pthread Qt5::Widgets)
