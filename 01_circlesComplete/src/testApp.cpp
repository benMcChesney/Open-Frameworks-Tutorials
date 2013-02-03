#include "testApp.h"





//--------------------------------------------------------------
void testApp::setup(){
    

    ///////////////////
    //     STEP 1    //
    ///////////////////
    //First the background color
    //pixel values are between 0 and 255
    //ofBackground ( R , G , B ) 
    ofBackground( 15 , 15 , 15 ) ;
    
    //ofSetVerticalSync forces vertical sync which prevents screentearing
    ofSetVerticalSync( true ) ;
    //Initialize our MAX number of circles
    maxCircles = 5000 ;

    
    //Allocate the FBO so it knows how big it's texture size is
    //we start with an FBO as big as the screen and then later we only need 1/4 of the total screen space
    mirrorFbo.allocate( ofGetWidth() / 2 , ofGetHeight() / 2 ) ;
    
    ///////////////////
    //     STEP 4    //
    ///////////////////
    //set the color palette , these were obtained off of adobe kuler
    colorPool.push_back( ofColor (  255, 97, 56) ) ; 
    colorPool.push_back( ofColor (  255, 255, 157) ) ; 
    colorPool.push_back( ofColor (  190, 235, 159) ) ; 
    colorPool.push_back( ofColor (  121, 189, 143) ) ; 
    colorPool.push_back( ofColor (  0, 163, 136) ) ;
    
}

//--------------------------------------------------------------
void testApp::update(){

    //Draws more interesting shapes
    ofSetCircleResolution( sin( ofGetElapsedTimef() ) * 10.0f + 13.0f ) ;
    
    //OF gives acces to a lot of values to the window including the title
    //OF also has a string conversion utility ofToString( ) 
    ofSetWindowTitle( ofToString( ofGetFrameRate() ) ) ; 
    
    ///////////////////
    //     STEP 2    //
    ///////////////////
    //Generate a colorPoint object and fill it with data to draw
    colorPoint cp ;
    cp.color = ofColor( ofRandom( 255 ) , ofRandom( 255 ) , ofRandom( 255 ) ) ;
    cp.position = ofVec2f ( mouseX , mouseY ) ; 
    cp.radius = ofRandom( 12 , 25 ) ; 

    ///////////////////
    //     STEP 3    //
    ///////////////////
    int index = points.size() - 1 ; 
   
    if ( index > 1 ) 
    {
        ofVec2f mousePos = cp.position ; 
        ofVec2f lastMousePos = points[index-1].position ; 
        mouseDistance = ofDist( mousePos.x, mousePos.y , lastMousePos.x , lastMousePos.y ) ; 
        cp.radius = 1 + mouseDistance ;
        cp.color = getRandomColor() ; 
    }

    //Add it to our vector of points and remove the oldest circle if we have too many
    points.push_back( cp ) ; 
    if ( points.size() > maxCircles )
        points.erase( points.begin() ) ; 
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ///////////////////
    //     STEP 3    //
    ///////////////////
    //to record into an FBO call begin() 
    mirrorFbo.begin() ;
    
    ///////////////////
    //     STEP 1    //
    ///////////////////
    //Draw the background
    ofSetColor ( 0 , 0, 0 ) ; 
    ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ; 


    //Let's to scale the scene and then flip it for a kaleidscope effect
    //Push and pop are modifiers that effect everything drawn already in the draw() loop
    ofPushMatrix() ; 
    

        //Before anything gets drawn we have to set the color for OF
        //ofSetColor( r , g , b )
        ofSetColor( 0 , ofRandom( 125 , 255 ) , ofRandom( 125 , 255 ) ) ; 
        
        //Now we draw a circle
        ofCircle ( mouseX , mouseY , 25 ) ; 

        ///////////////////
        //     STEP 3    //
        ///////////////////
        //scale the FBO being drawn as it will be redrawn and flipped 4 times
        ofScale ( .5f , .5f , 1 ) ;
    
        ///////////////////
        //     STEP 2    //
        ///////////////////
        //Iterate and draw all the circles
        for ( int i = 0 ; i < points.size() ; i++ ) 
        {
            ofSetColor ( points[i].color ); 
            ofCircle ( points[i].position.x , points[i].position.y , points[i].radius ) ; 
        }
    
    //End scaling the scene
    ofPopMatrix() ; 
    
    ///////////////////
    //     STEP 3    //
    ///////////////////
    //end the recording
    mirrorFbo.end( ) ; 
    
    
    //Now we move the whole scene to the middle so the FBOs can be flipped and still drawn at 0 , 0 
    ofPushMatrix() ;
        //First 
        ofTranslate( ofGetWidth() / 2 , ofGetHeight() / 2 )  ; 
        
        //Draw the FBO at full color
        ofSetColor ( 255 , 255 , 255 ) ; 
        //Top left
        mirrorFbo.draw( 0 , 0 ) ; 
        
        //Top right
        ofPushMatrix() ; 
            ofScale( -1 , 1 , 1 ) ; 
            mirrorFbo.draw( 0 , 0 ) ; 
        ofPopMatrix() ;
        
        //Bottom Left
        ofPushMatrix() ; 
            ofScale( 1 , -1 , 1 ) ; 
            mirrorFbo.draw( 0 , 0 ) ; 
        ofPopMatrix() ; 
        
        //Bottom Right
        ofPushMatrix() ; 
            ofScale( -1 , -1 , 1 ) ; 
            mirrorFbo.draw( 0 , 0 ) ; 
        ofPopMatrix() ; 
    ofPopMatrix() ;
    
}

///////////////////
//     STEP 4    //
///////////////////
ofColor testApp::getRandomColor( ) 
{
    int randomIndex = ofRandom ( colorPool.size() ) ; 
    return colorPool[ randomIndex ] ; 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    ///////////////////
    //     STEP 4    //
    ///////////////////
    switch ( key ) 
    {
        //if upper or lower case C was pressed down on the keyboard
        case 'c':
        case 'C':
            //reset points
            points.clear() ; 
            //draw a black rectangle over the FBO to reset it's appearence
            mirrorFbo.begin() ; 
                ofSetColor ( 0 , 0, 0 ) ; 
                ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ; 
            mirrorFbo.end() ; 

            break ; 
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}