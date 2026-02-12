
#include "iGraphics.h"

void drawMainMenu();
void drawOptionMenu();
void drawCreditMenu();
void drawStartMenu();
void drawEasyMenu();
void OptionButtonClickHandler();
void CreditButtonClickHandler();
void StartButtonClickHandler();
void BackButtonClickHandler();
void BackButtonClickHandler2();
void EasyButtonClickHandler();
int x, y;
int mainmenu = 1;
int optionmenu = 0;
int creditmenu = 0;
int startmenu = 0;
int easylevel = 0;
/* -------------------- DRAW -------------------- */

void iDraw()
{
	iClear();
	if (mainmenu == 1){
		drawMainMenu();
	}
	else if (optionmenu == 1){
		drawOptionMenu();
	}
	else if (creditmenu == 1){
		drawCreditMenu();
	}
	else if (startmenu == 1){
		drawStartMenu();
	}
	else if (easylevel == 1){
		drawEasyMenu();
	}
}
	/* -------------------- INPUT -------------------- */
	void iMouseMove(int mx, int my)
	{
		printf("co-ordinations are : x :%d y:%d\n", mx, my);
	}

	void iPassiveMouseMove(int mx, int my)
	{
		x = mx;
		y = my;

	}
	void iMouse(int button, int state, int mx, int my)
	{

		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (mainmenu == 1 && (mx >= 357 && mx <= 431) && (my>=413&&my<=435)){
				OptionButtonClickHandler();
			}
			else if (optionmenu == 1 && (mx >= 338 && mx <= 461) && (my >= 224&& my <= 250)){
			
				CreditButtonClickHandler();
			}
			else if (mainmenu == 1 && (mx >= 447 && mx <= 511) && (my >= 402 && my <= 432)){
				exit(0);
			}
			else if (mainmenu == 1 && (mx >= 240 && mx <= 346) && (my >= 409 && my <= 434)){
				StartButtonClickHandler();
			}
			else if (startmenu == 1 | optionmenu == 1 && (mx >= 35 && mx <= 71) && (my >= 482 && my <= 518)){
				BackButtonClickHandler();
			}
			else if (creditmenu == 1 && (mx >= 35 && mx <= 71) && (my >= 482 && my <= 518)){
				BackButtonClickHandler2();
			}
			else if (startmenu == 1 && (mx >= 300 && mx <= 490) && (my >= 375 && my <= 415)){
				EasyButtonClickHandler();
			}

		}


		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{

		}
	}

	void fixedUpdate() {

	}
	
	void drawMainMenu(){
		iSetColor(255, 255, 255);
		iFilledRectangle(0,0,800,533);
		iShowBMP(0,0,"Images//MainMenu.bmp");
	}
	void drawOptionMenu(){
		iFilledRectangle(0, 0, 800, 533);
		iShowBMP(0, 0, "Images//OptionMenu.bmp");
		iShowBMP2(26, 475, "Images//backbutton.bmp", 0);
	}
	void drawCreditMenu(){
		iFilledRectangle(0, 0, 800, 533);
		iShowBMP(0, 0, "Images//Credits.bmp");
		iShowBMP2(26, 475, "Images//backbutton.bmp", 0);
	}
	void drawStartMenu(){
		iFilledRectangle(0, 0, 800, 533);
		iShowBMP(0, 0, "Images//StartMenu.bmp");
		iShowBMP2(26, 475, "Images//backbutton.bmp", 0);
	}
	void drawEasyMenu(){
		
	}
	void OptionButtonClickHandler(){
		mainmenu = 0;
		optionmenu = 1;
	}
	void CreditButtonClickHandler(){
		mainmenu = 0;
		optionmenu = 0;
		creditmenu = 1;
	}
	void StartButtonClickHandler(){
		mainmenu = 0;
		optionmenu = 0;
		creditmenu = 0;
		startmenu = 1;
	}
	void BackButtonClickHandler(){
		mainmenu = 1;
		optionmenu = 0;
		startmenu = 0;
	}
	void BackButtonClickHandler2(){
		optionmenu = 1;
		creditmenu = 0;
	}
	void EasyButtonClickHandler(){
		mainmenu = 0;
		optionmenu = 0;
		creditmenu = 0;
		startmenu = 0;
		easylevel = 1;

	}

	int main()
	{

		iInitialize(800, 533, "Errand Day");

		

		iStart();
		return 0;
	}

