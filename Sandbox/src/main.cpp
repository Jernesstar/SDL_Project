#include <iostream>

#include <Saddle/Core/Application.h>

#include "Demos/TextureDemo.h"
#include "Demos/Demo3D.h"

using namespace Saddle;

Application* CreateApplication(const ApplicationCommandLineArgs& args)
{
    if(args.Count == 1)
        return new TextureDemo();

    if(std::string("3D") == args[1]) 
        return new Demo3D();

    return new TextureDemo();
}
