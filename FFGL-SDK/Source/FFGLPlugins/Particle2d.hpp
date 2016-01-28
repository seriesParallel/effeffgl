#ifndef PARTICLE_2D_HPP
#define PARTICLE_2D_HPP

#include "Vec2.hpp"
#include "Colour4f.hpp"

class Particle2D
{
protected:
    Vec2<float> location;  // The current location of the particle
    Vec2<float> speed;     // The current speed of the particle
    
    Colour4f colour;       // The colour of the particle
    
    int size;              // The size of the particle i.e. how big the pointsprite will be drawn
    
    int framesToLive;      // Number of frames before the particle is destroyed
    
public:
    // ---------- Static particle parameters -----------
    
    static const int FRAMES_TO_LIVE    = 100;
    
    static const int MIN_PARTICLE_SIZE = 10;
    static const int MAX_PARTICLE_SIZE = 64;
    
    static const float X_SPEED_RANGE   = 3.0f;
    static const float Y_SPEED_RANGE   = 8.0f;
    
    static const float GRAVITY         = 0.2f;
    
    // ---------- Constructors -------------------------
    
    // Constructor that takes an initial position as a Vec2
    Particle2D(Vec2<float> initialLocation)
    {
        location = initialLocation; // Set the particle location
        
        initialise();
    }
    
    // Constructor that takes an initial position as values (instead of a Vec2)
    
    Particle2D(int xLocation, int yLocation)
    {
        location.set(xLocation, yLocation);
        
        speed.set(Utils::randRange(-X_SPEED_RANGE, X_SPEED_RANGE), Utils::randRange(0.0f, Y_SPEED_RANGE) );
        
        initialise();
    }
    
    // Constructor that takes a position and a speed
    Particle2D(Vec2<float> initialLocation, Vec2<float> initialSpeed)
    {
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
};

#endif