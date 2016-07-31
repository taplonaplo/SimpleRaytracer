#pragma once
#include "glm/glm.hpp"
#include "Ray.h"

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
	glm::vec3 GetDiffuse() const { return diffuseColor; }
};



class ReflectiveMaterial : public Material
{
private:
	glm::vec3 reflectiveColor;
public:
	ReflectiveMaterial(glm::vec3 reflectiveColor)
		: reflectiveColor(reflectiveColor)
	{ }
	glm::vec3 GetReflective() const { return reflectiveColor; }
	glm::vec3 GetReflectionDirection(glm::vec3 incident, glm::vec3 normal) const { return glm::reflect(incident, normal); }
	virtual bool IsReflective() const { return true; }
};

class RefractiveMaterial;
class RefractiveModel
{
private:
	glm::vec3 reflectiveCoefficient;
	glm::vec3 refractiveCoefficient;
	Ray reflectedRay;
	Ray refractedRay;
public:
	RefractiveModel(const Ray& ray, const IntersectionRecord& surfaceRecord, const RefractiveMaterial* material);
	bool HasReflection() { return glm::dot(reflectiveCoefficient, glm::vec3(1.f)) > 0.f; }
	bool HasRefraction() { return glm::dot(refractiveCoefficient, glm::vec3(1.f)) > 0.f; }
	Ray GetReflectedRay() { return reflectedRay; }
	Ray GetRefractedRay() { return refractedRay; }
	glm::vec3 GetReflectiveCoefficient() { return reflectiveCoefficient; }
	glm::vec3 GetRefractiveCoefficient() { return refractiveCoefficient; }
};

class RefractiveMaterial : public Material
{
private:
	float averageRefractiveIndex;
	glm::vec3 fresnel0;
	glm::vec3 Fresnel0(glm::vec3 refractiveIndex, glm::vec3 extinctionCoefficient)
	{
		return ((refractiveIndex - glm::vec3(1)) * (refractiveIndex - glm::vec3(1)) 
						+ extinctionCoefficient * extinctionCoefficient)
			/ ((refractiveIndex + glm::vec3(1)) * (refractiveIndex + glm::vec3(1))
				+ extinctionCoefficient * extinctionCoefficient);
	}
public:
	RefractiveMaterial(glm::vec3 refractiveIndex, glm::vec3 extinctionCoefficient)
	{ 
		averageRefractiveIndex = glm::dot(refractiveIndex, glm::vec3(1)) / 3.f;
		fresnel0 = Fresnel0(refractiveIndex, extinctionCoefficient);
	}
	virtual RefractiveModel GetRefractiveModel(const Ray& ray, const IntersectionRecord& surfaceRecord)
	{
		return RefractiveModel(ray, surfaceRecord, this);
	}
	virtual float GetRefractiveIndex() const { return averageRefractiveIndex; }
	virtual glm::vec3 GetFresnel0() const { return fresnel0; }
	virtual bool IsRefractive() const { return true; }
};


