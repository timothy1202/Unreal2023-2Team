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
#include "Kismet/GameplayStatics.h"
#include "NPC.h"
#include "NPCAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include"Perception/AIPerceptionStimuliSourceComponent.h"
#include"Perception/AISense_Sight.h"
#include "Kismet/KismetMathLibrary.h"


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
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// À½¿°ÁØ - ¿À¸¥¼Õ ÁÖ¸Ô¿¡´Ù ÄÝ¸®Àü ¹Ú½º ÇÒ´ç
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

	//¹Ú±¤ÈÆ - ±Û¶óÀÌµå ¸Þ½¬ ÇÒ´ç
	GliderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GlidingMesh"));
	GliderMesh->SetupAttachment(RootComponent);

	//¹Ú±¤ÈÆ - ÆÖ ½ºÇÁ¸µ¾Ï ÇÒ´ç
	PetSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PetSpringArm"));
	PetSpringArm->SetupAttachment(RootComponent);

	//¹Ú±¤ÈÆ - ÆÖ ½ºÄÌ·¹Åæ ¸Þ½¬ ÇÒ´ç
	PetSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PetSkeletalMesh"));
	PetSkeletalMesh->SetupAttachment(PetSpringArm);


	SetupStimulusSource();
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	playerHacked = false;
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

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATeamUnreal2023_2Character::HandleOverlap);

	IsInvisible = false;

	GliderMesh->SetVisibility(false);
	PetSkeletalMesh->SetVisibility(false);
	okayToSummonPet = false;

}


/// <summary>
/// ¹Ú±¤ÈÆ - Æ½ ÀÌº¥Æ®
/// </summary>
/// <param name="DeltaTime"></param>
void ATeamUnreal2023_2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Delta = DeltaTime;

	DescentPlayer();

	if (GetCharacterMovement()->IsWalking() && IsGliding)
	{
		StopGliding();
	}
}

/// <summary>
/// ¹Ú°­ÈÆ - ±¸½½ ¿À¹ö·¦ ÇÔ¼ö
/// </summary>
/// <param name="OverlappedComponent"></param>
/// <param name="OtherActor"></param>
/// <param name="OtherComp"></param>
/// <param name="OtherBodyIndex"></param>
/// <param name="bFromSweep"></param>
/// <param name="SweepResult"></param>
void ATeamUnreal2023_2Character::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (playerHacked == false)
	{
		if (OtherComp->ComponentHasTag("InvisibleMarble"))
		{
			IsInvisible = true;

			UpdateInvisible(IsInvisible);
			ChangeMaterialToInvisible();
			GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &ATeamUnreal2023_2Character::DelayPlay, 3.f, false);
		}
	}
	else
	{

	}

}

/// <summary>
/// ¹Ú±¤ÈÆ - µô·¹ÀÌ ÈÄ ½ÇÇà ÇÔ¼ö
/// </summary>
void ATeamUnreal2023_2Character::DelayPlay()
{
	IsInvisible = false;
	UpdateInvisible(IsInvisible);
	RestoreOriginalMaterial();
}

/// <summary>
/// ¹Ú±¤ÈÆ - ÇÃ·¹ÀÌ¾î Åõ¸í ¸ÓÆ¼¸®¾ó ÀÔÈ÷±â
/// </summary>
void ATeamUnreal2023_2Character::ChangeMaterialToInvisible()
{
	if (USkeletalMeshComponent* MeshComponent = GetMesh())
	{
		if (UMaterialInterface* InvisibleMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("'/Game/M_Invisible.M_Invisible'")))
		{
			MeshComponent->SetMaterial(0, InvisibleMaterial);
			MeshComponent->SetMaterial(1, InvisibleMaterial);
		}
	}
}

void ATeamUnreal2023_2Character::ChangeHackedPlayerToInvisible()
{
	if (USkeletalMeshComponent* MeshComponent = GetMesh())
	{
		if (UMaterialInterface* InvisibleMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("'/Game/M_Hacked.M_Hacked'")))
		{
			MeshComponent->SetMaterial(0, InvisibleMaterial);
			MeshComponent->SetMaterial(1, InvisibleMaterial);
		}
	}
}

