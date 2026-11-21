#pragma once

#include "vec.h"
#include "model.h"

class Parameterization
{
public:
	
	std::vector<Vec3> calculateNormalVectorPerTriangle(const std::vector<Vec3>& _vertices,const  std::vector<unsigned int>& _indices);

};


