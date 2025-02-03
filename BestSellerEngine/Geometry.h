#pragma once
class Geometry
{
public:
	VertexBufferLayout layout;

	const std::vector<float> vertices;
	const std::vector<unsigned int> indices;

	Geometry(const std::vector<float> vertices, const std::vector<unsigned int> indices, VertexBufferLayout layout)
		: vertices(vertices), indices(indices), layout(layout) {}

	Geometry() {}
};

