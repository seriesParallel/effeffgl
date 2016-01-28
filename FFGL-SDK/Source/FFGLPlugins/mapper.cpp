//
//  mapper.cpp
//  FFGLPlugins
//
//  Created by Mary Scahill on 1/27/16.
//
//

#include <stdio.h>
//#include "mapper.h"

float mapper(float value,
          float istart,
          float istop,
          float ostart,
          float ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

