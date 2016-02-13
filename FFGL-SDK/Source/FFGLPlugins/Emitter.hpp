//
//  Emitter.h
//  FFGLPlugins
//
//  Created by Mary Scahill on 2/10/16.
//
//

#ifndef Emitter_h
#define Emitter_h

#include "Vec2.hpp"
#include "Colour4f.hpp"


class Emitter
{
protected:
    float emitterID;
    
    
    Vec2<float> eLocation;  // The current location of the emitter
    Vec2<float> eSpeed;     // The current speed of the emitter
    
    Colour4f colour;       // The colour of the particle
    
    int size;              // The size of the particle i.e. how big the pointsprite will be drawn
    
    int framesToLive;      // Number of frames before the particle is destroyed
    
public:
    // ---------- Static particle parameters -----------
    
    static const int FRAMES_TO_LIVE    = 100;
    
    static const int MAX_EMITTERS = 3;
    
    static const int MIN_PARTICLE_SIZE = 2;
    static const int MAX_PARTICLE_SIZE = 100;
    
    static const float X_SPEED_RANGE   = 3.0f;
    static const float Y_SPEED_RANGE   = 8.0f;
    
//    static const float GRAVITY         = 0.2f;
    
    // ---------- Constructors -------------------------
    
    
    // Constructor that takes an initial position as a Vec2
    Emitter(Vec2<float> initialLocation)
    {
        eLocation = initialLocation; // Set the emitter location
        
        initialise();
    }
    
    
    // Constructor that takes an initial position as values (instead of a Vec2)
    
    Emitter(int xLocation, int yLocation)
    {
        eLocation.set(xLocation, yLocation);
        
        eSpeed.set(Utils::randRange(-X_SPEED_RANGE, X_SPEED_RANGE), Utils::randRange(0.0f, Y_SPEED_RANGE) );
        
        initialise();
    }
    
    // Constructor that takes a position and a speed
    Emitter(Vec2<float> initialLocation, Vec2<float> initialSpeed)
    {
        eLocation = initialLocation;
        eSpeed    = initialSpeed;
        
        initialise();
    }
    
    
    // ---------- Helper Methods and Getters & Setters -------------------------
    
    // Method to setup other properties of the emitter
    void initialise()
    {
        // Set the initial framesToLive count (this counts down to 0 - at 0 the particle is removed)
        framesToLive = FRAMES_TO_LIVE;
        
        // Set an entirely random colour (including random alpha value)
        colour.fullyRandomise();
        
        // Randomise the size of the particle
        size = Utils::randRange(MIN_PARTICLE_SIZE, MAX_PARTICLE_SIZE);
        
        std::vector<Emitter> e;

        
    }
    
    
    void updateAndDraw(Vec2<float> eLocation)
    {
     
//        if (emitterID.size() < MAX_EMITTERS)
//        {
//            Particle2D temp(windowMidX, windowMidY);
//            emitterID.push_back(temp);
//            
//        }
        
        // Clear the screen and depth buffer
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Reset the modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // Enable 2D textures and point sprites
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_POINT_SPRITE);
        
        
        
        
//        // Iterate over all emitters in the vector
//        vector<int>::iterator i;
//        for (i = p.begin(); i != p.end(); ++i)
//        {
//            // If the particle time to live is more than zero...
//            if (i->getFramesToLive() > 0)
//            {
//                // ...update the particle position position and draw it.
//                i->update();
//                i->draw();
//            }
//            else // // If it's time to destroy the particle...
//            {
//                // ...then remove it from the vector...
//                // NOTE: Calling erase(SOME-ELEMENT) removes the element from the vector and
//                // returns the next element in the vector, even if it's the "one-past-the-last-element"
//                // i.e. "end()" element which signifies the end of the vector.
//                //
//                // It's VERY important to assign this next element back to the iterator
//                // because we're modyfing the length of the vector inside a loop which goes
//                // until it gets to the end of a vector --- which, ya know, we're actually changing
//                // as we go! If you don't assign the next element back to the iterator when calling
//                // erase - don't be surprised when your code bombs out with a segfault, k? ;-D
//                i = p.erase(i);
//                
//                // ...and then add a new particle to replace it!
//                
////                Particle2D tempParticle(windowMidX, windowMidY);
////                p.push_back(tempParticle);
//            }
//            
//        } // End of iterator loop
        
        // Disable 2D textures and point sprites
        glDisable(GL_POINT_SPRITE);
        glDisable(GL_TEXTURE_2D);
        
        // ----- Stop Drawing Stuff! ------
        
        //    glfwSwapBuffers(); // Swap the buffers to display the scene (so we don't have to watch it being drawn!)




#endif /* Emitter_h */
