// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Dom/JsonObject.h"
#include "MODToolEditorUtilityWidgetCPP.generated.h"

#define TO_STRING(VariableName) #VariableName

/**
 * 
 */



//�����ɒǉ������v�f��UMODToolEditorUtilityWidgetCPP�̃R���X�g���N�^�œo�^���Ă�������
USTRUCT(BlueprintType)
struct FPlayerParam {
	GENERATED_USTRUCT_BODY()

	int start_var;
	//////////////////////////////////////////////////////////////////////////////
	//�������牺�ɗv�f��ǉ����Ă�������
		
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Weapon)
	float Health;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Weapon)
	float Attack;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Weapon)
	int Defense;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Weapon)
	float Speed;

	//�U�����[�V�����X�s�[�h
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Weapon)
		float test4;

	//�U�����[�V�����X�s�[�h
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Weapon)
		float test5;

	///////////////////////////////////////////////////////////////////////////////
	//���������ɗv�f��ǉ����Ă�������
	int end_var;		


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Weapon)
		TArray<FString> var_name;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Weapon)
		TArray<FString> var_Type;


	void AddVar(const char* name, const char* type) {
		var_name.Add(name);
		//printf("%s", typeid(var).name());
		//FString kata = (char*)typeid(var).name();
		var_Type.Add(type);
	}

	void* begin() { return &this->start_var; };

	void* end() { return &this->end_var; };
};

////�����ɒǉ������v�f��UMODToolEditorUtilityWidgetCPP�̃R���X�g���N�^�œo�^���Ă�������
//USTRUCT(BlueprintType)
//struct FPlayerParam {
//	GENERATED_USTRUCT_BODY()
//		int start_var;		//�������牺�ɗv�f��ǉ����Ă�������
//	
//		float Damage = 1.f;
//		float Interval;
//		int Ammo;
//		float MotionSpeed;
//
//	int end_var;		//���������ɗv�f��ǉ����Ă�������
//
//	TArray<FString> var_name;
//
//	TArray<FString> var_Type;
//
//
//	void AddVar(const char* name, const char* type) {
//		var_name.Add(name);
//		//printf("%s", typeid(var).name());
//		//FString kata = (char*)typeid(var).name();
//		var_Type.Add(type);
//	}
//
//	/*int* begin() { return &this->start_var + 1; };
//
//	int* end() { return &this->end_var; };*/
//};

UENUM(BlueprintType)
enum class EPrameType : uint8
{
	Player,
	Weapons,
	Map
};

UCLASS()
class MODTOOLBUTTON_API UMODToolEditorUtilityWidgetCPP : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UMODToolEditorUtilityWidgetCPP();

	

	//�Q�b�^�[
	UFUNCTION(BlueprintPure, Category = "EUW")
	int32 GetPlayerPrameItemCount() {
		return player_param.var_name.Num();
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
	FString GetPlayerPrameName(int32 index) {
		return player_param.var_name[index];
	}

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void GetPlayerPrame(int32 index,FString& var_type, int32& out1, float& out2, FString& out3);

	UFUNCTION(BlueprintCallable, Category = "EUW")
	void SetPlayerPrame(int32 index, int32 in1, float in2, FString in3);

	UPROPERTY(EditAnywhere, Category = "ModEUW")
	FPlayerParam player_param;
};
