#pragma once

#ifndef RWDE_MESH
#define RWDE_MESH

#include "rw_dff.h"
#include "GL\glew.h"
#include "glm\glm.hpp"

namespace RWDE {
	struct Vertex {
	public:
		Vertex() {}
		Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal) {
			this->pos = pos;
			this->texCoord = texCoord;
			this->normal = normal;
		}
		
		void setPos(glm::vec3& pos) { this->pos = pos; }
		void setTexCoord(glm::vec2& texCoord) { this->texCoord = texCoord; }
		void setNormal(glm::vec3& normal) { this->normal = normal; }
		glm::vec3* getPos() { return &pos; }
		glm::vec2* getTexCoord() { return &texCoord; }
		glm::vec3* getNormal() { return &normal; }
	private:
		glm::vec3 pos;
		glm::vec2 texCoord;
		glm::vec3 normal;
	};

	enum MeshBufferPositions {
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		VERTEXCOLOR_VB
	};

	class Mesh {
	public:
		Mesh(RwDff* dff);
		~Mesh();

		void draw();

	private:
		static const unsigned int NUM_BUFFERS = 5;
		GLuint vertexArrayObject;
		GLuint vertexArrayBuffers[NUM_BUFFERS];
		unsigned int numIndices;

		void init();
	};
}
#endif