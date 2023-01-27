#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

const int FPS{60};                  // Fixed framerate
const int MS_PER_FRAME{1000/FPS};   // Duration in ms of each frame
const bool FPS_CAPPING{true};       // If true, framerate is capped

class Game
{
    private:
        bool isRunning;
        int msPreviousFrame{0};
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        Game();
        ~Game();
        void Initialize();
        void Setup();
        void Run();
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();

        int windowWidth;
        int windowHeight;
};

#endif