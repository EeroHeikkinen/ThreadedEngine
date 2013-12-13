#include "test_models.hh"

#include <cmath>
#include <vector>
#include <glm/glm.hpp>

#define PI 3.14159265358979323846


namespace {
    // packed vertex struct for position, UV, normal
    struct PackedVertex_PUN {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
    };
}

void Test::makeBox(GLuint& VBO_, GLuint& IBO_, GLuint& VAO_, unsigned int& numIndices_,
                   float xSize, float ySize, float zSize){

    PackedVertex_PUN vertices[24];

    //top
    vertices[0].position = glm::vec3(-xSize, ySize, -zSize);
    vertices[1].position = glm::vec3(xSize, ySize, -zSize);
    vertices[2].position = glm::vec3(-xSize, ySize, zSize);
    vertices[3].position = glm::vec3(xSize, ySize, zSize);
    vertices[0].uv = glm::vec2(0.0f, 0.0f);
    vertices[1].uv = glm::vec2(0.25f, 0.0f);
    vertices[2].uv = glm::vec2(0.0f, 0.25f);
    vertices[3].uv = glm::vec2(0.25f, 0.25f);
    for (size_t i=0; i<=3; ++i)
        vertices[i].normal = glm::vec3(0.0f, 1.0f, 0.0f);

    //sides
    vertices[4].position = glm::vec3(-xSize, -ySize, -zSize);
    vertices[5].position = glm::vec3(-xSize, -ySize, zSize);
    vertices[6].position = glm::vec3(-xSize, ySize, -zSize);
    vertices[7].position = glm::vec3(-xSize, ySize, zSize);
    vertices[4].uv = glm::vec2(0.0f, 0.50f);
    vertices[5].uv = glm::vec2(0.25f, 0.50f);
    vertices[6].uv = glm::vec2(0.0f, 0.25f);
    vertices[7].uv = glm::vec2(0.25f, 0.25f);
    for (size_t i=4; i<=7; ++i)
        vertices[i].normal = glm::vec3(-1.0f, 0.0f, 0.0f);

    vertices[8].position = glm::vec3(-xSize, -ySize, zSize);
    vertices[9].position = glm::vec3(xSize, -ySize, zSize);
    vertices[10].position = glm::vec3(-xSize, ySize, zSize);
    vertices[11].position = glm::vec3(xSize, ySize, zSize);
    vertices[8].uv = glm::vec2(0.25f, 0.50f);
    vertices[9].uv = glm::vec2(0.50f, 0.50f);
    vertices[10].uv = glm::vec2(0.25f, 0.25f);
    vertices[11].uv = glm::vec2(0.50f, 0.25f);
    for (size_t i=8; i<=11; ++i)
        vertices[i].normal = glm::vec3(0.0f, 0.0f, 1.0f);

    vertices[12].position = glm::vec3(xSize, -ySize, zSize);
    vertices[13].position = glm::vec3(xSize, -ySize, -zSize);
    vertices[14].position = glm::vec3(xSize, ySize, zSize);
    vertices[15].position = glm::vec3(xSize, ySize, -zSize);
    vertices[12].uv = glm::vec2(0.50f, 0.50f);
    vertices[13].uv = glm::vec2(0.75f, 0.50f);
    vertices[14].uv = glm::vec2(0.50f, 0.25f);
    vertices[15].uv = glm::vec2(0.75f, 0.25f);
    for (size_t i=12; i<=15; ++i)
        vertices[i].normal = glm::vec3(1.0f, 0.0f, 0.0f);

    vertices[16].position = glm::vec3(xSize, -ySize, -zSize);
    vertices[17].position = glm::vec3(-xSize, -ySize, -zSize);
    vertices[18].position = glm::vec3(xSize, ySize, -zSize);
    vertices[19].position = glm::vec3(-xSize, ySize, -zSize);
    vertices[16].uv = glm::vec2(0.75f, 0.50f);
    vertices[17].uv = glm::vec2(1.00f, 0.50f);
    vertices[18].uv = glm::vec2(0.75f, 0.25f);
    vertices[19].uv = glm::vec2(1.00f, 0.25f);
    for (size_t i=16; i<=19; ++i)
        vertices[i].normal = glm::vec3(0.0f, 0.0f, -1.0f);

    //bottom
    vertices[20].position = glm::vec3(-xSize, ySize, -zSize);
    vertices[21].position = glm::vec3(xSize, ySize, -zSize);
    vertices[22].position = glm::vec3(-xSize, ySize, zSize);
    vertices[23].position = glm::vec3(xSize, ySize, zSize);
    vertices[20].uv = glm::vec2(0.25f, 0.0f);
    vertices[21].uv = glm::vec2(0.50f, 0.0f);
    vertices[22].uv = glm::vec2(0.25f, 0.25f);
    vertices[23].uv = glm::vec2(0.50f, 0.25f);
    for (size_t i=20; i<=23; ++i)
        vertices[i].normal = glm::vec3(0.0f, -1.0f, 0.0f);

    const GLshort indices[36] = {
        0,  1,  2,  1,  2,  3, //top
        4,  5,  6,  5,  6,  7, //sides
        8,  9,  10, 9,  10, 11,
        12, 13, 14, 13, 14, 15,
        16, 17, 18, 17, 18, 19,
        20, 21, 22, 21, 22, 23 //bottom
    };

    size_t numVertices = 24;
    numIndices_ = 36;

    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 32, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices_ * 2, indices, GL_STATIC_DRAW);

    //The Vertex Array Object
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);

    glEnableVertexAttribArray(0); // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (GLvoid*)0);

    glEnableVertexAttribArray(1); // uv
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (GLvoid*)12);

    glEnableVertexAttribArray(2); // normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (GLvoid*)20);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);

    glBindVertexArray(0);
}

