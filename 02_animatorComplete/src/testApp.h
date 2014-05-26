#pragma once


//#define STEP2 2
//#define STEP3 3

#include "ofMain.h"

#ifdef STEP3
#include "ofxGui.h"
#endif

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mousePressed(int x, int y, int button);
        void mouseReleased( int x , int y , int button ) ;
        void exit( ) ;
    
        int maxFrames ;             //total frames to loop
        int currentFrame ;          //current index
    
        vector<ofFbo> frames ;      //keep all of our FBOs in a vector
        void resetAllFbos() ;       //easy reset
    
        bool bMousePressed ;        //use a bool to keep track is the mouse is pushed down
        
#ifdef STEP2
        ///////////////////
        //     STEP 2    //
        ///////////////////
        ofPoint lastMouse ;         //last position of mouse used to calculate speed and circle radius
        ofColor randomColor ;       //random Color to make things a little more interesting
#endif
    
#ifdef STEP3
        ///////////////////
        //     STEP 3    //
        ///////////////////
        bool bShowGui ; 
        ofxPanel gui;                      
        ofParameter<ofColor> color1;
        ofParameter<ofColor> color2;
    
        ofxButton saveSettingsButton;
        ofxButton loadSettingsButton;
    
        void color1Changed(ofColor & color);
        void color2Changed(ofColor & color);
    
    

#endif
		
};
