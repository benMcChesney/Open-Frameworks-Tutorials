//
//  CustomClass.h
//  emptyExample
//
//  Created by Ben McChesney on 3/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//  This is just an example class to label and show what each individual part is

// the "#" at the beginning of a line indicates a preprocessor instruction
// these are given priority to the normal compilation 
// can do many things including help to avoid duplicate compilations as well as setting targets for the OS
#ifndef emptyExample_CustomClass_h
#define emptyExample_CustomClass_h

// OR do
//#pragma once

//similar to import statements these tell the compiler what files to include
#include "ofMain.h"

//Comment this line out to change 
#define superCoolNumber 4 

//class ClassName : scope inheritedClass
class CustomClass : public ofBaseApp
{
    public :
        CustomClass() { }

        float number ;              //~7 digit number
        int integer ;               //-2147483648 to 2147483647
        unsigned char uChar ;       // 0 - 255 
        string text ;               // "Hello World!" 
    
        vector<float> floats ;      //dynamically sized container, in this case for objects of a "float" type
    
     
        //method that returns a void object
        //in c++ the return type is placed in front of the method name
        void setup ( ) 
        {
            //this is the constructor
            #ifdef superCoolNumber
                        
                        //cout allows you to output to the IDEs log, and sometimes the system log
                        cout << "SuperCoolNumber is defined! " << endl ; 
                        
            #endif
                        
            #ifndef superCoolNumber
                        
                        float negative1 = -1.000001f ; 
                        cout << "Oh no! The superCoolNumber is *NOT* defined ! " << negative1 << endl ; 
                        
            #endif
        }
                                    
    
        
            
//When you create a class, be sure to add a semicolon at the end of the declaration !
//otherwise the compiler won't know where this class start and the next one begins
};


#endif
