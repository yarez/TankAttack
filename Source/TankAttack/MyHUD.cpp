/*
Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
Date: 12-12-2015

This is the cpp file for the MyHUD class.
*/

#include "TankAttack.h"
#include "MyHUD.h"

//Define numbers for several button types
#define BUTTONTYPE_MAIN_RESTART 	3
#define BUTTONTYPE_MAIN_EXIT 		2
#define BUTTONTYPE_MAIN_RESUME		1

#define BUTTONTYPE_CONFIRM_YES 	1
#define BUTTONTYPE_CONFIRM_NO 	2

#define CANVAS_WHITE if(Canvas) Canvas->SetDrawColor(FColor_White);

//Creates some const colors for use in the hud 
const FColor AMyHUD::FColorBlack = FColor(0, 0, 0, 255);
const FColor AMyHUD::FColorRed = FColor(255, 0, 0, 255);
const FColor AMyHUD::FColorYellow = FColor(255, 255, 0, 255);
const FColor AMyHUD::FColorBlue = FColor(0, 0, 255, 255);
const FColor AMyHUD::FColor_White = FColor(255, 255, 255, 255);

const FLinearColor AMyHUD::LC_Black = FLinearColor(0, 0, 0, 1);
const FLinearColor AMyHUD::LC_Pink = FLinearColor(1, 0, 1, 1);
const FLinearColor AMyHUD::LC_Red = FLinearColor(1, 0, 0, 1);
const FLinearColor AMyHUD::LC_Yellow = FLinearColor(1, 1, 0, 1);
const FLinearColor AMyHUD::LC_White = FLinearColor(1, 1, 1, 1);

AMyHUD::AMyHUD(const class FObjectInitializer &PCIP) :Super(PCIP){
	//Draw HUD?
	DontDrawHUD = true;

	//States
	ConfirmDialogOpen = false;
	InMainMenu = true;

	//Scale
	GlobalHUDMult = 1;
	DefaultFontScale = 0.7;   //scaling down a size 36 font

	//	I recommend creating fonts at a high resolution / size like 36
	//	then you can scale down the font as needed to any size of your choice
	// this avoids needing to make multiple fonts for different sizes, but have a high
	// resolution when you use larger font sizes
}

void AMyHUD::AddHealth(){
	//Gets called when a health pack is hit to set the add to true 
	//for use in the drawhud
	add = true;
}

void AMyHUD::LoseHealth(){
	//Gets called the player is hit to set the lose to true
	//for use in the drawhud
	lose = true;
}

void AMyHUD::BotsDead(){
	botsRemaining--;
	if (botsRemaining == 0)
		botsKilled = true;
}

// Draw Dialogs
void AMyHUD::DrawHUD_DrawDialogs()
{
	DrawMainMenuButtons();
	if (ConfirmDialogOpen) DrawConfirm();
}

void AMyHUD::DrawConfirm()
{
	//Black rect with white border around it
	DrawHUDRect(Canvas->SizeX / 2 - 100, Canvas->SizeY / 2 - 60, 220, 120, FLinearColor(1, 1, 1, 1));
	DrawHUDRect(Canvas->SizeX / 2 - 90, Canvas->SizeY / 2 - 50, 200, 100, FLinearColor(0, 0, 0, 1));

	//Draw buttons
	DrawConfirmButtons();
}

