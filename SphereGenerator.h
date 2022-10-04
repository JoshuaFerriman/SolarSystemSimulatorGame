#ifndef CLASS_SPHEREGENERATOR_H
#define CLASS_SPHEREGENERATOR_H

#include"Mesh.h"
#include<map>

class SphereGenerator
{
public:
    struct OpenMesh
    {
        std::vector <glm::vec3> vertices;
        std::vector <GLuint> indices;
    };

    SphereGenerator(void);
    ~SphereGenerator(void);
    Mesh CreateSphereMesh(int vertexFactor);

private:
    int index;
    OpenMesh mesh;
    std::map<__int64, int> middlePointIndexCache;

	void CreateIcosahedron(int recursionLevel);
	GLuint AddVertex(glm::vec3 vertexCoordinates);
	GLuint GetMiddlePoint(GLuint p1, GLuint p2);
};

#endif


