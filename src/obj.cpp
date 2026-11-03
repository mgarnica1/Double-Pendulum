#include <SDL.h>
#include "../include/engine/obj.hpp"
#include <cmath>
#include <iostream>

long double accel(int id, ObjState Sm1, ObjState Sm2, float g){
    long double thDelta = Sm2.th - Sm1.th;
    float M = Sm1.m + Sm2.m;
    long double alpha = Sm1.m + Sm2.m * std::exp2l(std::sinl(thDelta));

    using namespace std;

    if(id == 1){
        long double accm1 = -1 * sinl(thDelta) * (Sm2.m * Sm1.l * exp2l(Sm1.vth) * cosl(thDelta) + Sm2.m * Sm2.l * exp2l(Sm2.vth));
        accm1 -= g * (M*sinl(Sm1.th) - Sm2.m*sinl(Sm2.th)*cosl(thDelta));
        accm1 = accm1 / (Sm1.l*alpha) ;
        return accm1;
    }
    else if(id == 2){
        long double accm2 = sinl(thDelta) * (M * Sm1.l * exp2l(Sm1.vth) + Sm2.m * Sm2.l * exp2l(Sm2.vth) * cosl(thDelta));
        accm2 += g * (M*sinl(Sm1.th)*cosl(thDelta) - M*sinl(Sm2.th));
        accm2 = accm2 / (Sm2.l*alpha) ;
        return accm2;
    }
    else{
        long double l = 0;
        return l;
    }
}



Mass::Mass(long double th, long double vth, long double dvth, float m, double l) :
    th(th),vth(vth),dvth(dvth),m(m),l(l) { }

void Mass::update(float dt){
    vth += dvth * dt;
    th += vth * dt;
}
void Mass::acc(long double x){
    dvth = x;
}

ObjState Mass::getState(){
    ObjState st = {th,vth,dvth,m,l};
    return st;
}



System::System(int centerx, int centery) : 
    centerx(centerx),centery(centery) { }
void System::init(SystemState st){
    m1 = Mass(st.a1,st.va1,st.dva1,st.m1,st.l1);
    m2 = Mass(st.a2,st.va2,st.dva2,st.m2,st.l2);
    g = st.g;
}
void System::update(float dt){
    ObjState Sm1 = m1.getState();
    ObjState Sm2 = m2.getState();
    
    long double accm1 = accel(1,Sm1,Sm2,g);
    long double accm2 = accel(2,Sm1,Sm2,g);

    m1.acc(accm1); m1.update(dt);
    m2.acc(accm2); m2.update(dt);
}   

ObjState System::getState1(){
    ObjState st = m1.getState();
    return st;
}
ObjState System::getState2(){
    ObjState st = m2.getState();
    return st;
}
Vec2 System::getCenter(){
    long double cx = centerx;
    long double cy = centery;
    
    Vec2 cen = {cx,cy};
    return cen;
}
