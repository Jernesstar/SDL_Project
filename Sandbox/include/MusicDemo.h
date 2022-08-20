#include <Saddle/Core/Application.h>
#include <Saddle/Scene/Entity.h>
#include <Saddle/Systems/Systems.h>

using namespace Saddle;

class MusicBlock : public Entity {

public:
    MusicBlock(const std::string& sound_path, int width, int height)
        : m_Sound(sound_path), m_Width(width), m_Height(height)
    {
        AddComponent<TextureComponent>();
        AddComponent<RGBColorComponent>(255, 255, 255);

        TextureSystem::CreateRectangle(*this, width, height);
    }
    ~MusicBlock() { }

    void Play()
    {
        m_Sound.Play();
    }

private:
    int m_Width, m_Height;
    Sound m_Sound;
};

class MusicDemo {

public:
    MusicDemo();
    ~MusicDemo();

    void Run();

private:
    Saddle::Window m_Window;

};
