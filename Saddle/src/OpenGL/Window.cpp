#include "Window.h"

#include <glad/glad.h>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <stb_image/stb_image.h>

#include "Saddle/Core/Application.h"
#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Utils.h"
#include "Saddle/Events/EventSystem.h"

namespace Saddle {

Window::Window(const WindowSpecification& specs)
    : m_Specs(specs)
{
    // Create a window with width and height, have it not be fullscreen and not share resources
    m_Window = glfwCreateWindow(specs.Width, specs.Height, specs.Title.c_str(), nullptr, nullptr);
    SADDLE_CORE_ASSERT(m_Window, "Could not create the window");

    glfwMakeContextCurrent(m_Window);

    SetVSync(specs.VSync);
    SetWindowIcon(specs.IconPath);

    EventSystem::RegisterEventListener<WindowClosedEvent>(
    [](const WindowClosedEvent& event)
    {
        Application::Close();
    });

    EventSystem::RegisterEventListener<WindowResizedEvent>(
    [this](const WindowResizedEvent& event)
    {
        SetFramebufferSize(event.Width, event.Height);
    });

    InitImGui();
}

Window::~Window()
{
    if(m_Window) glfwDestroyWindow(m_Window);
    m_Window = nullptr;

    CloseImGui();
}

void Window::SetWindowIcon(const std::string& path)
{
    if(path == "" || path.find_first_not_of(" ") == std::string::npos) 
    {
        glfwSetWindowIcon(m_Window, 0, nullptr);
        return;
    }
    m_Specs.IconPath = path;

    GLFWimage icon;
    icon.pixels = Utils::ReadImage(path, icon.width, icon.height);
    glfwSetWindowIcon(m_Window, 1, &icon);
    stbi_image_free(icon.pixels);
}

void Window::SetTitle(const std::string& title)
{
    m_Specs.Title = title;
    glfwSetWindowTitle(m_Window, title.c_str());
}
void Window::SetVSync(bool vsync)
{
    m_Specs.VSync = vsync;
    glfwSwapInterval((int)vsync);
}

void Window::SetFramebufferSize(uint32_t width, uint32_t height)
{
    m_Specs.Width = width;
    m_Specs.Height = height;
    glViewport(0, 0, width, height);
}

glm::vec2 Window::GetFrameBufferSize() const
{
    int width, height;
    glfwGetFramebufferSize(m_Window, &width, &height);
    return { width, height };
}

void Window::InitImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
    io.DisplaySize = ImVec2{ 1600, 900 };

    EventSystem::RegisterEventListener<MouseButtonPressedEvent>(
    [](MouseButtonPressedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.MouseButton] = true;
        event.Handled = true;
    });
    EventSystem::RegisterEventListener<MouseButtonReleasedEvent>(
    [](MouseButtonReleasedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.MouseButton] = false;
        event.Handled = true;
    });
    EventSystem::RegisterEventListener<MouseScrolledEvent>(
    [](MouseScrolledEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += event.ScrollX;
        io.MouseWheel += event.ScrollY;
        event.Handled = true;
    });
    EventSystem::RegisterEventListener<MouseMovedEvent>(
    [](const MouseMovedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2{ event.x, event.y };
    });
    EventSystem::RegisterEventListener<WindowResizedEvent>(
    [](const WindowResizedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2{ (float)event.Width, (float)event.Height };
    });

    // Todo: Add more event handlers
}

void Window::CloseImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

}