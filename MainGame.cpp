#include "MainGame.h"
#include <iostream>
#include <string>
#include "Errors.h"

using namespace std;


MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 1600;
	_screenHeight = 900;
	_gameState = GameState::PLAY;
}


MainGame:: ~MainGame()
{

}

void MainGame::run()
{
	initSystems();

	_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);

	gameLoop();
}

void MainGame::initSystems()
{
	//Let's get that SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	
	_window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr)
	{
		fatalError("SDL WIndow couldn't be created");
	}

	//open GL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr)
	{
		fatalError("SDL_GL context couldn't be created!");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("Couldn't initialize glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);//tells SDL that we want to double buffer - we have 2 windows that swap (1 is drawn on, the other is being cleared)

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	void initShaders();
}
void MainGame::initShaders()
{
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.linkShaders();
}
void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}
void MainGame::processInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << evnt.motion.x << " " << evnt.motion.yrel << endl;
			break;
		}
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //bitwise or |, comnbines 2 bits 

	//https://www.youtube.com/watch?v=j91xhXPJezg&list=PLSPw4ASQYyymu3PfG9gxywSPghnSMiOAW&index=9
	//viens no shiem mani pieviila
	_colorProgram.use(); //nezinu kapec nestrada krasas, pacheko sho https://www.youtube.com/watch?v=LLUtSE2osfI&list=PLSPw4ASQYyymu3PfG9gxywSPghnSMiOAW&index=10

	_sprite.draw();

	_colorProgram.unuse();
	//Triangles V
	/*
	//<triangle>
	glEnableClientState(GL_COLOR_ARRAY);

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);//3f nozime 3 parametri
	glVertex2f(-1, -1);//2f nozime ka ir 2
	glVertex2f(0, -1);
	glVertex2f(0, 0);
	glEnd();
	//</triangle>
	*/

	//Sprites



	//swapping the buffer
	SDL_GL_SwapWindow(_window);
}