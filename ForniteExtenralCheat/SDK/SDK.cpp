#include "SDK.h"
#include <Driver/Driver.h>
#include <Offset.h>

namespace Math 
{
	D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
	{
		D3DMATRIX pOut;
		pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
		pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
		pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
		pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
		pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
		pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
		pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
		pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
		pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
		pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
		pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
		pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
		pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
		pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
		pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
		pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

		return pOut;
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
	//	std::cout << "[World] BaseAddress + UWorld = 0x" << std::hex << (BaseAddress + Offset::UWorld) << std::endl;
	//	std::cout << "[World] UWorld = 0x" << std::hex << world << std::endl;
		return world;
	}
}

namespace UPlayer
{
	uintptr_t GetInstanceGame()
	{
		uintptr_t instance = ReadMemory<uintptr_t>(World::GetWorld() + Offset::OwningGameInstance);
	//	std::cout << "[UPlayer] GameInstance = 0x" << std::hex << instance << std::endl;
		return instance;
	}

	uintptr_t GetAPlayerController()
	{
		uintptr_t localPlayers = ReadMemory<uintptr_t>(GetInstanceGame() + Offset::LocalPlayers);
	//	std::cout << "[UPlayer] LocalPlayers = 0x" << std::hex << localPlayers << std::endl;

		uintptr_t player = ReadMemory<uintptr_t>(localPlayers);
	//	std::cout << "[UPlayer] LocalPlayer = 0x" << std::hex << player << std::endl;

		uintptr_t controller = ReadMemory<uintptr_t>(player + Offset::PlayerController);
	//	std::cout << "[UPlayer] PlayerController = 0x" << std::hex << controller << std::endl;

		return controller;
	}

	uintptr_t GetLocalPlayer()
	{
		uintptr_t pawn = ReadMemory<uintptr_t>(GetAPlayerController() + Offset::AcknowledgedPawn);
	//	std::cout << "[UPlayer] LocalPawn = 0x" << std::hex << pawn << std::endl;
		return pawn;
	}
}

namespace Aactor
{
	uintptr_t GetGameState()
	{
		uintptr_t gs = ReadMemory<uintptr_t>(World::GetWorld() + Offset::GameState);
	//	std::cout << "[Aactor] GameState = 0x" << std::hex << gs << std::endl;
		return gs;
	}

	uintptr_t GetPlayerArray()
	{
		uintptr_t array = ReadMemory<uintptr_t>(GetGameState() + Offset::PlayerArray);
		//std::cout << "[Aactor] PlayerArray = 0x" << std::hex << array << std::endl;
		return array;
	}

	int GetPlayerArraySize()
	{
		int size = ReadMemory<int>(GetGameState() + Offset::PlayerArray + Offset::SizePlayerArray);
		//std::cout << "[Aactor] PlayerArraySize = " << std::dec << size << std::endl;
		return size;
	}

	uintptr_t GetActorAddress(int index)
	{
		uintptr_t array = GetPlayerArray();
		uintptr_t actor = ReadMemory<uintptr_t>(array + (index * sizeof(uintptr_t)));

		//std::cout << "[Aactor] Actor[" << index << "] = 0x" << std::hex << actor << std::endl;

		return ReadMemory<uintptr_t>(actor+Offset::PawnPrivate);
	}
	FVector GetActorLocation(uintptr_t actor)
	{
		uintptr_t root = ReadMemory<uintptr_t>(actor + Offset::RootComponent);
		std::cout << "root: " << root << std::endl;
		//if (!root) return FVector(); 

		FVector location = ReadMemory<FVector>(root + Offset::RelativeLocation);
		return location;
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

	FVector GetBoneWithRotation(uintptr_t AactorAddress, int id)
	{
		FTransform bone = GetBoneIndex(AactorAddress, id);
		FTransform ComponentToWorld = ReadMemory<FTransform>(GetMesh(AactorAddress) + Offset::ComponentToWorld);

		D3DMATRIX Matrix;
		Matrix = Math::MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

		return FVector(Matrix._41, Matrix._42, Matrix._43);
	}
}