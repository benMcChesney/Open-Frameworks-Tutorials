#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //Black background
    ofBackground( 0 , 0, 0 ) ; 
    ofSetVerticalSync( true ) ; 
    ofSetFrameRate( 60 ) ;
    maxParticles = 500 ;
    particleLife = 90 ;
    friction = 0.99f ;
    spawnRadius = 15.0f ;
    particleSize = 4.0f ;
    maxPerSpawn = 10.0f ;
    maxForce = 6.0f ;    
    
#ifdef STEP2
    ///////////////////
    //     STEP 2    //
    ///////////////////
    gui.setup("03 Particles Panel" ) ;
    //when setting up a slider it's '.set( "label" , value , minValue , maxValue )'
    gui.add( forceRadius.set( "force radius" , 45 , 0.0f , 150.0f ) ) ;
    gui.add( friction.set( "friction" , 0.85f , 0.0f , 1.0f ) ) ;
    gui.add( particleSize.set( "particle size" , 2.0f , 1.0f , 20.0f ) ) ;
    gui.add( maxPerSpawn.set( "max per spawn" , 2.0f , 1.0f , 70.0f ) ) ;
    gui.add( maxParticles.set( "max particles" , 500.0f , 100.0f , 100000.0f ) ) ;
    gui.add( particleLife.set( "particle life" , 90.0f , 10.0f , 400.0f ) ) ;
    gui.add( maxForce.set( "max force" , 2.0f , 0.001f , 30.0f )) ;
    gui.add( spawnRadius.set( "spawn radius" , 25.0f , 0.0f , 300.0f ) ) ; 
    forceRadius = 45.0f ;

#endif
        
#ifdef STEP3
     bDrawTriangles = false ;
    gui.add( bDrawTriangles.set( "draw triangles" , false ) ) ;
    gui.add( bDrawTriangleStrip.set( "draw triangle strip" , false ) ) ;
    gui.add( bDrawLines.set( "draw lines" , false ) ) ;
    gui.add( bDrawLineLoop.set( "draw line loops" , false ) ) ;
    gui.add( bDrawQuads.set( "draw quads" , false ) ) ;
    gui.add( bDrawPoints.set( "draw points" , true ) ) ;

    gui.add( fboFade.set( "fbo fade" , 15.0f , 0.0f , 255.0f ) ) ;
    fbo.allocate ( ofGetWidth() , ofGetHeight() , GL_RGBA32F_ARB ) ;
            //Do this to clear the frame buffer object of "garbage" left in memory
    fbo.begin() ;
        ofClear( 0 , 0 , 0, 1 ) ;
    fbo.end() ;
    
#endif
    
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle( ofToString ( ofGetFrameRate() ) ) ; 
    
    
#ifdef STEP2
    ///////////////////
    //     STEP 2    //
    ///////////////////
    ofPoint diff ;          //Difference between particle and mouse
    float dist ;            //distance from particle to mouse ( as the crow flies ) 
    float ratio ;           //Ratio of how strong the effect is = 1 + (-dist/maxDistance) ;
    const ofPoint mousePosition = ofPoint( mouseX , mouseY ) ; //Allocate and retrieve mouse values once.
#endif 
    
    //Create an iterator to cycle through the vector
    vector<Particle>::iterator p ; 
    //A vector can be thought of as a linked list, this is another way to iterate through it
    for ( p = particles.begin() ; p != particles.end() ; p++ ) 
    {
        p->update() ; 
        //remove "dead" particles
        if ( p->life < 0 )
            particles.erase( p ) ;
    
#ifndef STEP2
        //vector math is much easier when you can apply operators easily to them
        p->velocity *= friction ;
        p->position += p->velocity ;
#endif
        
#ifdef STEP2
        p->acceleration = ofPoint() ;
        diff = mousePosition - p->position ;
        diff *= .1 ; 
        dist = ofDist( 0 , 0 , diff.x , diff.y ) ;
        //If within the zone of interaction
        if ( dist < forceRadius )  
        {
            //Repulsion
            if ( !ofGetMousePressed() )
                p->acceleration -= ( diff ) ;
            
            //Attraction
            else
                p->acceleration += ( diff ) ;
        }
        
        //limit is a useful function to make sure vector values don't exceed ranges
        p->velocity.limit( maxForce ) ; 
        p->velocity += p->acceleration ;
        p->velocity *= friction ;
        p->position += p->velocity ;
#endif
        
}
    
    //If any particles were removed we want to try and stay near the top
    int numSpawnedThisWave = 0 ;
    while ( particles.size() < maxParticles )
    {
        if ( numSpawnedThisWave > maxPerSpawn )
            break ;
        
        float xOffset = ofRandom( -spawnRadius, spawnRadius ) ;
        float yOffset = ofRandom( -spawnRadius, spawnRadius ) ; 
        ofColor color = ofColor::fromHsb( ofRandom( 255 ) , 255 , 255 ) ;
        particles.push_back( Particle ( ofPoint (  mouseX + xOffset , mouseY + yOffset  ) , color , particleLife ) ) ;
        (*particles.end()).velocity = ofPoint ( ofRandom( -5 , 5 ) , ofRandom( -5 ,5 ) ) ;
        
        numSpawnedThisWave++ ; 
    }
}



//--------------------------------------------------------------
void ofApp::draw()
{
    //stringstreams are useful c++ tool to build strings
    stringstream ss ;
    ss << "# particles " << particles.size() ; 
    ofDrawBitmapStringHighlight( ss.str() , 15 , ofGetHeight() - 25 ) ;
    
    //Begin the openGL Drawing Mode
    //this will draw a small point at each vertex we define
     ofEnableAlphaBlending() ; 
    
#ifdef STEP3
    
    ///////////////////
    //     STEP 3    //
    ///////////////////
    fbo.begin() ;
    //to get the trail effect we draw a very faint rectangle the size of the screen and the color of the background
    ofSetColor( 0 , 0 , 0, fboFade ) ;
    ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ;

    if ( bDrawTriangles )
        glBegin( GL_TRIANGLES );
    
    if ( bDrawLines )
        glBegin( GL_LINES );
    
    if ( bDrawTriangleStrip )
        glBegin( GL_TRIANGLE_STRIP );
    
    if ( bDrawLineLoop )
        glBegin( GL_LINE_LOOP );
    
    if ( bDrawQuads )
        glBegin( GL_QUADS );
    
    if ( bDrawPoints )
        glBegin( GL_POINTS );

#endif
    
    //Our particles start out as small 1 x 1 pixel points
    glPointSize( particleSize ) ;
#ifndef STEP3
    glBegin(GL_POINTS);
#endif
    
    //Create an iterator to cycle through the vector
    for ( auto p = particles.begin() ; p != particles.end() ; p++ )
    {
        ofSetColor( (*p).color ,  255 ) ;
        glVertex3f( (*p).position.x , (*p).position.y , 0 );
    }
    
    glEnd();

#ifdef STEP3
    ///////////////////
    //     STEP 2    //
    ///////////////////
    fbo.end() ; 
    ofSetColor ( 255 , 255 , 255 ) ; 
    fbo.draw( 0 , 0 ) ;
#endif
    
#ifdef STEP2
    gui.draw( ) ;
#endif
 
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){


}
