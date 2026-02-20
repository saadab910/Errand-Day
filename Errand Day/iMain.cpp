#include "iGraphics.h"
#include "Button.hpp"
#include "Obstacle.hpp"
#include <cstdlib>     

// CONSTANTS
const int SCREEN_W = 708;
const int SCREEN_H = 1080;


// ROAD
const int ROAD_LEFT_X = 72;
const int ROAD_RIGHT_X = 636;

double roadOffsetY; // Vertical road scrolling
const double MIN_SPEED = 4.0;
double roadSpeed = MIN_SPEED;


//CAR
const int CAR_W = 157;
const int CAR_H = 169;
double carX;
const int CAR_Y = 200; // Uplift distace from bottom

const double STEER_SPEED = 12.0;

const double MAX_SPEED = 18;
const double ACCEL_RATE = 0.15;
const double BRAKE_RATE = 0.4;
const double FRICTION_RATE = 0.04;
const double STEER_MIN = 3.5;
const double STEER_MAX = 10;


//BAT
const int BAT_FRAMES = 10;
int batImg[BAT_FRAMES];

bool batPlaying = false;
int batFrame = 0;

// image adjustments
const int BAT_EXTRA_W = 24;
const int BAT_OFFSET_X = -24;
const int BAT_OFFSET_Y = 0;


// GLOBALS

int x = 0;
int y = 0;
int mouseX, mouseY;
int menuBG;

struct MenuButtons {
	Button start;
	Button highScores;
	Button options;
	Button gameExit;
	Button easy;
	Button medium;
	Button hard;
	Button credits;
	Button controls;
	Button back;
} btn;


//RESOURCE_VARIABLES
int roadImgA;
int roadImgB;
int carImg;
int carBrakedImg;
int obsImg[OB_COUNT];
bool damageBlink = false;
int blinkTicks = 0;

//CONDITIONS
bool prevO = false;

// DRAW FUCTIONS
void drawHome();
void drawStart();
void drawOptions();
void drawControls();
void drawCredits();
void drawEasyGame();
void initGame();
void updateBatAnimation();

// BUTTON MANAGEMENTS
void startButtonClickHandler();
void backButtonClickHandler();
void optionsButtonClickHandler();
void controlsButtonClickHandler();
void creditsButtonClickHandler();
void easyButtonClickHandler();

// PAGE STATES
int homePage = 1;
int startPage = 0;
int optionsPage = 0;
int controlsPage = 0;
int creditsPage = 0;
int easyGame = 0;

void iDraw()
{

	iClear();

	if (homePage == 1){
		drawHome();
	}
	else if (startPage == 1){
		drawStart();
	}
	else if (optionsPage == 1){
		drawOptions();
	}
	else if (controlsPage == 1){
		drawControls();
	}
	else if (creditsPage == 1){
		drawCredits();
	}
	else if (easyGame == 1){
		drawEasyGame();
	}
}

void iMouseMove(int mx, int my)
{

}

void iPassiveMouseMove(int mx, int my)
{
	mouseX = mx;
	mouseY = my;
}

void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//printf("x: %d\t y: %d\n", mx, my);


		if (homePage == 1){
			if (mx >= 316 && mx <= 602 && my >= 240 && my <= 321){
				startButtonClickHandler();
			}
			else if (mx >= 316 && mx <= 549 && my >= 68 && my <= 149){
				optionsButtonClickHandler();
			}
			else if (mx >= 553 && mx <= 634 && my >= 68 && my <= 149){
				exit(0);
			}
		}
		else if (startPage == 1){
			if (mx >= 312 && mx <= 392 && my >= 240 && my <= 320){
				backButtonClickHandler();
			}
			else if (mx >= 402 && mx <= 633 && my >= 240 && my <= 320){
				easyButtonClickHandler();
			}
		}
		else if (optionsPage == 1){
			if (mx >= 268 && mx <= 348 && my >= 240 && my <= 320){
				backButtonClickHandler();
			}
			else if (mx >= 356 && mx <= 631 && my >= 240 && my <= 320){
				controlsButtonClickHandler();
			}
			else if (mx >= 356 && mx <= 630 && my >= 152 && my <= 232){
				creditsButtonClickHandler();
			}
		}
		else if (controlsPage == 1){
			if (mx >= 64 && mx <= 144 && my >= 652 && my <= 732){
				optionsButtonClickHandler();
			}
		}
		else if (creditsPage == 1){
			if (mx >= 74 && mx <= 154 && my >= 532 && my <= 612){
				optionsButtonClickHandler();
			}
		}

		else if (easyGame == 1)
		{
			batPlaying = true;
			batFrame = 0;
		}

	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}


