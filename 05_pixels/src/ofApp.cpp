#include "ofApp.h"

//#define STEP2 2
//#define STEP3 3
//--------------------------------------------------------------
void ofApp::setup(){

    //Black background
    ofBackground( 0 , 0, 0 ) ;
    
    //Set this to false so we can "build" on the canvas
    ofSetBackgroundAuto( false ) ;
    ofSetVerticalSync( true ) ; 
    ofSetFrameRate( 60 ) ;
    
    //Loading our image is really simple
    bool bLoadedOK = sourceImage.loadImage( "abstractImage.jpg" ) ; 
    if ( bLoadedOK ) 
        ofLogNotice() << "the image loaded OK ! " << endl ;
    else
        ofLogError() << "the image DID NOT LOAD!!! PANIC!! " << endl ;
    
    numSamples = 15 ;
    circleRadiusMin = 1.0f ;
    circleRadiusMax = 4.0f ; 
    
#ifdef STEP2
    //Setup the GUI
    gui.setup("05 Pixels Panel" ) ;
    gui.add( numSamples.set( "num samples" , 20.0f , 1.0f , 5000.0f ) ) ;
    gui.add( circleRadiusMin.set( "circle min radius" , 1.0f , 1.0f , 20.0f ) ) ;
    gui.add( circleRadiusMax.set( "circle max radius" , 1.0f , 1.0f , 20.0f ) ) ;
    
#ifndef STEP3
    //Load the the movie located in the /data/ folder
    video.loadMovie( "yelle_loop.mov" ) ;
    video.play() ;
#endif
#endif

#ifdef STEP3

    //Initialize the video particle parameters
    vidGrabber.listDevices() ;
    vidGrabber.initGrabber( 480 , 320 ) ;
    vidGrabber.videoSettings() ;
#endif
        

}

//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle( ofToString ( ofGetFrameRate() ) ) ;
    
#ifdef STEP2
#ifndef STEP3
    ///////////////////
    //     STEP 2    //
    ///////////////////
    // We have to manually update the video ! It doesn't know to update itself
    video.update() ; 
#endif
#endif
    
#ifdef STEP3
    ///////////////////
    //     STEP 3    //
    ///////////////////
    // We have to manually update the video grabber ! It doesn't know to update itself
    vidGrabber.update() ;
#endif
   
}



//--------------------------------------------------------------
void ofApp::draw()
{
    ofEnableAlphaBlending() ;
    ofSetColor( ofColor::white )  ;
    
        
    ofPixels pix ;
    pix = sourceImage.getPixelsRef() ;
    sourceImage.draw( ofGetWidth() / 2 + pix.getWidth() / -2 , 25  ) ;

#ifdef STEP2
#ifndef STEP3
    pix = video.getPixelsRef() ;
    video.draw( ofGetWidth() / 2 + pix.getWidth() / -2 , 25  ) ;
#endif
#endif


#ifdef STEP3
    pix = vidGrabber.getPixelsRef() ;
    vidGrabber.draw( ofGetWidth() / 2 + pix.getWidth() / -2 , 25) ;
#endif
    
    ofPushStyle() ; 
    ofPushMatrix() ;
    ofTranslate( ofGetWidth() / 2 + pix.getWidth() / -2 , 50 + pix.getHeight() ) ;
    for ( int i = 0 ; i < numSamples ; i++ )
    {
        int xIndex = ofRandom( 0 , sourceImage.getWidth() ) ;
        int yIndex = ofRandom( 0 , sourceImage.getHeight() ) ;
        
        ofColor color = pix.getColor( xIndex , yIndex ) ;
        
#ifndef STEP4
        float radius = ofRandom ( circleRadiusMin , circleRadiusMax ) ;
        ofSetColor( color ) ;
        ofCircle( xIndex , yIndex , radius ) ;
#endif
#ifdef STEP4
        if ( i != 0 )
        {
            float distanceX = ofRandom ( circleRadiusMin , circleRadiusMax ) ;
            float distanceY = ofRandom ( circleRadiusMin , circleRadiusMax ) ;
            ofSetLineWidth( 2.0f ) ;
            ofSetColor( color ) ;
            ofLine( xIndex , yIndex , xIndex + distanceX , yIndex + distanceY ) ;
        }
        
#endif
    }
    ofPopMatrix() ;
    ofPopStyle() ; 
    
#ifdef STEP2
    gui.draw( ) ;
#endif
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    stringstream filePath ;
    filePath << ofGetYear() << "_" << ofGetMonth() << "_" << ofGetDay() << "_" ;
    filePath << ofGetHours() << ":"<< ofGetMinutes() << ":" << ofGetSeconds() << ".png" ;
    
    switch ( key )
    {
        case 's':
        case 'S':
            ofSaveScreen( filePath.str() ) ; 
            break ;
    }
}
