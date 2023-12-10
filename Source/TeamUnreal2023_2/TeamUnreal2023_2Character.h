// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Animation/AnimMontage.h"
#include "TeamUnreal2023_2Character.generated.h"


UCLASS(config=Game)
class ATeamUnreal2023_2Character : public ACharacter
{
	GENERATED_BODY()

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// 음영준 - 플레이어 Attack Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	// 음영준 - Attack Action -> 플레이어 공격 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	// 음영준 - Focus Action -> 시간 여유가 되면 추가 될 액션
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FocusAction;

	// 음영준 - RightFistCollisionBox -> 플레이어 공격 시 잠시 활성화되는 박스콜리전
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* RightFistCollisionBox;

	class UAIPerceptionStimuliSourceComponent* StimulusSource;

	void SetupStimulusSource();

	/// <summary>
	/// 박광훈 - 캐릭터 투명 유무
	/// </summary>
	bool IsInvisible;

	

public:
	FORCEINLINE bool GetIsInvisible()
	{
		return IsInvisible;
	}


	/// <summary>
	/// 박광훈 - 오버랩 함수
	/// </summary>
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/// <summary>
	/// 박광훈 - 딜레이
	/// </summary>
	FTimerHandle DelayTimerHandle;

	/// <summary>
	/// 박광훈 - 플레이어 투명으로 만드는 커스텀 이벤트
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Custom")
	void SetInvisibility();
	
	/// <summary>
	/// 박광훈 - 틱 이벤트 추가
	/// </summary>
	virtual void Tick(float DeltaTime) override;


	void DelayPlay();

	ATeamUnreal2023_2Character();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// 음영준 - Attack기능이 탑재된 함수(Attack Action에 바인딩 됨)
	void Attack();

	// 음영준 - Focus기능이 탑재된 함수(Focus Action에 바인딩 됨)
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Input)
	void Focus();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// 음영준 - Attack시 RightFistCollision활성화 (Player Attack Montage에 탑재된 PlayerAttackAnimNotifyState클래스에서 호출됨)
	void AttackCollisionEnable();

	// 음영준 - Attack이 끝날 시 RightFistCollision비활성화 (Player Attack Montage에 탑재된 PlayerAttackAnimNotifyState클래스에서 호출됨)
	void AttackCollisionDisable();

	void UpdateInvisible(bool isVisible);
};

