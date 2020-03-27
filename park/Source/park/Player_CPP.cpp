// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_CPP.h"

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
		}
		else {
			Reset();
			wait_time = 3.f;
		}
	}
	else if (wait_time <= 0.f) {
		reset_frag = false;
		RollingMotionCheck();
		JumpMotionCheck();
		SlidingMotionCheck();
		BoostMotionCheck();
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
		if (speed < 100.f) {
			speed += 50.f * d_time;
		}
		else {
			speed -= 15.f * d_time;
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
			if (speed < 100.f) {
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

			boost += 30.f;
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

			boost += 30.f;
			speed = 150.f;
		}
	}
}

void APlayer_CPP::WallDashRight() {
	play_anim = AnimType::WallDashR;
	invisible_frag = true;
	speed = 150.f;
	boost += 30.f;
}

void APlayer_CPP::WallDashLeft() {
	play_anim = AnimType::WallDashL;
	invisible_frag = true;
	speed = 150.f;
	boost += 30.f;
}

void APlayer_CPP::RollingRight() {
	if (!act_frag) {
		if (wall_jump_frag) {
			wall_jump_wait_time_r = 0.3f;
		}
		else if (lane_pos + 1 <= 3) {
			lane_pos++;
			act_frag = true;
			speed = 150.f;
			roll_end_frag = false;
			play_anim = AnimType::RollR;
		}
	}

}

void APlayer_CPP::RollingLeft() {
	if (!act_frag) {
		if (wall_jump_frag) {
			wall_jump_wait_time_l = 0.3f;
		}
		else if (lane_pos - 1 >= -3) {
			lane_pos--;
			act_frag = true;
			speed = 150.f;
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
	if (M_Con_R.pos.Z < 0.f) {
		M_Con_R.jump_point = 1;
	}
	else if (M_Con_R.pos.Z >= 0.f && M_Con_R.jump_point == 1) {
		M_Con_R.jump_point = 2;
		M_Con_R.jump_wai_time = 0.3f;
	}
	else if (M_Con_R.pos.Z >= 10.f && M_Con_R.jump_point == 2 && M_Con_R.jump_wai_time > 0.f) {
		M_Con_R.jump_point = 3;
		Jump();
	}

	if (M_Con_L.pos.Z < 0.f) {
		M_Con_L.jump_point = 1;
	}
	else if (M_Con_L.pos.Z >= 0.f && M_Con_L.jump_point == 1) {
		M_Con_L.jump_point = 2;
		M_Con_L.jump_wai_time = 0.3f;
	}
	else if (M_Con_L.pos.Z >= 10.f && M_Con_L.jump_point == 2 && M_Con_L.jump_wai_time > 0.f) {
		M_Con_L.jump_point = 3;
		Jump();
	}


	if (M_Con_R.jump_wai_time > 0.f) {
		M_Con_R.jump_wai_time -= d_time;
	}
	if (M_Con_L.jump_wai_time > 0.f) {
		M_Con_L.jump_wai_time -= d_time;
	}
}

void APlayer_CPP::SlidingMotionCheck() {
	if (M_Con_R.pos.Z > -15.f) {
		M_Con_R.sliding_point = 1;
	}
	else if (M_Con_R.pos.Z <= -15.f && M_Con_R.sliding_point == 1) {
		M_Con_R.sliding_point = 2;
		M_Con_R.sliding_wai_time = 0.3f;
	}
	else if (M_Con_R.pos.Z <= -20.f && M_Con_R.sliding_point == 2 && M_Con_R.sliding_wai_time > 0.f) {
		M_Con_R.sliding_point = 3;
		Sliding();
	}

	if (M_Con_L.pos.Z > -15.f) {
		M_Con_L.sliding_point = 1;
	}
	else if (M_Con_L.pos.Z <= -15.f && M_Con_L.sliding_point == 1) {
		M_Con_L.sliding_point = 2;
		M_Con_L.sliding_wai_time = 0.3f;
	}
	else if (M_Con_L.pos.Z <= -20.f && M_Con_L.sliding_point == 2 && M_Con_L.sliding_wai_time > 0.f) {
		M_Con_L.sliding_point = 3;
		Sliding();
	}


	if (M_Con_R.sliding_wai_time > 0.f) {
		M_Con_R.sliding_wai_time -= d_time;
	}
	if (M_Con_L.sliding_wai_time > 0.f) {
		M_Con_L.sliding_wai_time -= d_time;
	}
}

void APlayer_CPP::RollingMotionCheck() {
	if (Head.pos.Y < 2.f) {
		Head.rolling_r_point = 1;
	}
	else if (Head.pos.Y >= 2.f && Head.rolling_r_point == 1) {
		Head.rolling_r_point = 2;
		Head.rolling_r_wai_time = 0.3f;
	}
	else if (Head.pos.Y >= 5.f && Head.rolling_r_point == 2 && Head.rolling_r_wai_time > 0.f) {
		Head.rolling_r_point = 3;
		RollingRight();
	}

	if (Head.pos.Y > -2.f) {
		Head.rolling_l_point = -1;
	}
	else if (Head.pos.Y <= -2.f && Head.rolling_l_point == -1) {
		Head.rolling_l_point = -2;
		Head.rolling_l_wai_time = 0.3f;
	}
	else if (Head.pos.Y <= -5.f && Head.rolling_l_point == -2 && Head.rolling_l_wai_time > 0.f) {
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
	if (Head.pos.X > 10.f) {
		BoostOn();
	}
	else {
		BoostOff();
	}
}