//Buttons
void AMyHUD::DrawMainMenuButtons()
{
	//Start Point
	float xStart = 100;
	float yStart = 190;

	//Background
	//Tile imported into content browser with black border
	DrawHUDRect(xStart-10, yStart - 10, 170, 80, FLinearColor(0, 0, 0, 1));
	VDrawTile(ButtonBackground, xStart, yStart, 150, 60, FColor(255, 255, 255, 255)); //alpha 120/255

	//Resume Text for Menu
	DrawHUDText(
		SketchFont, "Resume", xStart + 25, yStart + 10,
		FColorBlack, DefaultFontScale,
		false
		);

	//Clear buttons with ButtonsMain.Empty()
	//Sets up the info for the button with the struct
	if (ButtonsMain.Num() < 1)
	{
		FHUDButtonStruct newButton = FHUDButtonStruct();
		newButton.type = BUTTONTYPE_MAIN_RESUME;
		newButton.minX = xStart;
		newButton.maxX = xStart + 150;
		newButton.minY = yStart;
		newButton.maxY = yStart + 80;

		//Add to correct array
		ButtonsMain.Add(newButton);
	}

	//Start Point
	xStart = 100;
	yStart = 280;
	//Background
	//Tile imported into content browser with black border
	DrawHUDRect(xStart - 10, yStart - 10, 170, 80, FLinearColor(0, 0, 0, 1));
	VDrawTile(ButtonBackground, xStart, yStart, 150, 60, FColor(255, 255, 255, 255)); 

	//Exit Text
	DrawHUDText(
		SketchFont, "Exit", xStart + 45, yStart + 10,
		FColorBlack, DefaultFontScale,
		false
		);

	//Sets up the info for the button with the struct
	if (ButtonsMain.Num() < 2)
	{
		FHUDButtonStruct newButton = FHUDButtonStruct();
		newButton.type = BUTTONTYPE_MAIN_EXIT;
		newButton.minX = xStart;
		newButton.maxX = xStart + 150;
		newButton.minY = yStart;
		newButton.maxY = yStart + 80;

		//Add to correct array
		ButtonsMain.Add(newButton);
	}

	//Start Point
	xStart = 100;
	yStart = 370; 

	//Background
	//Tile imported into content browser with black border
	DrawHUDRect(xStart - 10, yStart - 10, 170, 80, FLinearColor(0, 0, 0, 1));
	VDrawTile(ButtonBackground, xStart, yStart, 150, 60, FColor(255, 255, 255, 255)); //alpha 120/255

	//Restart Text
	DrawHUDText(
		SketchFont, "Restart", xStart + 23, yStart + 10,
		FColorBlack, DefaultFontScale,
		false
		);

	//Sets up the info for the button with the struct
	if (ButtonsMain.Num() < 3)
	{
		FHUDButtonStruct newButton = FHUDButtonStruct();
		newButton.type = BUTTONTYPE_MAIN_RESTART;
		newButton.minX = xStart;
		newButton.maxX = xStart + 150;
		newButton.minY = yStart;
		newButton.maxY = yStart + 80;

		//Add to correct array
		ButtonsMain.Add(newButton);
	}

}
void AMyHUD::DrawConfirmButtons()
{
	//Start Point
	float xStart = Canvas->SizeX / 2 - 100;
	float yStart = Canvas->SizeY / 2 - 40;

	//Highlighted?
	if (ActiveButton_Type == BUTTONTYPE_CONFIRM_YES) ColorPtr = &LC_Red;
	else ColorPtr = &LC_White;

	//Yes Text
	DrawHUDText(
		SketchFont, "Yes", xStart + 30, yStart + 20,
		*ColorPtr, DefaultFontScale,
		true, LC_White
		);

	//Sets up the info for the button with the struct
	if (ButtonsConfirm.Num() < 1)
	{
		FHUDButtonStruct newButton = FHUDButtonStruct();
		newButton.type = BUTTONTYPE_CONFIRM_YES;
		newButton.minX = xStart;
		newButton.maxX = xStart + 75;
		newButton.minY = yStart + 20;
		newButton.maxY = yStart + 60;

		//Add to correct array
		ButtonsConfirm.Add(newButton);
	}

	//Start Point
	xStart = Canvas->SizeX / 2 + 20;
	yStart = Canvas->SizeY / 2 - 40;

	//Highlighted?
	if (ActiveButton_Type == BUTTONTYPE_CONFIRM_NO) ColorPtr = &LC_Red;
	else ColorPtr = &LC_White;

	//No Text
	DrawHUDText(
		SketchFont, "No", xStart + 30, yStart + 20,
		*ColorPtr, DefaultFontScale,
		true, LC_White
		);

	//Sets up the info for the button with the struct
	if (ButtonsConfirm.Num() < 2)
	{
		FHUDButtonStruct newButton = FHUDButtonStruct();
		newButton.type = BUTTONTYPE_CONFIRM_NO;
		newButton.minX = xStart;
		newButton.maxX = xStart + 75;
		newButton.minY = yStart + 20;
		newButton.maxY = yStart + 60;

		//Add to correct array
		ButtonsConfirm.Add(newButton);
	}
}

void AMyHUD::DrawHealthBar()
{
	//Health Text
	DrawHUDText(
		ToyFont, "Health", 100, 50,
		FColor_White, DefaultFontScale,
		true
		);

	//Tank Attack Text at the top of the screen
	DrawHUDText(
		ToyFont, "Tank Attack", 290, 20,
		FColor_White, 1.0F,
		true
		);

	//Goes from left to right incrementing the health
	//when add is true and it is not gameover
	if (add && !gameover){
		if (LC_Blue2.A == 0){
			LC_Blue2.A = 1;
			add = false;
		}
		else if (LC_Blue3.A == 0){
			LC_Blue3.A = 1;
			add = false;
		}
		else if (LC_Blue4.A == 0){
			LC_Blue4.A = 1; 
			add = false;
		}
		else if (LC_Blue5.A == 0){
			LC_Blue5.A = 1;
			add = false;
		}

	}

	//when lose is true it decrements health
	if (lose){
		if (LC_Blue5.A == 1){
			LC_Blue5.A = 0;
			lose = false;
		}
		else if (LC_Blue4.A == 1){
			LC_Blue4.A = 0;
			lose = false;
		}
		else if (LC_Blue3.A == 1){
			LC_Blue3.A = 0;
			lose = false;
		}
		else if (LC_Blue2.A == 1){
			LC_Blue2.A = 0;
			lose = false;
		}
		else if (LC_Blue1.A == 1){
			LC_Blue1.A = 0;
			lose = false;
			gameover = true; 
		}
	}


	//Draws the squares for the health bar
	DrawHUDRect(100, 100, 20, 20, LC_Blue1);
	DrawHUDRect(120, 100, 20, 20, LC_Blue2);
	DrawHUDRect(140, 100, 20, 20, LC_Blue3);
	DrawHUDRect(160, 100, 20, 20, LC_Blue4);
	DrawHUDRect(180, 100, 20, 20, LC_Blue5);

}

