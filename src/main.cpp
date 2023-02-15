#include "headers/scene.h"
#include "headers/main.h"
#include "headers/logger.h"

int main(void) {
    
    logger.log("Before render");
    Scene sc = Scene(800, 600);
    sc.renderLoop();

    return 0;
}