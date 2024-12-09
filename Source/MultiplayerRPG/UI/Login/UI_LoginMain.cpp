// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_LoginMain.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"

#include "HttpModule.h"
#include "Serialization/JsonSerializerMacros.h"
#include <Kismet/GameplayStatics.h>

UUI_LoginMain::UUI_LoginMain(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UUI_LoginMain::NativeConstruct()
{
	Super::NativeConstruct();

	LoginButton->OnPressed.AddDynamic(this, &UUI_LoginMain::SignIn);
	RegisterButton->OnPressed.AddDynamic(this, &UUI_LoginMain::RegisterIn);
}

void UUI_LoginMain::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_LoginMain::SignIn()
{
	UE_LOG(LogTemp, Display, TEXT("-----------------------------SignIn"));
	FString AccountString = Account->GetText().ToString();
	FString PasswordString = Password->GetText().ToString();
	UE_LOG(LogTemp, Display, TEXT("SignIn___Account: [%s], Password: [%s]"), *AccountString, *PasswordString);

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("Account", AccountString);
	RequestObj->SetStringField("Password", PasswordString);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UUI_LoginMain::OnResponseReceived);

	Request->SetURL("http://127.0.0.1:80/Login");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);

	Request->ProcessRequest();
}

void UUI_LoginMain::RegisterIn()
{
	UE_LOG(LogTemp, Display, TEXT("-----------------------------RegisterIn"));
}

void UUI_LoginMain::OnResponseReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (bSucceeded)
	{
		UE_LOG(LogTemp, Display, TEXT("-----------------------------HttpRequest"));
		TSharedPtr<FJsonObject> ResponseObj;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
		FJsonSerializer::Deserialize(Reader, ResponseObj);

		UE_LOG(LogTemp, Display, TEXT("Response: %s"), *HttpResponse->GetContentAsString());
		UE_LOG(LogTemp, Display, TEXT("Message: %s"), *ResponseObj->GetStringField("Message"));
		FString MapName = "ThirdPersonMap";


		UGameplayStatics::OpenLevel(this, FName(*MapName), true, FString());
	}
}
