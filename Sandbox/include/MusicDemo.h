// #include "Application.h"

// class MusicBlock : public Saddle::Entity {

// public:
//     MusicBlock(const std::string& sound_path, int width, int height)
//         : m_MusicNote(sound_path), m_Width(width), m_Height(height)
//     {
//         SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
//         SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255)); 
//     }
//     ~MusicBlock() { }

//     void Play()
//     {
//         m_MusicNote.Play();
//     }

// private:
//     Saddle::SoundComponent m_MusicNote;
//     int m_Width;
//     int m_Height;
// };

// class MusicDemo {

// public:
//     MusicDemo();
//     ~MusicDemo();

//     void Run();

// private:
//     Saddle::Window m_Window;

// };

