#pragma once

#include "ofMain.h"

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
    
        int maxFrames ;             //total frames to loop
        int currentFrame ;          //current index
    
        vector<ofFbo> frames ;      //keep all of our FBOs in a vector
        void resetAllFbos() ;       //easy reset
        
        /*
        //2
        ofPoint lastMouse ; 
        ofColor randomColor ;
         */
		
};
