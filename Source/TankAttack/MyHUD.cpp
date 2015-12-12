// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAttack.h"
#include "MyHUD.h"

#define BUTTONTYPE_MAIN_RESTART 	3
#define BUTTONTYPE_MAIN_EXIT 		2
#define BUTTONTYPE_MAIN_RESUME		1

#define BUTTONTYPE_CONFIRM_YES 	1
#define BUTTONTYPE_CONFIRM_NO 	2

#define CANVAS_WHITE if(Canvas) Canvas->SetDrawColor(FColor_White);

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
	add = true;
}

void AMyHUD::LoseHealth(){
	lose = true;
}

// Draw Dialogs
void AMyHUD::DrawHUD_DrawDialogs()
{
	DrawMainMenuButtons();
	if (ConfirmDialogOpen) DrawConfirm();
}

void AMyHUD::DrawConfirm()
{
	//Blue rect with alpha 50%
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
	DrawHUDRect(xStart-10, yStart - 10, 170, 80, FLinearColor(0, 0, 0, 1));
	VDrawTile(ButtonBackground, xStart, yStart, 150, 60, FColor(255, 255, 255, 255)); //alpha 120/255

	//Text
	DrawHUDText(
		SketchFont, "Resume", xStart + 25, yStart + 10,
		FColorBlack, DefaultFontScale,
		false
		);

	//Clear buttons with ButtonsMain.Empty()
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


	xStart = 100;
	yStart = 280;
	DrawHUDRect(xStart - 10, yStart - 10, 170, 80, FLinearColor(0, 0, 0, 1));
	VDrawTile(ButtonBackground, xStart, yStart, 150, 60, FColor(255, 255, 255, 255)); //alpha 120/255

	//Text
	DrawHUDText(
		SketchFont, "Exit", xStart + 45, yStart + 10,
		FColorBlack, DefaultFontScale,
		false
		);

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

	xStart = 100;
	yStart = 370; 
	DrawHUDRect(xStart - 10, yStart - 10, 170, 80, FLinearColor(0, 0, 0, 1));
	VDrawTile(ButtonBackground, xStart, yStart, 150, 60, FColor(255, 255, 255, 255)); //alpha 120/255

	//Text
	DrawHUDText(
		SketchFont, "Restart", xStart + 23, yStart + 10,
		FColorBlack, DefaultFontScale,
		false
		);

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
	float xStart = Canvas->SizeX / 2 - 100;
	float yStart = Canvas->SizeY / 2 - 40;

	//Highlighted?
	if (ActiveButton_Type == BUTTONTYPE_CONFIRM_YES) ColorPtr = &LC_Red;
	else ColorPtr = &LC_White;

	//Text
	DrawHUDText(
		SketchFont, "Yes", xStart + 30, yStart + 20,
		*ColorPtr, DefaultFontScale,
		true, LC_White
		);

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

	xStart = Canvas->SizeX / 2 + 20;
	yStart = Canvas->SizeY / 2 - 40;

	//Highlighted?
	if (ActiveButton_Type == BUTTONTYPE_CONFIRM_NO) ColorPtr = &LC_Red;
	else ColorPtr = &LC_White;

	//Text
	DrawHUDText(
		SketchFont, "No", xStart + 30, yStart + 20,
		*ColorPtr, DefaultFontScale,
		true, LC_White
		);

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
	DrawHUDText(
		ToyFont, "Health", 100, 50,
		FColor_White, DefaultFontScale,
		true
		);

	//Goes from left to right
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
		GetWorldTimerManager().SetTimer(Handle1, 1.0f, false);
		GetWorldTimerManager().SetTimer(Handle2, 1.0f, false);
		GetWorldTimerManager().SetTimer(Handle3, 1.0f, false);
		GetWorldTimerManager().SetTimer(Handle4, 1.0f, false);
		GetWorldTimerManager().PauseTimer(Handle2);
		GetWorldTimerManager().PauseTimer(Handle3);
		GetWorldTimerManager().PauseTimer(Handle4);
		d1 = true, d2 = false, d3 = false, d4 = false;
		gameover = false;
		ThePC->ConsoleCommand("RestartLevel");
		
		return;
	}
	if (ClickedButtonType == BUTTONTYPE_MAIN_EXIT)
	{
		ConfirmDialogOpen = true;
		return;
	}
	if (ClickedButtonType == BUTTONTYPE_MAIN_RESUME)
	{
		ThePC->ConsoleCommand("Pause");
		DontDrawHUD = true; 
		return;
	}
}
void AMyHUD::DrawHUD_CheckCursorInButtons()
{
	if (ConfirmDialogOpen)
	{
		CheckCursorInButtonsConfirm();

		return;
	}

	CheckCursorInButtonsMain();
}

