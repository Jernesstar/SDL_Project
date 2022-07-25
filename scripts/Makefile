path = vendor/SDL/include
C++Flags = -std=c++17
C++IncludeFlags = -I include -I $(path)/SDL2 -I $(path)/SDL_image -I $(path)/SDL_mixer -I $(path)/SDL_ttf
C++LibFlags = -L vendor/SDL/lib -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
ProgramName = main

bin/$(ProgramName):
	@g++ src/*.cpp -o $@.exe $(C++Flags) $(C++IncludeFlags) $(C++LibFlags)