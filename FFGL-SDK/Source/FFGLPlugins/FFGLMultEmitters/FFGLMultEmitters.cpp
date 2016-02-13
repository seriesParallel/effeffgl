#include <FFGL.h>
#include <FFGLLib.h>
#include "FFGLParticles.h"


#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <mapper.h>
#include <OpenGL/gl3.h>
//#include <glew.h>      // Include the extension wrangler to have access to enhanced OpenGL features, like pointsprites
//#include <glu.h>      // Include the extension wrangler to have access to enhanced OpenGL features, like pointsprites
//#include <glfw.h>      // Include OpenGL Framework library

#include "Particle2dMulti.hpp" // Include our custom Particle2D class

//#define ILUT_USE_OPENGL	  // This MUST be defined before calling the DevIL headers or we don't get OpenGL functionality
//#include <il.h>
//#include <ilu.h>
//#include <ilut.

using namespace std;

// Define our vector (resizable array) of Particle2D objects
vector<Particle2D> p;

// Specify a limit for the size of our particle vector
//const int MAX_PARTICLES = 100;

GLint windowWidth;             // Width of our window
GLint windowHeight;              // Heightof our window

GLint windowMidX; // Middle of the window horizontally
GLint windowMidY; // Middle of the window vertically


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
                                   FFGLParticles::CreateInstance,	// Create method
                                   "GLMR",								// Plugin unique ID
                                   "FFGLBlue",			// Plugin name
                                   1,						   			// API major version number
                                   000,								  // API minor version number
                                   1,										// Plugin major version number
                                   000,									// Plugin minor version number
                                   FF_EFFECT,						// Plugin type
                                   "Sample FFGL Mirror plugin",	// Plugin description
                                   "by Trey Harrison - www.harrisondigitalmedia.com" // About
);


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FFGLParticles::FFGLParticles()
: CFreeFrameGLPlugin()
{
    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);
    
    // No Parameters
}




////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD FFGLParticles::ProcessOpenGL(ProcessOpenGLStruct *pGL)
{
    if (pGL->numInputTextures<1)
        return FF_FAIL;
    
    if (pGL->inputTextures[0]==NULL)
        return FF_FAIL;
    
    FFGLTextureStruct &Texture = *(pGL->inputTextures[0]);
    
    
    ///////////////////////////////
    ///////////////
    ///////
    //////////////
    ///////////////////////
    
    windowWidth   = Texture.Width;             // Width of our window
    windowHeight  = Texture.Height;              // Heightof our window
    
    windowMidX    = windowWidth  / 2; // Middle of the window horizontally
    windowMidY    = windowHeight / 2; // Middle of the window vertically
    
    //bind the texture handle to its target
    glBindTexture(GL_TEXTURE_2D, Texture.Handle);
    
    //enable texturemapping
    glEnable(GL_TEXTURE_2D);
    
    //get the max s,t that correspond to the
    //width,height of the used portion of the allocated texture space
    FFGLTexCoords maxCoords = GetMaxGLTexCoords(Texture);
    
    //modulate texture colors with white (just show
    //the texture colors as they are)
    glColor4f(1.f, 1.f, 1.f, 1.f);
    //(default texturemapping behavior of OpenGL is to
    //multiply texture colors by the current gl color)
    
    
    
    //////////////////////////////////////////////
    //Draw the whole texture (video from resolume)
    //////////////////////////////////////////////
    glBegin(GL_QUADS);
    
    //lower left
    glTexCoord2d(0,0);
    glVertex2f(-1,-1);
    
    //upper left
    glTexCoord2d(0, maxCoords.t);
    glVertex2f(-1,1);
    
    //upper right
    glTexCoord2d(maxCoords.s, maxCoords.t);
    glVertex2f(1,1);
    
    //lower right
    glTexCoord2d(maxCoords.s, 0.0);
    glVertex2f(1,-1);
    glEnd();
    
    // Unique identifier for the texture we'll apply to our pointsprites
    //    int textureId;
    
    //    glewInit();
    
    //    glfwSwapInterval(1); // Enable vsync
    
    // ----- Window and Projection Settings -----
    
    // Setup our viewport to be the entire size of the window
    glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
    
    // Change to the projection matrix, reset the matrix and set up our projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Specify orthographic projection (2D - no size attentuation) with the origin on the bottom left
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    // ----- OpenGL settings -----
    
    glClearColor(0.0, 0.0f, 0.0f, 1.0f); // Set our clear colour to black, full alpha
    
    // Enable blending and specify the blending function
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Enable point sprites (Note: We need more than basic OpenGL 1.0 for this functionality - so be sure to use GLEW or such)
    glEnable(GL_POINT_SPRITE);
    
    // Specify the origin of the point sprite
    glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT); // Default - only other option is GL_LOWER_LEFT
    
    glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
    
    // Specify the drawing mode for point sprites
    //    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);       // Draw on top of stuff
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Try this if you like...
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);   // Or this... not sure exactly how they differ ;-)
    
    // Enable 2D Textures
    glEnable(GL_TEXTURE_2D);
    
    // Specify linear filtering for minification and magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    // Specify that textures are clamped to edges
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    
    //    // Load our texture
    //    ILstring filename = "star1.png";
    //    textureId = ilutGLLoadImage(filename);
    
    // As we're only using a single texture we can just bind to it here instead of per frame
    //    glBindTexture(GL_TEXTURE_2D, textureId);
    glBindTexture(GL_TEXTURE_2D, Texture.Handle);
    //    glPointSize(1.0f);
    //    glBegin(GL_POINTS); //starts drawing of points
    //    glVertex3f(1.0f,1.0f,0.0f);//upper-right corner
    //    glVertex3f(-1.0f,-1.0f,0.0f);//lower-left corner
    //    glEnd();//end drawing of points
    
    
    
    
    
    // Frame counter and window settings variables
    int redBits    = 8, greenBits = 8,    blueBits    = 8;
    int alphaBits  = 8, depthBits = 24,   stencilBits = 0;
    
    // Flag to keep our main loop running
    bool running = true;
    
    // Seed random number generator
    srand(time(NULL));
    
    
    
    
    // Clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Reset the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Enable 2D textures and point sprites
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_POINT_SPRITE);
    
    ////////////DRAW THE PARTICLES
    ///////////
    ///////////
    Particle2D mi(windowMidY,windowMidY,p);
    mi.updateAndDrawParticles();
    ///////////
    // Disable 2D textures and point sprites
    glDisable(GL_POINT_SPRITE);
    glDisable(GL_TEXTURE_2D);
    return FF_SUCCESS;
}

