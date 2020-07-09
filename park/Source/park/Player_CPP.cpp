// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_CPP.h"
#include "HAL/PlatformFilemanager.h"
#include "Engine/StreamableManager.h"
#include "Misc/PackageName.h"
#include "AssetRegistryModule.h"
#include "Engine/ObjectLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"


// Sets default values
APlayer_CPP::APlayer_CPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayer_CPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayer_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	d_time = DeltaTime;
	if (game_over_frag) {
		if (game_over_wait_time > 0.f) {
			game_over_wait_time -= d_time;
			speed = 0.f;
		}
		else {
			Reset();
			wait_time = MaxWaitTime;
		}
	}
	else if (wait_time <= 0.f) {
		reset_frag = false;
		RollingMotionCheck();
		JumpMotionCheck();
		SlidingMotionCheck();
		BoostMotionCheck();
		//AimingMotionCheck();
		if(!act_frag)Boost();
		Move();



		if (wall_jump_wait_time_r > 0.f) {
			wall_jump_wait_time_r -= d_time;
		}
		if (wall_jump_wait_time_l > 0.f) {
			wall_jump_wait_time_l -= d_time;
		}
	}
	else {
		wait_time -= d_time;
	}

}

// Called to bind functionality to input
void APlayer_CPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);




}

void APlayer_CPP::Reset() {
	standby_anim = AnimType::None;
	play_anim = AnimType::None;

	act_frag = false;
	boost_frag = false;
	game_over_frag = false;
	invisible_frag = false;
	roll_end_frag = false;
	wall_jump_frag = false;

	speed = 0.f;
	boost = 0.f;
	time = 0.f;
	Rolling_Wait_time = 0.f;
	wall_jump_wait_time_r = 0.f;
	wall_jump_wait_time_l = 0.f;

	score = 0;

	lane_pos = 0;
	reset_frag = true;

	SetActorLocation(FVector(0,0,140.f));
}

void APlayer_CPP::Move() {
	FVector pos = GetActorLocation();
	
	if (play_anim != AnimType::RollR && play_anim != AnimType::RollL) {
		float max_speed;
		if (aiming_frag) {
			max_speed = AimingMaxSpeed;
		}
		else {
			max_speed = DefaultMaxSpeed;
		}
		if (speed < max_speed) {
			speed += 50.f * d_time;
		}
		else {
			if (aiming_frag) {
				speed -= 40.f * d_time;
			}
			else {
				speed -= 15.f * d_time;
			}
		}
		pos.X += speed * d_time * 10.f;

		SetActorLocation(pos);
	}
	else {
		speed -= 20.f * d_time;
		if (lane_pos * 400.f > pos.Y) {
			pos.Y += speed * d_time * 10.f;
			if (lane_pos * 400.f < pos.Y) {
				pos.Y = lane_pos * 400.f;
			}
		}
		else if (lane_pos * 400.f < pos.Y) {
			pos.Y -= speed * d_time * 10.f;
			if (lane_pos * 400.f > pos.Y) {
				pos.Y = lane_pos * 400.f;
			}
		}

		if (roll_end_frag) {
			if (speed < DefaultMaxSpeed) {
				speed += 50.f * d_time;
			}
			else {
				speed -= 10.f * d_time;
			}
			pos.X += speed * d_time * 10.f;

		}


		SetActorLocation(pos);
	}
}

void APlayer_CPP::Jump() {
	if (!act_frag) {
		act_frag = true;
		if (wall_jump_wait_time_r > 0.f) {
			WallDashRight();
		}
		else if (wall_jump_wait_time_l > 0.f) {
			WallDashLeft();
		}
		else if (standby_anim == AnimType::JumpSpin) {
			play_anim = AnimType::JumpSpin;
			invisible_frag = true;

			boost += BoostAddVar;
		}
		else {
			play_anim = AnimType::JumpNormal;
		}
	}
}

