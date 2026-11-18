#include <iostream>
#include "world/World.h"

int main() {
    std::cout << "Starting RenzoSimCore Simulation Loop..." << std::endl;
    
    World world(800, 600);
    
    // Change World.Update() to lowercase update()
    world.update(0.016);

    std::cout << "Simulation loop completed successfully." << std::endl;
    return 0;
}