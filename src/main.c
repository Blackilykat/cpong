#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	const int SCREEN_SIZE_X = 1000, SCREEN_SIZE_Y = 800;

	// pixels per second
	const float paddleSpeed = 500.0;
	const float baseBallSpeeX = 200.0;
	const float baseBallSpeedY = 300.0;
	const float ballAcceleration = 0.01;

	const int paddleHeight = 100;
	const int paddleWidth = 20;
	const int ballHeight =20;
	const int ballWidth = 20;

	const int distanceFromEdges = 20;

	const int minBallX = distanceFromEdges + paddleWidth;
	const int maxBallX = SCREEN_SIZE_X - distanceFromEdges * 2 - ballWidth;
	const int minBallY = 0;
	const int maxBallY = SCREEN_SIZE_Y - ballHeight;


	InitWindow(SCREEN_SIZE_X, SCREEN_SIZE_Y, "Pong");

	SetTargetFPS(90);


	float leftPaddle = 0.0, rightPaddle = 0.0;
	float ballX = SCREEN_SIZE_X / 2.0;
	float ballY = SCREEN_SIZE_Y / 2.0;
	char ballDirectionX = 1;
	char ballDirectionY = 1;
	float ballSpeedMultiplier = 1.0;

	while(!WindowShouldClose()) {
		BeginDrawing();
		float deltaTime = GetFrameTime();
		ballSpeedMultiplier += ballAcceleration * deltaTime;
		

		if(IsKeyDown(KEY_W)) {
			leftPaddle -= deltaTime * paddleSpeed;
		}
		if(IsKeyDown(KEY_S)) {
			leftPaddle += deltaTime * paddleSpeed;
		}
		if(leftPaddle < 0) leftPaddle = 0;
		if(leftPaddle > SCREEN_SIZE_Y - paddleHeight) leftPaddle = SCREEN_SIZE_Y - paddleHeight;

		if(IsKeyDown(KEY_UP)) {
			rightPaddle -= deltaTime * paddleSpeed;
		}
		if(IsKeyDown(KEY_DOWN)) {
			rightPaddle += deltaTime * paddleSpeed;
		}
		if(rightPaddle < 0) rightPaddle = 0;
		if(rightPaddle > SCREEN_SIZE_Y - paddleHeight) rightPaddle = SCREEN_SIZE_Y - paddleHeight;

		ballX += ballDirectionX * baseBallSpeeX * ballSpeedMultiplier * deltaTime;
		int pushBack = (ballDirectionX == 1 ? maxBallX : minBallX) - ballX;

		if(ballDirectionX == 1 && pushBack < 0) {
			if(ballY > rightPaddle - ballHeight && ballY < rightPaddle + paddleHeight) {
				ballX += pushBack;
				ballDirectionX *= -1;
			} else {
				printf("LEFT WON!!\n");
				exit(0);
			}
		}

		if(ballDirectionX == -1 && pushBack > 0) {
			if(ballY > leftPaddle - ballHeight && ballY < leftPaddle + paddleHeight) {
				ballX += pushBack;
				ballDirectionX *= -1;
			} else {
				printf("RIGHT WON!!\n");
				exit(0);
			}

		}


		ballY += ballDirectionY * baseBallSpeedY * deltaTime;
		pushBack = (ballDirectionY == 1 ? maxBallY : minBallY) - ballY;
		if((ballDirectionY == 1 && pushBack < 0) || (ballDirectionY == -1 && pushBack > 0)) {
			ballY += pushBack;
			ballDirectionY *= -1;
		}

		ClearBackground(BLACK);
		DrawRectangle(distanceFromEdges, leftPaddle, paddleWidth, paddleHeight, RAYWHITE);
		DrawRectangle(SCREEN_SIZE_X - distanceFromEdges - paddleWidth, rightPaddle, paddleWidth, paddleHeight, RAYWHITE);
		DrawRectangle(ballX, ballY, ballWidth, ballHeight, RAYWHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
