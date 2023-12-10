#pragma once

namespace MainLoop {
    void Init();   // Allocate resources for runtime
    void Update(); // Per frame update function.
    void DeInit(); // Save progress and free resources
}