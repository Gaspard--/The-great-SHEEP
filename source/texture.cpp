#include "texture.hpp"
#include "game.hpp"

Texture::Texture(Game &game, const std::string &name)
{
  std::string file_path("assets/" + name);

  texture = IMG_LoadTexture(game.getRenderer(), file_path.c_str());
  if (!texture)
    {
      std::cerr << "Failed to open a texture: " << name << std::endl
		<< SDL_GetError() << std::endl;
      exit(-1);
    }
}

Texture::~Texture()
{
  SDL_DestroyTexture(texture);
}

SDL_Texture *Texture::getTexture() const
{
  return (texture);
}
