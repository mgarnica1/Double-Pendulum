#include <SDL.h>
#include <iostream>
#include "../include/engine/drawer.hpp"
#include "../include/engine/obj.hpp"

int main(int argc, char* argv[]) {
    
    SDL_Window* window = SDL_CreateWindow("Doble Pendulo",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);

    bool running = true;
    SDL_Event event;
    
    System sys = System(400,300);
    
    SystemState conditions = {1,0,0,0,0,0,150,90,20,5,9.8};
    sys.init(conditions);

    Drawer draw = Drawer(renderer);

    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    double deltaTime = 0;

    while (running){
        
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
            }
        }
            
        last = now;
        now = SDL_GetPerformanceCounter();// Calculate delta time in seconds
        deltaTime = static_cast<double>(now - last) / SDL_GetPerformanceFrequency();


        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        draw.drMass1(sys.getState1(),sys.getCenter());
        draw.drMass2(sys.getState1(),sys.getState2(), sys.getCenter());
        draw.drLines(sys.getCenter(),sys.getState1(),sys.getState2());
        SDL_RenderPresent(renderer);

        int steps = 12;
        for(int i=0; i<steps; i++){
            sys.update(deltaTime/steps);
            SDL_Delay(1);
        }
        std::cout<<deltaTime<<"\n";
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}