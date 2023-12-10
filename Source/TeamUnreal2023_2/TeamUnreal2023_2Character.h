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

	// ������ - �÷��̾� Attack Montage
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

	// ������ - Attack Action -> �÷��̾� ���� �׼�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	// ������ - Focus Action -> �ð� ������ �Ǹ� �߰� �� �׼�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FocusAction;

	// ������ - RightFistCollisionBox -> �÷��̾� ���� �� ��� Ȱ��ȭ�Ǵ� �ڽ��ݸ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* RightFistCollisionBox;

	class UAIPerceptionStimuliSourceComponent* StimulusSource;

	void SetupStimulusSource();

	/// <summary>
	/// �ڱ��� - ĳ���� ���� ����
	/// </summary>
	bool IsInvisible;

	

public:
	FORCEINLINE bool GetIsInvisible()
	{
		return IsInvisible;
	}


	/// <summary>
	/// �ڱ��� - ������ �Լ�
	/// </summary>
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/// <summary>
	/// �ڱ��� - ������
	/// </summary>
	FTimerHandle DelayTimerHandle;

	/// <summary>
	/// �ڱ��� - �÷��̾� �������� ����� Ŀ���� �̺�Ʈ
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Custom")
	void SetInvisibility();
	
	/// <summary>
	/// �ڱ��� - ƽ �̺�Ʈ �߰�
	/// </summary>
	virtual void Tick(float DeltaTime) override;


	void DelayPlay();

	ATeamUnreal2023_2Character();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// ������ - Attack����� ž��� �Լ�(Attack Action�� ���ε� ��)
	void Attack();

	// ������ - Focus����� ž��� �Լ�(Focus Action�� ���ε� ��)
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

	// ������ - Attack�� RightFistCollisionȰ��ȭ (Player Attack Montage�� ž��� PlayerAttackAnimNotifyStateŬ�������� ȣ���)
	void AttackCollisionEnable();

	// ������ - Attack�� ���� �� RightFistCollision��Ȱ��ȭ (Player Attack Montage�� ž��� PlayerAttackAnimNotifyStateŬ�������� ȣ���)
	void AttackCollisionDisable();

	void UpdateInvisible(bool isVisible);
};

