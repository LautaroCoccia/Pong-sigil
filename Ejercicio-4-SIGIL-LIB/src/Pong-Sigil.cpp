#include "sl.h"

struct Vector2
{
	int x;
	int y;
};
struct Ball {
	float ballMovementX;
	float ballMovementY;
	int ballSize;
	Vector2 ballPosition;
	Vector2 ballSpeed;
	//Color ballColor;
	bool ballDirection;
};
struct Ball ball;

int main(int args, char *argv[])
{
	const int screenWidth = 800;
	const int screenHeight = 450;
	ball.ballMovementX = 7.0f;
	ball.ballMovementY = 5.0f;
	//ball.ballColor = WHITE;
	ball.ballPosition.x = (float)screenWidth / 2;
	ball.ballPosition.y = (float)screenHeight / 2;
	ball.ballSize = 10.0f;
	ball.ballDirection = false;
	ball.ballSpeed.x = ball.ballMovementX;
	ball.ballSpeed.y = ball.ballMovementY;
	const int limit = 35;
	const float rectangleMovement = 6.0f;
	const int rectangleHeight = 90;
	const int rectangleWidth = 25;
	int player1Points = 0;
	int player2Points = 0;
	//Color colorOptions[5] = { BLUE,GOLD, RED, GREEN, PURPLE };
	bool checkColission = false;



	Vector2 boxP1 = { (double)(rectangleHeight / 2), (double)(screenHeight / 2)  };
	Vector2 boxP2 = {  (double)(screenWidth - rectangleHeight / 2), (double)(screenHeight / 2) };
	// Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------
	
	//Game Menu loop
	bool game = true;
	bool playing = true;
	int countP1 = 0;
	int countP2 = 1;
	/*boxP1.color = colorOptions[countP1];
	boxP2.color = colorOptions[countP2];*/
	// Main game loop
	// set up our window and a few resources we need
	slWindow(screenWidth, screenHeight, "Simple SIGIL Example", false);
	slSetFont(slLoadFont("ttf/white_rabbit.ttf"), 24);
	slSetTextAlign(SL_ALIGN_CENTER);
	int tex = slLoadTexture("png/glow.jpeg");
	bool CheckCollisionCircleRec(Vector2 center, float radius, Vector2 rec);
	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		if (slGetKey('S') && boxP1.y > (limit + (rectangleHeight/2))) boxP1.y -= rectangleMovement;
		if (slGetKey('W') && boxP1.y < (screenHeight - rectangleHeight)) boxP1.y += rectangleMovement;

		//Player 2
		//----------------------------------------------------------------------------------
		if (slGetKey(SL_KEY_DOWN) && boxP2.y > (limit + (rectangleHeight/2))) boxP2.y -= rectangleMovement;
		if (slGetKey(SL_KEY_UP) && boxP2.y < (screenHeight - rectangleHeight)) boxP2.y += rectangleMovement;

		// Check walls limit
		//----------------------------------------------------------------------------------
		if ((ball.ballPosition.x >= (screenWidth - ball.ballSize))) ball.ballPosition.x = (float)screenWidth / 2, (float)screenHeight / 2,
			player1Points++;
		else if (ball.ballPosition.x <= ball.ballSize)
			ball.ballPosition.x = (float)screenWidth / 2, (float)screenHeight / 2, player2Points++;
		if ((ball.ballPosition.y >= (screenHeight - ball.ballSize - limit)) || (ball.ballPosition.y <= (ball.ballSize ))) ball.ballSpeed.y *= -1.0f;

		if (player1Points == 3 || player2Points == 3) game = false;
		// collision
		//----------------------------------------------------------------------------------
	/*	if ( )
		{
			ball.ballDirection = false;
			ball.ballSpeed.x *= -1.0f;
			checkColission = false;
		}
		if ((ball.ballPosition.x - ball.ballSize) >= (boxP2.x - rectangleWidth / 2) && ball.ballPosition.x <= (boxP2.x + rectangleWidth / 2
			&& ball.ballPosition.y - rectangleHeight / 2) && ball.ballPosition.y <= (boxP2.y + rectangleHeight / 2) && (checkColission == false))
		{
			ball.ballDirection = true;
			ball.ballSpeed.x *= -1.0f;
			checkColission = true;
		}
		if ( CheckCollisionCircleRec(ball.ballPosition, ball.ballSize, boxP1) && (checkColission == true))
		{
			ball.ballDirection = false;
			ball.ballSpeed.x *= -1.0f;
			checkColission = false;
		};*/
		if ((ball.ballPosition.x - ball.ballSize) >= (boxP2.x - rectangleWidth / 2) && ball.ballPosition.x <= (boxP2.x + rectangleWidth / 2
			&& ball.ballPosition.y - rectangleHeight / 2) && ball.ballPosition.y <= (boxP2.y + rectangleHeight / 2) && (checkColission == false))
		{
			ball.ballDirection = true;
			ball.ballSpeed.x *= -1.0f;
			checkColission = true;
		}

		ball.ballPosition.x += ball.ballSpeed.x;
		ball.ballPosition.y += ball.ballSpeed.y;
		if (player1Points == 3 || player2Points == 3)playing = false;
		slRender();// draw everything
		slCircleFill(ball.ballPosition.x,ball.ballPosition.y,ball.ballSize,100);
		slRectangleFill((double)boxP1.x,(double)boxP1.y, (double)rectangleWidth, (double)rectangleHeight);
		slRectangleFill((double)boxP2.x, (double)boxP2.y, (double)rectangleWidth, (double)rectangleHeight);
	}
	slClose(); // close the window and shut down SIGIL
	return 0;
}

