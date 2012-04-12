#include "testApp.h"

//#define STEP2 2
//#define STEP3 3
//--------------------------------------------------------------
void testApp::setup(){

    //Black background
    ofBackground( 0 , 0, 0 ) ; 
    //Prevent Screen Tearing
    ofSetVerticalSync( true ) ; 
    ofSetFrameRate( 60 ) ; 

    //Calculate the total number
    //numParticles = ( sourceImage.width * sourceImage.height ) / sampling ; 
    
    //Set the spring parameters
    forceRadius = 45 ; 
    friction = 0.85 ; 
    springFactor = 0.12 ; 
    
    //Loading our image is really simple
    bool bLoadedOK = sourceImage.loadImage( "abstractImage.jpg" ) ; 
    if ( bLoadedOK ) 
        cout << "the image loaded OK ! " << endl ; 
    else
        cout << "the image DID NOT LOAD!!! PANIC!! " << endl ; 
    
    //if the app performs slowly raise this number
    //this is the number of pixels to skip when making particles
    sampling = 2 ;
    
    //Retrieve the pixels from the loaded image
    //An Image is, at it's core, an ordered collection of unsigned chars ( 0 - 255 ) 
    //unsigned char * pixels = sourceImage.getPixels() ;
    
    //Populate particles for the first time 
    //store width and height for optimization and clarity
    int w = sourceImage.width ; 
    int h = sourceImage.height ;
    
    
    //offsets to center the particles on screen
    int xOffset = ( ofGetWidth() - w ) / 2 ; 
    int yOffset = ( ofGetHeight() - h ) / 2 ;
    
    /*
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
    */
    //2
    fbo.allocate ( ofGetWidth() , ofGetHeight() ) ; 
    ofClear( 0 , 0 , 0, 1 ) ; 

    //3 Set the particles to a video !
    video.loadMovie( "yelle_loop.mov" ) ; 
    video.play() ; 
    video.update() ; 
    
    w = video.getWidth() ; 
    h = video.getHeight() ;

    unsigned char * pixels = video.getPixels() ; 
    
    //offsets to center the particles on screen
    xOffset = (ofGetWidth() - w ) /2 ; 
    yOffset = (ofGetHeight() - h ) * 0.825f ;
    
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

    bDrawTriangles = false ; 
}

//--------------------------------------------------------------
void testApp::update()
{
  
    ofSetWindowTitle( ofToString ( ofGetFrameRate() ) ) ; 
    

    //2
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
        
        if ( ofGetKeyPressed() ) 
        {
            //Move back to the original position
            p->acceleration.x += springFactor * (p->spawnPoint.x - p->position.x);
            p->acceleration.y += springFactor * (p->spawnPoint.y - p->position.y) ;
        }
        
        p->velocity += p->acceleration * ratio ; 
        p->position += p->velocity ; 
    }
    
    //3
    video.update() ; 
    updateParticlePixels() ; 
    
}



//--------------------------------------------------------------
void testApp::draw()
{
    ofSetColor(255, 255, 255) ; 
    video.draw ( ofGetWidth() / 2 + video.getWidth() / -2 , 25 ) ; 
    //Begin the openGL Drawing Mode
    //this will draw a small point at each vertex we define
     ofEnableAlphaBlending() ; 
    
    //2
    fbo.begin() ;    
        ofSetColor( 0 , 0 , 0, 6 ) ; 
        ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ;  
    
        if ( bDrawTriangles == true ) 
            glBegin(GL_TRIANGLES);
        else    
            glBegin(GL_POINTS); 
        
        //Create an iterator to cycle through the vector
        std::vector<Particle>::iterator p ; 
        for ( p = particles.begin() ; p != particles.end() ; p++ )
        {
            ofSetColor ( p->color.r , p->color.g , p->color.b , 255 ) ; 
            glVertex3f(p->position.x, p->position.y , 0 );
        }
        
        glEnd();
    
    //2
    fbo.end() ; 
    ofSetColor ( 255 , 255 , 255 ) ; 
    fbo.draw( 0 , 0 ) ; 
}


void testApp::updateParticlePixels() 
{
    //Populate particles for the first time 
    //store width and height for optimization and clarity
    int w = video.width  ; 
    int h = video.height ;
    
    
    //offsets to center the particles on screen
    int xOffset = (ofGetWidth() - w ) /2 ; 
    int yOffset = (ofGetHeight() - h ) /2 ;
    
    unsigned char * pixels = video.getPixels() ;
    
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
//            particles.push_back( Particle ( ofPoint ( x + xOffset , y + yOffset ) , color ) ) ;  
        }
    }
    
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

    //Toggle drawing triangles
    if ( key == 't' || key == 'T' )
        bDrawTriangles = !bDrawTriangles ; 
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