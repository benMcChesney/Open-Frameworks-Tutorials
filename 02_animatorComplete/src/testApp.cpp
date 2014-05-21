#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ///////////////////
    //     STEP 1    //
    ///////////////////
    //initialize values
    maxFrames = 30 ; 
    currentFrame = 0 ; 
    bMousePressed = false ; 
    
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
    ofBackground( 0 , 0, 0 ) ; 
    
#ifdef STEP2
    ///////////////////
    //     STEP 2    //
    ///////////////////
    lastMouse = ofPoint ( 0 , 0 ) ; 
#endif
    
#ifdef STEP3
    ///////////////////
    //     STEP 3    //
    ///////////////////
    
    //Let's create our GUI panel
    gui.setup("panel");
    
    //There are many different ways to generate an ofColor
    //and it's easy to convert from HSB to RGB to HEX etc,,
    color1 = ofColor::fromHex(0xFF0000) ;
    color2 = ofColor::fromHsb( ofRandom( 255 ) , 255.0f, 255.0f ) ;
    
    color1.addListener(this, &testApp::color1Changed );
    color2.addListener(this, &testApp::color2Changed );

    //Sliders are added with the following paramters
    //gui.add( ofParameter<?>.set( string label , startValue , minValue , maxValue );
    gui.add(color1.set("color1",color1,ofColor(0,0),ofColor(255,255)));
    gui.add(color2.set("color2",color2,ofColor(0,0),ofColor(255,255)));
    
   
    
    bShowGui = true ;
#endif
}

//--------------------------------------------------------------
void testApp::update(){

    ///////////////////
    //     STEP 1    //
    ///////////////////
    currentFrame++ ; 
    
    if ( currentFrame == maxFrames ) 
        currentFrame = 0 ; 
 

    ofSetWindowTitle( ofToString( ofGetFrameRate() ) ) ; 
}

//--------------------------------------------------------------
void testApp::draw(){

        ofEnableAlphaBlending() ; 
#ifdef STEP2
        ///////////////////
        //     STEP 2    //
        ///////////////////
        //record the current mouse position
        ofPoint mousePos = ofPoint( mouseX , mouseY ) ; 
        float mouseDistance = ofDist( mousePos.x , mousePos.y , lastMouse.x , lastMouse.y ) + 15.0f ;    
    
        //Simple if-else to limit the size of the radius
        if ( mouseDistance > 35.0f ) 
            mouseDistance = 35.0f ; 
#endif
    
    
        ///////////////////
        //     STEP 1    //
        ///////////////////
        ofSetColor( 255 , 255 , 255 ) ; 
        //Begin recording the FBO
        frames[currentFrame].begin() ;         
    
        //redraw the fbo into itself
        frames[currentFrame].draw(0 , 0 ) ; 
    
        if ( bMousePressed == true ) 
        {
#ifndef STEP2
            ofSetColor ( 215 , 215 , 215 ) ; 
            ofCircle( mouseX , mouseY , 14.0f ) ; 
#endif
            
#ifdef STEP2
            ///////////////////
            //     STEP 2    //
            ///////////////////
            ofSetColor ( randomColor ) ;           
            ofCircle( mouseX , mouseY , mouseDistance ) ; 
#endif
        }
        
        //stop drawing into FBO
        frames[currentFrame].end() ; 
        
        //Draw the FBO with full color
        ofSetColor ( 255 , 255 , 255 ) ; 
        frames[currentFrame].draw(0 , 0 ) ;
    
#ifdef STEP2
        ///////////////////
        //     STEP 2    //
        ///////////////////
        lastMouse = mousePos ; 
#endif
    if ( bShowGui )
        gui.draw()  ; 
    
}	

void testApp::resetAllFbos()
{
    //Easy way to reset each FBO is to draw it with a full rectangle
    for ( int i = 0; i < maxFrames ; i++ ) 
    {
        frames[i].begin() ; 
        ofSetColor( 0 , 0 , 0 ) ; 
        ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ;
        frames[i].end() ;
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{    
    //This function listens for keyboardEvents
    // Maps the "R" key to clearing all the FBOs
    switch ( key) 
    {
        case 'r' :
        case 'R' :
            resetAllFbos() ; 
            break;
            
#ifdef STEP3
        case 'g':
        case 'G':
            bShowGui = !bShowGui ; 
            break ; 
#endif
        default:
            break;
    }
}


void testApp::exit( )
{
    //Always a good idea to remove listeners on exit and do some cleanup
    color1.removeListener(this, &testApp::color1Changed );
    color2.removeListener(this, &testApp::color2Changed );
}

void testApp::color1Changed(ofColor & color)
{
    
}

void testApp::color2Changed(ofColor & color)
{
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    bMousePressed = true ; 
#ifdef STEP2
    ///////////////////
    //     STEP 2    //
    ///////////////////
    //create a random color
    randomColor = ofColor ( ofRandom ( 255 ) , ofRandom ( 255 ) , ofRandom( 255 ) ) ; 
#endif
    
#ifdef STEP3
    ///////////////////
    //     STEP 3    //
    ///////////////////
    //If gui is open and we are clicking over it we dont want to be recording that into the FBO
    //if ( gui->isEnabled() == true && x < 300 )

    //set our cursor color to our ofxUI slider values
    randomColor = ofColor( ofRandom( color1->r , color2->r ) ,
                           ofRandom( color1->g , color2->g ) ,
                           ofRandom( color1->b , color2->b ) ) ;
#endif 
    
}

void testApp::mouseReleased(int x, int y, int button){
    bMousePressed = false ; 
}
