#include "transform.h"

glm::mat4 Transform::GetModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = model * glm::mat4_cast(rotation);
    model = glm::scale(model, scale);
    return model;
}

