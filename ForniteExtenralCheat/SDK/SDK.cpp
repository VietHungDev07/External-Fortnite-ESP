#include "SDK.h"
#include <Driver/Driver.h>
#include <Offset.h>
using namespace std;
namespace Math 
{
	inline D3DMATRIX MatrixMultiplication(D3DMATRIX pm1, D3DMATRIX pm2)
	{
		D3DMATRIX pout{};
		pout._11 = pm1._11 * pm2._11 + pm1._12 * pm2._21 + pm1._13 * pm2._31 + pm1._14 * pm2._41;
		pout._12 = pm1._11 * pm2._12 + pm1._12 * pm2._22 + pm1._13 * pm2._32 + pm1._14 * pm2._42;
		pout._13 = pm1._11 * pm2._13 + pm1._12 * pm2._23 + pm1._13 * pm2._33 + pm1._14 * pm2._43;
		pout._14 = pm1._11 * pm2._14 + pm1._12 * pm2._24 + pm1._13 * pm2._34 + pm1._14 * pm2._44;
		pout._21 = pm1._21 * pm2._11 + pm1._22 * pm2._21 + pm1._23 * pm2._31 + pm1._24 * pm2._41;
		pout._22 = pm1._21 * pm2._12 + pm1._22 * pm2._22 + pm1._23 * pm2._32 + pm1._24 * pm2._42;
		pout._23 = pm1._21 * pm2._13 + pm1._22 * pm2._23 + pm1._23 * pm2._33 + pm1._24 * pm2._43;
		pout._24 = pm1._21 * pm2._14 + pm1._22 * pm2._24 + pm1._23 * pm2._34 + pm1._24 * pm2._44;
		pout._31 = pm1._31 * pm2._11 + pm1._32 * pm2._21 + pm1._33 * pm2._31 + pm1._34 * pm2._41;
		pout._32 = pm1._31 * pm2._12 + pm1._32 * pm2._22 + pm1._33 * pm2._32 + pm1._34 * pm2._42;
		pout._33 = pm1._31 * pm2._13 + pm1._32 * pm2._23 + pm1._33 * pm2._33 + pm1._34 * pm2._43;
		pout._34 = pm1._31 * pm2._14 + pm1._32 * pm2._24 + pm1._33 * pm2._34 + pm1._34 * pm2._44;
		pout._41 = pm1._41 * pm2._11 + pm1._42 * pm2._21 + pm1._43 * pm2._31 + pm1._44 * pm2._41;
		pout._42 = pm1._41 * pm2._12 + pm1._42 * pm2._22 + pm1._43 * pm2._32 + pm1._44 * pm2._42;
		pout._43 = pm1._41 * pm2._13 + pm1._42 * pm2._23 + pm1._43 * pm2._33 + pm1._44 * pm2._43;
		pout._44 = pm1._41 * pm2._14 + pm1._42 * pm2._24 + pm1._43 * pm2._34 + pm1._44 * pm2._44;
		return pout;
	}

	inline _MATRIX Matrix(FVector Vec4, FVector origin = FVector(0, 0, 0))
	{
		double radPitch = (Vec4.x * double(M_PI) / 180.f);
		double radYaw = (Vec4.y * double(M_PI) / 180.f);
		double radRoll = (Vec4.z * double(M_PI) / 180.f);

		double SP = sinf(radPitch);
		double CP = cosf(radPitch);
		double SY = sinf(radYaw);
		double CY = cosf(radYaw);
		double SR = sinf(radRoll);
		double CR = cosf(radRoll);

		_MATRIX matrix;
		matrix.m[0][0] = CP * CY;
		matrix.m[0][1] = CP * SY;
		matrix.m[0][2] = SP;
		matrix.m[0][3] = 0.f;

		matrix.m[1][0] = SR * SP * CY - CR * SY;
		matrix.m[1][1] = SR * SP * SY + CR * CY;
		matrix.m[1][2] = -SR * CP;
		matrix.m[1][3] = 0.f;

		matrix.m[2][0] = -(CR * SP * CY + SR * SY);
		matrix.m[2][1] = CY * SR - CR * SP * SY;
		matrix.m[2][2] = CR * CP;
		matrix.m[2][3] = 0.f;

		matrix.m[3][0] = origin.x;
		matrix.m[3][1] = origin.y;
		matrix.m[3][2] = origin.z;
		matrix.m[3][3] = 1.f;

		return matrix;
	}


}

namespace World
{
	uintptr_t GetWorld()
	{
		uintptr_t world = ReadMemory<uintptr_t>(BaseAddress + Offset::UWorld);
		return world;
	}
}

namespace UPlayer
{
	uintptr_t GetInstanceGame()
	{
		uintptr_t instance = ReadMemory<uintptr_t>(World::GetWorld() + Offset::OwningGameInstance);
		return instance;
	}

	uintptr_t GetAPlayerController()
	{
		uintptr_t localPlayers = ReadMemory<uintptr_t>(GetInstanceGame() + Offset::LocalPlayers);
		uintptr_t player = ReadMemory<uintptr_t>(localPlayers);
		uintptr_t controller = ReadMemory<uintptr_t>(player + Offset::PlayerController);

		return controller;
	}

