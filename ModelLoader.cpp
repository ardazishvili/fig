#include "ModelLoader.h"
#include <filesystem>

namespace fig
{
ModelLoader::ModelLoader(Shader& shader) : _shader(shader)
{
}

void ModelLoader::load()
{
  auto assets = std::filesystem::current_path().string() + "/assets";

  auto shellModel = std::make_unique<Model>(_shader);
  shellModel->load(assets + "/shell.dae");
  _models.emplace(Models::Shell, std::move(shellModel));

  auto tankModel = std::make_unique<Model>(_shader);
  tankModel->load(assets + "/tank.dae");
  tankModel->loadTexture(assets + "/blue.png", TexturePackType::OnSelection);
  tankModel->loadTexture(assets + "/red.png", TexturePackType::UnderFire);
  tankModel->loadTexture(assets + "/black.png", TexturePackType::Destroyed);
  _models.emplace(Models::Tank, std::move(tankModel));

  auto tankFactoryModel = std::make_unique<Model>(_shader);
  tankFactoryModel->load(assets + "/garage.dae");
  tankFactoryModel->loadTexture(assets + "/grey.png",
                                TexturePackType::PreBuild);
  tankFactoryModel->loadTexture(assets + "/blue.png",
                                TexturePackType::OnSelection);
  tankFactoryModel->loadTexture(assets + "/red.png",
                                TexturePackType::UnderFire);
  tankFactoryModel->loadTexture(assets + "/black.png",
                                TexturePackType::Destroyed);
  _models.emplace(Models::TankFactory, std::move(tankFactoryModel));

  auto hqModel = std::make_unique<Model>(_shader);
  hqModel->load(assets + "/hq.dae");
  hqModel->loadTexture(assets + "/grey.png", TexturePackType::PreBuild);
  hqModel->loadTexture(assets + "/blue.png", TexturePackType::OnSelection);
  hqModel->loadTexture(assets + "/red.png", TexturePackType::UnderFire);
  hqModel->loadTexture(assets + "/black.png", TexturePackType::Destroyed);
  _models.emplace(Models::Hq, std::move(hqModel));

  auto plantModel = std::make_unique<Model>(_shader);
  plantModel->load(assets + "/plant.dae");
  _models.emplace(Models::Plant, std::move(plantModel));

  auto treeModel = std::make_unique<Model>(_shader);
  treeModel->load(assets + "/tree.dae");
  _models.emplace(Models::Tree, std::move(treeModel));

  auto barrierModel = std::make_unique<Model>(_shader);
  barrierModel->load(assets + "/barrier.dae");
  barrierModel->loadTexture(assets + "/grey.png", TexturePackType::PreBuild);
  barrierModel->loadTexture(assets + "/blue.png", TexturePackType::OnSelection);
  barrierModel->loadTexture(assets + "/red.png", TexturePackType::UnderFire);
  barrierModel->loadTexture(assets + "/black.png", TexturePackType::Destroyed);
  _models.emplace(Models::Barrier, std::move(barrierModel));

  auto shroudModel = std::make_unique<Model>(_shader);
  shroudModel->load(assets + "/shroud.dae");
  shroudModel->loadTexture(assets + "/blue.png", TexturePackType::OnSelection);
  shroudModel->loadTexture(assets + "/red.png", TexturePackType::UnderFire);
  shroudModel->loadTexture(assets + "/black.png", TexturePackType::Destroyed);
  _models.emplace(Models::Shroud, std::move(shroudModel));

  auto turbineModel = std::make_unique<Model>(_shader);
  turbineModel->load(assets + "/turbine.dae");
  turbineModel->loadTexture(assets + "/grey.png", TexturePackType::PreBuild);
  turbineModel->loadTexture(assets + "/blue.png", TexturePackType::OnSelection);
  turbineModel->loadTexture(assets + "/red.png", TexturePackType::UnderFire);
  turbineModel->loadTexture(assets + "/black.png", TexturePackType::Destroyed);
  _models.emplace(Models::Turbine, std::move(turbineModel));

  auto tfTexture =
    std::make_shared<Texture>(GL_TEXTURE_2D, assets + "/Garage.png");
  tfTexture->load();
  _menuTextures.emplace(MenuTextures::TankFactory, std::move(tfTexture));
  auto hqTexture = std::make_shared<Texture>(GL_TEXTURE_2D, assets + "/Hq.png");
  hqTexture->load();
  _menuTextures.emplace(MenuTextures::Hq, std::move(hqTexture));
  auto lightTankTexture =
    std::make_shared<Texture>(GL_TEXTURE_2D, assets + "/lightTank.png");
  lightTankTexture->load();
  _menuTextures.emplace(MenuTextures::TankLight, std::move(lightTankTexture));
  auto mediumTankTexture =
    std::make_shared<Texture>(GL_TEXTURE_2D, assets + "/mediumTank.png");
  mediumTankTexture->load();
  _menuTextures.emplace(MenuTextures::TankMedium, std::move(mediumTankTexture));
  auto heavyTankTexture =
    std::make_shared<Texture>(GL_TEXTURE_2D, assets + "/heavyTank.png");
  heavyTankTexture->load();
  _menuTextures.emplace(MenuTextures::TankHeavy, std::move(heavyTankTexture));

  auto plantTexture =
    std::make_shared<Texture>(GL_TEXTURE_2D, assets + "/Plant.png");
  plantTexture->load();
  _menuTextures.emplace(MenuTextures::Plant, std::move(plantTexture));
  auto treeTexture =
    std::make_shared<Texture>(GL_TEXTURE_2D, assets + "/Tree.png");
  treeTexture->load();
  _menuTextures.emplace(MenuTextures::Tree, std::move(treeTexture));

  auto barrierTexture =
    std::make_shared<Texture>(GL_TEXTURE_2D, assets + "/Barrier.png");
  barrierTexture->load();
  _menuTextures.emplace(MenuTextures::Barrier, std::move(barrierTexture));

  auto turbineTexture =
    std::make_shared<Texture>(GL_TEXTURE_2D, assets + "/Turbine.png");
  turbineTexture->load();
  _menuTextures.emplace(MenuTextures::Turbine, std::move(turbineTexture));
}

ModelsMapping ModelLoader::models()
{
  return _models;
}

MenuTexturesMapping ModelLoader::menuTextures()
{
  return _menuTextures;
}
}
