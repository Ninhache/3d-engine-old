#ifndef POST_PROCESSING_HEADER
#define POST_PROCESSING_HEADER

#include <glm/gtc/matrix_transform.hpp>

struct ChromaticAberation_t{
    float red, blue, green;
};

struct Bloom_t{

};

class PostProcessing{

public:
    ChromaticAberation_t& getChromatic();
    Bloom_t& getBloom();
private:
    bool m_bloom = false, m_chromaticAberation = false, m_blur = false;
    ChromaticAberation_t cAberation;
    Bloom_t bloom; 
};

#endif // POST_PROCESSING_HEADER