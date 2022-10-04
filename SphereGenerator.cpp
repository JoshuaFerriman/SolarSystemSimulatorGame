#include "SphereGenerator.h"

SphereGenerator::SphereGenerator(void)
{
	
}

SphereGenerator::~SphereGenerator(void)
{

}

// add vertex to mesh, fix position to be on unit sphere, return index
GLuint SphereGenerator::AddVertex(glm::vec3 vertexCoords)
{
	float length = glm::sqrt((vertexCoords.x * vertexCoords.x) + (vertexCoords.y * vertexCoords.y) + (vertexCoords.z * vertexCoords.z));

	mesh.vertices.push_back(glm::vec3(vertexCoords.x / length, vertexCoords.y / length, vertexCoords.z / length));

	return index++;
}

// return index of point in the middle of p1 and p2
GLuint SphereGenerator::GetMiddlePoint(GLuint p1, GLuint p2)
{
	// first check if we have it already
	bool firstIsSmaller = p1 < p2;
	__int64 smallerIndex = firstIsSmaller ? p1 : p2;
	__int64 greaterIndex = firstIsSmaller ? p2 : p1;
	__int64 key = (smallerIndex << 32) + greaterIndex;

	int ret;
	if (middlePointIndexCache.find(key) != middlePointIndexCache.end())
	{
		return middlePointIndexCache[key];
	}


	// not in cache, calculate it
	glm::vec3 point1 = mesh.vertices[p1];
	glm::vec3 point2 = mesh.vertices[p2];
	glm::vec3 middle = glm::vec3(
		(point1.x + point2.x) / 2.0f,
		(point1.y + point2.y) / 2.0f,
		(point1.z + point2.z) / 2.0f);

	// add vertex makes sure point is on unit sphere
	int i = AddVertex(middle);

	// store it, return index

	middlePointIndexCache[key] = i;

	return i;
		
	
}

void SphereGenerator::CreateIcosahedron(int recursionLevel)
{
	index = 0;

	// create 12 vertices of a icosahedron

	float t = (1.0 + sqrt(5.0f)) / 2.0;

	AddVertex(glm::vec3(-1, t, 0));

	AddVertex(glm::vec3(1, t, 0));

	AddVertex(glm::vec3(-1, -t, 0));

	AddVertex(glm::vec3(1, -t, 0));

	AddVertex(glm::vec3(0, -1, t));

	AddVertex(glm::vec3(0, 1, t));

	AddVertex(glm::vec3(0, -1, -t));

	AddVertex(glm::vec3(0, 1, -t));

	AddVertex(glm::vec3(t, 0, -1));

	AddVertex(glm::vec3(t, 0, 1));

	AddVertex(glm::vec3(-t, 0, -1));

	AddVertex(glm::vec3(-t, 0, 1));



	// create 20 triangles of the icosahedron

	std::vector<glm::vec3> faces;

	// 5 faces around point 0

	faces.push_back(glm::vec3(0, 11, 5));

	faces.push_back(glm::vec3(0, 5, 1));

	faces.push_back(glm::vec3(0, 1, 7));

	faces.push_back(glm::vec3(0, 7, 10));

	faces.push_back(glm::vec3(0, 10, 11));

	// 5 adjacent faces

	faces.push_back(glm::vec3(1, 5, 9));

	faces.push_back(glm::vec3(5, 11, 4));

	faces.push_back(glm::vec3(11, 10, 2));

	faces.push_back(glm::vec3(10, 7, 6));

	faces.push_back(glm::vec3(7, 1, 8));

	// 5 faces around point 3

	faces.push_back(glm::vec3(3, 9, 4));

	faces.push_back(glm::vec3(3, 4, 2));

	faces.push_back(glm::vec3(3, 2, 6));

	faces.push_back(glm::vec3(3, 6, 8));

	faces.push_back(glm::vec3(3, 8, 9));

	// 5 adjacent faces

	faces.push_back(glm::vec3(4, 9, 5));

	faces.push_back(glm::vec3(2, 4, 11));

	faces.push_back(glm::vec3(6, 2, 10));

	faces.push_back(glm::vec3(8, 6, 7));

	faces.push_back(glm::vec3(9, 8, 1));

	// refine triangles

	for (int i = 0; i < recursionLevel; i++)

	{

		std::vector<glm::vec3> faces2;

		for (int r = 0; r < faces.size(); r++)

		{

			glm::vec3 tri = faces[r];

			// replace triangle by 4 triangles

			int a = GetMiddlePoint(tri.x, tri.y);

			int b = GetMiddlePoint(tri.y, tri.z);

			int c = GetMiddlePoint(tri.z, tri.x);

			faces2.push_back(glm::vec3(tri.x, a, c));

			faces2.push_back(glm::vec3(tri.y, b, a));

			faces2.push_back(glm::vec3(tri.z, c, b));

			faces2.push_back(glm::vec3(a, b, c));

		}

		faces = faces2;

		/*
		faces.clear();
		
		for (int r = 0; r < faces2.size(); r++)

		{

			faces.push_back(faces2[r]);

		}
		*/
	}

	// done, now add triangles to mesh

	for (int r = 0; r < faces.size(); r++)

	{

		glm::vec3 tri = faces[r];

		mesh.indices.push_back(tri.x);

		mesh.indices.push_back(tri.y);

		mesh.indices.push_back(tri.z);

	}

}

Mesh SphereGenerator::CreateSphereMesh(int vertexFactor)
{
	mesh.vertices.clear();
	mesh.indices.clear();
	
	index = 0;

	CreateIcosahedron(vertexFactor);


	std::vector<Vertex> vertices;
	std::vector<GLuint> indices = mesh.indices;
	std::vector<Texture> textures = {};

	for (auto vertex : mesh.vertices)
	{
		Vertex newVertex;
		newVertex.position = vertex;
		newVertex.normal = vertex;
		newVertex.color = glm::vec3(0.5f, 0.5f, 0.5f);
		newVertex.texUV = glm::vec2(0.0f, 0.0f);

		vertices.push_back(newVertex);
	}

	

	Mesh output(vertices, indices, textures);

	std::cout << "Icoshape created";
	return output;
	
}
