#define GLM_ENABLE_EXPERIMENTAL
#include "gameLayer.h"
#include <glad/glad.h>
#include <glm/gtx/transform.hpp>
#include <gl2d/gl2d.h>


gl2d::Renderer2D renderer;

gl2d::Texture spaceShipTexture;

bool initGame()
{
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	spaceShipTexture.loadFromFile(RESOURCES_PATH "spaceShip/ships/green.png", true);
	
	return true;
}



bool gameLogic(float deltaTime)
{
#pragma region init stuff
	int w = 0; int h = 0;
	w = platform::getFrameBufferSizeX(); //window w
	h = platform::getFrameBufferSizeY(); //window h
	
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT); //clear screen

	renderer.updateWindowMetrics(w, h);
#pragma endregion



	renderer.renderRectangle({100,100, 100, 100}, spaceShipTexture);


	renderer.flush();

	//ImGui::ShowDemoWindow();


	return true;
//#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{



}
