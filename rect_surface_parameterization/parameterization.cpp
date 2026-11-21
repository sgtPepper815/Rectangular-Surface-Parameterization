
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "parameterization.h"

std::vector<Vec3> Parameterization::calculateNormalVectorPerTriangle(const std::vector<Vec3>& _vertices, const std::vector<unsigned int>& _indices)
{
	std::vector<Vec3> lineVertices;
	lineVertices.reserve((_vertices.size() / 3) * 6);

	// iterate over the indices in groups of three to get the vertices of each triangle
	for (size_t i = 0; i + 2 < _indices.size(); i += 3)
	{
		unsigned int i0 = _indices[i];
		unsigned int i1 = _indices[i + 1];
		unsigned int i2 = _indices[i + 2];

		// normal
		Vec3 e1 = _vertices[i1] - _vertices[i0]; // edge vector from vertex 0 to vertex 1
		Vec3 e2 = _vertices[i2] - _vertices[i0]; // edge vector from vertex 0 to vertex 2
		Vec3 normalOfTriangle = (e1.cross(e2));
		normalOfTriangle = normalOfTriangle.normalized();

		// tangents
		Vec3 t1 = e1.normalized(); // first tangent - along the edge e1
		Vec3 t2 = normalOfTriangle.cross(t1); // second tangent - perpendicular to the first tangent and the normal

		// center of triangle
		Vec3 A = (_vertices[i0] + _vertices[i1] + _vertices[i2]) / 3; // centroid of the triangle
		Vec3 B = A + (0.2f * normalOfTriangle); // point along the normal direction from the centroid with length 0.2

		Vec3 offset = A + 0.005f * normalOfTriangle;

		Vec3 T1 = offset + 0.2f * t1;
		Vec3 T2 = offset + 0.2f * t2;

		// normal
		lineVertices.push_back(A);
		lineVertices.push_back(B);

		// first tangent
		lineVertices.push_back(offset);
		lineVertices.push_back(T1);

		// second tangent
		lineVertices.push_back(offset);
		lineVertices.push_back(T2);
	}

	return lineVertices;

}