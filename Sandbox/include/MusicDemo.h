#include <Saddle/Core/Application.h>
#include <Saddle/Scene/Entity.h>
#include <Saddle/Events/Events.h>
#include <Saddle/Systems/Systems.h>

using namespace Saddle;
    
class MusicBlock : public Entity {
public:
    MusicBlock(const std::string& sound_path, float width, float height, int r = 255, int g = 255, int b = 255)
        : m_Sound(sound_path), m_Width(width), m_Height(height)
    {
        AddComponent<TextureComponent>();
        AddComponent<RGBColorComponent>(r, g, b);
        AddComponent<RectComponent>(width, height);

        TextureSystem::CreateRectangle(*this, width, height);

        AddComponent<EventListenerComponent>()
        .OnMouseButtonPressed = [this](MouseButtonPressedEvent& event) {
            if(Input::MousePressedOn(GetComponent<RectComponent>(), GetComponent<Coordinate2DComponent>()))
                Play();
        };
        
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
    Scene m_Scene;
};