void fixedUpdate()
{
	if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP))
	{
		y++;
	}
	if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT))
	{
		x--;
	}
	if (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN))
	{
		y--;
	}
	if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT))
	{
		x++;
	}

	if (isKeyPressed(' ')) {
		// Playing the audio once
		mciSendString("play ggsong from 0", NULL, 0, NULL);
	}
}

void initBackground()
{
	menuBG = iLoadImage("Assets\\global\\menu_background.png");
}

void initImages(){

	/*------------------------------------MENU------------------------------------*/
	// GLOBAL
	btn.back.normal = iLoadImage("Assets\\global\\buttons\\back.png");
	btn.back.hover = iLoadImage("Assets\\global\\buttons\\back_hover.png");

	// HOME PAGE
	btn.start.normal = iLoadImage("Assets\\home\\buttons\\start.png");
	btn.highScores.normal = iLoadImage("Assets\\home\\buttons\\high_scores.png");
	btn.options.normal = iLoadImage("Assets\\home\\buttons\\options.png");
	btn.gameExit.normal = iLoadImage("Assets\\home\\buttons\\exit.png");

	btn.start.hover = iLoadImage("Assets\\home\\buttons\\start_hover.png");
	btn.highScores.hover = iLoadImage("Assets\\home\\buttons\\high_scores_hover.png");
	btn.options.hover = iLoadImage("Assets\\home\\buttons\\options_hover.png");
	btn.gameExit.hover = iLoadImage("Assets\\home\\buttons\\exit_hover.png");

	// START PAGE
	btn.easy.normal= iLoadImage("Assets\\start\\buttons\\easy.png");
	btn.medium.normal = iLoadImage("Assets\\start\\buttons\\medium.png");
	btn.hard.normal = iLoadImage("Assets\\start\\buttons\\hard.png");

	btn.easy.hover = iLoadImage("Assets\\start\\buttons\\easy_hover.png");
	btn.medium.hover = iLoadImage("Assets\\start\\buttons\\medium_hover.png");
	btn.hard.hover = iLoadImage("Assets\\start\\buttons\\hard_hover.png");

	// OPTIONS PAGE
	btn.credits.normal = iLoadImage("Assets\\options\\buttons\\credits.png");
	btn.controls.normal = iLoadImage("Assets\\options\\buttons\\controls.png");

	btn.credits.hover = iLoadImage("Assets\\options\\buttons\\credits_hover.png");
	btn.controls.hover = iLoadImage("Assets\\options\\buttons\\controls_hover.png");

	/*----------------------------------------------------------------------------*/

	/*------------------------------------GAME------------------------------------*/
	roadImgA = iLoadImage("Assets\\game\\road.png");
	roadImgB = iLoadImage("Assets\\game\\road.png");
	carImg = iLoadImage("Assets\\game\\car.png");
	carBrakedImg = iLoadImage("Assets\\game\\car_braked.png");


	// BAT
	batImg[0] = iLoadImage("Assets\\game\\bat\\bat0.png");
	batImg[1] = iLoadImage("Assets\\game\\bat\\bat1.png");
	batImg[2] = iLoadImage("Assets\\game\\bat\\bat2.png");
	batImg[3] = iLoadImage("Assets\\game\\bat\\bat3.png");
	batImg[4] = iLoadImage("Assets\\game\\bat\\bat4.png");
	batImg[5] = iLoadImage("Assets\\game\\bat\\bat5.png");
	batImg[6] = iLoadImage("Assets\\game\\bat\\bat6.png");
	batImg[7] = iLoadImage("Assets\\game\\bat\\bat7.png");
	batImg[8] = iLoadImage("Assets\\game\\bat\\bat8.png");
	batImg[9] = iLoadImage("Assets\\game\\bat\\bat9.png");


	// OBSTACLES

	for (int i = 0; i < OB_COUNT; i++) {
		char path[128];
		sprintf_s(path, "Assets//game//obstacles//obs%d.png", i);
		obsImg[i] = iLoadImage(path);
	}
}

