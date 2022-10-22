#include <Saddle/Core/Application.h>

#include "Demos/TextureDemo.h"
#include "Demos/Demo3D.h"

using namespace Saddle;

Application* CreateApplication()
{
    return new Demo3D();
}
