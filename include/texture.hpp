#ifndef TEXTURE_HPP_
# define TEXTURE_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <iostream>

class Game;

class Texture
{
private:
  SDL_Texture *texture;
public:
  Texture(Game &game, const std::string& name);
  ~Texture();
  SDL_Texture *getTexture() const;
};

#endif // !TEXTURE_HPP_
