#pragma once


//#define STEP2 2
//#define STEP3 3

#include "ofMain.h"

#ifdef STEP3
#include "ofxUI.h"
#endif

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mousePressed(int x, int y, int button);
        void mouseReleased( int x , int y , int button ) ; 
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
        ofxUICanvas *gui;           //the "*" notation specifys a pointer which holds a reference 
                                    //Pointers require a more indepth discussion but for now that's all you need
        
        void guiEvent(ofxUIEventArgs &e);       //event handler for GUI events
        float red, green, blue;     //First Color
        float red2, green2, blue2; 	//Second Color
#endif
		
};
