
#include "vec.h"
#include "model.h"

class Parameterization
{
public:
	
	void calculateNormalVectorPerTriangle(std::vector<Vec3>& vertices, std::vector<unsigned int>& indices);

private:


};


inline void Parameterization::calculateNormalVectorPerTriangle(std::vector<Vec3>& vertices, std::vector<unsigned int>& indices)
{
	// iterate over the indices in groups of three to get the vertices of each triangle
	for (size_t i = 0; i + 2 < indices.size(); i += 3)
	{
		unsigned int i0 = indices[i];
		unsigned int i1 = indices[i + 1];
		unsigned int i2 = indices[i + 2];

		std::cout << vertices[i0] << " " << vertices[i1] << " " << vertices[i2] << " \n";
	}
	
}
