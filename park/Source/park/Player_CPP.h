// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player_CPP.generated.h"

UENUM(BlueprintType)
enum AnimType {
	None,
	Spawn,
	JumpNormal,
	JumpSpin,
	WallDashR,
	WallDashL,
	RollR,
	RollL,
	Sliding
};


struct MotionControllerMgr {
	FVector pos;
	int32 jump_point;
	float jump_wai_time;
	int32 sliding_point;
	float sliding_wai_time;
};

struct VRHeadGearMgr {
	FVector pos;
	int32 rolling_r_point;
	float rolling_r_wai_time;
	int32 rolling_l_point;
	float rolling_l_wai_time;
};

UCLASS()
class PARK_API APlayer_CPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_CPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void Reset();

	//ゲッター
	UFUNCTION(BlueprintPure, Category = "Player")
	float GetSpeed() { return speed; }
	UFUNCTION(BlueprintPure, Category = "Player")
	float GetBoost() { return boost; }
	UFUNCTION(BlueprintPure, Category = "Player")
	float GetD_time() { return d_time; }

	UFUNCTION(BlueprintPure, Category = "Player")
	float GetWait_time() { return wait_time; }


	UFUNCTION(BlueprintPure, Category = "Player")
	bool GetAct_frag() { return act_frag; }
	UFUNCTION(BlueprintPure, Category = "Player")
	bool GetGame_over_frag() { return game_over_frag; }
	UFUNCTION(BlueprintPure, Category = "Player")
	bool GetInvisible_frag() { return invisible_frag; }
	UFUNCTION(BlueprintPure, Category = "Player")
	bool GetReset_frag() { return reset_frag; }

	UFUNCTION(BlueprintPure, Category = "Player")
	AnimType GetPlay_anim() { return play_anim; }
	UFUNCTION(BlueprintPure, Category = "Player")
	AnimType GetStandby_anim() { return standby_anim; }

	//セッター
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetSpeed(float in) {  speed = in; }
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetBoost(float in) {  boost = in; }
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetD_time(float in) {  d_time = in; }
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetWait_time(float in) { wait_time = in; }
	UFUNCTION(BlueprintCallable, Category = "Player")
	void Setgame_over_wait_time(float in) { game_over_wait_time = in; }

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetAct_frag(bool in) {  act_frag = in; }
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetGame_over_frag(bool in) { game_over_frag = in; }
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetInvisible_frag(bool in) { invisible_frag = in; }
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetRoll_end_frag(bool in) { roll_end_frag = in; }
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetWall_jump_frag(bool in) { wall_jump_frag = in; }


	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetPlay_anim(AnimType in) { play_anim = in; }
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetStandby_anim(AnimType in) { standby_anim = in; }

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetMotionControllerPos(FVector right, FVector lest, FVector head) { 
		M_Con_R.pos = right;
		M_Con_L.pos = lest;
		Head.pos = head;
	}

private:

	void Move();
	void Jump();
	void Sliding();
	void WallDashRight();
	void WallDashLeft();
	void RollingRight();
	void RollingLeft();
	void Boost();
	void BoostOn();
	void BoostOff();

	void JumpMotionCheck();
	void SlidingMotionCheck();
	void RollingMotionCheck();
	void BoostMotionCheck();

	AnimType standby_anim;
	AnimType play_anim;

	bool act_frag;
	bool boost_frag;
	bool game_over_frag;
	bool invisible_frag;
	bool roll_end_frag;
	bool wall_jump_frag;
	bool reset_frag;

	float speed;
	float boost;
	float time;
	float Rolling_Wait_time;
	float d_time;
	float wait_time;
	float game_over_wait_time;
	float wall_jump_wait_time_r;
	float wall_jump_wait_time_l;

	int64 score;

	int32 lane_pos;

	MotionControllerMgr M_Con_R;
	MotionControllerMgr M_Con_L;
	VRHeadGearMgr Head;



};
