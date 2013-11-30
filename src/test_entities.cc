#include "test_entities.hh"
#include "test_models.hh"
#include "mesh.hh"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>//TEMP

#define PI 3.14159265359


// Camera

Test::Camera::Camera(void) :
    angle(0.0f),
    pos(25.0f*sin(angle), 0.0f, 20.0f*cos(angle)),
    view(glm::lookAt(pos,                           // camera position
                     glm::vec3(0.0f, 0.0f, 0.0f),   // spot to look at
                     glm::vec3(0.0f, 1.0f, 0.0f))), // up vector
    projection(glm::perspective(60.0f,              // FOV
                                4.0f / 3.0f,        // aspect ratio
                                0.1f,               // near clipping plane
                                100.0f))            // far clipping plane
    {}

void Test::Camera::logic(void){
    angle += 0.0035;
    if (angle > 2*PI) angle -= 2*PI;
    pos = glm::vec3(25.0f*sin(angle), 0.0f, 20.0f*cos(angle));
    view = glm::lookAt(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}

const glm::mat4& Test::Camera::getViewMatrix(void) const{
    return view;
}

const glm::mat4& Test::Camera::getProjectionMatrix(void) const{
    return projection;
}

// SingleMeshEntity

Test::SingleMeshEntity::SingleMeshEntity(Mesh* pMesh_, glm::mat4 model_) :
    pMesh(pMesh_),
    model(model_) { }

void Test::SingleMeshEntity::render(const glm::mat4& view, const glm::mat4& projection) {
    pMesh->render(view, projection, model);
}
