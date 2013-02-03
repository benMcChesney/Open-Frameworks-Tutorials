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
		
        ///////////////////
        //     STEP 2    //
        ///////////////////
        struct colorPoint {
            ofColor color ;
            ofVec2f position ;
            float radius ; 
        } ;
    
        //Keep all our points a vector a dynamically sized array
        vector<colorPoint> points ;
        int maxCircles ; 

        ///////////////////
        //     STEP 3    //
        ///////////////////
        //change the radius based on the mouse movement
        float mouseDistance ;
        
        //Fbos store pixel data on the graphics card and are very fast at minipulating/drawing pixels
        ofFbo mirrorFbo ;

    
        ///////////////////
        //     STEP 4    //
        ///////////////////
        vector<ofColor> colorPool ; 
        ofColor getRandomColor ( ) ; 
    
};
