#pragma once
#include "glm/glm.hpp"

class Material
{
public:
	Material() { }
	virtual bool IsDiffuse() const { return false; }
	virtual bool IsReflective() const { return false; }
	virtual bool IsRefractive() const { return false; }
};

class DiffuseMaterial : public Material
{
private:
	glm::vec3 diffuseColor;
public:
	DiffuseMaterial(glm::vec3 diffuseColor)
		: diffuseColor(diffuseColor)
	{ }

	virtual bool IsDiffuse() const { return true; }
	glm::vec3 GetDiffuse() { return diffuseColor; }
};

class ReflectiveMaterial : public Material
{
private:
	glm::vec3 reflectiveColor;
public:
	ReflectiveMaterial(glm::vec3 reflectiveColor)
		: reflectiveColor(reflectiveColor)
	{ }

	virtual bool IsReflective() const { return true; }
};

class RefractiveMaterial : public Material
{
private:
	glm::vec3 refractiveColor;
public:
	RefractiveMaterial(glm::vec3 refractiveColor)
		: refractiveColor(refractiveColor)
	{ }
	virtual bool IsRefractive() const { return true; }
};