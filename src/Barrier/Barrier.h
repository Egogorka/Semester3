//
// Created by meeve on 11.09.2021.
//

#ifndef SEMESTER3_BARRIER_H
#define SEMESTER3_BARRIER_H

class Barrier {
public:
    float x;//coordinates of the left corner
    float y;
    int *arr;
    float dx; // rectangle length
    float dy; // rectangle width
    Barrier(float inx, float iny, float indx, float indy); // constructor
};

#endif //SEMESTER3_BARRIER_H