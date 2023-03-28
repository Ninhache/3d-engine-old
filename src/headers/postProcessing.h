#ifndef POST_PROCESSING_HEADER
#define POST_PROCESSING_HEADER

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <map>

#include "shader.h"

/** 
 * @struct ChromaticAberation_t
 * @brief struct for the Chromatic aberation post processing effect, controls
 * the desired offset for each color
 */
struct ChromaticAberation_t
{
    float redOff = 0.009, greenOff = 0.006, blueOff = -0.002;
};

/**
 * @struct Bloom_t
 * @brief struct for the Bloom post processing effect, added as a struct to add more
 * parameters later on
 *
 */
struct Bloom_t
{
    float intensity = 1.0;
};

/**
 * @struct Hdr_t
 * @brief struct for the HDR post processing effect, controls the exposure,
 * the gamma and the use of reinhard tone mapping
 * 
 */
struct Hdr_t
{
    float exposure = 2.0;
    float gamma = 2.0;
    bool reinhard = false;
};

class PostProcessing
{
public:
    /**
     * @brief Get a reference to the Chromatic struct
     * 
     * @return ChromaticAberation_t& 
     */
    ChromaticAberation_t &getChromatic();

    /**
     * @brief Get a reference to the Bloom struct
     * 
     * @return Bloom_t& 
     */
    Bloom_t &getBloom();

    /**
     * @brief Get a reference to the Hdr struct
     * 
     * @return Hdr_t& 
     */
    Hdr_t &getHdr();
    
    /**
     * @brief Get the boolean value of the effect
     * 
     * @param name The desired effect's name
     * @return true If the effect should be used
     * @return false If the effect should not be used
     */
    bool &getBool(std::string name);

    /**
     * @brief Updates the given shader's uniforms according to post processing struct
     * 
     * @param shader The shader to be updated
     */
    void updateUniforms(Shader &shader);

private:
    std::map<std::string, bool> effects = {{"bloom", false}, {"chromaticAberation", false}, {"blur", false}, {"hdr", false}};
    ChromaticAberation_t cAberation;
    Bloom_t bloom;
    Hdr_t hdr;
};

#endif // POST_PROCESSING_HEADER