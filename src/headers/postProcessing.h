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

struct Hdr_t{
    float exposure = 2.0;
    float gamma = 2.0;
    bool reinhard = false;
};

class PostProcessing{

public:
    ChromaticAberation_t& getChromatic();
    Bloom_t& getBloom();
    Hdr_t& getHdr();
    bool& getBool(std::string name);
    void updateUniforms(Shader& shader);
private:
    std::map<std::string, bool> effects = { {"bloom", false}, {"chromaticAberation", false}, {"blur", false}, {"hdr", false} };
    ChromaticAberation_t cAberation;
    Bloom_t bloom; 
    Hdr_t hdr;
};

#endif // POST_PROCESSING_HEADER