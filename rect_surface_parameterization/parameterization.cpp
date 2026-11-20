
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "parameterization.h"

std::vector<Vec3> Parameterization::calculateNormalVectorPerTriangle(const std::vector<Vec3>& vertices, const std::vector<unsigned int>& indices)
{
	std::vector<Vec3> lineVertices;
	lineVertices.reserve((indices.size() / 3) * 2);

	// iterate over the indices in groups of three to get the vertices of each triangle
	for (size_t i = 0; i + 2 < indices.size(); i += 3)
	{
		unsigned int i0 = indices[i];
		unsigned int i1 = indices[i + 1];
		unsigned int i2 = indices[i + 2];

		// normal
		Vec3 e1 = vertices[i1] - vertices[i0];
		Vec3 e2 = vertices[i2] - vertices[i0];

		Vec3 normalOfTriangle = (e1.cross(e2));
		normalOfTriangle = normalOfTriangle.normalized();

		// center of triangle
		Vec3 A = (vertices[i0] + vertices[i1] + vertices[i2]) / 3;

		Vec3 B = A + (0.2 * normalOfTriangle);

		lineVertices.push_back(A);
		lineVertices.push_back(B);

		std::cout << normalOfTriangle << std::endl;

		
	}



	for (int i = 0; i < lineVertices.size(); i++)
	{
		std::cout << lineVertices[i] << std::endl;
	}

	return lineVertices;

}