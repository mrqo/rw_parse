#include "stdafx.h"
#include "rwde_mesh.h"

RWDE::Mesh::Mesh(RwDff* dff) {
	
	// Change to pointers
	std::vector<Vec3<float> > verticesVector = dff->getVertexInformation();
	std::vector<Vec2<int> > uvsVector = dff->getTextureMappingInformation();
	std::vector<Vec3<float> > normalsVector = dff->getNormalInformation();
	std::vector<Vec3PlusFlag<int> > facesVector = dff->getFaceInformation();
	std::vector<ColorRGBA> vertexColorVector = dff->getColorInformation();

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec4> vertexColors;
	std::vector<unsigned int> indices;
	
	for (int i = 0; i < verticesVector.size(); i++) {
		vertices.push_back(glm::vec3(verticesVector[i].x, verticesVector[i].y, verticesVector[i].z));
		//normals.push_back(vertices[i]);
	}

	for (int i = 0; i < uvsVector.size(); i++) {
		uvs.push_back(glm::vec2(uvsVector[i].x, uvsVector[i].y));
	}

	for (int i = 0; i < normalsVector.size(); i++) {
		normals.push_back(glm::vec3(normalsVector[i].x, normalsVector[i].y, normalsVector[i].z));
	}

	for (int i = 0; i < facesVector.size(); i++) {
		indices.push_back(facesVector[i].x);
		indices.push_back(facesVector[i].y);
		indices.push_back(facesVector[i].z);
	}

	for (int i = 0; i < vertexColorVector.size(); i++) {
		vertexColors.push_back(glm::vec4((float)vertexColorVector[i].R / 255, (float)vertexColorVector[i].G / 255, (float)vertexColorVector[i].B / 255, (float)vertexColorVector[i].A / 255) + 0.2f);
	}

	numIndices = indices.size();

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs[0]) * uvs.size(), &uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	//glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[VERTEXCOLOR_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors[0]) * vertexColors.size(), &vertexColors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

RWDE::Mesh::~Mesh() {
	glDeleteBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void RWDE::Mesh::draw() {
	glBindVertexArray(vertexArrayObject);
	glDrawElementsBaseVertex(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0, 0);
	glBindVertexArray(0);
}