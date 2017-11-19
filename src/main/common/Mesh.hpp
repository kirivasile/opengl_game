#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include <string>
#include <map>
#include <memory>

class DataBuffer
{
public:
	/**
	������� ����� � �������
	\param target ��� ������ (GL_ARRAY_BUFFER, GL_TEXTURE_BUFFER � ������)
	*/
	DataBuffer(GLenum target = GL_ARRAY_BUFFER) :
		_target(target)
	{
		glGenBuffers(1, &_vbo);
	}

	~DataBuffer()
	{
		glDeleteBuffers(1, &_vbo);
	}

	/**
	�������� ������ �� ����������� ������ � �����������, ������� ������ ��� ������ ��� �������������
	\param size ������ ������ � ������
	\param data ��������� �� ������ ������� ������ � ����������� ������
	*/
	void setData(GLsizeiptr size, const GLvoid* data)
	{
		glBindBuffer(_target, _vbo);
		glBufferData(_target, size, data, GL_STATIC_DRAW);
		glBindBuffer(_target, 0);
	}

	void bind() const
	{
		glBindBuffer(_target, _vbo);
	}

	void unbind() const
	{
		glBindBuffer(_target, 0);
	}

	/**
	���������� ������������� �������
	*/
	GLuint id() const { return _vbo; }

protected:
	DataBuffer(const DataBuffer&) = delete;
	void operator=(const DataBuffer&) = delete;

	///������������� ������
	GLuint _vbo;

	///��� ������
	GLenum _target;
};

typedef std::shared_ptr<DataBuffer> DataBufferPtr;

class Mesh {
public:
	Mesh() :
		_primitiveType(GL_TRIANGLES),
		_vertexCount(0)
	{
		glGenVertexArrays(1, &_vao);
	}

	~Mesh()
	{
		glDeleteVertexArrays(1, &_vao);
	}

	/**
	������������� ��������� ���������� �������� ������������� ������
	\param index ����� �������� (0, 1, 2, ...)
	\param size ���������� ����������� � �������� (1, 2, 3 ��� 4)
	\param type ��� ������ ����������� �������� (GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED � ������)
	\param normalized ������ �� ������ ���� ������������� �� �������� 0..1 (GL_TRUE) ��� �������������� ��� ���� (GL_FALSE)
	\param stride ���������� � ������ ����� ���������� ���� ���������������� ������. ���� 0, �� �������� ����������� � ������ ������ (��� �����������)
	\param offset ����� � ������ �� ������ ������
	\param buffer ����� � �������, ��� �������� �������� ��������
	*/
	void setAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint offset, const DataBufferPtr& buffer)
	{
		_buffers[index] = buffer; //����� ����� �� ��� ������ ������ ������

		glBindVertexArray(_vao);

		buffer->bind();
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, reinterpret_cast<void*>(offset));
		buffer->unbind();

		glBindVertexArray(0);
	}

	/**
	������������� ����������� ��� ���������� �������� (����������� �� 10� ��������, ������������ ��� �����������)
	\param index ����� �������� (0, 1, 2, ...)
	\param divisor ���� 0, �� ���� �������� �������� ������������� ����� �������, ���� >0, �� ���� �������� �������� ������������� ���� �������� ��� divisor ��������� ������
	*/
	void setAttributeDivisor(GLuint index, GLuint divisor)
	{
		glBindVertexArray(_vao);

		glVertexAttribDivisor(index, divisor);

		glBindVertexArray(0);
	}

	/**
	������������� ��� ��������� (GL_POINTS, GL_LINES, GL_TRIANGLES � ������)
	*/
	void setPrimitiveType(GLuint type) { _primitiveType = type; }

	/**
	������������� ���������� ������, ������� ������ ���� �����������
	*/
	void setVertexCount(GLuint count) { _vertexCount = count; }

	/**
	������� ������ (����������� ��������� ���������� � �������)
	*/
	glm::mat4 modelMatrix() const { return _modelMatrix; }

	/**
	������������� ������� ������
	*/
	void setModelMatrix(const glm::mat4& m) { _modelMatrix = m; }

	/**
	������ ������
	*/
	void draw() const
	{
		glBindVertexArray(_vao);
		glDrawArrays(_primitiveType, 0, _vertexCount);
	}

	/**
	������ ������ instanceCount ��� (����������� �� 10� ��������)
	*/
	void drawInstanced(unsigned int instanceCount) const
	{
		glBindVertexArray(_vao);
		glDrawArraysInstanced(_primitiveType, 0, _vertexCount, instanceCount);
	}
protected:
	Mesh(const Mesh&) = delete;
	void operator=(const Mesh&) = delete;

	///������������� Vertex Array Object
	GLuint _vao;

	///������ � ������� - ������ �����, ����� ��� �� ���� ������� ������ ������
	std::map<GLuint, DataBufferPtr> _buffers;

	///��� ��������������� ���������
	GLuint _primitiveType;

	///���������� ������ � ������
	GLuint _vertexCount;

	///������� ������ (local to world)
	glm::mat4 _modelMatrix;
};

typedef std::shared_ptr<Mesh> MeshPtr;

MeshPtr makeRelief(float size=1., unsigned int frequency=100, int num_octvaes=1, float persistence=0.5f);