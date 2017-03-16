// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "BeamFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FBeamUserListTableRow : public FTableRowBase {

	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamUser")
		FString BeamUsername;
};

USTRUCT(BlueprintType)
struct FBeamChannel {

	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString audience;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 badgeId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 coverId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString createdAt;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString deletedAt;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString description;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		bool featured;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 ftl;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		bool hasTranscode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		bool hasVod;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 hosteeId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 id;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		bool interactive;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 interactiveGameId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 languageId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 numFollowers;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		bool online;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		bool partnered;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		bool suspended;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 thumbnailId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString token;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 transcodingProfileId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 typeId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString updatedAt;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 userId;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 viewersCurrent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 viewersTotal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		bool vodsEnabled;
};

USTRUCT(BlueprintType)
struct FBeamSocial {

	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString discord;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString facebook;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString player;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString twiter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		TArray<FString> verified;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString youtube;
};

USTRUCT(BlueprintType)
struct FBeamUser {

	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString avatarUrl;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString bio;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FBeamChannel channel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString createdAt;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString deletedAt;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 experience;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 id;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 level;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 primaryTeam;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FBeamSocial social;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		int32 sparks;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString updatedAt;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		FString username;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamUser")
		bool verified;

};

/**
* Beam Function Library Class
*/

DECLARE_DYNAMIC_DELEGATE_OneParam(FBeamUserDelegate, FBeamUser, BeamUser);

UCLASS(BlueprintType)
class UBeamFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "BeamUser")
		void GetBeamUserInfo(FString BeamUsername, const FBeamUserDelegate& Callback);

	UBeamFunctionLibrary();

private:
	FString BaseURL = FString("https://beam.pro/api/v1");
	FHttpModule* Http;
	FBeamUserDelegate SetBeamUser;
	void BeamUserInfoHandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnRequestProgress(FHttpRequestPtr request, int32 bytesSent, int32 bytesReceived);
};
