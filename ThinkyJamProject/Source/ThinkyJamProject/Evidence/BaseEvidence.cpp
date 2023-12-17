// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEvidence.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseEvidence::ABaseEvidence()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    MeshComp->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
    //MeshComp->SetRelativeRotation(FRotator(90, 0, 0));
    RootComponent = MeshComp;

    ID = 0;
    DisplayText = "";
    Position = { 0,0 };

}

// Called when the game starts or when spawned
void ABaseEvidence::BeginPlay()
{
	Super::BeginPlay();

    if (IsValid(WidgetTemplate))
    {
        WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetTemplate);

        WidgetInstance->AddToViewport();
    }
	
}

// Called every frame
void ABaseEvidence::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEvidence::ResizeMesh()
{
    if (IsValid(WidgetInstance))
    {
        if (IsValid(MeshComp->GetStaticMesh()))
        {
            FVector2D Size = WidgetInstance->GetDesiredSize();

            FBox BoundBox = MeshComp->GetStaticMesh()->GetBoundingBox();

            FVector BoxSize = BoundBox.GetSize();

            MeshComp->SetWorldScale3D(FVector(Size.Y / BoxSize.Y, 0.01, Size.X / BoxSize.X));
        }
        //Needs to be removes from viewport if it exists regardess of resizing
        WidgetInstance->RemoveFromViewport();
        WidgetInstance = nullptr;
    }
}
