#pragma once

#include "ofMain.h"
#include "Particle.h"

//#define STEP2 2
//#define STEP3 3

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        
		void keyPressed  (int key);
    
        ofImage sourceImage ;
    
        void createParticlesFromPixels ( ofPixels pix ) ; 

        int sampling ;                  //pixels to skip
        vector<Particle> particles ;    //vector to store pixels
        
#ifdef STEP2
        ///////////////////
        //     STEP 2    //
        ///////////////////
        float forceRadius ;             //radius of repellent/attraction force
        float friction ;                //damping to slow the particles down
        float springFactor ;            //how much the particle "springs" back to it's origin   
        ofFbo fbo ;                     //Let's add in some alpha trails for things to get awesome
#endif
    
#ifdef STEP3
        ///////////////////
        //     STEP 3    //
        ///////////////////
        ofVideoPlayer video ;           //OF has a core video player that's based off of quicktime or gstreamer
        void updateParticlePixels() ;   //Special method to update the pixel color from the video
        bool bDrawTriangles ;           //OPENGL drawing modes can have very different results
#endif
		
    
};
