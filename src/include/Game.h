#include <iostream>

class Game {
public:
    const std::string player_1_name;
    const std::string player_2_name;
    SDL_Renderer* renderer;

    Game(std::string name_1, std::string name_2, SDL_Renderer* _renderer);
    ~Game();
};