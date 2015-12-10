// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */


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
	FVector2D MouseLocation;

	//Buttons
	TArray<FHUDButtonStruct> ButtonsMain;
	TArray<FHUDButtonStruct> ButtonsConfirm;

	//Cursor In buttons
	void DrawHUD_CheckCursorInButtons();
	void CheckCursorInButtonsMain();
	void CheckCursorInButtonsConfirm();
	const FHUDButtonStruct* CurCheckButton;
	int32 CheckCursorInButton(const TArray<FHUDButtonStruct>& ButtonArray);
	int32 ClickedButtonType;
	//States
	bool ConfirmDialogOpen;
	bool InMainMenu;

	int32 		ActiveButton_Type;

	bool CursorHoveringInButton;
	//Colors
	const FLinearColor * ColorPtr;
	//Colors
	static const FColor		FColorBlack;
	static const FColor		FColorRed;
	static const FColor		FColorYellow;
	static const FColor		FColorBlue;
	static const FColor		FColor_White;
	static const FLinearColor LC_Black;
	static const FLinearColor LC_Pink;
	static const FLinearColor LC_Red;
	static const FLinearColor LC_Yellow;

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

	//DrawText
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
	bool gameover = false, begun = false, win = false, nowin = false;
	float t;
	int32 min, sec;
	FTimerHandle Handle1, Handle2, Handle3, Handle4;
	void AddHealth();
	void LoseHealth();
	bool d1=true, d2=false, d3=false, d4=false;
	//AMyHUD(const class FObjectInitializer &PCIP);
	UFont *HUDFont;
	virtual void BeginPlay() override;
	int i = 400, j = 200;
	int nw = 200;
	float x = 330, y = 150;
	virtual void DrawHUD() override;
	virtual void Tick(float DeltaTime) override;
	void Draw();
	void WinDraw();
	void NoWinDraw();
};
