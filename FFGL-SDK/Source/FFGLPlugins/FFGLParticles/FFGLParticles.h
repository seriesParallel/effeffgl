#ifndef FFGLParticles_H
#define FFGLParticles_H

#include "../FFGLPluginSDK.h"

class FFGLParticles :
public CFreeFrameGLPlugin
{
public:
    FFGLParticles();
    virtual ~FFGLParticles() {}
    
    

    
    ///////////////////////////////////////////////////
    // FreeFrame plugin methods
    ///////////////////////////////////////////////////
    
    DWORD	ProcessOpenGL(ProcessOpenGLStruct* pGL);
    
    ///////////////////////////////////////////////////
    // Factory method
    ///////////////////////////////////////////////////
    
    static DWORD __stdcall CreateInstance(CFreeFrameGLPlugin **ppOutInstance)
    {
        *ppOutInstance = new FFGLParticles();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }
    
protected:
    
    void updateAndDraw();
    int main(int argc, char **argv);
//    void Draw1();
//    void Draw2();
//    void Draw3();
//    void Draw4();
//    void Draw5();
//    void Draw6();
//    void Draw7();
//    void Draw8();
//    void Draw9();
//    void DrawDecimal();
//    
//    // Time
//    double m_curTime;
};


#endif
