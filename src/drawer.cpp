#include <SDL.h>
#include "../include/engine/drawer.hpp"
#include <cmath>

int drCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

Vec2 getRec(ObjState a){
    long double y = a.l * std::cosl(a.th);
    long double x = a.l * std::sinl(a.th);
    Vec2 coord = {x,y};
    return coord;
}



Drawer::Drawer(SDL_Renderer* rend):
    rend(rend) {}

void Drawer::drMass1(ObjState m, Vec2 cent){
    Vec2 recco = getRec(m);
    SDL_SetRenderDrawColor(rend,255,255,255,255);
    drCircle(rend,cent.a1 + recco.a1,cent.a2 + recco.a2,10);
}

void Drawer::drMass2(ObjState m1, ObjState m2, Vec2 cent){
    Vec2 rec1 = getRec(m1);
    Vec2 rec2 = getRec(m2);
    SDL_SetRenderDrawColor(rend,255,255,255,255);
    drCircle(rend,cent.a1 + rec2.a1 + rec1.a1,cent.a2 + rec2.a2 + rec1.a2,10);
}

void Drawer::drLines(Vec2 cent, ObjState m1, ObjState m2){
    SDL_SetRenderDrawColor(rend,255,255,255,255);
    Vec2 rec1 = getRec(m1);
    Vec2 rec2 = getRec(m2);
    SDL_RenderDrawLine(rend,cent.a1,cent.a2,cent.a1 + rec1.a1, cent.a2 + rec1.a2);
    SDL_RenderDrawLine(rend,cent.a1 + rec1.a1, cent.a2 + rec1.a2,cent.a1 + rec2.a1 + rec1.a1,cent.a2 + rec2.a2 + rec1.a2);
}

