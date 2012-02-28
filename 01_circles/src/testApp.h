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
		
    
        //2
        struct colorPoint {
            ofColor color ;
            ofVec2f position ;
            
            //3
            float radius ; 
        } ;
    
        vector<colorPoint> points ; 
    
        //3
        //change the radius based on the mouse movement
        float mouseDistance ; 
        //FBOs are similar to bitmapData objects in flash, they store pixels to be used on the GPU
        ofFbo mirrorFbo ;
    
        vector<ofColor> colorPool ; 
        ofColor getRandomColor ( ) ; 

};
