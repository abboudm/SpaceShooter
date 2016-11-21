// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLinearColor;
class UTexture2D;
struct FVector;
class UWorld;
#ifdef OCEANPLUGIN_OceanManager_generated_h
#error "OceanManager.generated.h already included, missing '#pragma once' in OceanManager.h"
#endif
#define OCEANPLUGIN_OceanManager_generated_h

#define SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_75_GENERATED_BODY \
	friend OCEANPLUGIN_API class UScriptStruct* Z_Construct_UScriptStruct_FWaveSetParameters(); \
	static class UScriptStruct* StaticStruct();


#define SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_35_GENERATED_BODY \
	friend OCEANPLUGIN_API class UScriptStruct* Z_Construct_UScriptStruct_FWaveParameter(); \
	static class UScriptStruct* StaticStruct();


#define SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetHeightmapPixel) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_U); \
		P_GET_PROPERTY(UFloatProperty,Z_Param_V); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FLinearColor*)Z_Param__Result=this->GetHeightmapPixel(Z_Param_U,Z_Param_V); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoadLandscapeHeightmap) \
	{ \
		P_GET_OBJECT(UTexture2D,Z_Param_Tex2D); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->LoadLandscapeHeightmap(Z_Param_Tex2D); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetWaveHeightValue) \
	{ \
		P_GET_STRUCT_REF(FVector,Z_Param_Out_location); \
		P_GET_OBJECT(UWorld,Z_Param_World); \
		P_GET_UBOOL(Z_Param_HeightOnly); \
		P_GET_UBOOL(Z_Param_TwoIterations); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FVector*)Z_Param__Result=this->GetWaveHeightValue(Z_Param_Out_location,Z_Param_World,Z_Param_HeightOnly,Z_Param_TwoIterations); \
		P_NATIVE_END; \
	}


#define SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetHeightmapPixel) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_U); \
		P_GET_PROPERTY(UFloatProperty,Z_Param_V); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FLinearColor*)Z_Param__Result=this->GetHeightmapPixel(Z_Param_U,Z_Param_V); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execLoadLandscapeHeightmap) \
	{ \
		P_GET_OBJECT(UTexture2D,Z_Param_Tex2D); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->LoadLandscapeHeightmap(Z_Param_Tex2D); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetWaveHeightValue) \
	{ \
		P_GET_STRUCT_REF(FVector,Z_Param_Out_location); \
		P_GET_OBJECT(UWorld,Z_Param_World); \
		P_GET_UBOOL(Z_Param_HeightOnly); \
		P_GET_UBOOL(Z_Param_TwoIterations); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FVector*)Z_Param__Result=this->GetWaveHeightValue(Z_Param_Out_location,Z_Param_World,Z_Param_HeightOnly,Z_Param_TwoIterations); \
		P_NATIVE_END; \
	}


#define SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAOceanManager(); \
	friend OCEANPLUGIN_API class UClass* Z_Construct_UClass_AOceanManager(); \
	public: \
	DECLARE_CLASS(AOceanManager, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/OceanPlugin"), NO_API) \
	DECLARE_SERIALIZER(AOceanManager) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_INCLASS \
	private: \
	static void StaticRegisterNativesAOceanManager(); \
	friend OCEANPLUGIN_API class UClass* Z_Construct_UClass_AOceanManager(); \
	public: \
	DECLARE_CLASS(AOceanManager, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/OceanPlugin"), NO_API) \
	DECLARE_SERIALIZER(AOceanManager) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AOceanManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AOceanManager) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AOceanManager); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AOceanManager); \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API AOceanManager(const AOceanManager& InCopy); \
public:


#define SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AOceanManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API AOceanManager(const AOceanManager& InCopy); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AOceanManager); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AOceanManager); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AOceanManager)


#define SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_133_PROLOG
#define SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_RPC_WRAPPERS \
	SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_INCLASS \
	SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_RPC_WRAPPERS_NO_PURE_DECLS \
	SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_INCLASS_NO_PURE_DECLS \
	SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h_136_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class OceanManager."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SpaceShooter_Plugins_OceanPlugin_Source_OceanPlugin_Classes_OceanManager_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
