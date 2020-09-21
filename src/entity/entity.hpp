// Copyright 2020 urlordjames
#include <vector>
#include "SDL.h"

class DrawComponent {
 protected:
  SDL_Texture *tex;
 public:
  double rot;
  SDL_Rect rect;

  DrawComponent(double rotation, SDL_Rect rectangle, SDL_Texture* texture) {
    rot = rotation;
    rect = rectangle;
    tex = texture;
  }

  SDL_Texture* getTexture() {
    return tex;
  }
};

class Entity {
 public:
  std::vector<DrawComponent *> textures;
  double x = 0;
  double y = 0;
};
