#pragma once

#include <iostream>
#include <stack>

#include <imgui/imgui.h>

#include "../src/InstanceManager.h"
#include "../src/ECS/SceneManager.h"

class Scene5 : public State {

	//Private Setup Variables
private:

	InstanceManager* m_InstanceManager;

	Window* m_Window;
	InputManager* m_Input;
	ShaderLibrary* m_ShaderLib;

	unsigned int light_VAO = NULL;
	unsigned int cube_VAO = NULL;
	unsigned int cube_VBO = NULL;
	unsigned int cube_EBO = NULL;
	float cube_vertices[192] = {
			// POSITION          // NORMAL            // TEXCORD
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,  // front top right
			0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  // front bottom right
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  // front bottom left
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,  // front top left
								  		 	    	   
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,  // back top right
			0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,  // back bottom right
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,  // back bottom left
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,  // back top left
								   		 	    	   
			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  // right top right
			0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // right bottom right
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  // right bottom left
			0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // right top left 
								  		 	    	   
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,  // left top right
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // left bottom right
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  // left bottom left
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,  // left top left 
								   		 	    	   
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,  // top top right
			0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,  // top bottom right
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,  // top bottom left
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,  // top top left 
								   		 	    	   
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,  // bottom top right
			0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,  // bottom bottom right
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,  // bottom bottom left
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f   // bottom top left 
	};
	unsigned int cube_indices[36] = {
		0, 1, 3,
		1, 2, 3,

		4, 5, 7,
		5, 6, 7,

		8, 9, 11,
		9, 10, 11,

		12, 13, 15,
		13, 14, 15,

		16, 17, 19,
		17, 18, 19,

		20, 21, 23,
		21, 22, 23
	};

public:

	explicit Scene5(InstanceManager* instanceManager)
		: m_InstanceManager(instanceManager)
	{
		std::cout << "[L20] Opening Scene 5..." << std::endl;
		m_Window = m_InstanceManager->getWindowInstance();
		m_Input = m_InstanceManager->getInputInstance();
		m_ShaderLib = m_InstanceManager->getShaderLibInstance();

		glEnable(GL_DEPTH_TEST);
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Init Cube VAO
		glGenVertexArrays(1, &cube_VAO);
		glGenBuffers(1, &cube_VBO);
		glGenBuffers(1, &cube_EBO);

		glBindVertexArray(cube_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, cube_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(2);
			
		// Init Light VAO
		glGenVertexArrays(1, &light_VAO);
		glBindVertexArray(light_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, cube_VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_EBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);	

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_SceneCamera = new Camera(m_Window, glm::vec3(0.0f, 3.0f, 10.0f));
		m_SceneCamera->MovementSpeed = 10.0f;
		m_SceneCamera->MovementYDamp = 0.65f;

		light_trans.position = glm::vec3(0.0f, 10.0f, 0.0f);
		cube_trans.scale = glm::vec3(5.0f, 1.0f, 5.0f);
					
	}
	~Scene5() override
	{
		std::cout << "[L20] Closing Scene 5..." << std::endl;
		glDisable(GL_DEPTH_TEST);
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		glDeleteVertexArrays(1, &light_VAO);
		glDeleteVertexArrays(1, &cube_VAO);
		glDeleteBuffers(1, &cube_VBO);
		glDeleteBuffers(1, &cube_EBO);

		delete m_SceneCamera;
	}

private:

	float box_colour[4] = { 0.992f, 0.325f, 0.325f, 1.0f };
	float back_colour[4] = { 120.0f / 255.0f, 200.0f / 255.0f, 255.0f, 1.0f };

	TransformComponent cube_trans;
	TransformComponent light_trans;

	Camera* m_SceneCamera = nullptr;


	float currentTime = 0;
	float lastTime = 0;
	float deltaTime = 0;

public:


	void update() override {
		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		light_trans.position = glm::vec3(sin(currentTime) * 5, 10.0f, cos(currentTime) * 5);

		m_SceneCamera->Update(deltaTime);
	}

	void draw() override {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = m_SceneCamera->getViewMatrix();
		glm::mat4 proj = glm::perspective(glm::radians(60.0f), m_Window->getWidth() / m_Window->getHeight(), 0.1f, 100.0f);

		// Draw Light Source
		Shader* shader = m_ShaderLib->getShader("basic");
		if (shader) {
			glBindVertexArray(light_VAO);

			shader->Bind();
			shader->setMat4("view", view);
			shader->setMat4("proj", proj);
			shader->setVec4("ourColour", glm::vec4(1.0f));
			shader->setMat4("model", light_trans.getTransform());
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}

		// Draw Cube
		shader = m_ShaderLib->getShader("basic_phong");
		if (shader) {
			glBindVertexArray(cube_VAO);

			shader->Bind();
			shader->setMat4("view", view);
			shader->setMat4("proj", proj);
			shader->setMat3("normalToWorld", glm::mat3(glm::transpose(glm::inverse(cube_trans.getTransform()))));
			shader->setVec3("viewPos", m_SceneCamera->getPosition());
			shader->setVec3("lightPos", light_trans.position);
			shader->setVec4("lightColour", glm::vec4(1.0f));

			glm::vec3 pos = glm::vec3(0.0f);
			for (int x = 1; x <= 9; x++)
			{
				pos.x = -9 / 2 + x - cube_trans.scale.x / 2;
				for (int z = 1; z <= 9; z++)
				{
					pos.z = -9 / 2 + z - cube_trans.scale.z / 2; 
						
					double time = glfwGetTime();
					pos.y = (float)sin((time * 8 + floor(x - 9) + floor(z - 9))) / 9 * 9;

					if (z % 2 != 0 || x % 2 != 0)
					{
						shader->setVec4("targetColour", glm::vec4(box_colour[0], box_colour[1], box_colour[2], box_colour[3]));
					}
					else {
						shader->setVec4("targetColour", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
					}

					shader->setMat4("model", glm::translate(cube_trans.getTransform(), pos));
					glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
				}
			}
		}

		processGUI();
	}

private:

	void processGUI() {

		static bool wireFrame = false;

		ImGui::Begin("Scene Control", (bool*)0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);

		ImGui::SetWindowCollapsed(true, ImGuiCond_FirstUseEver);
		ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
		ImGui::SetWindowSize(ImVec2(300.0f, 400.0f));

		ImGui::Text("F9 = Toggle FPS\nF10 = Toggle Console\nF11 = Toggle Fullscreen");
		ImGui::Checkbox("Wireframe Mode", &wireFrame);

		if (!wireFrame)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		ImGui::Separator();

		if (ImGui::TreeNode("Cube Transform"))
		{
			ImGui::DragFloat3("Light Translate", glm::value_ptr(cube_trans.position), 0.01f, 0, 0, "%.2f");
			ImGui::DragFloat3("Rotate", glm::value_ptr(cube_trans.rotation), 1.0f, 0, 0, "%.2f");
			ImGui::DragFloat3("Scale", glm::value_ptr(cube_trans.scale), 0.01f, 0, 0, "%.2f");
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Colours"))
		{
			ImGui::ColorPicker4("Background", back_colour);
			ImGui::ColorPicker4("Box", box_colour);
			ImGui::TreePop();
		}

		glClearColor(back_colour[0], back_colour[1], back_colour[2], back_colour[3]);

		ImGui::End();
	}
};