void APlayer_CPP::Sliding() {
	if (!act_frag) {
		if (standby_anim == AnimType::Sliding) {
			act_frag = true;
			play_anim = AnimType::Sliding;
			invisible_frag = true;

			boost += BoostAddVar;
			speed = BoostMaxSpeed;
		}
	}
}

void APlayer_CPP::WallDashRight() {
	play_anim = AnimType::WallDashR;
	invisible_frag = true;
	speed = BoostMaxSpeed;
	boost += BoostAddVar;
}

void APlayer_CPP::WallDashLeft() {
	play_anim = AnimType::WallDashL;
	invisible_frag = true;
	speed = BoostMaxSpeed;
	boost += BoostAddVar;
}

void APlayer_CPP::RollingRight() {
	if (!act_frag) {
		if (wall_jump_frag) {
			wall_jump_wait_time_r = 0.5f;
		}
		else if (lane_pos + 1 <= 3 && roll_frag) {
			lane_pos++;
			act_frag = true;
			speed = BoostMaxSpeed;
			roll_end_frag = false;
			play_anim = AnimType::RollR;
		}
	}

}

void APlayer_CPP::RollingLeft() {
	if (!act_frag) {
		if (wall_jump_frag) {
			wall_jump_wait_time_l = 0.5f;
		}
		else if (lane_pos - 1 >= -3 && roll_frag) {
			lane_pos--;
			act_frag = true;
			speed = BoostMaxSpeed;
			roll_end_frag = false;
			play_anim = AnimType::RollL;
		}
	}

}

void APlayer_CPP::Boost() {
	if (boost_frag) {
		if (boost > 0.f) {
			boost -= 20.f * d_time;
			speed += 10.f * d_time;

		}
		else {
			boost = 0.f;
		}
	}
}

void APlayer_CPP::BoostOn() {
	boost_frag = true;
}

void APlayer_CPP::BoostOff() {
	boost_frag = false;
}

void APlayer_CPP::JumpMotionCheck() {
	/*if (M_Con_R.pos.Z < 0.f) {
		M_Con_R.jump_point = 1;
	}
	else if (M_Con_R.pos.Z >= 0.f && M_Con_R.jump_point == 1) {
		M_Con_R.jump_point = 2;
		M_Con_R.jump_wai_time = 0.3f;
	}
	else if (M_Con_R.pos.Z >= 10.f && M_Con_R.jump_point == 2 && M_Con_R.jump_wai_time > 0.f) {
		M_Con_R.jump_point = 3;
		Jump();
	}*/

	if (M_Con_L.pos.Z < JumpMotionPoint2) {
		M_Con_L.jump_point = 1;
	}
	else if (M_Con_L.pos.Z >= JumpMotionPoint2 && M_Con_L.jump_point == 1) {
		M_Con_L.jump_point = 2;
		M_Con_L.jump_wai_time = 0.3f;
	}
	else if (M_Con_L.pos.Z >= JumpMotionPoint3 && M_Con_L.jump_point == 2 && M_Con_L.jump_wai_time > 0.f) {
		M_Con_L.jump_point = 3;
		Jump();
	}


	/*if (M_Con_R.jump_wai_time > 0.f) {
		M_Con_R.jump_wai_time -= d_time;
	}*/
	if (M_Con_L.jump_wai_time > 0.f) {
		M_Con_L.jump_wai_time -= d_time;
	}
}

void APlayer_CPP::SlidingMotionCheck() {
	//if (M_Con_R.pos.Z > -15.f) {
	//	M_Con_R.sliding_point = 1;
	//}
	//else if (M_Con_R.pos.Z <= -15.f && M_Con_R.sliding_point == 1) {
	//	M_Con_R.sliding_point = 2;
	//	M_Con_R.sliding_wai_time = 0.3f;
	//}
	//else if (M_Con_R.pos.Z <= -20.f && M_Con_R.sliding_point == 2 && M_Con_R.sliding_wai_time > 0.f) {
	//	M_Con_R.sliding_point = 3;
	//	Sliding();
	//}

	if (M_Con_L.pos.Z > SlidingMotionPoint2) {
		M_Con_L.sliding_point = 1;
	}
	else if (M_Con_L.pos.Z <= SlidingMotionPoint2 && M_Con_L.sliding_point == 1) {
		M_Con_L.sliding_point = 2;
		M_Con_L.sliding_wai_time = SlidingMotionWaitTime;
	}
	else if (M_Con_L.pos.Z <= SlidingMotionPoint3 && M_Con_L.sliding_point == 2 && M_Con_L.sliding_wai_time > 0.f) {
		M_Con_L.sliding_point = 3;
		Sliding();
	}


	/*if (M_Con_R.sliding_wai_time > 0.f) {
		M_Con_R.sliding_wai_time -= d_time;
	}*/
	if (M_Con_L.sliding_wai_time > 0.f) {
		M_Con_L.sliding_wai_time -= d_time;
	}
}

