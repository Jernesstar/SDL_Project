#include "PongGame.h"

PongGame::PongGame(const std::string& name_1, const std::string& name_2, Saddle::Window& _window) 
    : player_1_name(name_1), player_2_name(name_2), SCREEN_WIDTH(_window.Width), SCREEN_HEIGHT(_window.Height)
{  
    window = &_window;
    paddle_1 = (SDL_Surface*)malloc(sizeof(SDL_Surface));
    paddle_2 = (SDL_Surface*)malloc(sizeof(SDL_Surface));

    int flags, paddle_width, paddle_height, depth;
    flags = 0;
    paddle_width = 5;
    paddle_height = 80;
    depth = 32;
    
    paddle_1 = SDL_CreateRGBSurface(flags, paddle_width, paddle_height, depth, 0, 0, 0, 0);
    paddle_2 = SDL_CreateRGBSurface(flags, paddle_width, paddle_height, depth, 0, 0, 0, 0);

    SDL_FillRect(paddle_1, NULL, SDL_MapRGB(paddle_1->format, 255, 255, 255)); 
    SDL_FillRect(paddle_2, NULL, SDL_MapRGB(paddle_2->format, 255, 255, 255));
}

PongGame::~PongGame()
{
    SDL_FreeSurface(paddle_1);
    SDL_FreeSurface(paddle_2);  
}

void PongGame::Run()
{
    SDL_RenderClear(*window->GetRenderer());
    paddle_1->clip_rect.x = SCREEN_WIDTH / 4;
    paddle_1->clip_rect.y = SCREEN_HEIGHT / 2;

    SDL_Texture* paddle = SDL_CreateTextureFromSurface(*window->GetRenderer(), paddle_1);

    uint32_t _radius = 20;
    SDL_Color circle_color = { 255, 0, 0 };
    SDL_Point center = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 250 };
    Saddle::GameObjects::Circle ball(_radius, circle_color, *window->GetRenderer(), center.x, center.y);

    int radius = 20;
    int speed = 1;
    int velocity_x = -speed;
    int velocity_y = speed;
    
    SDL_Event event;
    bool paused = false;
    bool running = true;
    while(running)
    {
        window->AddGameObject(ball);
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            if(paddle_1->clip_rect.y - 30 > 0)
                                paddle_1->clip_rect.y += -30;
                            break;
                        case SDLK_DOWN:
                            if(paddle_1->clip_rect.y + paddle_1->clip_rect.h < SCREEN_HEIGHT)
                                paddle_1->clip_rect.y += 30;
                            break;
                        case SDLK_RETURN:
                            paused = !paused;
                            break;
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                    }
                    break;
            }
        }

        if(center.x - radius <= paddle_1->clip_rect.x + paddle_1->clip_rect.w
            && center.x - radius >= paddle_1->clip_rect.x)
        {
            if(center.y <= paddle_1->clip_rect.y + paddle_1->clip_rect.h && center.y >= paddle_1->clip_rect.y)
                velocity_x *= -1;
        }
        if(center.x + radius >= SCREEN_WIDTH || center.x - radius <= 0)
        {
            if(center.x + radius >= SCREEN_WIDTH) center.x = SCREEN_WIDTH - radius;
            else if(center.x - radius <= 0) center.x = radius;

            velocity_x *= -1;
        }
        if(center.y + radius >= SCREEN_HEIGHT || center.y - radius <= 0)
        {
            // Circle is touching the top of the screen, thus set the center of the circle to be a radius higher than the bottom of the screen
            if(center.y + radius >= SCREEN_HEIGHT) center.y = SCREEN_HEIGHT - radius;
            // Circle is touching the bottom of the screen, thus set the center to the radius exactly
            else if(center.y - radius <= 0) center.y = radius;

            velocity_y *= -1;
        }
        if(paused == false)
        {
            center.x += velocity_x;
            center.y += velocity_y;

            ball.GetRect()->x += velocity_x;
            ball.GetRect()->y += velocity_y;
        }
        if(center.x + radius < paddle_1->clip_rect.x)
        {
            // running = false;
        }
        window->RenderGameObjects();
    }
    return;
}