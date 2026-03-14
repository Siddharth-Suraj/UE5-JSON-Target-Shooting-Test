#include "JsonManager.h"
#include "BoxTarget.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonUtilities.h"

AJsonManager::AJsonManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AJsonManager::BeginPlay()
{
    Super::BeginPlay();
    FetchJson();
}

void AJsonManager::FetchJson()
{
    UE_LOG(LogTemp, Warning, TEXT("Fetching JSON..."));

    FString Url = "https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json";

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
        FHttpModule::Get().CreateRequest();

    Request->SetURL(Url);
    Request->SetVerb("GET");

    Request->OnProcessRequestComplete().BindLambda(
        [this](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bSuccess)
        {
            if (!bSuccess || !Response.IsValid())
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to download JSON"));
                return;
            }

            FString JsonString = Response->GetContentAsString();

            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<>> Reader =
                TJsonReaderFactory<>::Create(JsonString);

            if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON"));
                return;
            }

            UE_LOG(LogTemp, Warning, TEXT("JSON parsed successfully"));

            // Read all box type definitions first
            const TArray<TSharedPtr<FJsonValue>>* TypesArray;

            if (!JsonObject->TryGetArrayField(TEXT("types"), TypesArray))
            {
                UE_LOG(LogTemp, Error, TEXT("Types array not found"));
                return;
            }

            // Read all box objects that need to be spawned
            const TArray<TSharedPtr<FJsonValue>>* ObjectsArray;

            if (!JsonObject->TryGetArrayField(TEXT("objects"), ObjectsArray))
            {
                UE_LOG(LogTemp, Error, TEXT("Objects array not found"));
                return;
            }

            UE_LOG(LogTemp, Warning, TEXT("Objects count: %d"), ObjectsArray->Num());

            for (auto JsonValue : *ObjectsArray)
            {
                TSharedPtr<FJsonObject> Object = JsonValue->AsObject();

                if (!Object.IsValid())
                    continue;

                FString Type = Object->GetStringField(TEXT("type"));

                TSharedPtr<FJsonObject> TransformObject =
                    Object->GetObjectField(TEXT("transform"));

                const TArray<TSharedPtr<FJsonValue>>* LocationArray;
                const TArray<TSharedPtr<FJsonValue>>* RotationArray;
                const TArray<TSharedPtr<FJsonValue>>* ScaleArray;

                // Make sure all transform data exists before spawning
                if (TransformObject->TryGetArrayField(TEXT("location"), LocationArray) &&
                    TransformObject->TryGetArrayField(TEXT("rotation"), RotationArray) &&
                    TransformObject->TryGetArrayField(TEXT("scale"), ScaleArray))
                {
                    FVector Location(
                        (*LocationArray)[0]->AsNumber(),
                        (*LocationArray)[1]->AsNumber(),
                        (*LocationArray)[2]->AsNumber()
                    );

                    // JSON rotation is [roll, pitch, yaw], but FRotator expects (pitch, yaw, roll)
                    FRotator Rotation(
                        (*RotationArray)[1]->AsNumber(),
                        (*RotationArray)[2]->AsNumber(),
                        (*RotationArray)[0]->AsNumber()
                    );

                    FVector Scale(
                        (*ScaleArray)[0]->AsNumber(),
                        (*ScaleArray)[1]->AsNumber(),
                        (*ScaleArray)[2]->AsNumber()
                    );

                    FActorSpawnParameters SpawnParams;

                    UE_LOG(LogTemp, Warning, TEXT("Attempting to spawn box"));

                    ABoxTarget* Box = GetWorld()->SpawnActor<ABoxTarget>(
                        ABoxTarget::StaticClass(),
                        Location,
                        Rotation,
                        SpawnParams
                    );

                    if (Box)
                    {
                        Box->SetActorScale3D(Scale);

                        // Match this spawned object with its type data
                        for (auto TypeValue : *TypesArray)
                        {
                            TSharedPtr<FJsonObject> TypeObject = TypeValue->AsObject();

                            FString TypeName = TypeObject->GetStringField(TEXT("name"));

                            if (TypeName == Type)
                            {
                                int32 Health = TypeObject->GetIntegerField(TEXT("health"));
                                int32 Score = TypeObject->GetIntegerField(TEXT("score"));

                                Box->Health = Health;
                                Box->ScoreValue = Score;

                                const TArray<TSharedPtr<FJsonValue>>* ColorArray;

                                // Convert RGB values from JSON into Unreal color values
                                if (TypeObject->TryGetArrayField(TEXT("color"), ColorArray) && ColorArray->Num() >= 3)
                                {
                                    FLinearColor Color(
                                        (*ColorArray)[0]->AsNumber() / 255.0f,
                                        (*ColorArray)[1]->AsNumber() / 255.0f,
                                        (*ColorArray)[2]->AsNumber() / 255.0f,
                                        1.0f
                                    );

                                    if (Box->BoxMesh)
                                    {
                                        UMaterialInstanceDynamic* DynMat =
                                            Box->BoxMesh->CreateAndSetMaterialInstanceDynamic(0);

                                        if (DynMat)
                                        {
                                            DynMat->SetVectorParameterValue(TEXT("Color"), Color);
                                        }
                                    }
                                }

                                break;
                            }
                        }

                        UE_LOG(LogTemp, Warning, TEXT("Spawned Box of type %s"), *Type);
                    }
                }
            }
        });

    Request->ProcessRequest();
}
