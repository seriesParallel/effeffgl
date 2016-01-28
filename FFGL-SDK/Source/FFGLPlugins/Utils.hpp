#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdlib>

class Utils
{
    // Methods to return a random value between ranges
    // Yes, it probably would make more sense to templatise it, but the integer version
    // works slightly differenly. Maybe if that was placed first and THEN the templatised
    // version it would use the specific version for ints but the generic version for all
    // other data types - feel free to experiment and let me know how it works out ;-).
    
public:
    static double randRange(double min, double max)
    {
        return min + (((double)rand() / (double)RAND_MAX) * (max - min));
    }
    
    static float randRange(float min, float max)
    {
        return min + (((float)rand() / (float)RAND_MAX) * (max - min));
    }
    
    static int randRange(int min, int max)
    {
        return ((int)rand() % (max - min + 1)) + min;
    }
    
};

#endif