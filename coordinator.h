#pragma once
#ifndef Coordinator2_h
#define Coordinator2_h

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "IntersectionController.h"



class Coordinator {

public:
    std::vector<IntersectionController*> intersections;


    Coordinator() {}
    void addIntersection(IntersectionController* intersection); //addition d'une intersection
    void updateAll(float deltaTime);                            //mettre a jour tout les intersection
    void switchModeAll(bool adaptive);     //changer le mode pour toutes les intersections





};


#endif
