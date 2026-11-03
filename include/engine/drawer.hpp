#pragma once
#include <SDL.h>
#include "obj.hpp"

class Drawer{
    private:
        SDL_Renderer* rend;
    public:
        Drawer(SDL_Renderer* rend);
        ~Drawer() = default; 
        void drMass1(ObjState m, Vec2 cent);
        void drMass2(ObjState m1, ObjState m2, Vec2 cent);
        void drLines(Vec2 cent, ObjState m1, ObjState m2);
        
};