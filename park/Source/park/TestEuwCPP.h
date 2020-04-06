// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Serialization/JsonSerializerMacros.h"
#include "Dom/JsonObject.h"
#include "TestEuwCPP.generated.h"

struct  FJsonItem : public FJsonSerializable
{

};


/**
 * 
 */
UCLASS()
class PARK_API UTestEuwCPP : public UEditorUtilityWidget
{
	GENERATED_BODY()

	TSharedPtr<FJsonObject> jsonObject;
	FString OutputString;
	//TSharedRef<TJsonWriter<>> Writer;

public:
	UFUNCTION(BlueprintCallable, Category = "EUW")
	void FileCreate(FString file_name, FString& in);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void FileWriter(FString in);

	
};
