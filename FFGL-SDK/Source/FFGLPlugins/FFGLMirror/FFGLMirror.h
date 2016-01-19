#ifndef FFGLMirror_H
#define FFGLMirror_H

#include "../FFGLPluginSDK.h"

class FFGLMirror :
public CFreeFrameGLPlugin
{
public:
	FFGLMirror();
  virtual ~FFGLMirror() {}

	///////////////////////////////////////////////////
	// FreeFrame plugin methods
	///////////////////////////////////////////////////
	
	DWORD	ProcessOpenGL(ProcessOpenGLStruct* pGL);
    DWORD	GetParameter(DWORD dwIndex);
    DWORD	SetParameter(const SetParameterStruct* pParam);



	///////////////////////////////////////////////////
	// Factory method
	///////////////////////////////////////////////////

	static DWORD __stdcall CreateInstance(CFreeFrameGLPlugin **ppOutInstance)
  {
  	*ppOutInstance = new FFGLMirror();
	  if (*ppOutInstance != NULL)
      return FF_SUCCESS;
	  return FF_FAIL;
  }
    
    
protected:
    // Parameters
    float m_Red;
    float m_Green;
    float m_Blue;
};


#endif
