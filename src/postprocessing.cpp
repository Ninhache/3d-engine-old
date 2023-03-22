#include "headers/postProcessing.h"

ChromaticAberation_t& PostProcessing::getChromatic(){
    return this->cAberation;
}

Bloom_t& PostProcessing::getBloom(){
    return this->bloom;
}