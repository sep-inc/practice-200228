// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "MyEditorUtilityWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UMyEditorUtilityWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:

	void CreatePackage1();
	int32 aaa;
	
};
