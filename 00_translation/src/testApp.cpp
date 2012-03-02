#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    //Set our background to black
    ofBackground( 0 , 0 , 0 ) ; 
    
    rotation = 0.0f ; 
    ofSetFrameRate( 60 ) ; 
}

//--------------------------------------------------------------
void testApp::update(){
    rotation += 0.25f ; 
    
}

//--------------------------------------------------------------
void testApp::draw()
{
    //Three squares will de drawn using the transformation stack
    //the processing.org site has a very good explanation : http://processing.org/learning/transform2d/
    //in OF you change the coordinate spaces translation, rotation, and scale
    //You can also think of it as there being a global registration point from a flash perspective

    //ofPushMatrix() marks the beginning of adding a "stack" to be actively changed
    
    ofTranslate( 50 , 350 , 0 ) ;    //lets move everything a little bit from the edge
    
    //Set the global color tint to red
    ofSetColor( 255 , 0 , 0 ) ; 
    ofPushMatrix() ;
        drawRegistrationPoint( ) ; 
        ofTranslate( 100 , 0 , 0 ) ;      //moving the x 100 pixels , the y 50 pixels and the z 0 pixels
        ofLine ( -100 , 0 , 0 , 0 ) ;    //draw a line back to origin
        drawRegistrationPoint( ) ; 
        ofRect(  0 , 0 , 100 , 100 ) ;       //draw a rectangle with the origin in the middle
    ofPopMatrix() ;
    
    
    ofTranslate( 350 , 0 , 0 ) ;            //Move right 250 pixels for some more space

    //turn the global color to green
    ofSetColor( 0 , 255 , 0 ) ; 
    ofPushMatrix() ;
        drawRegistrationPoint( ) ; 
        ofTranslate( 100 , 0 ) ; 
        ofLine ( 0 , 0 , -100 , 0 ) ;      //draw a line to the origin point
        drawRegistrationPoint( ) ; 
        ofRotateZ( rotation ) ;                   //Rotate along the zAxis in degrees ( 2D  rotation ) 
        ofRect( 0 , 0 , 100 , 100 ) ; 
    ofPopMatrix() ; 
    
    ofTranslate( 350 , 0 , 0 ) ;            //Move right 250 pixels for some more space
    
    //Last square is blue
    ofSetColor( 0 , 0 , 255 ) ; 
    ofPushMatrix() ;
            drawRegistrationPoint( ) ; 
            ofRotateZ( rotation ) ;               //if we rotate the coordinate space first, we get a different result
            ofTranslate( 100, 0 ) ;         //Only translate in the X direction, then rotate it
            ofRect( 0 , 0 , 100 , 100 ) ;
            drawRegistrationPoint( ) ; 
            ofLine ( 0 , 0 , -100 , 0 ) ;   //draw a line back to origin

    ofPopMatrix() ; 
}

void testApp::drawRegistrationPoint( float x , float y )
{
    //Working locally makes this a lot easier
    ofPushMatrix() ; 
        ofRect( -2 , -10 , 4 , 20 ) ; 
        ofRect( -10 , -2 , 20 , 4 ) ; 
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
