#include <FFGL.h>
#include <FFGLLib.h>
#include "FFGLMirror.h"
#include "Math.h"

#define FFPARAM_Red (0)
#define FFPARAM_Green (1)
#define FFPARAM_Blue (2)

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo ( 
	FFGLMirror::CreateInstance,	// Create method
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

FFGLMirror::FFGLMirror()
: CFreeFrameGLPlugin()
{
	// Input properties
	SetMinInputs(1);
	SetMaxInputs(1);

  
  // Parameters
  SetParamInfo(FFPARAM_Red, "Red", FF_TYPE_STANDARD, 0.5f);
  m_Red = 0.5f;
  
  SetParamInfo(FFPARAM_Green, "Green", FF_TYPE_STANDARD, 0.5f);
  m_Green = 0.5f;
  
  SetParamInfo(FFPARAM_Blue, "Blue", FF_TYPE_STANDARD, 0.5f);
  m_Blue = 0.5f;
}






////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD FFGLMirror::ProcessOpenGL(ProcessOpenGLStruct *pGL)
{
  if (pGL->numInputTextures<1)
    return FF_FAIL;

  if (pGL->inputTextures[0]==NULL)
    return FF_FAIL;
  
  FFGLTextureStruct &Texture = *(pGL->inputTextures[0]);

  
 

  
  //bind the texture handle to its target
  glBindTexture(GL_TEXTURE_2D, Texture.Handle);

  //enable texturemapping
//  glEnable(GL_TEXTURE_2D);

  //get the max s,t that correspond to the 
  //width,height of the used portion of the allocated texture space
  FFGLTexCoords maxCoords = GetMaxGLTexCoords(Texture);

  //modulate texture colors with white (just show
  //the texture colors as they are)
  glColor4f(0.f, 0.f, 1.f, 1.f);
  //(default texturemapping behavior of OpenGL is to
  //multiply texture colors by the current gl color)
  
  //first, the left side of the mirror
  glBegin(GL_QUADS);

  //lower left
  glColor4f(1.f, 1.f, 1.f, 1.f);
  glVertex2f(-1,-1);

  //upper left
//  glTexCoord2d(0, maxCoords.t);
  glVertex2f(-1,1);

  //upper right
//  glTexCoord2d(maxCoords.s*0.25, maxCoords.t);
  glVertex2f(0,1);

  //lower right
//  glTexCoord2d(maxCoords.s*0.25, 0.0);
  glVertex2f(0,-1);
  glEnd();

  //now, the right side of the mirror
  glBegin(GL_QUADS);
  glColor4f(0.f, 1.f, 0.f, 1.f);

  //lower left
  glTexCoord2d(maxCoords.s*0.5, 0.0);
  glVertex2f(0,-1);

  //upper left
  glTexCoord2d(maxCoords.s*0.5, maxCoords.t);
  glVertex2f(0,1);

  //upper right
  glTexCoord2d(0.0, maxCoords.t);
  glVertex2f(1,1);

  //lower right
  glTexCoord2d(0.0, 0.0);
  glVertex2f(1,-1);
  glEnd();
  
  
  //now, the shit I'm doing here to test
  glBegin(GL_QUADS);
  glColor4f(1.f, 0.f, 1.f, 1.f);

  //lower left
  glTexCoord2d(0,0);
  glVertex2f(-.5,-.7);
  
  //upper left
  glTexCoord2d(0, maxCoords.t);
  glVertex2f(-.5,.6);
  
  //upper right
  glTexCoord2d(maxCoords.s*0.25, maxCoords.t);
  glVertex2f(.5,.9);
  
  //lower right
  glTexCoord2d(maxCoords.s*0.25, 0.0);
  glVertex2f(.7,-.7);
  glEnd();
  
  

  //unbind the texture
  glBindTexture(GL_TEXTURE_2D, 0);

  //disable texturemapping
  glDisable(GL_TEXTURE_2D);

  return FF_SUCCESS;
}

DWORD FFGLMirror::GetParameter(DWORD dwIndex)
{
  DWORD dwRet;
  
  switch (dwIndex) {
      
    case FFPARAM_Red:
      *((float *)(unsigned)&dwRet) = m_Red;
      return dwRet;
    case FFPARAM_Green:
      *((float *)(unsigned)&dwRet) = m_Green;
      return dwRet;
    case FFPARAM_Blue:
      *((float *)(unsigned)&dwRet) = m_Blue;
      return dwRet;
      
    default:
      return FF_FAIL;
  }
}

DWORD FFGLMirror::SetParameter(const SetParameterStruct* pParam)
{
  if (pParam != NULL) {
    
    switch (pParam->ParameterNumber) {
        
      case FFPARAM_Red:
        m_Red = *((float *)(unsigned)&(pParam->NewParameterValue));
        break;
      case FFPARAM_Green:
        m_Green = *((float *)(unsigned)&(pParam->NewParameterValue));
        break;
      case FFPARAM_Blue:
        m_Blue = *((float *)(unsigned)&(pParam->NewParameterValue));
        break;
        
      default:
        return FF_FAIL;
    }
    
    return FF_SUCCESS;
    
  }
  
  return FF_FAIL;
}