// Mouse Hover Position Verifier
bool inside(int mx, int my, int x1, int x2, int y1, int y2){
	return mx >= x1 && mx <= x2 && my >= y1 && my <= y2;
}

void drawHome()
{

	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, SCREEN_W, SCREEN_H);

	iShowImage(0, 0, SCREEN_W, SCREEN_H, menuBG);

	// buttons
	iShowImage(316, 240, 286, 81, btn.start.normal);
	iShowImage(316, 154, 346, 81, btn.highScores.normal);
	iShowImage(316, 68, 233, 81, btn.options.normal);
	iShowImage(553, 68, 81, 81, btn.gameExit.normal);

	// hovers
	if (inside(mouseX, mouseY, 316, 602, 240, 321)){
		iShowImage(316, 240, 286, 81, btn.start.hover);
	}
	else if (inside(mouseX, mouseY, 316, 546, 154, 235)){
		iShowImage(316, 154, 346, 81, btn.highScores.hover);
	}
	else if (inside(mouseX, mouseY, 316, 549, 68, 149)){
		iShowImage(316, 68, 233, 81, btn.options.hover);
	}
	else if (inside(mouseX, mouseY, 553, 634, 68, 149)){
		iShowImage(553, 68, 81, 81, btn.gameExit.hover);
	}
}

void drawStart()
{
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, SCREEN_W, SCREEN_H);
	iShowImage(0, 0, SCREEN_W, SCREEN_H, menuBG);

	//BUTTONS
	iShowImage(312, 240, 80, 80, btn.back.normal);
	iShowImage(402, 240, 231, 80, btn.easy.normal);
	iShowImage(402, 154, 231, 80, btn.medium.normal);
	iShowImage(402, 66, 231, 80, btn.hard.normal);


	//BUTTON_HOVERS
	if (inside(mouseX, mouseY, 312, 392, 240, 320)){
		iShowImage(312, 240, 80, 80, btn.back.hover);
	}
	else if (inside(mouseX, mouseY, 402, 633, 240, 320)){
		iShowImage(402, 240, 231, 80, btn.easy.hover);
	}
	else if (inside(mouseX, mouseY, 402, 633, 154, 234)){
		iShowImage(402, 154, 231, 80, btn.medium.hover);
	}
	else if (inside(mouseX, mouseY, 402, 633, 38, 118)){
		iShowImage(402, 66, 231, 80, btn.hard.hover);
	}

}

void drawOptions()
{
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, SCREEN_W, SCREEN_H);
	iShowImage(0, 0, SCREEN_W, SCREEN_H, menuBG);

	// BUTTONS
	iShowImage(268, 240, 80, 80, btn.back.normal);
	iShowImage(356, 240, 275, 80, btn.controls.normal);
	iShowImage(356, 152, 274, 80, btn.credits.normal);

	// BUTTON_HOVERS
	if (inside(mouseX, mouseY, 268, 348, 240, 320)){
		iShowImage(268, 240, 80, 80, btn.back.hover);
	}
	else if (inside(mouseX, mouseY, 356, 631, 240, 320)){
		iShowImage(356, 240, 275, 80, btn.controls.hover);
	}
	else if (inside(mouseX, mouseY, 356, 630, 152, 232)){
		iShowImage(356, 152, 274, 80, btn.credits.hover);
	}

}

