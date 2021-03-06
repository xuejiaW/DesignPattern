#include "Mesh_InverseCube.h"

Mesh_InverseCube::Mesh_InverseCube()
{
    vertices = new float[192]{                                                  // 6*4*8
                              -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, // front face
                              0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
                              0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
                              -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,

                              0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // back face
                              -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                              -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                              0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

                              0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // right face
                              0.5f, -0.5f, -0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                              0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
                              0.5f, 0.5f, 0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,

                              -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // left face
                              -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                              -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                              -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,

                              -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, // top face
                              0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
                              0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
                              -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

                              -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom face
                              0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                              0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                              -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};

    indices = new unsigned int[36]{         // 6*6
                                   0, 1, 2, // front face
                                   0, 2, 3,

                                   4, 5, 6, // back face
                                   4, 6, 7,

                                   8, 9, 10, // right face
                                   8, 10, 11,

                                   12, 13, 14, // left face
                                   12, 14, 15,

                                   16, 17, 18, // top face
                                   16, 18, 19,

                                   20, 21, 22, // bottom face
                                   20, 22, 23};

    singleDataSize = 8;
    vertexNum = 36;
    dataSize_byte = 192 * sizeof(float);
    indicesSize_byte = 36 * sizeof(unsigned int);
}

Mesh_InverseCube::~Mesh_InverseCube() {}