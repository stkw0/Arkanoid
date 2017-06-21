#pragma once

#include "Scene.h"
#include <map>

namespace GDES {
class SceneManager {
  public:
    SceneManager();
    ~SceneManager();

    bool AddScene(int sceneIndex, Scene* scene, bool isCurrentScene = false);
    bool LoadScene(int sceneIndex);
    bool RemoveScene(int sceneIndex, bool removeFromMemory);
    Scene* GetScene(int sceneIndex);
    Scene* GetCurrentScene() {
        return currentScene;
    }

  private:
    Scene* currentScene;
    std::map<int, Scene*> sceneMap;
};
}