/// <summary>
/// ¹Ú±¤ÈÆ - ÇÃ·¹ÀÌ¾î ¿ø·¡ ¸ÓÆ¼¸®¾ó ÀÔÈ÷±â
/// </summary>
void ATeamUnreal2023_2Character::RestoreOriginalMaterial()
{
	if (USkeletalMeshComponent* MeshComponent = GetMesh())
	{
		if (UMaterialInterface* OriginalMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("'/Game/Characters/Mannequins/Materials/MI_Manny_01.MI_Manny_01'")))
		{
			MeshComponent->SetMaterial(0, OriginalMaterial);

		}
		if (UMaterialInterface* OriginalMaterial1 = LoadObject<UMaterialInterface>(nullptr, TEXT("'/Game/Characters/Mannequins/Materials/MI_Manny_02.MI_Manny_02'")))
		{
			MeshComponent->SetMaterial(1, OriginalMaterial1);
		}
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

/// <summary>
/// ¹Ú±¤ÈÆ - ¸ðµç ¾×ÅÍµéÀÇ Åõ¸íÈ­ Àû¿ë
/// </summary>
/// <param name="isVisible"></param>
void ATeamUnreal2023_2Character::UpdateInvisible(bool isVisible)
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPC::StaticClass(), OutActors);
	for (AActor* outActor : OutActors)
	{
		ANPC* anpc = Cast<ANPC>(outActor);
		ANPCAIController* npcAIControllerClass = Cast<ANPCAIController>(UAIBlueprintHelperLibrary::GetAIController(anpc));
		npcAIControllerClass->MakeIsInvisibleFalse(isVisible);
	}
}

/// <summary>
/// ¹Ú±¤ÈÆ - ±Û¶óÀÌµù ÇÔ¼ö
/// </summary>
void ATeamUnreal2023_2Character::Togglegliding()
{
	if (playerHacked == false)
	{
		if (IsGliding == false)
		{
			StartGliding();
		}
		else
		{
			StopGliding();
		}
	}
}

/// <summary>
/// ¹Ú±¤ÈÆ - ±Û¶óÀÌµù ½ÃÀÛ Á¶°Ç ÇÔ¼ö
/// </summary>
void ATeamUnreal2023_2Character::StartGliding()
{
	//¹Ú±¤ÈÆ - ±Û¶óÀÌµùÀÌ °¡´ÉÇÑÁö

	if (CanStartGliding())
	{
		GliderMesh->SetVisibility(true);
		CurrentVelocity = GetCharacterMovement()->Velocity;
		IsGliding = true;
		RecordOrignalSettings();

		GetCharacterMovement()->RotationRate = FRotator(0.f, 250.f, 0.0f);
		GetCharacterMovement()->GravityScale = 0.0;
		GetCharacterMovement()->AirControl = 0.9;
		GetCharacterMovement()->BrakingDecelerationFalling = 350.f;
		GetCharacterMovement()->MaxAcceleration = 1024;
		GetCharacterMovement()->MaxWalkSpeed = 600;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;

	}
}

/// <summary>
/// ¹Ú±¤ÈÆ - ±Û¶óÀÌµù ¸ØÃß´Â ÇÔ¼ö
/// </summary>
void ATeamUnreal2023_2Character::StopGliding()
{
	ApplyOrignalSettings();
	IsGliding = false;
	GliderMesh->SetVisibility(false);
}

