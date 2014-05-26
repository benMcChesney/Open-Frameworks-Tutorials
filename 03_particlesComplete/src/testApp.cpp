#include "testApp.h"

//#define STEP2 2
//#define STEP3 3
//--------------------------------------------------------------
void testApp::setup(){

    //Black background
    ofBackground( 0 , 0, 0 ) ; 
    ofSetVerticalSync( true ) ; 
    ofSetFrameRate( 60 ) ;
    
    //Loading our image is really simple
    bool bLoadedOK = sourceImage.loadImage( "abstractImage.jpg" ) ; 
    if ( bLoadedOK ) 
        cout << "the image loaded OK ! " << endl ; 
    else
        cout << "the image DID NOT LOAD!!! PANIC!! " << endl ; 
    
    //if the app performs slowly raise this number
    //this is the number of pixels to skip when making particles
    sampling = 2 ;
    
#ifndef STEP3
    createParticlesFromPixels( sourceImage.getPixelsRef() ) ;
#endif
    
#ifdef STEP2
    ///////////////////
    //     STEP 2    //
    ///////////////////
    //Set the spring parameters
    gui.setup("03 Particles Panel" ) ;
    gui.add( forceRadius.set( "force radius" , 45 , 0.0f , 150.0f ) ) ;
    gui.add( friction.set( "friction" , 0.85f , 0.0f , 1.0f ) ) ;
    gui.add( springFactor.set( "spring factor" , 0.12f , 0.0f , 1.0f ) ) ;
    gui.add( fboFade.set( "fbo fade" , 15.0f , 0.0f , 255.0f ) ) ;
    
    fbo.allocate ( ofGetWidth() , ofGetHeight() ) ;
    //Do this to clear the frame buffer object of "garbage" left in memory
    fbo.begin() ;
        ofClear( 0 , 0 , 0, 1 ) ;
    fbo.end() ;
    
#endif

#ifdef STEP3
#ifndef STEP4
    ///////////////////
    //     STEP 3    //
    ///////////////////
    //Initialize the video particle parameters
    video.loadMovie( "yelle_loop.mov" ) ; 
    video.play() ; 
    video.update() ; 
    
    createParticlesFromPixels( video.getPixelsRef() ) ; 
    bDrawTriangles = false ; 
#endif
#endif
        
#ifdef STEP4
    ///////////////////
    //     STEP 4    //
    ///////////////////
    //Use a live webcam instead of a video
    vidGrabber.listDevices() ;
    vidGrabber.initGrabber( 480 , 320 ) ;
    vidGrabber.videoSettings() ;
    
    createParticlesFromPixels( vidGrabber.getPixelsRef() ) ;
     bDrawTriangles = false ; 
#endif
}

void testApp::createParticlesFromPixels ( ofPixels pix )
{
    int w = pix.getWidth() ; 
    int h = pix.getHeight() ;

    unsigned char * pixels = pix.getPixels() ;
    //offsets to center the particles on screen
    int xOffset = (ofGetWidth() - w ) /2 ;
    //We're drawing the actual video too so we'll bump down where the video pixels are drawn too
    int yOffset = (ofGetHeight() - h ) * 0.825f ;
    
    //Loop through all the rows
    for ( int x = 0 ; x < w ; x+=sampling )
    {
        //Loop through all the columns
        for ( int y = 0 ; y < h ; y+=sampling )
        {
            //Pixels are stored as unsigned char ( 0 <-> 255 ) as RGB
            //If our image had transparency it would be 4 for RGBA
            int index = ( y * w + x ) * 3 ;
            ofColor color ;
            color.r = pixels[index] ;       //red pixel
            color.g = pixels[index+1] ;     //green pixel
            color.b = pixels[index+2] ;     //blue pixel
            
            particles.push_back( Particle ( ofPoint ( x + xOffset , y + yOffset ) , color ) ) ;
        }
    }

}

//--------------------------------------------------------------
void testApp::update()
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
    
    //Create an iterator to cycle through the vector
    vector<Particle>::iterator p ; 
    //A vector can be thought of as a linked list, this is another way to iterate through it
    for ( p = particles.begin() ; p != particles.end() ; p++ ) 
    {
        ratio = 1.0f ; 
        p->velocity *= friction ; 
        //reset acceleration every frame
        p->acceleration = ofPoint() ; 
        diff = mousePosition - p->position ;  
        dist = ofDist( 0 , 0 , diff.x , diff.y ) ;
        //If within the zone of interaction
        if ( dist < forceRadius )  
        {
            ratio = -1 + dist / forceRadius ; 
            //Repulsion
            if ( ofGetMousePressed() ) 
                p->acceleration -= ( diff * ratio) ;
            //Attraction
            else
                p->acceleration += ( diff * ratio ) ; 
        }
        
        //Easy OF helper utility to see if a keyboard key is currently pressed
        if ( ofGetKeyPressed() ) 
        {
            //Overloaded operators allow us to create custom operators for classes
            //making vector math way easier than in AS3 !
            //Move back to the original position
            ofPoint diff = p->spawnPoint - p->position ; 
            p->acceleration += ( springFactor * diff ) ; 
        }
        
        p->velocity += p->acceleration * ratio ; 
        p->position += p->velocity ; 
    }