void APlayer_CPP::RollingMotionCheck() {
	if (Head.pos.Y < RollingMotionPoint2) {
		Head.rolling_r_point = 1;
	}
	else if (Head.pos.Y >= RollingMotionPoint2 && Head.rolling_r_point == 1) {
		Head.rolling_r_point = 2;
		Head.rolling_r_wai_time = RollingMotionWaitTime;
	}
	else if (Head.pos.Y >= RollingMotionPoint3 && Head.rolling_r_point == 2 && Head.rolling_r_wai_time > 0.f) {
		Head.rolling_r_point = 3;
		RollingRight();
	}

	if (Head.pos.Y > -RollingMotionPoint2) {
		Head.rolling_l_point = -1;
	}
	else if (Head.pos.Y <= -RollingMotionPoint2 && Head.rolling_l_point == -1) {
		Head.rolling_l_point = -2;
		Head.rolling_l_wai_time = RollingMotionWaitTime;
	}
	else if (Head.pos.Y <= -RollingMotionPoint3 && Head.rolling_l_point == -2 && Head.rolling_l_wai_time > 0.f) {
		Head.rolling_l_point = -3;
		RollingLeft();
	}

	if (Head.rolling_r_wai_time > 0.f) {
		Head.rolling_r_wai_time -= d_time;
	}
	if (Head.rolling_l_wai_time > 0.f) {
		Head.rolling_l_wai_time -= d_time;
	}
}

void APlayer_CPP::BoostMotionCheck() {
	if (Head.pos.X > BoostMotionPoint) {
		BoostOn();
	}
	else {
		BoostOff();
	}
}

void APlayer_CPP::AimingMotionCheck() {

	if (M_Con_R.pos.X - Head.pos.X > AimingMotionPoint) {
		aiming_frag = true;
	}
	else {
		aiming_frag = false;
	}
}

bool APlayer_CPP::OpenPakFile(const FString pak_file_name) {
	//プラットフォームファイルの生成
	if (PakPlatformFile == nullptr) {
		IPlatformFile* exi = FPlatformFileManager::Get().FindPlatformFile(TEXT("PakFile"));
		//すでに存在する場合そのまま使用できる
		if (exi) {
			PakPlatformFile = static_cast<FPakPlatformFile*>(exi);
		}
		else {
			IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
			PakPlatformFile = new FPakPlatformFile();
			PakPlatformFile->Initialize(&PlatformFile, TEXT(""));
			PakPlatformFile->InitializeNewAsyncIO();
			FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);
		}
	}

	//名前確認
	FString pla_name = PakPlatformFile->GetName();
	UE_LOG(LogClass, Log, TEXT("%s"), *pla_name);

	//Pakファイル生成
	FPakFile PakFile(PakPlatformFile->GetLowerLevel(), *pak_file_name, true);

	//マウント
	FString MountPoint(FPaths::EngineContentDir());
	PakFile.SetMountPoint(*MountPoint);

	if (PakPlatformFile->Mount(*pak_file_name, 0, *MountPoint)) {
		return true;
	}
	return false;
}

void APlayer_CPP::ClosePakFile(const FString pak_file_name) {
	PakPlatformFile->Unmount(*pak_file_name);
	FPlatformFileManager::Get().RemovePlatformFile(PakPlatformFile);
}


