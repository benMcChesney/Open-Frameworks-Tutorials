#include "testApp.h"





//--------------------------------------------------------------
void testApp::setup(){
    
    //1
    //First the background color
    //pixel values are between 0 and 255
    //ofBackground ( R , G , B ) 
    ofBackground( 15 , 15 , 15 ) ; 
    
    //2
    //ofSetVerticalSync caps the framerate at the refresh rate of your monitor
    ofSetVerticalSync( true ) ; 
    
    //Before you use an FBO you have to allocate enough memory to use it
    mirrorFbo.allocate( ofGetWidth() / 2 , ofGetHeight() / 2 ) ;
    
    //4 set the color palette
    colorPool.push_back( ofColor (  255, 97, 56) ) ; 
    colorPool.push_back( ofColor (  255, 255, 157) ) ; 
    colorPool.push_back( ofColor (  190, 235, 159) ) ; 
    colorPool.push_back( ofColor (  121, 189, 143) ) ; 
    colorPool.push_back( ofColor (  0, 163, 136) ) ;
}

//--------------------------------------------------------------
void testApp::update(){
    
    //1
    //OF gives acces to a lot of values to the window including the title
    //of also has a string conversion utility ofToString( ) 
    ofSetWindowTitle( ofToString( ofGetFrameRate() ) ) ; 
    
    //2
    //Update
    colorPoint cp ; 
    cp.color = getRandomColor() ; 
    cp.position = ofVec2f ( mouseX , mouseY ) ; 
    cp.radius = 5.0f ; 
    
    //3
    int index = points.size() - 1 ; 
   
    if ( index > 1 ) 
    {
        ofVec2f mousePos = cp.position ; 
        ofVec2f lastMousePos = points[index-1].position ; 
        mouseDistance = ofDist( mousePos.x, mousePos.y , lastMousePos.x , lastMousePos.y ) ; 
        cp.radius = 1 + mouseDistance ;
    }
    
    points.push_back( cp ) ; 
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //3
    //to record into an FBO call begin() 
    ofSetColor ( 255 , 255 , 255 ) ; 
    mirrorFbo.begin() ; 
    
    //Draw the background
    ofSetColor ( 0 , 0, 0 ) ; 
    ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ; 

    //Let's to scale the scene and then flip it for a kaleidscope effect
    //Push and pop are modifiers that effect everything drawn already in the draw() loop
    ofPushMatrix() ; 
              
        ofScale ( .5f , .5f , 1 ) ;
        //1
        //Before anything gets drawn we have to set the color for OF
        //ofSetColor( r , g , b )
        ofSetColor( 0 , 255 , 0 ) ; 

        //Now we draw a circle
        //ofCircle ( x , y , radius ) ; 
        //ofCircle ( mouseX , mouseY , 25 ) ; 

        //2
        //Iterate and draw all the circles
        for ( int i = 0 ; i < points.size() ; i++ ) 
        {
            ofSetColor ( points[i].color ); 
            ofCircle ( points[i].position.x , points[i].position.y , points[i].radius ) ; 
        }
    
    //End scaling the scene
    ofPopMatrix() ; 
    
    //end the recording
    mirrorFbo.end( ) ; 
    
    //Now we move the whole scene to the middle so the FBOs can be flipped and still drawn at 0 , 0 
    ofPushMatrix() ;
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

ofColor testApp::getRandomColor( ) 
{
    int randomIndex = ofRandom ( colorPool.size() ) ; 
    return colorPool[ randomIndex ] ; 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    //Extra
    switch ( key ) 
    {
        //if upper or lower case C was pressed down on the keyboard
        case 'c':
        case 'C':
            //reset points
            points.clear() ; 
            //draw a black rectangle over the FBO
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