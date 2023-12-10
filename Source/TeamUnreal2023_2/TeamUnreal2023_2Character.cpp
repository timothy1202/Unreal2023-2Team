// Copyright Epic Games, Inc. All Rights Reserved.

#include "TeamUnreal2023_2Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InvisibleMarble.h"


#include"Perception/AIPerceptionStimuliSourceComponent.h"
#include"Perception/AISense_Sight.h"


//////////////////////////////////////////////////////////////////////////
// ATeamUnreal2023_2Character

void ATeamUnreal2023_2Character::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

ATeamUnreal2023_2Character::ATeamUnreal2023_2Character()
{
	// 박광훈 - 오버랩 
	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
		// RootComponent에 연결
		OverlapComponent->SetupAttachment(GetMesh());
		// 오버랩 이벤트 활성화
		OverlapComponent->SetGenerateOverlapEvents(true);

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// 음염준 - 오른손 주먹에다 콜리전 박스 할당
	RightFistCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightFistCollisionBox"));
	if (RightFistCollisionBox)
	{
		FAttachmentTransformRules const newRules
		{
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepWorld,
			false
		};
		RightFistCollisionBox->AttachToComponent(GetMesh(), newRules, FName("hand_r_socket"));
		RightFistCollisionBox->SetRelativeLocation(FVector(-7.f, 0.f, 0.f));
		RightFistCollisionBox->SetBoxExtent(FVector(5.f), false);
	}
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	SetupStimulusSource();
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ATeamUnreal2023_2Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}


	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ATeamUnreal2023_2Character::HandleOverlap);


}

/// <summary>
/// 박광훈 - 틱 이벤트
/// </summary>
/// <param name="DeltaTime"></param>
void ATeamUnreal2023_2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetInvisibility();
}

/// <summary>
/// 박강훈 - 구슬 오버랩 함수
/// </summary>
/// <param name="OverlappedComponent"></param>
/// <param name="OtherActor"></param>
/// <param name="OtherComp"></param>
/// <param name="OtherBodyIndex"></param>
/// <param name="bFromSweep"></param>
/// <param name="SweepResult"></param>
void ATeamUnreal2023_2Character::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag("InvisibleMarble"))
	{
		IsInvisible = true; 
		UE_LOG(LogTemp, Warning, TEXT("Your message here."));
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &ATeamUnreal2023_2Character::DelayPlay, 3.f, false);
	}

}

//박광훈 - 플레이 투명 유무 초기화
bool ATeamUnreal2023_2Character::IsInvisible = false;

/// <summary>
/// 박광훈 - 딜레이 후 실행 함수
/// </summary>
void ATeamUnreal2023_2Character::DelayPlay()
{
	IsInvisible = false;
}

/// <summary>
/// 플레이어 투명화 적용 (시각적으로)
/// </summary>
void ATeamUnreal2023_2Character::SetInvisibility()
{
	if (IsInvisible == true)
	{
		
	}
	else
	{

	}
}

void ATeamUnreal2023_2Character::AttackCollisionEnable()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Attack Start!"));
	RightFistCollisionBox->SetCollisionProfileName("Fist");
	RightFistCollisionBox->SetNotifyRigidBodyCollision(true);
}

void ATeamUnreal2023_2Character::AttackCollisionDisable()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Attack Finish!"));
	RightFistCollisionBox->SetCollisionProfileName("NoCollision");
	RightFistCollisionBox->SetNotifyRigidBodyCollision(false);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATeamUnreal2023_2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATeamUnreal2023_2Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATeamUnreal2023_2Character::Look);

		//Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ATeamUnreal2023_2Character::Attack);

		//Focus
		//시간 여유가 되면 C++로 추가할 예정
		//카메라가 바라보고 있는 방향의 제일 가까운 적을 찾아서 포커싱
		EnhancedInputComponent->BindAction(FocusAction, ETriggerEvent::Started, this, &ATeamUnreal2023_2Character::Focus);
	}

}

void ATeamUnreal2023_2Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATeamUnreal2023_2Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATeamUnreal2023_2Character::Attack()
{
	if (AttackMontage)
		if(!(GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage)))
			PlayAnimMontage(AttackMontage);
}