// Is cursor in Buttons
int32 AMyHUD::CheckCursorInButton(const TArray<FHUDButtonStruct>& ButtonArray)
{
	for (int32 b = 0; b < ButtonArray.Num(); b++)
	{
		CurCheckButton = &ButtonArray[b];

		//check cursor in bounds
		if (CurCheckButton->minX <= MouseLocation.X && MouseLocation.X <= CurCheckButton->maxX &&
			CurCheckButton->minY <= MouseLocation.Y && MouseLocation.Y <= CurCheckButton->maxY)
		{

			//Active Button Type
			ActiveButton_Type = CurCheckButton->type;

			//Mouse Clicked?
			if (ThePC->WasInputKeyJustPressed(EKeys::LeftMouseButton))
			{
				return ActiveButton_Type;
			}
		}
	}

	//No Click Occurred This Tick
	return -1;
}

//Check Confirm
void AMyHUD::CheckCursorInButtonsConfirm()
{
	//Check Confirm Buttons
	ClickedButtonType = CheckCursorInButton(ButtonsConfirm); //fills global ActiveButton_Type

	if (ClickedButtonType == BUTTONTYPE_CONFIRM_YES)
	{
		//Exits game
		ThePC->ConsoleCommand("Exit");
		return;
	}
	if (ClickedButtonType == BUTTONTYPE_CONFIRM_NO)
	{
		ConfirmDialogOpen = false;
		ButtonsConfirm.Empty(); //Buttons not needed anymore
		return;
	}
}

//Check Buttons
void AMyHUD::CheckCursorInButtonsMain()
{
	//Check Confirm Buttons
	ClickedButtonType = CheckCursorInButton(ButtonsMain);

	if (ClickedButtonType == BUTTONTYPE_MAIN_RESTART)
	{
		//Restarts the level and resets information so everything redisplays on hud
		d1 = true, d2 = false, d3 = false, d4 = false;
		gameover = false;
		LC_Blue1.A = 1, LC_Blue2.A = 1, LC_Blue3.A, LC_Blue4.A = 1, LC_Blue5.A = 1;
		botsKilled = false;
		ThePC->ConsoleCommand("RestartLevel");
		return;
	}
	if (ClickedButtonType == BUTTONTYPE_MAIN_EXIT)
	{
		//Turns on the confirm buttons
		ConfirmDialogOpen = true;
		return;
	}
	if (ClickedButtonType == BUTTONTYPE_MAIN_RESUME)
	{
		//Unpauses the game when resume is selected
		ThePC->ConsoleCommand("Pause");
		DontDrawHUD = true; 
		return;
	}
}

//Check cursor
void AMyHUD::DrawHUD_CheckCursorInButtons()
{
	if (ConfirmDialogOpen)
	{
		CheckCursorInButtonsConfirm();

		return;
	}

	CheckCursorInButtonsMain();
}

//Resets infomation after each tick
void AMyHUD::DrawHUD_Reset()
{
	ActiveButton_Type = -1;
	CursorHoveringInButton = false;
}

