#ifndef POST_PROCESSING_HEADER
#define POST_PROCESSING_HEADER

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <map>

#include "shader.h"

struct ChromaticAberation_t{
    float redOff = 0.009, greenOff = 0.006, blueOff = -0.002;
};

struct Bloom_t{

};

class PostProcessing{

public:
    ChromaticAberation_t& getChromatic();
    Bloom_t& getBloom();
    bool& getBool(std::string name);
    void updateUniforms(Shader& shader);
private:
    std::map<std::string, bool> effects = { {"bloom", false},{"chromaticAberation", false}, {"blur", true} };
    ChromaticAberation_t cAberation;
    Bloom_t bloom; 
};

#endif // POST_PROCESSING_HEADER