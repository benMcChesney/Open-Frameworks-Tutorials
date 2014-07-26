#pragma once

#include "ofMain.h"
#include "ofxGui.h"

//#define STEP2 2
//#define STEP3 3
//#define STEP4 4
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        
		void keyPressed  (int key);
    
        ofImage sourceImage ;
        ofParameter<float> numSamples ;                  //pixels to use every frame
        ofParameter<float> circleRadiusMin ;    
        ofParameter<float> circleRadiusMax ;
#ifdef STEP2
        ///////////////////
        //     STEP 2    //
        ///////////////////
        ofVideoPlayer video ;           //OF has a core video player
        ofxPanel gui ;
   
#endif
	
	
#ifdef STEP3
        ///////////////////
        //     STEP 3    //
        ///////////////////
        ofVideoGrabber vidGrabber ;     //OF has a core video feed as well
#endif 
    
};
