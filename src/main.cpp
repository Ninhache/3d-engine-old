#include "headers/scene.h"
#include "headers/main.h"

int main(void) {
    
    Core::Scene sc = Core::Scene(800, 600);
    sc.renderLoop();

    return 0;
}