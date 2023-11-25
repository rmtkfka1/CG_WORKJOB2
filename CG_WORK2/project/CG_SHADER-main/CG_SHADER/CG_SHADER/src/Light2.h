#pragma once





class Light2
{

public:

	Light2();
	~Light2();
	void UseLight(Shader& shader);



public:
	void SetLightPos(glm::vec3 pos);

	void SetLightAmbient(glm::vec3 sa);
	void SetLightDiffuse(glm::vec3 sd);

	void SetLightSpecular(glm::vec3 ss);

	void SetMaterialSpecular(glm::vec3 ms);
	void SetShininess(float shininess);

	struct Light
	{
		glm::vec3 lvector;
		glm::vec3 position; //������ ��ġ
		glm::vec3 direction; //������ ��ġ
		glm::vec2 cutoff;
		glm::vec3 ambient;
		float distance;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};


	struct Material
	{
		glm::vec3 specular;
		float shininess;
	};


public:

	Light _light;
	Material _material;





};

