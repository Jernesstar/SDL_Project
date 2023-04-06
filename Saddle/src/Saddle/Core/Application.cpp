#include "Application.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include "Assert.h"
#include "Saddle/Events/EventSystem.h"
#include "Saddle/Events/ApplicationEvents.h"
#include "Saddle/Renderer/Renderer.h"
#include "Saddle/Text/Text.h"
#include "Saddle/Core/Time.h"

namespace Saddle {

Application::Application(const ApplicationSpecification& specs)
    : Window(specs.WindowSpecification)
{
    SADDLE_CORE_ASSERT(!s_Instance, "Application already exists!");
    SADDLE_CORE_ASSERT(gladLoadGL(), "Glad could not load OpenGL");

    s_Instance = this;
    s_Specification = specs;

    IMGUI_CHECKVERSION();
    auto* c = ImGui::CreateContext();
    ImGui::SetCurrentContext(c);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.DisplaySize = ImVec2{ 1600, 900 };

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(s_Instance->Window.GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 450 core");
    ImGui_ImplOpenGL3_NewFrame();

    Renderer::Init();
    EventSystem::Init();
}

void Application::Init(const ApplicationSpecification& specs)
{    
    SADDLE_CORE_ASSERT(!s_Instance, "Application was constructed before calling Application::Init");
    SADDLE_CORE_ASSERT(glfwInit(), "Failed to initialize GLFW");

    s_Specification = specs;

    Font::Init();
}

void Application::Init(const ApplicationCommandLineArgs& args, const ApplicationSpecification& specs)
{
    Application::Init();
    s_Specification.CommandLineArgs = args;
}

void Application::Run()
{
    while(s_Instance->Window.IsOpen())
    {
        TimePoint time = Time::GetTime();
        TimeStep ts = time - s_LastFrame;
        s_LastFrame = time;

        ApplicationUpdatedEvent event(ts);
        EventSystem::Dispatch(event);
        EventSystem::PollEvents();

        ImGui::NewFrame();

        s_Instance->OnUpdate(ts);
        s_Instance->Window.Update();

        ImGui::Render();
    }
}

void Application::Close()
{
    delete s_Instance;

    Font::Close();

    glfwTerminate();
    exit(0);
}

}