#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //Load the external files for our shader program.
    //Vertex shaders handle vertices and generating geometry
    //Fragment shaders focus on manipulating rasterized pixels 
    shader.load( "basic.vert" , "HexTunnel.frag" ) ;
    
    fbo.allocate( ofGetWidth() , ofGetHeight() ) ;
    fbo.begin() ;
        ofClear( 0 , 0 , 0 , 1 ) ;
    fbo.end() ;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{
    
    ofSetColor(255, 255, 255);
    //Try adding new variables and see how it effects the visuals
    shader.begin() ;
    shader.setUniform1f("time", ofGetElapsedTimef() ) ;
    shader.setUniform2f("resolution", ofGetWidth()  , ofGetHeight() );
    
    ofSetColor( 255 ) ;
    ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ;
    shader.end() ;

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
