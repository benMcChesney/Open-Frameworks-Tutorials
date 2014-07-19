#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    //Set our background to black
    ofBackground( 0 , 0 , 0 ) ; 
    ofSetVerticalSync( true ) ; 
}

//--------------------------------------------------------------
void testApp::update(){
   
    
}

//--------------------------------------------------------------
void testApp::draw()
{
    //Quick way to get a nice cycling number between 0 and 1.
    //sin ( ofGetElapsedTimef() ) cycles between -1 and 1 .
    float amount = ( sin ( ofGetElapsedTimef() ) + 1.0f ) / 2.0f ;
    
    
    //Translate
    ofDrawBitmapStringHighlight("Translate", 25 , 20 ) ;
    ofPushMatrix();
        //Move it away from the edge a bit
        ofTranslate( 25 , 125 ) ;
        ofSetColor( ofColor::red ) ;
        ofCircle( 0 , 0 , 15 ) ;
    
        ofTranslate( 100 * amount , 100 * amount ) ;
        ofSetColor( 0 , 255 , 0 ) ;
        ofCircle( 0 , 0 , 15 ) ;
    
        ofTranslate( 100 * amount , 100 * amount ) ;
        ofSetHexColor( 0x0000FF ) ;
        ofCircle( 0 , 0 , 15 ) ;
    
    ofPopMatrix() ;
    
    //Rotation
    ofDrawBitmapStringHighlight("Rotate", 350 , 20 ) ;
    ofPushMatrix() ;
        ofTranslate( 350 , 125 ) ;
        int numItems = 12 ;
        float anglePer = 360.0f / (float) numItems ;
        
        for ( int i = 0 ; i < numItems ; i++ )
        {
            ofSetColor( ofColor::fromHsb( i * 35.0f , 255.0f , 255.0f ) ) ;
            ofPushMatrix() ;
                ofRotate( anglePer * (float)i * amount ) ;
                ofRect( -10 , 0 , 20 , 60 ) ; 
            ofPopMatrix() ;
        }
    ofPopMatrix() ;
    
    //Scale
    ofPushMatrix() ;
        ofDrawBitmapStringHighlight("Scale", 550 , 20 ) ;
        ofTranslate( 550 , 125 ) ;
        int triSize = 75 ;
        ofSetColor( ofColor::red ) ;
        ofTriangle( -triSize , triSize , 0 , -triSize , triSize , triSize ) ;
    
        //Make everything half as big
        ofScale( 0.5 * amount , 0.5 * amount ) ;
        ofSetColor( ofColor::green ) ;
        ofTriangle( -triSize , triSize , 0 , -triSize , triSize , triSize ) ;
    
        //Shrink it down again
        ofScale( 0.5 * amount , 0.5 * amount ) ;
        ofSetColor( ofColor::magenta ) ;
        ofTriangle( -triSize , triSize , 0 , -triSize , triSize , triSize ) ;
    
    ofPopMatrix() ;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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
