// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "UI_LoginMain.generated.h"


/**
 * 
 */
class UEditableTextBox;
class UButton;
UCLASS()
class MULTIPLAYERRPG_API UUI_LoginMain : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Account;
	
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Password;

	UPROPERTY(meta = (BindWidget))
	UButton* LoginButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RegisterButton;

public:
	UUI_LoginMain(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct();
	virtual void NativeDestruct();

protected:
	UFUNCTION()
	void SignIn();
	UFUNCTION()
	void RegisterIn();

	void OnResponseReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};