#endif
    
#ifdef STEP3
#ifndef STEP4
    ///////////////////
    //     STEP 3    //
    ///////////////////
    // We have to manually update the video ! It doesn't know to update itself
    video.update() ; 
    updateParticlePixels( video.getPixelsRef() ) ;
#endif
#endif
    
#ifdef STEP4
    ///////////////////
    //     STEP 4    //
    ///////////////////
    // We have to manually update the video ! It doesn't know to update itself
    vidGrabber.update() ;
    //if ( vidGrabber.isFrameNew() )
        updateParticlePixels( vidGrabber.getPixelsRef() ) ;
#endif
   
}



//--------------------------------------------------------------
void testApp::draw()
{

     ofSetColor( ofColor::white )  ;
#ifdef STEP3
#ifndef STEP4
    video.draw ( ofGetWidth() / 2 + video.getWidth() / -2 , 25 ) ;
#endif
#endif
    
#ifdef STEP4
    vidGrabber.draw( ofGetWidth() / 2 + vidGrabber.getWidth() / -2 , 25) ;
#endif
    
    //Begin the openGL Drawing Mode
    //this will draw a small point at each vertex we define
     ofEnableAlphaBlending() ; 
    
#ifdef STEP2
    ///////////////////
    //     STEP 2    //
    ///////////////////
    fbo.begin() ;    
        //to get the trail effect we draw a very faint rectangle the size of the screen and the color of the background
        ofSetColor( 0 , 0 , 0, fboFade ) ;
        ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ;  
#endif
    
#ifdef STEP3
    
        ///////////////////
        //     STEP 3    //
        ///////////////////
        if ( bDrawTriangles == true ) 
            glBegin( GL_TRIANGLES );
    
            //There are lots of other fun OpenGL draw modes ! Here's a few to play with
            //glBegin( GL_LINE_LOOP ) ; 
            //glBegin( GL_LINES ) ; 
            //glBegin( GL_QUADS ) ; 
           
        else
#endif
        //Our particles start out as small 1 x 1 pixel points
        glBegin(GL_POINTS); 
        
        //Create an iterator to cycle through the vector
        for ( int i = 0 ; i < particles.size() ; i++ )
        {
            ofSetColor( particles[i].color ,  255 ) ; 
            glVertex3f( particles[i].position.x , particles[i].position.y , 0 );
        }
        
        glEnd();

#ifdef STEP2
    ///////////////////
    //     STEP 2    //
    ///////////////////
    fbo.end() ; 
    ofSetColor ( 255 , 255 , 255 ) ; 
    fbo.draw( 0 , 0 ) ;
    
    gui.draw( ) ;
#endif
    
 
}

#ifdef STEP3
///////////////////
//     STEP 3    //
///////////////////
void testApp::updateParticlePixels( ofPixels pix )
{
    //Populate particles for the first time 
    //store width and height for optimization and clarity
    int w = pix.getWidth()  ;
    int h = pix.getHeight() ;
    
    
    //offsets to center the particles on screen
    int xOffset = (ofGetWidth() - w ) /2 ; 
    int yOffset = (ofGetHeight() - h ) /2 ;
    
    unsigned char * pixels = pix.getPixels() ; 
    
    int particleCount = 0 ; 
    
    //Loop through all the rows
    for ( int x = 0 ; x < w ; x+=sampling ) 
    {
        //Loop through all the columns
        for ( int y = 0 ; y < h ; y+=sampling ) 
        {
            //Pixels are stored as unsigned char ( 0 <-> 255 ) as RGB
            //If our image had transparency it would be 4 for RGBA
            int index = ( y * w + x ) * 3 ;
            int pIndex = ( y * w + x ) ; 
            ofColor color ; 
            color.r = pixels[index] ;       //red pixel
            color.g = pixels[index+1] ;     //green pixel
            color.b = pixels[index+2] ;     //blue pixel
            
            particleCount++ ; 
            particles[particleCount].color = color ; 
        }
    }
}
#endif


//--------------------------------------------------------------
void testApp::keyPressed(int key){

#ifdef STEP3
    ///////////////////
    //     STEP 3    //
    ///////////////////
    //Toggle drawing triangles
    if ( key == 't' || key == 'T' )
        bDrawTriangles = !bDrawTriangles ; 
#endif 
}
