// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEuwCPP.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/FileHelper.h"

void UTestEuwCPP::FileCreate(FString file_name, FString& in) {
	jsonObject = MakeShareable(new FJsonObject());
	FFileHelper::SaveStringToFile(in, *file_name);

}

void UTestEuwCPP::FileWriter(FString in) {
	//FString OutputString;
	//TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);

	
	
	
	//FJsonSerializer::Serialize(jsonObject.ToSharedRef(), Writer);

}