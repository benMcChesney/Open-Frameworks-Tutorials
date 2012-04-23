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
    ofBackground( 255 , 255 , 255 ) ; 
    
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
    float dim = 35 ;    //height of sliders
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 

    red = ofRandom( 255 ) ; 
    green = ofRandom( 255 ) ; 
    blue= ofRandom( 255 ) ; 
    red2 = ofRandom( 255 ) ; 
    green2 = ofRandom( 255 ) ; 
    blue2 = ofRandom( 255 ) ; 
    
    //Here a new instance of ofxUICanvas is created, we store a refernce to it using a pointer
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
    
    //When accessing pointers you use the "->" notation
    gui->addWidgetDown(new ofxUILabel("AWESOME LABEL", OFX_UI_FONT_LARGE));    
    //Setup sliders for the first Colors
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 255.0, red, "RED" )); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 255.0, green, "GREEN" )); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 255.0, blue, "BLUE" )); 
    
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 255.0, red2, "RED2" )); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 255.0, green2, "GREEN2" )); 
    gui->addWidgetDown(new ofxUISlider(length-xInit,dim, 0.0, 255.0, blue2, "BLUE2" )); 
    
    //Add an event listener to react to changes in the ofxUI changes
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);	
    
    //Turn off the ofxUI rendering for now
    gui->disable() ; 
    gui->loadSettings("ofxUISettings.xml") ; 
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
            ofSetColor ( 15 , 15 , 15 ) ; 
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
            gui->toggleVisible(); 
            break ; 
#endif
        default:
            break;
    }
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
    if ( gui->isEnabled() == true && x < 300 ) 
        bMousePressed = false ; 
    //set our cursor color to our ofxUI slider values
    randomColor = ofColor( ofRandom( red , red2 ) , ofRandom( green , green2 ) , ofRandom( blue, blue2 ) ) ; 
#endif 
    
}

void testApp::mouseReleased(int x, int y, int button){
    bMousePressed = false ; 
}

#ifdef STEP3
///////////////////
//     STEP 3    //
///////////////////
void testApp::guiEvent(ofxUIEventArgs &e)
{
    //First the name of the widget is useful
	string name = e.widget->getName(); 
    
    if(name == "RED")
	{
        //Since all our widgets are ofxUISlider type, we know we can cast them without trouble
        //in flash you cast like:
            //var int myInt = int( 34.23 ) ;  
        //but in c++ you do 
            //int myInt = (int) 34.23 ; 
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		red = slider->getScaledValue(); 
    }
    if(name == "GREEN")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		green = slider->getScaledValue(); 
    }
    if(name == "BLUE")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		blue = slider->getScaledValue(); 
    }
    
    if(name == "RED2")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		red2 = slider->getScaledValue(); 
    }
    if(name == "GREEN2")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		green2 = slider->getScaledValue(); 
    }
    if(name == "BLUE2")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget; 
		blue2 = slider->getScaledValue(); 
    }

    
    //We can also store our settings to an external XML file ! If we want to resume our settings after the app closes
    gui->saveSettings("ofxUISettings.xml") ; 
}
#endif
