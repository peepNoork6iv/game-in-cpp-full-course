#define GLM_ENABLE_EXPERIMENTAL
#include "gameLayer.h"
#include <glad/glad.h>

#include <platformInput.h>
#include <glm/gtx/transform.hpp>
#include <gl2d/gl2d.h>
#include <tiledRenderer.h>

struct GameplayData
{
	glm::vec2 playerPos = {100, 100};
};

GameplayData data;

gl2d::Renderer2D renderer;

constexpr int BACKGROUNDS = 3;

gl2d::Texture spaceShipTexture;
gl2d::Texture backgroundTexture[BACKGROUNDS];

TiledRenderer tiledRenderer[BACKGROUNDS];

bool initGame()
{
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	spaceShipTexture.loadFromFile(RESOURCES_PATH "spaceShip/ships/green.png", true);
	backgroundTexture[0].loadFromFile(RESOURCES_PATH "background1.png", true);
	backgroundTexture[1].loadFromFile(RESOURCES_PATH "background2.png", true);
	backgroundTexture[2].loadFromFile(RESOURCES_PATH "background3.png", true);

	tiledRenderer[0].texture = backgroundTexture[0];
	tiledRenderer[1].texture = backgroundTexture[1];
	tiledRenderer[2].texture = backgroundTexture[2];

	tiledRenderer[0].paralaxStrength = 0;
	tiledRenderer[1].paralaxStrength = 0.42;
	tiledRenderer[2].paralaxStrength = 0.89;

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

#pragma region movement

	glm::vec2 move = {};

	if (
		platform::isButtonHeld(platform::Button::Left) ||
		platform::isButtonHeld(platform::Button::A)
		) {
		move.x = -1;
	}
	if (
		platform::isButtonHeld(platform::Button::Right) ||
		platform::isButtonHeld(platform::Button::D)
		) {
		move.x = 1;
	}
	if (
		platform::isButtonHeld(platform::Button::Up) ||
		platform::isButtonHeld(platform::Button::W)
		) {
		move.y = -1;
	}
	if (
		platform::isButtonHeld(platform::Button::Down) ||
		platform::isButtonHeld(platform::Button::S)
		) {
		move.y = 1;
	}

	if (move.x != 0 || move.y != 0) {
		move = glm::normalize(move);

		move *= deltaTime * 1000;
		data.playerPos += move;
	}

#pragma endregion

#pragma region render background

	renderer.currentCamera.zoom = 0.5;

	for (int i = 0; i < BACKGROUNDS; i++) {
		tiledRenderer[i].render(renderer);
	}

#pragma endregion

	renderer.currentCamera.follow(data.playerPos, deltaTime * 450, 10, 200, w, h);

	renderer.renderRectangle({data.playerPos, 100, 100}, spaceShipTexture);


	renderer.flush();

	//ImGui::ShowDemoWindow();


	return true;
//#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{



}
