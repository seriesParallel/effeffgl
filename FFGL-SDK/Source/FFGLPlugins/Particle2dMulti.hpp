//
//  Particle2dMulti.hpp
//  FFGLPlugins
//
//  Created by Mary Scahill on 2/10/16.
//
//

#ifndef PARTICLE_2DMULTI_HPP
#define PARTICLE_2DMULTI_HPP


#include "Vec2.hpp"
#include "Colour4f.hpp"
//#include "Emitter.hpp"
#include <cstdlib>

class Particle2D
{
protected:
    float particleID;
    
    Vec2<float> location;  // The current location of the particle
    Vec2<float> speed;     // The current speed of the particle
    
    Colour4f colour;       // The colour of the particle
    
    int size;              // The size of the particle i.e. how big the pointsprite will be drawn
    
    int framesToLive;      // Number of frames before the particle is destroyed

    std::vector<Particle2D> emitterID;         // Which emitter it's coming from
//
public:
    // ---------- Static particle parameters -----------
    
    static const int FRAMES_TO_LIVE    = 100;
    
    static const int MAX_PARTICLES = 100;
    
    static const int MIN_PARTICLE_SIZE = 2;
    static const int MAX_PARTICLE_SIZE = 100;
    
    static const float X_SPEED_RANGE   = 3.0f;
    static const float Y_SPEED_RANGE   = 8.0f;
    
    static const float GRAVITY         = 0.2f;
    

    
    // ---------- Constructors -------------------------
    
    // Constructor that takes an initial position as a Vec2
    Particle2D(Vec2<float> initialLocation, std::vector<Particle2D> _emitterID)
    {
        location = initialLocation; // Set the particle location
        emitterID = _emitterID; //Set emitter ID
        initialise();
    }
    
    // Constructor that takes an initial position as values (instead of a Vec2)
    
    Particle2D(int xLocation, int yLocation, std::vector<Particle2D> _emitterID)
    {
        emitterID = _emitterID; //Set emitter ID

        location.set(xLocation, yLocation);
        
        speed.set(Utils::randRange(-X_SPEED_RANGE, X_SPEED_RANGE), Utils::randRange(0.0f, Y_SPEED_RANGE) );
        
        initialise();
    }
    
    // Constructor that takes a position and a speed
    Particle2D(Vec2<float> initialLocation, Vec2<float> initialSpeed, std::vector<Particle2D> _emitterID)
    {
        emitterID = _emitterID; //Set emitter ID

        location = initialLocation;
        speed    = initialSpeed;
        
        initialise();
    }
    
    // ---------- Helper Methods and Getters & Setters -------------------------
    
    // Method to setup other properties of the particle
    void initialise()
    {
        // Set the initial framesToLive count (this counts down to 0 - at 0 the particle is removed)
        framesToLive = FRAMES_TO_LIVE;
        
        // Set an entirely random colour (including random alpha value)
        colour.fullyRandomise();
        
        // Randomise the size of the particle
        size = Utils::randRange(MIN_PARTICLE_SIZE, MAX_PARTICLE_SIZE);
    }
    
    float getRed()   { return colour.getRed();	 }
    float getGreen() { return colour.getGreen(); }
    float getBlue()  { return colour.getBlue();  }
    float getAlpha() { return colour.getAlpha(); }
    
    void setColour(const Colour4f &theColour)
    {
        colour.setColour(theColour);
    }
    
    void interpolateColourWith(const Colour4f &theColour, float theMixFactor)
    {
        colour.interpolateWith(theColour, theMixFactor);
    }
    
    void setInterpolatedColour(const Colour4f &sourceColour, const Colour4f &destinationColour, float mixFactor)
    {
        colour.setInterpolatedColour(sourceColour, destinationColour, mixFactor);
    }
    
    Vec2<float> getLocation()  { return location;        }
    float getXLocation()       { return location.getX(); }
    float getYLocation()       { return location.getY(); }
    
    int getSize()              { return size;            }
    
    int getFramesToLive()      { return framesToLive;    }
    
    // ---------- Main Methods To Define Particle Behaviour -------------------------
    
    void update()
    {
        // Calculate the new Y speed of the particle
        speed.setY( speed.getY() - GRAVITY);
        
        // Update the position of the particle by the speed it's moving at
        location += speed;
        
        framesToLive--; // Decrease the frames the particle will live for by 1
    }
    
    void draw()
    {
        // Set the size of the point and draw it
        glPointSize(size);
        glBegin(GL_POINTS);
        
        // Set the colour and draw the particle
        glColor4f( colour.getRed(), colour.getGreen(), colour.getBlue(), colour.getAlpha() );
        glVertex2f(location.getX(), location.getY() );
        
        glEnd();
    }
    
    
    void updateAndDrawParticles()
    {
    // If there are less than MAX_PARTICLES particles in existence, add one more particle to our particle vector
    if (emitterID.size() < MAX_PARTICLES)
    {
        
        Particle2D temp(location, emitterID);
        emitterID.push_back(temp);
        
    }
//    
//    // Clear the screen and depth buffer
//    glClear(GL_COLOR_BUFFER_BIT);
//    
//    // Reset the modelview matrix
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    
//    // Enable 2D textures and point sprites
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_POINT_SPRITE);
    
    // Iterate over all particles in the vector
    std::vector<Particle2D>::iterator i;
    for (i = emitterID.begin(); i != emitterID.end(); ++i)
    {
        // If the particle time to live is more than zero...
        if (i->getFramesToLive() > 0)
        {
            // ...update the particle position position and draw it.
            i->update();
            i->draw();
        }
        else // // If it's time to destroy the particle...
        {
            // ...then remove it from the vector...
            // NOTE: Calling erase(SOME-ELEMENT) removes the element from the vector and
            // returns the next element in the vector, even if it's the "one-past-the-last-element"
            // i.e. "end()" element which signifies the end of the vector.
            //
            // It's VERY important to assign this next element back to the iterator
            // because we're modyfing the length of the vector inside a loop which goes
            // until it gets to the end of a vector --- which, ya know, we're actually changing
            // as we go! If you don't assign the next element back to the iterator when calling
            // erase - don't be surprised when your code bombs out with a segfault, k? ;-D
            i = emitterID.erase(i);
            
            // ...and then add a new particle to replace it!
            
            Particle2D tempParticle(location, emitterID);
            emitterID.push_back(tempParticle);
        }
        
    } // End of iterator loop
    
//    // Disable 2D textures and point sprites
//    glDisable(GL_POINT_SPRITE);
//    glDisable(GL_TEXTURE_2D);

    
    }
    
    
};

#endif