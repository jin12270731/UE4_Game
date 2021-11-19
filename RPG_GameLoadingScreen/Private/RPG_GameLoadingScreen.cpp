// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "../Public/RPG_GameLoadingScreen.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"
#include "Widgets/Images/SThrobber.h"

#define LOCTEXT_NAMESPACE "RPG_GameLoadingScreen" 

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!
struct FRPGLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	bool isObject;
	FRPGLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		: FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		auto object = LoadObject<UObject>(NULL, *InTextureName.ToString());
		SetResourceObject(object);
		object ? isObject = true : isObject = false;
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (UObject* CachedResourceObject = GetResourceObject())
		{
			Collector.AddReferencedObject(CachedResourceObject);
		}
	}
};

class SRPGLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRPGLoadingScreen) {}
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs)
	{
		// Load version of the logo with text baked in, path is hardcoded because this loads very early in startup
		static const FName LoadingScreenName(TEXT("/Game/UI/Loading/T_test.T_test"));
		FVector2D Result = FVector2D(1920, 1080);

		if (GEngine && GEngine->GameViewport)
		{
			GEngine->GameViewport->GetViewportSize(Result);
		}
		//
		auto LoadObject = new FRPGLoadingScreenBrush(LoadingScreenName, Result);
		LoadingScreenBrush = MakeShareable(LoadObject);

		FSlateBrush* BGBrush = new FSlateBrush();
		BGBrush->TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

		FTextBlockStyle* TextStyle = new FTextBlockStyle();
		TextStyle->SetFont("Italic", 80);

		FSlateBrush* BGLoading = new FSlateBrush();
		BGLoading->SetImageSize(FVector2D(12, 12));
		
		if (LoadObject->isObject)
		{
			ChildSlot
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SBorder)
					.BorderImage(BGBrush)
				]
			+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Bottom)
				[
					SNew(SImage)
					.Image(LoadingScreenBrush.Get())
				]
			+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(FMargin(10.0f))
				[
					SNew(SCircularThrobber)
					.Visibility(this, &SRPGLoadingScreen::GetLoadIndicatorVisibility)
					.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f))
				]
				]
				];
		}
		else
		{
			ChildSlot
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SBorder)
					.BorderImage(BGBrush)
				]
			+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Bottom)
				[
					SNew(STextBlock)
					.Font(FCoreStyle::GetDefaultFontStyle("Regular", 80))
					.Text(LOCTEXT("Test", "Now Loading"))
					.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f))
					.Visibility(this, &SRPGLoadingScreen::GetLoadIndicatorVisibility)
					
					
				]
			+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(FMargin(20.0f))
				[
					SNew(SCircularThrobber)
					.Visibility(this, &SRPGLoadingScreen::GetLoadIndicatorVisibility)
					.ColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f))
					.PieceImage(BGLoading)
					.Radius(40.0f)
				]
				]
				];
		}
	}

private:
	/** Rather to show the ... indicator */
	EVisibility GetLoadIndicatorVisibility() const
	{
		bool Vis = GetMoviePlayer()->IsLoadingFinished();
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}

	/** Loading screen image brush */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

class FActionRPGLoadingScreenModule : public IActionRPGLoadingScreenModule
{
public:
	virtual void StartupModule() override
	{
		// Force load for cooker reference
		LoadObject<UObject>(nullptr, TEXT("/Game/UI/T_ActionRPG_TransparentLogo.T_ActionRPG_TransparentLogo"));

		if (IsMoviePlayerEnabled())
		{
			CreateScreen();
		}
	}

	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) override
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = !bPlayUntilStopped;
		LoadingScreen.bWaitForManualStop = bPlayUntilStopped;
		LoadingScreen.bAllowEngineTick = bPlayUntilStopped;
		LoadingScreen.MinimumLoadingScreenDisplayTime = PlayTime;
		LoadingScreen.WidgetLoadingScreen = SNew(SRPGLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

	virtual void StopInGameLoadingScreen() override
	{
		GetMoviePlayer()->StopMovie();
	}

	virtual void CreateScreen()
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 3.f;
		LoadingScreen.WidgetLoadingScreen = SNew(SRPGLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

};

IMPLEMENT_GAME_MODULE(FActionRPGLoadingScreenModule, RPG_GameLoadingScreen);

#undef LOCTEXT_NAMESPACE
