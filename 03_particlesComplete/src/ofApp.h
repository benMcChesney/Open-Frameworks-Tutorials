#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ofxGui.h"

#define STEP2 2
#define STEP3 3

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        
		void keyPressed  (int key);
    
        vector<Particle> particles ;    //vector to store pixels
        ofParameter<int> maxParticles ;
        ofParameter<float> friction ;       //damping to slow the particles down
        ofParameter<float> particleLife ;
    
#ifdef STEP2
        ///////////////////
        //     STEP 2    //
        ///////////////////         
        ofxPanel gui ; 
        ofParameter<float> forceRadius ;    //radius of repellent/attraction force
        ofParameter<float> particleSize ;
        ofParameter<int>   maxPerSpawn ;
        ofParameter<float> maxForce ;
        ofParameter<float> spawnRadius ; 
        
#endif
    
#ifdef STEP3
        ofParameter<bool> bDrawTriangles ;           //OPENGL drawing modes can have very different
        ofParameter<bool> bDrawLines ;
        ofParameter<bool> bDrawTriangleStrip  ;
        ofParameter<bool> bDrawLineLoop ;
        ofParameter<bool> bDrawQuads ;
        ofParameter<bool> bDrawPoints ; 
    
        ofFbo fbo ;
        ofParameter<float> fboFade ;        //Let's add in some alpha trails for things to get awesome
#endif
		
    
};
