#include <Application.h>
#include <Entity.h>
#include <Systems.h>

using namespace Saddle;

class MusicBlock : public Entity {

public:
    MusicBlock(const std::string& sound_path, int width, int height)
        : m_Width(width), m_Height(height)
    {
        AddComponent<TextureComponent>();
        AddComponent<RGBColorComponent>(255, 255, 255);
        AddComponent<SoundComponent>(sound_path);

        TextureSystem::CreateRectangle(this, width, height);
    }
    ~MusicBlock() { }

    void Play()
    {
        SoundSystem::PlaySound(this);
    }

private:
    int m_Width;
    int m_Height;
};

class MusicDemo {

public:
    MusicDemo();
    ~MusicDemo();

    void Run();

private:
    Saddle::Window m_Window;

};
