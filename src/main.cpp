#include "headers/scene.h"
#include "headers/main.h"
#include "headers/logger.h"

int main(void) {
    
    logger.setConsoleLog(true);
    logger.log("Here's a logger..");

    Core::Scene sc = Core::Scene(800, 600);
    sc.renderLoop();

    return 0;
}