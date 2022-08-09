// #include "Application.h"
// #include "Circle.h"
// #include "Utils.h"

// namespace Saddle {

// Circle::Circle() : Entity() { }

// Circle::Circle(uint32_t _radius, RGBColorComponent _color, uint32_t _x, uint32_t _y)
//     : Entity()
// {
//     auto center = AddComponent<Coordinate2DComponent>(_x, _y);
//     auto rect = AddComponent<RectComponent>();
//     AddComponent<RGBColorComponent>(_color);

//     radius = _radius;

//     uint32_t diameter = 2 * radius;
//     rect = {diameter, diameter};

//     Construct_Circle();
// }

// void Circle::Construct_Circle()
// {  
//     int flags = 0;
//     int depth = 32;
//     int _radius = (int)radius;

//     SDL_Surface* surface = SDL_CreateRGBSurface(flags, 2 * _radius, 2 * _radius, depth, 0, 0, 0, 0);
//     SDL_LockSurface(surface);

//     int dx, dy;
//     auto color_ = GetComponent<RGBColorComponent>();
//     SDL_Color _color = {color_.r, color_.g, color_.b};

//     for(int w = 0; w < surface->w; w++)
//     {
//         for(int h = 0; h < surface->h; h++)
//         {
//             dx = _radius - w; // horizontal offset
//             dy = _radius - h; // vertical offset
//             if((dx * dx + dy * dy) <= (_radius * _radius))
//             {
                
//                 SetPixel(surface, (surface->w * 0.5) + dx, (surface->h * 0.5) + dy, _color);
//             }
//         }
//     }
    
//     SDL_UnlockSurface(surface);

//     auto renderer = Application::Get().GetWindow().GetRenderer();
//     auto texture_component = AddComponent<TextureComponent>();
//     texture_component.texture = SDL_CreateTextureFromSurface(renderer, surface);
//     SDL_FreeSurface(surface);
// }

// }