void drawControls(){

	static int controlsBG = iLoadImage("Assets\\options\\controls\\controls_bg.png");
	iShowImage(0, 0, SCREEN_W, SCREEN_H, controlsBG);
	static int goBack = iLoadImage("Assets\\options\\controls\\go_back.png");
	static int controlsPreview = iLoadImage("Assets\\options\\controls\\controls_preview.png");

	iShowImage(64, 652, 80, 80, btn.back.normal);
	iShowImage(156, 652, 221, 80, goBack);
	iShowImage(64, 96, 471, 489, controlsPreview);


	if (inside(mouseX, mouseY, 64, 144, 652, 732)){
		iShowImage(64, 652, 80, 80, btn.back.hover);
	}
}

void drawCredits(){
	static int creditsBG = iLoadImage("Assets\\options\\credits\\credits_bg.png");
	iShowImage(0, 0, SCREEN_W, SCREEN_H, creditsBG);
	iShowImage(74, 532, 80, 80, btn.back.normal);
	if (inside(mouseX, mouseY, 74, 154, 532, 612)){
		iShowImage(74, 532, 80, 80, btn.back.hover);
	}
}

//MENU BUTTON HANDLERS
void startButtonClickHandler()
{
	homePage = 0;
	startPage = 1;
	optionsPage = 0;
	controlsPage = 0;
	creditsPage = 0;
	easyGame = 0;
}
void backButtonClickHandler()
{
	homePage = 1;
	startPage = 0;
	optionsPage = 0;
	controlsPage = 0;
	creditsPage = 0;
	easyGame = 0;
}
void optionsButtonClickHandler()
{
	homePage = 0;
	startPage = 0;
	optionsPage = 1;
	controlsPage = 0;
	creditsPage = 0;
	easyGame = 0;
}
void controlsButtonClickHandler(){
	homePage = 0;
	startPage = 0;
	optionsPage = 0;
	controlsPage = 1;
	creditsPage = 0;
	easyGame = 0;
}
void creditsButtonClickHandler(){
	homePage = 0;
	startPage = 0;
	optionsPage = 0;
	controlsPage = 0;
	creditsPage = 1;
	easyGame = 0;
}
void easyButtonClickHandler(){
	homePage = 0;
	startPage = 0;
	optionsPage = 0;
	controlsPage = 0;
	creditsPage = 0;
	easyGame = 1;

	initGame();
	batPlaying = false;
	batFrame = 0;

}


void drawEasyGame(){

	bool brakeHeld = isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN);

	bool drawCarNow = true;
	if (damageBlink) {
		drawCarNow = ((blinkTicks / 6) % 2 == 0);
	}

	// INFINITE ROAD DRAW
	iShowImage(0, (int)roadOffsetY, SCREEN_W, SCREEN_H, roadImgA);
	iShowImage(0, (int)roadOffsetY + SCREEN_H, SCREEN_W, SCREEN_H, roadImgB);

	// CAR DRAW
	if (drawCarNow)
	{
		if (batPlaying)
		{
			iShowImage((int)carX + BAT_OFFSET_X, CAR_Y + BAT_OFFSET_Y,
				CAR_W + BAT_EXTRA_W, CAR_H,
				batImg[batFrame]);
		}
		else
		{
			iShowImage((int)carX, CAR_Y, CAR_W, CAR_H,
				brakeHeld ? carBrakedImg : carImg);
		}
	}


	// OBSTACLES DRAW
	for (int i = 0; i < MAX_OBS_ON_SCREEN; i++) {
		if (!gObs[i].active) continue;
		iShowImage((int)gObs[i].x, (int)gObs[i].y,
			gObs[i].width, gObs[i].height,
			obsImg[gObs[i].imgIndex]);

	}



	// REAL-TIME DEBUG
	iSetColor(255, 255, 255);
	char txt[120];
	sprintf_s(txt, "Speed: %.1f   carX: %.0f", roadSpeed, carX);
	iText(10, SCREEN_H - 25, txt, GLUT_BITMAP_HELVETICA_18);

}


// CAR's SIDE MOVEMENT BINDER
double clampDouble(double v, double lo, double hi)
{
	if (v < lo) return lo;
	if (v > hi) return hi;
	return v;
}


