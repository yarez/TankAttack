/*
Names: Taylor Anderson-Barkley, William Bennett, Kira Foglesong
Date: 12-12-2015

This is the header file for the MyHUD class.
*/

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */


//Defines the struct for the buttons
USTRUCT()
struct FHUDButtonStruct
{
	GENERATED_USTRUCT_BODY()

		//Vars
		int32 		type;
		float 		minX;
		float 		maxX;
		float 		minY;
		float 		maxY;

	//~

	//default properties

	FHUDButtonStruct()
	{
		type = -1;
		minX = 0;
		maxX = 0;
		minY = 0;
		maxY = 0;
	}
};

UCLASS()
class TANKATTACK_API AMyHUD : public AHUD
{
	GENERATED_UCLASS_BODY()
		//Sets up fonts for game
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyHUD)
		UFont* ToyFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyHUD)
		UFont* SketchFont;

	/** Font Scaling Used By Your HUD Code */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyHUD)
		float DefaultFontScale;

	/** HUD Scaling */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyHUD)
		float GlobalHUDMult;

	/** Button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
		UTexture2D* ButtonBackground;

	/* Draw Hud? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)
		bool DontDrawHUD;

public:
	//Location of the mouse in order to know if mouse is in button
	FVector2D MouseLocation;

	//Buttons
	TArray<FHUDButtonStruct> ButtonsMain;
	TArray<FHUDButtonStruct> ButtonsConfirm;

	//Check if Cursor In buttons
	void DrawHUD_CheckCursorInButtons();
	void CheckCursorInButtonsMain();
	void CheckCursorInButtonsConfirm();
	const FHUDButtonStruct* CurCheckButton;
	int32 CheckCursorInButton(const TArray<FHUDButtonStruct>& ButtonArray);
	int32 ClickedButtonType;

	//States
	bool ConfirmDialogOpen;
	bool InMainMenu;
	bool canMove = false; 

	int32 		ActiveButton_Type;

	//Colors
	FLinearColor LC_Blue1 = FLinearColor(0, 0, 1, 1);
	FLinearColor LC_Blue2 = FLinearColor(0, 0, 1, 1);
	FLinearColor LC_Blue3 = FLinearColor(0, 0, 1, 1);
	FLinearColor LC_Blue4 = FLinearColor(0, 0, 1, 1);
	FLinearColor LC_Blue5 = FLinearColor(0, 0, 1, 1);

	//Bool for add health and lose health
	bool add = false, lose = false; 
	//Check if cursor is hovering over button
	bool CursorHoveringInButton;

	//Colors
	const FLinearColor * ColorPtr;
	static const FColor		FColorBlack;
	static const FColor		FColorRed;
	static const FColor		FColorYellow;
	static const FColor		FColorBlue;
	static const FColor		FColor_White;
	static const FLinearColor LC_Black;
	static const FLinearColor LC_Pink;
	static const FLinearColor LC_Red;
	static const FLinearColor LC_Yellow;
	static const FLinearColor LC_White;

	//Define the DrawHUDRect function for drawing rectangles
	FORCEINLINE void DrawHUDRect(
		float X, float Y,
		float Width, float Height,
		const FLinearColor& Color
		)
	{
		if (!Canvas) return;

		FCanvasTileItem RectItem(
			FVector2D(X, Y),
			FVector2D(Width, Height),
			Color
			);

		RectItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(RectItem);
	}

	//Define DrawHUDText function for drawing text
	FORCEINLINE void DrawHUDText(
		UFont*	TheFont,
		const FString& TheStr,
		const float& X, const float& Y,
		const FLinearColor& TheColor,
		const float& TheScale,
		bool DrawOutline = false,
		const FLinearColor OutlineColor = FLinearColor(0, 0, 0, 1)
		) {
		if (!Canvas) return;

		//Text and Font
		FCanvasTextItem NewText(
			FVector2D(X, Y),
			FText::FromString(TheStr),
			TheFont,
			TheColor
			);

		//Text Scale
		NewText.Scale.Set(TheScale, TheScale);

		//Outline gets its alpha from the main color
		NewText.bOutlined = true;
		NewText.OutlineColor = OutlineColor;
		NewText.OutlineColor.A = TheColor.A * 2;

		Canvas->DrawItem(NewText);
	}

	//Define VDrawTile for drawing rectangles with texture
	FORCEINLINE void VDrawTile(UTexture2D* tex, float x, float y, float screenX, float screenY, const FColor& TheColor)
	{
		if (!Canvas) return;
		if (!tex) return;

		Canvas->SetDrawColor(TheColor);

		Canvas->DrawTile(
			tex, x, y,
			screenX, //screen width
			screenY,  //screen height
			0, //texture start width
			0, //texture start height
			tex->GetSurfaceWidth(), //texture width from start
			tex->GetSurfaceHeight(), //texture height from start
			BLEND_Translucent
			);
	}

	
	void DrawHUD_DrawDialogs();

	//Menus
	void DrawConfirm();

	//Buttons
	void DrawMainMenuButtons();
	void DrawConfirmButtons();
	void DrawHealthBar();

	//Core
	APlayerController* ThePC;
	//Draw HUD
	void DrawHUD_Reset();
	AMyHUD();
	//boolean values for gameover and if the game has begun
	bool gameover = false, begun = false, win = false, nowin = false;
	float t;
	//Handles for the timers used
	FTimerHandle Handle1, Handle2, Handle3, Handle4, Handle5;
	void AddHealth();
	void LoseHealth();
	float x = 330, y = 75;
	bool d1 = false,d2 = false,d3 =false,d4=false,d5= true;
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	virtual void Tick(float DeltaTime) override;
	void Draw();
	void WinDraw();
	void NoWinDraw();
};
