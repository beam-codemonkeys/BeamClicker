// Fill out your copyright notice in the Description page of Project Settings.

#include "VegasClickerToolkit.h"
#include "BeamFunctionLibrary.h"

UBeamFunctionLibrary::UBeamFunctionLibrary() {
	this->Http = &FHttpModule::Get();
}

void UBeamFunctionLibrary::GetBeamUserInfo(FString BeamUsername, const FBeamUserDelegate& Callback) {
	this->SetBeamUser = Callback;
	UE_LOG(LogTemp, Display, TEXT("Attempting to get info for User: %s"), *BeamUsername);
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UBeamFunctionLibrary::BeamUserInfoHandleResponse);
	Request->OnRequestProgress().BindUObject(this, &UBeamFunctionLibrary::OnRequestProgress);
	Request->SetURL(this->BaseURL + "/users/search?limit=1&where=username:eq:" + BeamUsername + "&order=username:DESC");
	//UE_LOG(LogTemp, Display, TEXT("Using URL: %s"), *Request->GetURL());
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void UBeamFunctionLibrary::BeamUserInfoHandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (!bWasSuccessful) {
		UE_LOG(LogTemp, Error, TEXT("Request for Beam User Info Failed"));
	}
	else {
		FString ResponseBody = Response->GetContentAsString();
		//UE_LOG(LogTemp, Display, TEXT("Got response: \n%s"), *ResponseBody);
		TArray<FBeamUser> BeamUsers;
		if (FJsonObjectConverter::JsonArrayStringToUStruct(ResponseBody, &BeamUsers, 0, 0)) {
			if (this->SetBeamUser.IsBound()) {
				this->SetBeamUser.Execute(BeamUsers[0]);
			}
		}
	}
}

void UBeamFunctionLibrary::OnRequestProgress(FHttpRequestPtr request, int32 bytesSent, int32 bytesReceived) {
	UE_LOG(LogTemp, Display, TEXT("Request is Processing"));
}