	uintptr_t GetLocalPlayer()
	{
		uintptr_t pawn = ReadMemory<uintptr_t>(GetAPlayerController() + Offset::AcknowledgedPawn);
		return pawn;
	}


}

namespace Aactor
{
	uintptr_t GetGameState()
	{
		uintptr_t gs = ReadMemory<uintptr_t>(World::GetWorld() + Offset::GameState);
		return gs;
	}

	uintptr_t GetPlayerArray()
	{
		uintptr_t array = ReadMemory<uintptr_t>(GetGameState() + Offset::PlayerArray);
		return array;
	}

	int GetPlayerArraySize()
	{
		int size = ReadMemory<int>(GetGameState() + Offset::PlayerArray + Offset::SizePlayerArray);
		return size;
	}

	uintptr_t GetActorAddress(int index)
	{
		uintptr_t array = GetPlayerArray();
		uintptr_t actor = ReadMemory<uintptr_t>(array + (index * sizeof(uintptr_t)));
		return ReadMemory<uintptr_t>(actor+Offset::PawnPrivate);
	}
	FVector GetActorLocation(uintptr_t actor)
	{
		uintptr_t root = ReadMemory<uintptr_t>(actor + Offset::RootComponent);
		FVector location = ReadMemory<FVector>(root + Offset::RelativeLocation);
		return location;
	}

	int GetTeamID(uintptr_t actor)
	{
		int TeamID = ReadMemory<uintptr_t>(actor + Offset::TeamIndex);
		return TeamID;
	}



}


namespace Camera 
{

	SCamera GetCamera()
	{
		SCamera camera;
		auto camera_postion = camera;
		uintptr_t location_pointer = ReadMemory<uintptr_t>(World::GetWorld() + Offset::CameraCachePrivate);
		uintptr_t rotation_pointer = ReadMemory<uintptr_t>(World::GetWorld() + (Offset::CameraCachePrivate+0x10));
		FNRot fnrot{};
		fnrot.a = ReadMemory<double>(rotation_pointer);
		fnrot.b = ReadMemory<double>(rotation_pointer + 0x20);
		fnrot.c = ReadMemory<double>(rotation_pointer + 0x1D0);
		camera.Location = ReadMemory<FVector>(location_pointer);
		camera.Rotation.x = asin(fnrot.c) * (180.0 / M_PI);
		camera.Rotation.y = ((atan2(fnrot.a * -1, fnrot.b) * (180.0 / M_PI)) * -1) * -1;
		camera.FieldOfView = ReadMemory<float>(UPlayer::GetAPlayerController() + 0x3B4) * 90.0f; 

		return camera;
	}

	FVector2D ProjectWorldToScreen(FVector WorldLocation)
	{
		auto camera_postion = GetCamera();

		if (WorldLocation.x == 0) return FVector2D(0, 0);

		_MATRIX tempMatrix = Math::Matrix(camera_postion.Rotation);
		FVector vAxisX = FVector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		FVector vAxisY = FVector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		FVector vAxisZ = FVector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
		FVector vDelta = WorldLocation - camera_postion.Location;
		FVector vTransformed = FVector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.z < 1.f) vTransformed.z = 1.f;

		return FVector2D((ScreenWidth / 2.0f) + vTransformed.x * (((ScreenWidth / 2.0f) / tanf(camera_postion.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, (ScreenHeight / 2.0f) - vTransformed.y * (((ScreenWidth / 2.0f) / tanf(camera_postion.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z);
	}
}
namespace Bone
{
	uintptr_t GetMesh(uintptr_t AactorAddress)
	{
		return ReadMemory<uintptr_t>(AactorAddress + Offset::Mesh);

	}

	FTransform GetBoneIndex(uintptr_t AactorAddress, int index)
	{
		uintptr_t bonearray;
		bonearray = ReadMemory<uintptr_t>(GetMesh(AactorAddress) + Offset::CachedBoneSpaceTransforms);

		if (bonearray == NULL)
		{
			bonearray = ReadMemory<DWORD_PTR>(GetMesh(AactorAddress) + Offset::CachedComponentSpaceTransforms);
		}
		return ReadMemory<FTransform>(bonearray + (index * 0x60));
	}

	FVector GetBoneWithRotation(uintptr_t mesh, int id)
	{
		uintptr_t bone_array = ReadMemory<uintptr_t>(mesh + Offset::CachedBoneSpaceTransforms);
		if (bone_array == 0) bone_array = ReadMemory<uintptr_t>(mesh + Offset::CachedComponentSpaceTransforms);
		FTransform bone = ReadMemory<FTransform>(bone_array + (id * 0x60));
		FTransform component_to_world = ReadMemory<FTransform>(mesh + Offset::ComponentToWorld);
		D3DMATRIX matrix = Math::MatrixMultiplication(bone.ToMatrixWithScale(), component_to_world.ToMatrixWithScale());
		return FVector(matrix._41, matrix._42, matrix._43);
	}
}