/// <summary>
/// ¹Ú±¤ÈÆ - ±Û¶óÀÌµù ½ÃÀÛ ÇÔ¼ö
/// </summary>
/// <returns></returns>
bool ATeamUnreal2023_2Character::CanStartGliding()
{
	FHitResult Hit;

	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + GetActorUpVector() * MinimumHeight * -1.f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	TEnumAsByte<ECollisionChannel> TraceProperties = ECC_Visibility;

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceProperties, QueryParams);

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red);

	if (Hit.bBlockingHit == false && GetCharacterMovement()->IsFalling() == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// ¹Ú±¤ÈÆ - ±Û¶óÀÌµù ÀÌÀü ¼¼ÆÃ
/// </summary>
void ATeamUnreal2023_2Character::RecordOrignalSettings()
{
	OriginalOrientRotation = GetCharacterMovement()->bOrientRotationToMovement;
	OriginalGravityScale = GetCharacterMovement()->GravityScale;
	OriginalAirControl = GetCharacterMovement()->AirControl;
	OriginalDecelration = GetCharacterMovement()->BrakingDecelerationFalling;
	OriginalAcceleration = GetCharacterMovement()->MaxAcceleration;
	OriginalWalkingSpeed = GetCharacterMovement()->MaxWalkSpeed;
	OriginalDesiredRotation = GetCharacterMovement()->bUseControllerDesiredRotation;
}

void ATeamUnreal2023_2Character::DescentPlayer()
{
	if (CurrentVelocity.Z != DescendingRate * -1.f && IsGliding == true)
	{
		CurrentVelocity.Z = UKismetMathLibrary::FInterpTo(CurrentVelocity.Z, DescendingRate, Delta, 3.f);
		GetCharacterMovement()->Velocity.Z = DescendingRate * -1.f;
	}
}

void ATeamUnreal2023_2Character::ApplyOrignalSettings()
{
	GetCharacterMovement()->bOrientRotationToMovement = OriginalOrientRotation;
	GetCharacterMovement()->GravityScale = OriginalGravityScale;
	GetCharacterMovement()->AirControl = OriginalAirControl;
	GetCharacterMovement()->BrakingDecelerationFalling = OriginalDecelration;
	GetCharacterMovement()->MaxAcceleration = OriginalAcceleration;
	GetCharacterMovement()->MaxWalkSpeed = OriginalWalkingSpeed;
	GetCharacterMovement()->bUseControllerDesiredRotation = OriginalDesiredRotation;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

}

/// <summary>
/// ¹Ú±¤ÈÆ - ÆÖ ¼ÒÈ¯
/// </summary>
void ATeamUnreal2023_2Character::SummonPet()
{
	if (playerHacked == false)
	{
		if (okayToSummonPet == false)
		{
			PetSkeletalMesh->SetVisibility(true);
			GetCharacterMovement()->MaxWalkSpeed = 1000;
			okayToSummonPet = true;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATeamUnreal2023_2Character::CancelPet, 3.0f, false);
		}
	}
}

/// <summary>
/// ¹Ú±¤ÈÆ - ÆÖ »ç¿ë½Ã°£ ³¡³²
/// </summary>
void ATeamUnreal2023_2Character::CancelPet()
{
	PetSkeletalMesh->SetVisibility(false);
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetWorld()->GetTimerManager().SetTimer(CoolTimeHandle, this, &ATeamUnreal2023_2Character::PetCoolTime, 3.0f, false);
}

/// <summary>
/// ¹Ú±¤ÈÆ - ÆÖ ÄðÅ¸ÀÓ
/// </summary>
void ATeamUnreal2023_2Character::PetCoolTime()
{
	okayToSummonPet = false;
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

		//¹Ú±¤ÈÆ - ±Û¶óÀÌµù ÀÎÇ²
		EnhancedInputComponent->BindAction(GlidingAction, ETriggerEvent::Started, this, &ATeamUnreal2023_2Character::Togglegliding);

		//¹Ú±¤ÈÆ - ÆÖ ¼ÒÈ¯ ÀÎÇ²
		EnhancedInputComponent->BindAction(SummonPetAction, ETriggerEvent::Started, this, &ATeamUnreal2023_2Character::SummonPet);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATeamUnreal2023_2Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATeamUnreal2023_2Character::Look);

		//Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ATeamUnreal2023_2Character::Attack);

		//Focus
		//½Ã°£ ¿©À¯°¡ µÇ¸é C++·Î Ãß°¡ÇÒ ¿¹Á¤
		//Ä«¸Þ¶ó°¡ ¹Ù¶óº¸°í ÀÖ´Â ¹æÇâÀÇ Á¦ÀÏ °¡±î¿î ÀûÀ» Ã£¾Æ¼­ Æ÷Ä¿½Ì
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
	if (playerHacked == false)
	{
		if (AttackMontage)
			if (!(GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage)))
				PlayAnimMontage(AttackMontage);
	}
}
