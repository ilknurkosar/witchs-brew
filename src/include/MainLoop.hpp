#pragma once

namespace MainLoop {
    void Init();   // Allocate resources for runtime
    int Update(double delta, void* data); // Per frame update function.
    void DeInit(); // Save progress and free resources
}