void AMyHUD::DrawHUD_Reset()
{
	ActiveButton_Type = -1;
	CursorHoveringInButton = false;
}
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

	DrawHealthBar();


	FVector2D ScreenSize = FVector2D(Canvas->SizeX, Canvas->SizeY);
	Super::DrawHUD();
	/*DrawText(TEXT("Controls:"), FColor::Red, x, y, HUDFont, 2.0F, false);
	DrawText(TEXT("WASD to Move"), FColor::Red, x, y + 20, HUDFont, 2.0F, false);
	DrawText(TEXT("Arrow Keys to turn"), FColor::Red, x, y + 40, HUDFont, 2.0F, false);
	DrawText(TEXT("Click mouse on enemy to shoot them"), FColor::Red, x, y + 80, HUDFont, 2.0F, false);
	DrawText(TEXT("Some walls are breakable and can be shot at"), FColor::Red, x, y + 100, HUDFont, 2.0F, false);
	DrawText(TEXT("Press M for Menu"), FColor::Red, x, y + 120, HUDFont, 2.0F, false);
	DrawText(TEXT("Goal:"), FColor::Red, x, y + 160, HUDFont, 2.0F, false);
	DrawText(TEXT("Destroy all enemies"), FColor::Red, x, y + 180, HUDFont, 2.0F, false);
	DrawText(TEXT("Be the last one standing"), FColor::Red, x, y + 200, HUDFont, 2.0F, false);
	DrawText(TEXT("------"), FColor::Red, x, y + 220, HUDFont, 2.0F, false);
	DrawText(TEXT("------"), FColor::Red, x, y + 240, HUDFont, 2.0F, false);
	y -= .5;
	if (j > 450){ */
	if (d1){
		if (GetWorldTimerManager().GetTimerRemaining(Handle1) > 0)
			DrawText(TEXT("3"), FColor::Blue, Canvas->SizeX / 2 -70, Canvas->SizeY / 2 -50, SketchFont, 2.0F, false);
		else {
			GetWorldTimerManager().ClearTimer(Handle1);
			d1 = false;
			d2 = true;
			GetWorldTimerManager().SetTimer(Handle2, 1.0f, false);
			//GetWorldTimerManager().UnPauseTimer(Handle2);
		}
	}
	if (d2){
		if (GetWorldTimerManager().GetTimerRemaining(Handle2) > 0)
			DrawText(TEXT("2"), FColor::Blue, Canvas->SizeX / 2 -70, Canvas->SizeY / 2 - 50, SketchFont, 2.0F, false);
		else{
			GetWorldTimerManager().ClearTimer(Handle2);
			d2 = false;
			d3 = true;
			GetWorldTimerManager().SetTimer(Handle3, 1.0f, false);
			//GetWorldTimerManager().UnPauseTimer(Handle3);
		}
	}
	if (d3){
		if (GetWorldTimerManager().GetTimerRemaining(Handle3) > 0)
			DrawText(TEXT("1"), FColor::Blue, Canvas->SizeX / 2 -70, Canvas->SizeY / 2 -50, SketchFont, 2.0F, false);
		else{
			GetWorldTimerManager().ClearTimer(Handle3);
			d3 = false;
			d4 = true;
			GetWorldTimerManager().SetTimer(Handle4, 1.0f, false);
			//GetWorldTimerManager().UnPauseTimer(Handle4);
		}
	}
	if (d4){
		if (GetWorldTimerManager().GetTimerRemaining(Handle4) > 0)
			DrawText(TEXT("GO!"), FColor::Blue, (Canvas->SizeX / 2)-95, Canvas->SizeY / 2-50, SketchFont, 2.0F, false);
		else{
			d4 = false;
			GetWorldTimerManager().ClearTimer(Handle4);
			canMove = true;
		}
	}

	//Draw HUD?
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
		

	/*if (gameover)
		DrawText(TEXT("GAME OVER"), FColor::Black, 350, 200, HUDFont, 3.0F, false);
	if (win){
		DrawText(TEXT("YOU'RE CURED"), FColor::Black, 350, 200, HUDFont, 3.0F, false);
		//GetWorldTimerManager().PauseTimer(Handle);
	}
	if (nowin){
		nw -= .3;
		DrawText(TEXT("Need more pills"), FColor::Black, 350, nw, HUDFont, 3.0F, false);

	}
	if (nw < -50)
		nowin = false;*/
	/*if ((y + 240) < -50){
		DrawText(TEXT("Begin Your Quest"), FColor::White, i, j, HUDFont, 2.0F, false);
		i += 2;
		j += 2;
	}*/
}
void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	/*GetWorldTimerManager().SetTimer(Handle1, this, &AMyHUD::Draw, 10.0f, false);
	GetWorldTimerManager().SetTimer(Handle2, this, &AMyHUD::Draw, 10.0f, false);
	GetWorldTimerManager().SetTimer(Handle3, this, &AMyHUD::Draw, 10.0f, false);
	GetWorldTimerManager().SetTimer(Handle4, this, &AMyHUD::Draw, 10.0f, false);*/
	GetWorldTimerManager().SetTimer(Handle1, 1.0f, false);
	//GetWorldTimerManager().PauseTimer(Handle2);
	//GetWorldTimerManager().PauseTimer(Handle3);
	//GetWorldTimerManager().PauseTimer(Handle4);
	d1 = true, d2 = false, d3 = false, d4 = false;
	gameover = false; 

	//Create tick to display remaining time and possibly pause the time until the begin has made it off the screen
	//Destroy the actor when the time runs out with a bool that connects to the actor class from here 
	//in actor fix the calling of the function in block to switch the colors of the breadcrumbs 
}
void AMyHUD::Draw(){
	gameover = true;
	//FString Over = "Game Over";
	//FLinearColor FontC = FLinearColor(1.0f, 1.0f, 1.0f);
	//FCanvasTextItem NewText(FVector2D(50, 50), FText::FromString(Over), HUDFont, FontC);
	//NewText.Scale.Set(5,5);
	//Canvas->DrawItem(NewText);
}

void AMyHUD::WinDraw(){
	win = true;

}

void AMyHUD::NoWinDraw(){
	nowin = true;
}

void AMyHUD::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	//t = GetWorldTimerManager().GetTimerRemaining(Handle);

}


