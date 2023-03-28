#include "headers/postProcessing.h"

ChromaticAberation_t& PostProcessing::getChromatic(){
    return this->cAberation;
}

Bloom_t& PostProcessing::getBloom(){
    return this->bloom;
}

Hdr_t& PostProcessing::getHdr() {
    return this->hdr;
}

bool& PostProcessing::getBool(std::string name) {
    return this->effects.find(name)->second;
}

void PostProcessing::updateUniforms(Shader& shader) {
    
    shader.use();
    std::string uniform;

    for (const auto& pair : this->effects) {
        uniform = "effects." + pair.first;
        shader.setBool(uniform, pair.second);
    }
    shader.setFloat("cAberation.redOff", this->cAberation.redOff);
    shader.setFloat("cAberation.greenOff", this->cAberation.greenOff);
    shader.setFloat("cAberation.blueOff", this->cAberation.blueOff);

    shader.setBool("hdr_t.reinhard", this->hdr.reinhard);
    shader.setFloat("hdr_t.gamma", this->hdr.gamma);
    shader.setFloat("hdr_t.exposure", this->hdr.exposure);

    shader.setFloat("bloom_t.intensity", this->bloom.intensity);
}