// Fill out your copyright notice in the Description page of Project Settings.


#include "InvisibleMarble.h"
#include "Components/SphereComponent.h" //¹Ú±¤ÈÆ - ½ºÇÇ¾î Çì´õ Ãß°¡

// Sets default values
AInvisibleMarble::AInvisibleMarble()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // ¹Ú±¤ÈÆ - ÄÄÆ÷³ÍÆ® ¼³Á¤
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    RootComponent = SphereComponent;
    
    // ¹Ú±¤ÈÆ - ½ºÅÂÆ½ ÄÄÆ÷³ÍÆ® ¼³Á¤
    ShpereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShpereMesh"));
    ShpereMesh->SetupAttachment(SphereComponent);

    // ¹Ú±¤ÈÆ - ½ºÅÂÆ½ ¸Þ½¬ ·Îµå
    static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    if (StaticMeshAsset.Succeeded())
    {
        ShpereMesh->SetStaticMesh(StaticMeshAsset.Object);
    }

    // ¹Ú±¤ÈÆ - ±¸ Å©±â ¼³Á¤
    SphereComponent->SetSphereRadius(50.f);

    // ¹Ú±¤ÈÆ - ±¸ ¸ÓÆ¼¸®¾ó ¼³Á¤
    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/NewMaterial.NewMaterial"));
    if (MaterialAsset.Succeeded())
    {
        MyMaterial = MaterialAsset.Object;
        ShpereMesh->SetMaterial(0, MyMaterial);
    }

    // ¹Ú±¤ÈÆ - ¿¡¼Â ºÒ·¯¿À±â
    static ConstructorHelpers::FClassFinder<AActor> BPThirdPersonCharacterClassFinder(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter'"));
    if (BPThirdPersonCharacterClassFinder.Succeeded())
    {
        BPThirdPersonCharacterClass = BPThirdPersonCharacterClassFinder.Class;
    }

    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AInvisibleMarble::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AInvisibleMarble::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInvisibleMarble::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInvisibleMarble::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherActor->GetClass() == BPThirdPersonCharacterClass)
    {
        Destroy();
    }
}