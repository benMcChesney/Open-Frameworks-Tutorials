#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    

    ///////////////////
    //     STEP 1    //
    ///////////////////
    //First the background color
    //pixel values are between 0 and 255
    //ofBackground ( R , G , B ) 
    ofBackground( 15 , 15 , 15 ) ;
    
    //ofSetVerticalSync forces vertical sync which prevents screentearing
    ofSetVerticalSync( true ) ;
    
#ifdef STEP2
    //Initialize our MAX number of circles
    maxCircles = 5000 ;
#endif
    
#ifdef STEP3
    //Allocate the FBO so it knows how big it's texture size is
    //we start with an FBO as big as the screen and then later we only need 1/4 of the total screen space
    mirrorFbo.allocate( ofGetWidth() / 2 , ofGetHeight() / 2 ) ;
#endif

#ifdef STEP4
    ///////////////////
    //     STEP 4    //
    ///////////////////
    //set the color palette , these were obtained off of adobe kuler
    colorPool.push_back( ofColor (  255, 97, 56) ) ; 
    colorPool.push_back( ofColor (  255, 255, 157) ) ; 
    colorPool.push_back( ofColor (  190, 235, 159) ) ; 
    colorPool.push_back( ofColor (  121, 189, 143) ) ; 
    colorPool.push_back( ofColor (  0, 163, 136) ) ;
    bDragging = false;
#endif
    
}

//--------------------------------------------------------------
void ofApp::update(){

    //Draws more interesting shapes
    ofSetCircleResolution( sin( ofGetElapsedTimef() ) * 10.0f + 13.0f ) ;
    
    //OF gives acces to a lot of values to the window including the title
    //OF also has a string conversion utility ofToString( ) 
    ofSetWindowTitle( ofToString( ofGetFrameRate() ) ) ; 
    
#ifdef STEP2
    ///////////////////
    //     STEP 2    //
    ///////////////////
    //Generate a colorPoint object and fill it with data to draw
    colorPoint cp ;
    cp.color = ofColor( ofRandom( 255 ) , ofRandom( 255 ) , ofRandom( 255 ) ) ;
    cp.position = ofVec2f ( mouseX , mouseY ) ; 
    cp.radius = ofRandom( 12 , 25 ) ;
#endif
    
#ifdef STEP3
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
        cp.color = ofColor( ofRandom( 255 ) , ofRandom( 255 ) , ofRandom( 255 ) ) ;
    #ifdef STEP4
        cp.color = getRandomColor() ;
    #endif
    }
#endif
    
#ifdef STEP2
    //Add it to our vector of points and remove the oldest circle if we have too many
    #ifndef STEP4
        points.push_back( cp ) ;
    #endif
        
    #ifdef STEP4
        if ( bDragging == true )
            points.push_back( cp ) ;

    #endif
        if ( points.size() > maxCircles )
            points.erase( points.begin() ) ;
    
#endif
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
#ifdef STEP3
    ///////////////////
    //     STEP 3    //
    ///////////////////
    //to record into an FBO call begin() 
    mirrorFbo.begin() ;
#endif
    
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

#ifdef STEP3
        ///////////////////
        //     STEP 3    //
        ///////////////////
        //scale the FBO being drawn as it will be redrawn and flipped 4 times
        ofScale ( .5f , .5f , 1 ) ;
#endif
    
#ifdef STEP2
        ///////////////////
        //     STEP 2    //
        ///////////////////
        //Iterate and draw all the circles
        for ( int i = 0 ; i < points.size() ; i++ ) 
        {
            ofSetColor ( points[i].color ); 
            ofCircle ( points[i].position.x , points[i].position.y , points[i].radius ) ; 
        }
#endif
    
    //End scaling the scene
    ofPopMatrix() ; 
    
#ifdef STEP3
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
        //bottom right
        mirrorFbo.draw( 0 , 0 ) ; 
        
        //bottom left
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
#endif
    
}

#ifdef STEP4
///////////////////
//     STEP 4    //
///////////////////
ofColor ofApp::getRandomColor( ) 
{
    int randomIndex = ofRandom ( colorPool.size() ) ; 
    return colorPool[ randomIndex ] ; 
}
#endif

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    ///////////////////
    //     STEP 4    //
    ///////////////////
    switch ( key ) 
    {
        //if upper or lower case C was pressed down on the keyboard
        case 'c':
        case 'C':
           
#ifdef STEP2
             //reset points
            points.clear() ;
#endif
            
#ifdef STEP3
            //draw a black rectangle over the FBO to reset it's appearence
            mirrorFbo.begin() ; 
                ofSetColor ( 0 , 0, 0 ) ; 
                ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ; 
            mirrorFbo.end() ; 
#endif
            break ;
            
            
        case 's':
        case 'S':
            ofSaveScreen( ofToString( ofGetSystemTime() ) + ".png" ) ;
            break ; 
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
#ifdef STEP4
    bDragging = true ;
#endif
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
#ifdef STEP4
    bDragging = false ;
#endif
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}