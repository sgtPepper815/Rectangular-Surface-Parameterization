
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>

#include "parameterization.h"

std::vector<Vec3> Parameterization::calculateNormalVectorPerTriangle(const std::vector<Vec3>& _vertices, const std::vector<unsigned int>& _indices)
{
	std::vector<Vec3> lineVertices;
	lineVertices.reserve((_indices.size() / 3) * 6);

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

		// 3D to 2D - calculate the 2D coordinates of the triangle in the tangent space defined by t1 and t2 - manifold parameterization
		float u1 = e1.dot(t1); // projection of e1 onto t1
		float u2 = e2.dot(t1); // projection of e2 onto t1
		float v1 = e1.dot(t2); // projection of e1 onto t2
		float v2 = e2.dot(t2); // projection of e2 onto t2
		Vec2 P0(0.0f, 0.0f); // origin in the tangent space
		Vec2 P1(u1, v1); // coordinates of the first vertex in the tangent space
		Vec2 P2(u2, v2); // coordinates of the second vertex in the tangent space

	}

	return lineVertices;

}

// we want to find the adjacency of triangles based on their edges. 
// Two triangles are adjacent if they share an edge. An edge is defined by two vertices, 
// and we can represent it as a pair of vertex indices. We will iterate through the list of triangles, extract their edges, and store them to find adjacent triangles.
void Parameterization::findTriangleAdjacency(const std::vector<unsigned int>& _indices)
{
	unsigned int i0 = 0;
	unsigned int i1 = 0;
	unsigned int i2 = 0;

	std::map<std::pair<unsigned int, unsigned int>, std::vector<unsigned int>> edgeToTriangles;

	std::vector<std::pair<unsigned int, unsigned int>> interiorEdges;
	std::vector<std::pair<unsigned int, unsigned int>> boundaryEdges;

	for (int i = 0; i < _indices.size(); i += 3)
	{
		i0 = _indices[i];
		i1 = _indices[i + 1];
		i2 = _indices[i + 2];

		std::pair<unsigned int, unsigned int> edge1 = std::make_pair(std::min(i0, i1), std::max(i0, i1));
		std::pair<unsigned int, unsigned int> edge2 = std::make_pair(std::min(i1, i2), std::max(i1, i2));
		std::pair<unsigned int, unsigned int> edge3 = std::make_pair(std::min(i2, i0), std::max(i2, i0));

		std::cout << "(" << edge1.first << ", " << edge1.second << ")" << std::endl;
		std::cout << "(" << edge2.first << ", " << edge2.second << ")" << std::endl;
		std::cout << "(" << edge3.first << ", " << edge3.second << ")" << std::endl;

		unsigned int triangleID = i / 3;

		edgeToTriangles[edge1].push_back(triangleID);
		edgeToTriangles[edge2].push_back(triangleID);
		edgeToTriangles[edge3].push_back(triangleID);
	}

	for (const auto& [edge, triangleIDs] : edgeToTriangles)
	{
		if (triangleIDs.size() == 2)
		{
			interiorEdges.push_back(edge);
		}
		else if (triangleIDs.size() == 1)
		{
			boundaryEdges.push_back(edge);
		}
		else if (triangleIDs.size() > 2)
		{
			std::cerr << "Error: Non manifold edge (" << edge.first << ", " << edge.second << ")." << std::endl;
		}
	}
	/*
	for (auto& edge : boundaryEdges)
	{
		std::cout << "Boundary edge: (" << edge.first << ", " << edge.second << ")" << std::endl;
	}

	for (auto& edge : interiorEdges)
	{
		std::cout << "Interior edge: (" << edge.first << ", " << edge.second << ")" << std::endl;
	}*/
}