void initGame()
{
	double roadCenter = (ROAD_LEFT_X + ROAD_RIGHT_X) / 2.0;
	carX = roadCenter - (CAR_W / 2.0);

	prevO = false;

	initObstacleSystem(ROAD_LEFT_X, ROAD_RIGHT_X, SCREEN_H);
	resetObstacles();

	damageBlink = false;
	blinkTicks = 0;
}

// GAME REFRESH
void updateGame()
{

	if (easyGame != 1) {
		prevO = false;     // important: don't carry key state across menus
		return;
	}


	bool nowO = (isKeyPressed('o') != 0); // isKeyPressed returns int


	if (nowO && !prevO)   // just pressed
	{
		batPlaying = true;
		batFrame = 0;
	}

	prevO = nowO;


	bool leftHeld = isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT);
	bool rightHeld = isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT);


	// 4) STEERING (speed depends on roadSpeed)
	double t = (roadSpeed - MIN_SPEED) / (MAX_SPEED - MIN_SPEED);
	t = clampDouble(t, 0.0, 1.0);
	double steerThisFrame = STEER_MIN + t * (STEER_MAX - STEER_MIN);

	if (leftHeld)  carX -= steerThisFrame;
	if (rightHeld) carX += steerThisFrame;



	// --------------------------
	// 1) READ INPUT (HELD KEYS)
	// --------------------------
	bool accelerateHeld = isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP);
	bool brakeHeld = isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN);

	//bool leftHeld = isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT);
	//bool rightHeld = isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT);

	// CONTROLS
	if (accelerateHeld)
	{
		roadSpeed += ACCEL_RATE;
		if (roadSpeed > MAX_SPEED) roadSpeed = MAX_SPEED;
	}

	if (brakeHeld)
	{
		roadSpeed -= BRAKE_RATE;
		if (roadSpeed < MIN_SPEED) roadSpeed = MIN_SPEED;
		if (roadSpeed > MAX_SPEED) roadSpeed = MAX_SPEED;
	}

	// Friction slows the car when no accelerate/brake held
	if (!accelerateHeld && !brakeHeld)
	{
		roadSpeed -= FRICTION_RATE;
		if (roadSpeed < MIN_SPEED) roadSpeed = MIN_SPEED;
	}


	// Road Scroll
	roadOffsetY -= roadSpeed;

	// endless
	if (roadOffsetY <= -SCREEN_H)
		roadOffsetY += SCREEN_H;

	carX = clampDouble(carX, ROAD_LEFT_X, ROAD_RIGHT_X - CAR_W);

	//OBSTACLE REFRESH
	updateObstacles((float)roadSpeed);



	// COLLISION
	if (!damageBlink && checkObstacleCollision((float)carX, (float)CAR_Y, (float)CAR_W, (float)CAR_H)) {
		damageBlink = true;
		blinkTicks = 45;

		resetObstacles();            
		roadSpeed = 8;               
		if (roadSpeed < MIN_SPEED) roadSpeed = MIN_SPEED;
	}

	// DAMAGE
	if (damageBlink) {
		blinkTicks--;
		if (blinkTicks <= 0) {
			damageBlink = false;
			blinkTicks = 0;
		}
	}

	// BAT REFRESH
	updateBatAnimation();

}

void updateBatAnimation()
{
	if (!batPlaying) return;

	batFrame++;

	if (batFrame >= BAT_FRAMES)
	{
		batPlaying = false; 
		batFrame = 0;
	}
}



int main()
{
	// Opening/Loading the audio files
	//mciSendString("open \"Audios//background.mp3\" alias bgsong", NULL, 0, NULL);
	//mciSendString("open \"Audios//gameover.mp3\" alias ggsong", NULL, 0, NULL);

	// Playing the background audio on repeat
	//mciSendString("play bgsong repeat", NULL, 0, NULL);

	// If the use of an audio is finished, close it to free memory
	// mciSendString("close bgsong", NULL, 0, NULL);
	// mciSendString("close ggsong", NULL, 0, NULL);

	  // 60ms per frame (tune: 40 faster, 80 slower)

	iInitialize(SCREEN_W, SCREEN_H, "Errand Day");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initBackground();
	initImages();

	iSetTimer(12, updateGame);
	iStart();
	return 0;
}