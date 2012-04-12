#pragma once

#include "ofMain.h"
#include "Particle.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofImage sourceImage ; 

        int sampling ;                  //pixels to skip
        vector<Particle> particles ;    //vector to store pixels
        
        //2
        
        //Spring and Sink Factors
        float forceRadius ;             //radius of repellent/attraction force
        float friction ;                //damping to slow the particles down
        float springFactor ;          //how much the particle "springs" back to origin   
    
        //3
        ofVideoPlayer video ;
        void updateParticlePixels() ; 
        ofFbo fbo ;
    
        bool bDrawTriangles ;
		
};
