#pragma once

// WINDOWS LIBRARIES
#if defined _WIN64 || defined _WIN32
#include <Windows.h>
#endif

// STD LIBRARIES
#include <iostream>
#include <conio.h>
#include <stack>
#include <memory>

// GL LIBRARIES
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

// VENDER LIBRARIES
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
 
// CUSTOM HEADERS
#include "Window.h"
#include "Input.h"
#include "../Scenes/MainMenu.h"

class Engine {


public:
	Engine();
	~Engine();

	int run();
	
	Window* getWindow();

private:

	Window* m_Window;
	InputManager* m_Input;

	bool m_fpsToggled = true;

	std::stack<std::unique_ptr<State::SceneState>> m_States;
};