void Test::makeUVSphere(GLuint& VBO_, GLuint& IBO_, GLuint& VAO_,
                        unsigned int& numIndices_,
                        const unsigned int numSegments,
                        const unsigned int numRings){
    if (numSegments < 3){
        /*
        TODO
        Exception? Forced
        */
        return;
    }

    if (numRings < 3){
        /*
        TODO
        Exception?
        */
        return;
    }

    // some temp values
    const unsigned int numVertices( numSegments * (numRings+2) );
    numIndices_ = 6 * numSegments * (numRings-1);

    float
        sAngle( 2*PI / numSegments),
        rAngle( PI / numRings);

    // vertices
    PackedVertex_PUN* vertices = new PackedVertex_PUN[numVertices];

    for (unsigned int s=0; s<numSegments; ++s) {
        for (unsigned int r=0; r<numRings+1; ++r) {
            if (r <= numRings/2) {
                vertices[s*(numRings+2) + r].position = glm::vec3(s*sAngle, r*rAngle - PI/2, 0.0f);
                float t = (float)r/(numRings/2);
                vertices[s*(numRings+2) + r].uv = glm::vec2(0.25f + 0.25f*sinf(s*sAngle)*t, 0.75f + 0.25f*cosf(s*sAngle)*t);
            }
            if (r >= numRings/2) {
                vertices[s*(numRings+2) + r + 1].position = glm::vec3(s*sAngle, r*rAngle - PI/2, 0.0f);
                float t = (float)(numRings-r)/((numRings+1)/2);
                vertices[s*(numRings+2) + r + 1].uv = glm::vec2(0.25f + 0.25f*sinf(s*sAngle)*t, 0.25f + 0.25f*cosf(s*sAngle)*t);
            }
        }
    }

    // reconfiguring
    for (unsigned int i=0; i<numVertices; ++i) {
        vertices[i].position.z = -sinf(vertices[i].position.x) * cosf(vertices[i].position.y);
        vertices[i].position.x = cosf(vertices[i].position.x) * cosf(vertices[i].position.y);
        vertices[i].position.y = sinf(vertices[i].position.y);
        vertices[i].normal = glm::normalize(vertices[i].position);
    }

    // indices
    GLshort* indices = new GLshort[numIndices_];

    for (unsigned int s=0; s<numSegments; ++s) {
        for (unsigned int r=0; r<numRings-1; ++r) {
            unsigned int p(6 * (s*(numRings-1) + r));//first index of the partition
            short add[6];//index add in the middle(equator[whatever you wanna call it])
            if (r < numRings/2-1)
                { add[0]=0; add[1]=0; add[2]=0; add[3]=0; add[4]=0; add[5]=0; }
            else if (r > numRings/2-1)
                { add[0]=1; add[1]=1; add[2]=1; add[3]=1; add[4]=1; add[5]=1; }
            else
                { add[0]=0; add[1]=0; add[2]=0; add[3]=1; add[4]=1; add[5]=1; }

            if (s == numSegments-1) {
                indices[p] = add[0] + s*(numRings+2) + r;
                indices[p+1] = add[1] + r + 1;
                indices[p+2] = add[2] + s*(numRings+2) + r + 1;
                indices[p+3] = add[3] + s*(numRings+2) + r + 1;
                indices[p+4] = add[4] + r + 1;
                indices[p+5] = add[5] + r + 2;
            }
            else {
                indices[p] = add[0] + s*(numRings+2) + r;
                indices[p+1] = add[1] + (s+1)*(numRings+2) + r + 1;
                indices[p+2] = add[2] + s*(numRings+2) + r + 1;
                indices[p+3] = add[3] + s*(numRings+2) + r + 1;
                indices[p+4] = add[4] + (s+1)*(numRings+2) + r + 1;
                indices[p+5] = add[5] + (s+1)*(numRings+2) + r + 2;
            }
        }
    }

    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 32, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices_ * 2, indices, GL_STATIC_DRAW);

    // vertex array object
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);

    glEnableVertexAttribArray(0); // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (GLvoid*)0);

    glEnableVertexAttribArray(1); // uv
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (GLvoid*)12);

    glEnableVertexAttribArray(2); // normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (GLvoid*)20);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);

    glBindVertexArray(0);

    delete[] vertices;
    delete[] indices;
}
