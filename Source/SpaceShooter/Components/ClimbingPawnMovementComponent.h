// Copyright 2016 Dmitriy

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "ClimbingPawnMovementComponent.generated.h"

class Lib
{
public:

	static bool TraceLine(UWorld* World, AActor* ActorToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut, bool drawDebug, ECollisionChannel CollisionChannel = ECC_Pawn, bool ReturnPhysMat = false);
	static bool TraceLine(UWorld* World, AActor* ActorToIgnore, const FVector& Start, const FVector& End, FHitResult& HitOut, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None, ECollisionChannel CollisionChannel = ECC_Pawn, bool ReturnPhysMat = false);
	static bool TraceLine(UWorld* World, AActor* ActorToIgnore, const FVector& Start, const FVector& End, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None, ECollisionChannel CollisionChannel = ECC_Pawn, bool ReturnPhysMat = false);
	static float VectorXYAngle(FVector V1, FVector V2);
	static void Msg(FVector Vector, bool OnScreen = true, bool OnLog = false);
	static void Msg(FString Message, bool OnScreen = true, bool OnLog = false);
	static void Msg(float Message, bool OnScreen = true, bool OnLog = false);

};

UENUM(BlueprintType)
enum EClimbingMode
{

	CLIMB_None		UMETA(DisplayName = "None"),

	/** Climb. */
	CLIMB_Climb	UMETA(DisplayName = "Climb"),

	/**Run on Left side wall  */
	CLIMB_LeftWallRun	UMETA(DisplayName = "Left Wall Run"),

	/** Run on Right side wall */
	CLIMB_RightWallRun	UMETA(DisplayName = "Right Wall Run"),

	/** Slide on ground */
	CLIMB_Slide	UMETA(DisplayName = "Slide"),

	CLIMB_JumpOverBarrier	UMETA(DisplayName = "JumpOverBarrier"),

	CLIMB_UnderWallJump UMETA(DisplayName = "UnderWallJump"),

	CLIMB_ZipLine UMETA(DisplayName = "ZipLine"),
	/*Slide from inclined surfase*/
	CLIMB_InclinedSlide UMETA(DisplayName = "InclinedSlide"),

	CLIMB_Thruster UMETA(DisplayName = "Thruster"),


	CLIMB_MAX	UMETA(DisplayName = "Hide")

};

UCLASS()
class SPACESHOOTER_API UClimbingPawnMovementComponent : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()

