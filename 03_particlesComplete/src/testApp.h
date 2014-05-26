#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ofxGui.h"

//#define STEP2 2
//#define STEP3 3
//#define STEP4 4

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
        ofFbo fbo ;                         
        ofxPanel gui;
        ofParameter<float> fboFade ;        //Let's add in some alpha trails for things to get awesome
        ofParameter<float> forceRadius ;    //radius of repellent/attraction force
        ofParameter<float> friction ;       //damping to slow the particles down
        ofParameter<float> springFactor ;   //how much the particle "springs" back to it's origin   
    
#endif
    
#ifdef STEP3
        ///////////////////
        //     STEP 3    //
        ///////////////////
        ofVideoPlayer video ;           //OF has a core video player that's based off of quicktime or gstreamer
        void updateParticlePixels( ofPixels pix ) ;   //Special method to update the pixel color from the video
        ofParameter<bool> bDrawTriangles ;           //OPENGL drawing modes can have very different results
#endif
		
#ifdef STEP4
        ofVideoGrabber vidGrabber ;
#endif 
    
};