//DrawHUD gets called every tick
void AMyHUD::DrawHUD(){

	//Have PC for Mouse Cursor?
	if (!ThePC)
	{
		//Attempt to Reacquire PC
		ThePC = GetOwningPlayerController();

		//Could Not Obtain PC
		if (!ThePC) return;
	}
	//Display the Cursor
	ThePC->bShowMouseCursor = true;

	//Health Bar is always drawn on screen
	DrawHealthBar();


	FVector2D ScreenSize = FVector2D(Canvas->SizeX, Canvas->SizeY);
	Super::DrawHUD();

	//Display the instructions for until the timer hits zero
	if (d5){
		if (GetWorldTimerManager().GetTimerRemaining(Handle5) > 0){
			DrawHUDText(ToyFont, "Controls:", x, y, FColorRed, 1.0F,true);
			DrawHUDText(SketchFont, "WASD to Move", x, y+43, FColorRed, .5F, true, LC_Red);
			DrawHUDText(SketchFont, "Mouse to aim", x, y+63, FColorRed, .5F, true, LC_Red);
			DrawHUDText(SketchFont, "Click to shoot", x, y+83, FColorRed, .5F, true, LC_Red);
			DrawHUDText(SketchFont, "Some walls are breakable", x, y+103, FColorRed, .5F, true, LC_Red);
			DrawHUDText(SketchFont, "Press M for Menu", x, y+123, FColorRed, .5F, true, LC_Red);
			DrawHUDText(ToyFont, "-----------------", x, y+160, FColorRed, .5F, true, LC_Red);
			DrawHUDText(ToyFont, "Goal:", x, y+200, FColorRed, 1.0F, true);
			DrawHUDText(SketchFont, "Destroy every enemy", x, y+243, FColorRed, .5F, true,LC_Red);
			DrawHUDText(SketchFont, "Be the sole survivor", x, y+263, FColorRed, .5F, true,LC_Red);
		}
		else {
			GetWorldTimerManager().ClearTimer(Handle5);
			d5 = false;
			d1 = true; 
			GetWorldTimerManager().SetTimer(Handle1, 1.0f, false);
		}
	}
	//When the instructions are finished display 3,2,1, Go! on the screen based on timers
	if (d1){
		if (GetWorldTimerManager().GetTimerRemaining(Handle1) > 0)
			DrawText(TEXT("3"), FColor::Blue, Canvas->SizeX / 2 -70, Canvas->SizeY / 2 -50, SketchFont, 2.0F, false);
		else {
			GetWorldTimerManager().ClearTimer(Handle1);
			d1 = false;
			d2 = true;
			GetWorldTimerManager().SetTimer(Handle2, 1.0f, false);
		}
	}
	if (d2){
		if (GetWorldTimerManager().GetTimerRemaining(Handle2) > 0)
			DrawText(TEXT("2"), FColor::Blue, Canvas->SizeX / 2-70, Canvas->SizeY / 2-50, SketchFont, 2.0F, false);
		else{
			GetWorldTimerManager().ClearTimer(Handle2);
			d2 = false;
			d3 = true;
			GetWorldTimerManager().SetTimer(Handle3, 1.0f, false);
		}
	}
	if (d3){
		if (GetWorldTimerManager().GetTimerRemaining(Handle3) > 0)
			DrawText(TEXT("1"), FColor::Blue, Canvas->SizeX / 2-70, Canvas->SizeY / 2-50, SketchFont, 2.0F, false);
		else{
			GetWorldTimerManager().ClearTimer(Handle3);
			d3 = false;
			d4 = true;
			GetWorldTimerManager().SetTimer(Handle4, 1.0f, false);
		}
	}
	if (d4){
		if (GetWorldTimerManager().GetTimerRemaining(Handle4) > 0)
			DrawText(TEXT("GO!"), FColor::Blue, (Canvas->SizeX / 2)-95, (Canvas->SizeY / 2)-50, SketchFont, 2.0F, false);
		else{
			d4 = false;
			GetWorldTimerManager().ClearTimer(Handle4);
			canMove = true;
		}
	}

	//gameover text when gameover is reached
	if (gameover){
		DrawText(TEXT("GAME OVER"), FColor::Red, (Canvas->SizeX / 2) - 250, (Canvas->SizeY / 2) - 30, ToyFont, 2.0F, false);
		ThePC->ConsoleCommand("Pause");
		DontDrawHUD = false;
	}

	if (botsKilled){
		DrawText(TEXT("YOU WON!"), FColor::Red, (Canvas->SizeX / 2) - 250, (Canvas->SizeY / 2) - 30, ToyFont, 2.0F, false);
		ThePC->ConsoleCommand("Pause");
		DontDrawHUD = false;
	}

	//Draw HUD?
	//DrawHUD is only turned on when the menu button is pressed
	if (DontDrawHUD) return;

	//Super
	Super::DrawHUD();

	//No Canvas?
	if (!Canvas) return;

	//Reset States
	DrawHUD_Reset();

	//Get New Mouse Position
	ThePC->GetMousePosition(MouseLocation.X, MouseLocation.Y);

	//Cursor In Buttons
	DrawHUD_CheckCursorInButtons();

	//Draw Dialogs

	DrawHUD_DrawDialogs();
	//}
		


	
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	//Start the timer for the instructions as soon as you begin
	GetWorldTimerManager().SetTimer(Handle5, 13.0f, false);
	d1 = false, d2 = false, d3 = false, d4 = false, d5 = true;
	LC_Blue1.A = 1, LC_Blue2.A = 1, LC_Blue3.A, LC_Blue4.A = 1, LC_Blue5.A = 1; 
	botsKilled = false;
	gameover = false; 
}

void AMyHUD::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}