public:
	

	UFUNCTION(BlueprintCallable, Category = "ClimbingMovement")
	void SetClimbMode(EClimbingMode _ClimbingMode);

	UFUNCTION(BlueprintCallable, Category = "ClimbingMovement")
		void Thruster();

	UFUNCTION(BlueprintPure, Category = "ClimbingMovement")
	EClimbingMode GetClimbingMode() const;

	UFUNCTION(BlueprintPure, Category = "ClimbingMovement")
	bool CanSetClimbMode(EClimbingMode ClimbingMode);

	/*Offset from top of climbing surfase*/
	UPROPERTY(Category = "ClimbingMovement|Climb", EditAnywhere, BlueprintReadWrite)
		int32 ClimbDeltaZ;


	/*Velocity of climb movement*/
	UPROPERTY(Category = "ClimbingMovement|Climb", EditAnywhere, BlueprintReadWrite)
		bool AutoClimb;
	/*Velocity of climb movement*/
	UPROPERTY(Category = "ClimbingMovement|Climb", EditAnywhere, BlueprintReadWrite)
		bool HoldJumpToClimb;

	/*Velocity of climb movement*/
	UPROPERTY(Category = "ClimbingMovement|Climb", EditAnywhere, BlueprintReadWrite)
		float ClimbVelocity;

	/*Velocity of jump from climb state*/
	UPROPERTY(Category = "ClimbingMovement|Climb", EditAnywhere, BlueprintReadWrite)
		float ClimbJumpVelocity;

	/*Angle from center when state can change in degres*/
	UPROPERTY(Category = "ClimbingMovement|WallRun", EditAnywhere, BlueprintReadWrite)
		float WallRunLimitAngle;

	/*Offset from Wall when Wall Run*/
	UPROPERTY(Category = "ClimbingMovement|WallRun", EditAnywhere, BlueprintReadWrite)
		int32 WallOffset;

	/*Fall Gravity Scale when charecter run on wall*/
	UPROPERTY(Category = "ClimbingMovement|WallRun", EditAnywhere, BlueprintReadWrite)
		float WallRunFallGravityScale;

	/*Multiplier input vector when charecter run on wall*/
	UPROPERTY(Category = "ClimbingMovement|WallRun", EditAnywhere, BlueprintReadWrite)
		int32 WallRunInputVelocity;

	/*Velocity of jump near wall*/
	UPROPERTY(Category = "ClimbingMovement|WallRun", EditAnywhere, BlueprintReadWrite)
		float WallRunJumpZVelocity;

	/*Velocity of jump from wall run state*/
	UPROPERTY(Category = "ClimbingMovement|General", EditAnywhere, BlueprintReadWrite)
		float MaxSprintSpeed;
	/*Velocity of jump from wall run state*/
	UPROPERTY(Category = "ClimbingMovement|General", EditAnywhere, BlueprintReadWrite)
		float ThrusterForce;
	/*Velocity of jump from wall run state*/
	UPROPERTY(Category = "ClimbingMovement|General", EditAnywhere, BlueprintReadWrite)
		float ThrusterCoolDown;
	/*Velocity of jump from wall run state*/
	UPROPERTY(Category = "ClimbingMovement|WallRun", EditAnywhere, BlueprintReadWrite)
		float WallRunJumpVelocity;

	/*Offset from rope of zip line*/
	UPROPERTY(Category = "ClimbingMovement|ZipLine", EditAnywhere, BlueprintReadWrite)
		int32 ZipLineDeltaZ;

	/*Velocity*/
	UPROPERTY(Category = "ClimbingMovement|ZipLine", EditAnywhere, BlueprintReadWrite)
		float ZipLineVelocity;

	/*Velocity of jump from Zip Line state*/
	UPROPERTY(Category = "ClimbingMovement|ZipLine", EditAnywhere, BlueprintReadWrite)
		float ZipLineJumpVelocity;

	/*Angle of surfase when character slide*/
	UPROPERTY(Category = "ClimbingMovement|InclinedSlide", EditAnywhere, BlueprintReadWrite)
		float InclinedSlideAngle;

	UPROPERTY(Category = "ClimbingMovement|InclinedSlide", EditAnywhere, BlueprintReadWrite)
		float InclinedSlideVelocityForward;

	UPROPERTY(Category = "ClimbingMovement|InclinedSlide", EditAnywhere, BlueprintReadWrite)
		float InclinedSlideVelocityRight;

	UPROPERTY(Category = "ClimbingMovement|InclinedSlide", EditAnywhere, BlueprintReadWrite)
		float InclinedJumpVelocity;

	/*Velocity of Run movement*/
	UPROPERTY(Category = "ClimbingMovement", EditAnywhere, BlueprintReadWrite)
		FRuntimeFloatCurve RunVelocityCurve;
	/*Velocity of Run movement*/
	UPROPERTY(Category = "ClimbingMovement", EditAnywhere, BlueprintReadWrite)
		FRuntimeFloatCurve CrouchedRunVelocityCurve;
	/*Velocity of Run movement*/
	UPROPERTY(Category = "ClimbingMovement", EditAnywhere, BlueprintReadWrite)
		FRuntimeFloatCurve SprintVelocityCurve;

	/*Velocity of Slide movement*/
	UPROPERTY(Category = "ClimbingMovement", EditAnywhere, BlueprintReadWrite)
		FRuntimeFloatCurve SlideVelocityCurve;

	/*Threshold Velocity when char can Slide.*/
	UPROPERTY(Category = "ClimbingMovement", EditAnywhere, BlueprintReadWrite)
		float SlideThreshold;

	/*Velocity of jump near wall*/
	UPROPERTY(Category = "ClimbingMovement", EditAnywhere, BlueprintReadWrite)
		float UnderWallJumpZVelocity;

	


	/*-----------------------------------------------------------------------------------------
		UCharacterMovementComponent Interface
		These functions are called from HaloCCharacter !!!!!!!!!!!!
	*/
	virtual bool DoJump(bool bReplayingMoves) override;
	virtual float GetMaxSpeed() const override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	EClimbingMode ClimbingMode;
	EClimbingMode LastClimbingMode;
	
	float ClimbTopRayHeight;

	bool BlockClimb;
	bool BlockWallRun;
	bool BlockInclinedSlide;

	float MinRunTime;
	float MaxRunTime;

	float MinSlideTime;
	float MaxSlideTime;

	float LastThrusterTime;

	FTimerHandle InclinedSlideTimerHandle; 
	
	void DefineRunSpeed(float DeltaTime);
	void DefineClimbMode();
	bool SetMode(EClimbingMode ClimbingMode);
	void UnSetMode(EClimbingMode ClimbingMode);
	void UnBlockInclinedSlide();
	void UnblockClimbState();
	void UnblockWallRunState();
	bool CheckDeltaVectorInCurrentState(const FVector& InputDeltaVector, FVector& CheckDeltaVector, FRotator& CheckRotation); //Check climb is possibly from Approximate coordinate and return realy coordinate
	bool CheckDeltaVectorInCurrentState(FVector& CheckDeltaVector, FRotator& CheckRotation); //Check climb is possibly in current character location coordinate and return realy coordinate
	bool CheckDeltaVectorInCurrentState();//Check climb is possibly in current character location without return new coordinates
	void MoveTo(const FVector& Delta, const FRotator& NewRotation);
	
};