AActor* APlayer_CPP::LoadPakFile(const FString pak_file_name) {

	//プラットフォームファイルの生成
	if (PakPlatformFile == nullptr) {
		IPlatformFile* exi = FPlatformFileManager::Get().FindPlatformFile(TEXT("PakFile"));
		//すでに存在する場合そのまま使用できる
		if (exi) {
			PakPlatformFile = static_cast<FPakPlatformFile*>(exi);
		}
		else {
			IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
			PakPlatformFile = new FPakPlatformFile();
			PakPlatformFile->Initialize(&PlatformFile, TEXT(""));
			PakPlatformFile->InitializeNewAsyncIO();
			FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);
		}
	}
	
	//名前確認
	FString pla_name = PakPlatformFile->GetName();
	UE_LOG(LogClass, Log, TEXT("%s"), *pla_name);
	
	//Pakファイル生成
	FPakFile PakFile(PakPlatformFile->GetLowerLevel(),*pak_file_name, true);


	//TArray<FString> ArrAllMountedPakFile;
	//PakPlatformFile->GetMountedPakFilenames(ArrAllMountedPakFile);
	//for (int32 i = 0; i < ArrAllMountedPakFile.Num(); i++)
	//{
	//	FString PakFileName = ArrAllMountedPakFile[i];
	//	FString PakFilePathFull = FPaths::ConvertRelativePathToFull(PakFileName);
	//	FPakFile PakFile(PakPlatformFile->GetLowerLevel(), *PakFilePathFull, false);
	//	TArray<FString> FileList;
	//	FString MountPoint = PakFile.GetMountPoint();
	//	PakPlatformFile->Mount(*PakFilePathFull, 0, *MountPoint);
	//	PakFile.FindFilesAtPath(FileList, *MountPoint, true, false, true);
	//	for (int32 j = 0; j < FileList.Num(); j++)
	//	{
	//		FString AssetName = FileList[j];
	//		FString AssetShortName = FPackageName::GetShortName(AssetName);
	//		FString FileName, FileExt;
	//		AssetShortName.Split(TEXT("."), &FileName, &FileExt);
	//		FString NewAssetName = TEXT("/Game/Paks/") + FileName + TEXT(".") + FileName;

	//		FSoftObjectPath StrNewAssetRef = NewAssetName;
	//		FStreamableManager AssetLoader;
	//		UObject* NewLoadedObject = AssetLoader.LoadSynchronous(StrNewAssetRef);
	//		if (NewLoadedObject)
	//		{
	//			// do something, cast to compatible type.
	//			UE_LOG(LogClass, Log, TEXT("Object load Success..."));
	//		}
	//		else {
	//			UE_LOG(LogClass, Error, TEXT("Can't load asset..."));
	//		}
	//	}
	//}

	//マウント
	FString MountPoint(FPaths::ProjectContentDir());
	PakFile.SetMountPoint(*MountPoint);


	//オブジェクト生成
	if (PakPlatformFile->Mount(*pak_file_name, 0, *MountPoint)) {
		TArray<FString> FileList;
	

		PakFile.FindFilesAtPath(FileList, *PakFile.GetMountPoint(), true, false, true);
		FStreamableManager StreamableManager;
		FString AssetName = FileList[0];
	
		FString AssetShortName = FPackageName::GetShortName(AssetName);
		FString LeftStr;
		FString RightStr;
		AssetShortName.Split(TEXT("."), &LeftStr, &RightStr);
		AssetName = TEXT("/Game/Asset/") + LeftStr + TEXT(".") + LeftStr;
		FStringAssetReference Reference = AssetName;

		TArray<FString> aaaaaa;
		aaaaaa.Add(AssetName);
		FAssetRegistryModule& assetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
		IAssetRegistry& assetRegistry = assetRegistryModule.Get();
		assetRegistry.ScanPathsSynchronous(aaaaaa, true);

		FString path = "/Game/Asset/test3d2.test3d2_C"; 
		TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous(); 
		if (sc != nullptr)
		{
			AActor* a = GetWorld()->SpawnActor<AActor>(sc); // スポーン処理
			a->SetActorLocation(FVector(1500, 0, 0)); // 確認しやすいように座標を設定

			PakPlatformFile->Unmount(*pak_file_name);
			FPlatformFileManager::Get().RemovePlatformFile(PakPlatformFile);
			return a;
		}

		//UObject* LoadObject = StreamableManager.LoadSynchronous(Reference);
		//TArray<UObject*> asset;

		//GetAssetsInDirectory(AActor::StaticClass(), AssetName, true, asset);

		//if (asset.Num() == 0) {
		//	UE_LOG(LogClass, Error, TEXT("Can't load asset..."));
		//	return NULL;
		//}
		//else {
		//	UE_LOG(LogClass, Log, TEXT("Object load Success..."));
		//	return NULL;
		//}

		//if (LoadObject != nullptr)
		//{
		//	UE_LOG(LogClass, Log, TEXT("Object load Success..."));
		//	AActor* a = (AActor*)LoadObject;
		//	//AActor* b = GetWorld()->SpawnActor<AActor>(LoadObject->GetClass());
		//	return a;
		//}
		//else
		//{
		//	UE_LOG(LogClass, Error, TEXT("Can't load asset..."));
		//	return NULL;
		//}

		//終了処理(これがないとUE4がおかしくなる)
		PakPlatformFile->Unmount(*pak_file_name);
		FPlatformFileManager::Get().RemovePlatformFile(PakPlatformFile);
		return NULL;
	}
	else
	{
		//終了処理(これがないとUE4がおかしくなる)
		PakPlatformFile->Unmount(*pak_file_name);
		FPlatformFileManager::Get().RemovePlatformFile(PakPlatformFile);
		UE_LOG(LogClass, Error, TEXT("Mount failed"));
		return NULL;
	}
}

