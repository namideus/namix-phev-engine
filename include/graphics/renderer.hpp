#include "graphics/shader.hpp"

namespace phe::graphics {
    struct Renderer {
        Shader* shader = nullptr;

        Renderer();
        ~Renderer();
    };

    Renderer renderInit();

    void renderClear(float r, float g, float b, float a);
}

