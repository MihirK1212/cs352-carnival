#ifndef HUMAN_H
#define HUMAN_H

#include "../../libs.h"

#include "../shapes/shapes.h"
#include "../objects/objects.h"

double radian(double angle);

struct Human {

    double human_x;
    double human_y;
    double human_z; 

    double angle_x; 
    
    double leg_angle_1; 
    double leg_angle_2;
    double leg_flag; //left leg or right leg is moving
    double leg_coming_back; 
    
    double hand_angle_1; 
    double hand_angle_2;

    bool sittingRollerCoaster;

    Human(bool sittingRollerCoaster = false) {

        human_x = 10;
        human_y = -15;
        human_z = 50; 

        angle_x = 0; 
        
        leg_angle_1 = 0; 
        leg_angle_2 = 0;
        leg_flag = 0; 
        leg_coming_back = 0; 
        
        hand_angle_1 = 0; 
        hand_angle_2 = 0;

        this->sittingRollerCoaster = sittingRollerCoaster;
    }

    void drawCubeBodyPart();
    void drawHuman();
    void move(int key, int x, int y);
};


#endif
