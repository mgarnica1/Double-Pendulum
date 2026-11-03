#pragma once
#include <SDL.h>

struct SystemState{
    long double a1,a2,va1,va2,dva1,dva2;
    double l1,l2;
    float m1,m2,g;
};


struct ObjState{
    long double th,vth,dvth;
    float m;
    double l;
};

class Mass{
    private:
        long double th;
        long double vth;
        long double dvth;
        float m;
        double l;
    public:
    Mass(long double th, long double vth, long double dvth, float m, double l);
    ~Mass() = default;
    Mass() = default;
    void update(float dt);
    void acc(long double x);
    ObjState getState();
};

struct Vec2{
    long double a1,a2;
};

class System{
    private:
        Mass m1;
        Mass m2;
        int centerx,centery;
        double g;
    public:
        System(int centerx, int centery);   
        ~System() = default;
        void init(SystemState st);
        void update(float dt);
        ObjState getState1();
        ObjState getState2();
        Vec2 getCenter();
};