// Function to draw our scene

//void FFGLParticles::updateAndDraw(int emitterID)
//{
//    // If there are less than MAX_PARTICLES particles in existence, add one more particle to our particle vector
//    if (p.size() < MAX_PARTICLES)
//    {
//        Particle2D temp(windowMidX, windowMidY);
//        p.push_back(temp);
//        
//    }
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
//    
//    // Iterate over all particles in the vector
//    vector<Particle2D>::iterator i;
//    for (i = p.begin(); i != p.end(); ++i)
//    {
//        // If the particle time to live is more than zero...
//        if (i->getFramesToLive() > 0)
//        {
//            // ...update the particle position position and draw it.
//            i->update();
//            i->draw();
//        }
//        else // // If it's time to destroy the particle...
//        {
//            // ...then remove it from the vector...
//            // NOTE: Calling erase(SOME-ELEMENT) removes the element from the vector and
//            // returns the next element in the vector, even if it's the "one-past-the-last-element"
//            // i.e. "end()" element which signifies the end of the vector.
//            //
//            // It's VERY important to assign this next element back to the iterator
//            // because we're modyfing the length of the vector inside a loop which goes
//            // until it gets to the end of a vector --- which, ya know, we're actually changing
//            // as we go! If you don't assign the next element back to the iterator when calling
//            // erase - don't be surprised when your code bombs out with a segfault, k? ;-D
//            i = p.erase(i);
//            
//            // ...and then add a new particle to replace it!
//            
//            Particle2D tempParticle(windowMidX, windowMidY);
//            p.push_back(tempParticle);
//        }
//        
//    } // End of iterator loop
//    
//    // Disable 2D textures and point sprites
//    glDisable(GL_POINT_SPRITE);
//    glDisable(GL_TEXTURE_2D);
//    
//    // ----- Stop Drawing Stuff! ------
//    
////    //    glfwSwapBuffers(); // Swap the buffers to display the scene (so we don't have to watch it being drawn!)
//    return FF_SUCCESS;
//    
//}

// Fire it up...
int FFGLParticles::main(int argc, char **argv)
{
    //    // Frame counter and window settings variables
    //    int redBits    = 8, greenBits = 8,    blueBits    = 8;
    //    int alphaBits  = 8, depthBits = 24,   stencilBits = 0;
    //    
    //    // Flag to keep our main loop running
    //    bool running = true;
    //    
    //    // Seed random number generator
    //    srand(time(NULL));
    //    
    //    updateAndDraw();
    return FF_SUCCESS;
}



