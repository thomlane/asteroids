#include "bsepch.h"
#include "GeoFactory.h"

Geometry BuildSquare()
{
    //printf("== Building Square...\n");
    const std::vector<float> vertices
    {
        -0.5f,-0.5f, 0.0f, 0.0f, 0.0f, // 0
         0.5f,-0.5f, 0.0f, 1.0f, 0.0f, // 1
         0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // 2

        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f  // 3
    };

    const std::vector<GLuint> indices { 0,1,2,2,3,0 };

    VertexBufferLayout squareLayout;
    squareLayout.Push<float>(3);
    squareLayout.Push<float>(2);
    //printf("== Square Built!\n");

    return Geometry(vertices, indices, squareLayout);
}

Geometry BuildCircle(const int slices)
{
    std::vector <float> vertices;
    std::vector <GLuint> indices;

    float angle = 360.0f / slices;

    int triangleCount = slices - 2;

    // positions
    for (int i = 0; i < slices; i++)
    {
        float currentAngle = angle * i;
        float x = cos(glm::radians(currentAngle));
        float y = sin(glm::radians(currentAngle));
        float z = 0.0f;

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        vertices.push_back(0.);
        vertices.push_back(0.);
    }

    for (int i = 0; i < triangleCount; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);

    return Geometry(vertices, indices, layout);
}