AActor* APlayer_CPP::LoadPakFile_Actor(const FString name) {
	FString path = "/Engine/Asset/" + name + "." + name + "_C";
	//TSubclassOf<class AActor> sc = TSoftClassPtr<AActor>(FSoftObjectPath(*path)).LoadSynchronous();
	UClass* sc = LoadObject<UClass>(this, *("Class'" + path + "'"));

	if (sc != nullptr)
	{
		//AActor* a = GetWorld()->SpawnActor<AActor>(sc); // スポーン処理
		AActor* a = GetWorld()->SpawnActor(sc); // スポーン処理
		a->SetActorLocation(FVector(1500, 0, 0)); // 確認しやすいように座標を設定
		return a;
	}
	return NULL;
}

USkeletalMesh* APlayer_CPP::LoadPakFile_SkeletalMesh(const FString name) {
	FString path = "/Engine/Asset/" + name + "." + name;
	//TSubclassOf<class USkeletalMeshComponent> sc = TSoftClassPtr<USkeletalMeshComponent>(FSoftObjectPath(*path)).LoadSynchronous();
	USkeletalMesh* sc = LoadObject<USkeletalMesh>(this,*path);
	if (sc != nullptr)
	{
		//USkeletalMesh* a = GetWorld()->SpawnActor<AActor>(sc); // スポーン処理
		//a->SetActorLocation(FVector(1500, 0, 0)); // 確認しやすいように座標を設定
		return sc;
	}
	return NULL;
}

void APlayer_CPP::GetAssetsInDirectory(const TSubclassOf<UObject> assetClass, const FString path, const bool bRecursive, TArray<UObject*>&assets) {
	TArray<FAssetData> assetData;
	TSharedPtr<UObjectLibrary> objectLibrary = MakeShareable(UObjectLibrary::CreateLibrary(assetClass.Get(), false, true));
	objectLibrary->bRecursivePaths = bRecursive;
	objectLibrary->LoadAssetDataFromPath(*path);
	objectLibrary->GetAssetDataList(assetData);

	assets.Reset(assetData.Num());

	for(FAssetData& data : assetData)
	{
		assets.Add(data.GetAsset());
	}

}

