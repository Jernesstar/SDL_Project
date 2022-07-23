#include "Application.h"

namespace Saddle {

Application::Application()
{
    
}

Application::~Application()
{
    
}

void Application::Init()
{
    instance = new Application();
}

}