//
//  Particle.h
//  03_Pixels
//
//  Created by Ben McChesney on 7/2/11.
//
//  A Simple Particle Class
//  This could probably be a struct but learning to make a class is pretty important

#ifndef _PARTICLE
#define _PARTICLE

#include "ofMain.h" 

class Particle
{
    public : 
        Particle() ; 
        Particle( ofPoint _position , ofColor _color ) 
        {
            position = _position ; 
            color = _color ; 
            velocity = ofPoint ( ofRandom ( -5 , 5 ) , ofRandom ( -5 , 5 ) ) ; 
            spawnPoint = _position ; 
        }
        
        ofPoint position , velocity ;   //You can declare multiple variables of the same type ! Awesome
        ofPoint acceleration ;          //smoothing applied to velocity
        ofPoint spawnPoint ;            //original location to line up the picture
        ofColor color ;                 //Source color being drawn to the particle
};
#endif