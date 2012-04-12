#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    //initialize values
    maxFrames = 30 ; 
    currentFrame = 0 ; 

    for ( int i = 0; i < maxFrames ; i++ ) 
    {
        //Push back and allocate the screen in each Frame Buffer Object
        frames.push_back(ofFbo() ) ; 
        frames[i].allocate( ofGetWidth() , ofGetHeight() ) ; 
    }
    
    resetAllFbos( ) ; 
    
    //Prevents screen tearing
    ofSetVerticalSync( true ) ; 
    ofSetFrameRate( maxFrames ) ; 
    
    ofBackground( 255 , 255 , 255 ) ; 
    
    //2
    //lastMouse = ofPoint ( 0 , 0 ) ; 
}

//--------------------------------------------------------------
void testApp::update(){

    currentFrame += 1 ; 
    
    if ( currentFrame == maxFrames ) 
        currentFrame = 0 ; 
 

    ofSetWindowTitle( ofToString( ofGetFrameRate() ) ) ; 
}

//--------------------------------------------------------------
void testApp::draw(){

        //2
        /*
        //record the current mouse position
        ofPoint mousePos = ofPoint( mouseX , mouseY ) ; 
        float mouseDistance = ofDist( mousePos.x , mousePos.y , lastMouse.x , lastMouse.y ) + 15.0f ;    
         */
    
        ofSetColor( 255 , 255 , 255 ) ; 
        //Begin recording the FBO
        frames[currentFrame].begin() ;         
    
        //redraw the fbo into itself
        frames[currentFrame].draw(0 , 0 ) ; 
    
        if ( ofGetMousePressed() == true ) 
        {
            //2
            //ofSetColor ( randomColor ) ; 
            
            ofSetColor ( 15 , 15 , 15 ) ; 
            ofCircle( mouseX , mouseY , 14.0f ) ; 
            //2
            //ofCircle( mouseX , mouseY , mouseDistance ) ; 
        }
        
        //stop drawing
        frames[currentFrame].end() ; 
    
        ofSetColor ( 255 , 255 , 255 ) ; 
        frames[currentFrame].draw(0 , 0 ) ;
    
        //2
        //lastMouse = mousePos ; 
    
}

void testApp::resetAllFbos()
{
    //Easy way to reset each FBO is to draw it with a full rectangle
    for ( int i = 0; i < maxFrames ; i++ ) 
    {
        frames[i].begin() ; 
        ofSetColor( 255 , 255 , 255 ) ; 
        ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ;
        frames[i].end() ;
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{    
    //This function listens for keyboardEvents
    // Map the "R" key to clearing all the FBOs
    switch ( key) 
    {
        case 'r' :
        case 'R' :
            resetAllFbos() ; 
            break;
            
        default:
            break;
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
    //2
    //create a random color
    //randomColor = ofColor ( ofRandom ( 255 ) , ofRandom ( 255 ) , ofRandom( 255 ) ) ; 
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