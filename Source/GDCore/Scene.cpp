#include "Scene.h"

namespace GDES {
void Scene::AddEntity(std::unique_ptr<Entity>&& entity) {
    entity->LoadContent();
    entityList.emplace_back(std::move(entity));
}

void Scene::AddBreakable(std::shared_ptr<Entity> entity) {
    entity->LoadContent();
    breakables.emplace_back(std::move(entity));
}
void Scene::Update(sf::Time elapsedTime) {
    for (auto& e : entityList) {
        e->Update(elapsedTime);
    }
    for (auto& e: breakables)
    {
        e->Update(elapsedTime);
    }
}

void Scene::Draw(sf::RenderWindow* window) {

    if(!window) {
        return; // Nada que dibujar
    }

    for (auto& e : breakables)
        e->Draw(window);
    for(auto& e : entityList)
        e->Draw(window);

}
} // namespace GDES
