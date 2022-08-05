// #include "Application.h"
// #include "MusicDemo.h"

// using namespace Saddle;

// #define SCREEN_WIDTH 1200
// #define SCREEN_HEIGHT 640

// void Start_Screen()
// {
//     Saddle::Window window = Application::Get().GetWindow();
//     std::string title = "Music Demo";
//     std::string message = "Press any key to continue";

//     std::string font_path = "resources/pixel_font.ttf";
//     SDL_Color color = {255, 255, 255};
//     UI::Text title_text(title, font_path, 8, color, window.GetRenderer());
//     UI::Text message_text(message, font_path, 5, color, window.GetRenderer());

//     title_text.PlaceAt(
//         0.5 * SCREEN_WIDTH - title_text.GetCenter().x, 
//         0.5 * SCREEN_HEIGHT - 2 * title_text.GetRect().h
//     );

//     message_text.PlaceAt(
//         0.5 * SCREEN_WIDTH - message_text.GetCenter().x,
//         0.5 * SCREEN_HEIGHT 
//     );

//     SDL_Event event;
//     bool running = true;

//     while(running)
//     {
//         window.AddUIElement(title_text);
//         window.AddUIElement(message_text);

//         while(SDL_PollEvent(&event))
//         {
//             window.HandleEvent(event);
//             switch(event.type)
//             {
//                 case SDL_QUIT:
//                     running = false;
//                     break;

//                 case SDL_KEYDOWN:
//                     running = false;
//                     break;
//             }
//         }
//         window.RenderUI();
//     }
// }

// class App : public Application {

// public:
//     App() : Application() { }
//     ~App() { }

//     void Run()
//     {
//         Start_Screen();
//         MusicDemo demo;
//         demo.Run();
//     }

// };

// int main(int argc, char** argv)
// {
//     Application::Init();

//     App app;
//     app.Run();

//     Application::Close();

//     return 0;
// }

int main(int argc, char** argv) { }