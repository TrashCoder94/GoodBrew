#pragma once

/*
 TEMPORARY

 Using to test out how everything looks in the editor!

 */

#include "Component.h"
#include "GBEngine/Core/Colour.h"
#include "GBEngine/Renderer/Texture.h"

namespace GB
{
	class TestData : public BaseObject
	{
		GB_REFLECT()

	public:
		TestData();
		~TestData();

		// FLOATS
		GBVARIABLE(Edit)
		float m_Float;
		GBVARIABLE(Edit)
		float2 m_Float2;
		GBVARIABLE(Edit)
		float3 m_Float3;
		GBVARIABLE(Edit)
		float4 m_Float4;

		// INTS
		GBVARIABLE(Edit)
		int m_Int;
		GBVARIABLE(Edit)
		int2 m_Int2;
		GBVARIABLE(Edit)
		int3 m_Int3;
		GBVARIABLE(Edit)
		int4 m_Int4;

		// BOOLS
		GBVARIABLE(Edit)
		bool m_Bool;

		// STRINGS
		GBVARIABLE(Edit)
		std::string m_String;

		// COLOUR
		GBVARIABLE(Edit)
		Colour m_Colour;

		// TEXTURES
		GBVARIABLE(Edit)
		SharedPtr<Texture2D> m_pTexture;

		// VECTORS

		// OF FLOATS
		GBVARIABLE(Edit)
		std::vector<float> m_VectorOfFloats;
		GBVARIABLE(Edit)
		std::vector<float2> m_VectorOfFloat2s;
		GBVARIABLE(Edit)
		std::vector<float3> m_VectorOfFloat3s;
		GBVARIABLE(Edit)
		std::vector<float4> m_VectorOfFloat4s;

		// OF INTS
		GBVARIABLE(Edit)
		std::vector<int> m_VectorOfInts;
		GBVARIABLE(Edit)
		std::vector<int2> m_VectorOfInt2s;
		GBVARIABLE(Edit)
		std::vector<int3> m_VectorOfInt3s;
		GBVARIABLE(Edit)
		std::vector<int4> m_VectorOfInt4s;

		// OF STRINGS
		GBVARIABLE(Edit)
		std::vector<std::string> m_VectorOfStrings;

		// OF COLOURS
		GBVARIABLE(Edit)
		std::vector<Colour> m_VectorOfColours;

		// OF TEXTURES
		GBVARIABLE(Edit)
		std::vector<SharedPtr<Texture2D>> m_VectorOfTextures;
	};

	class TestComponent : public Component
	{
		GB_REFLECT()

	public:
		TestComponent();
		~TestComponent();

		// FLOATS
		GBVARIABLE(Edit)
		float m_Float;
		GBVARIABLE(Edit)
		float2 m_Float2;
		GBVARIABLE(Edit)
		float3 m_Float3;
		GBVARIABLE(Edit)
		float4 m_Float4;

		// INTS
		GBVARIABLE(Edit)
		int m_Int;
		GBVARIABLE(Edit)
		int2 m_Int2;
		GBVARIABLE(Edit)
		int3 m_Int3;
		GBVARIABLE(Edit)
		int4 m_Int4;

		// BOOLS
		GBVARIABLE(Edit)
		bool m_Bool;

		// STRINGS
		GBVARIABLE(Edit)
		std::string m_String;

		// COLOUR
		GBVARIABLE(Edit)
		Colour m_Colour;

		// TEXTURES
		GBVARIABLE(Edit)
		SharedPtr<Texture2D> m_pTexture;

		// CLASS
		GBVARIABLE(Edit)
		TestData m_Class;

		GBVARIABLE(Edit)
		TestData* m_pClass;

		GBVARIABLE(Edit)
		UniquePtr<TestData> m_pUniquePtrClass;

		GBVARIABLE(Edit)
		SharedPtr<TestData> m_pSharedPtrClass;

		// VECTORS

		// OF FLOATS
		GBVARIABLE(Edit)
		std::vector<float> m_VectorOfFloats;
		GBVARIABLE(Edit)
		std::vector<float2> m_VectorOfFloat2s;
		GBVARIABLE(Edit)
		std::vector<float3> m_VectorOfFloat3s;
		GBVARIABLE(Edit)
		std::vector<float4> m_VectorOfFloat4s;

		// OF INTS
		GBVARIABLE(Edit)
		std::vector<int> m_VectorOfInts;
		GBVARIABLE(Edit)
		std::vector<int2> m_VectorOfInt2s;
		GBVARIABLE(Edit)
		std::vector<int3> m_VectorOfInt3s;
		GBVARIABLE(Edit)
		std::vector<int4> m_VectorOfInt4s;

		// OF STRINGS
		GBVARIABLE(Edit)
		std::vector<std::string> m_VectorOfStrings;

		// OF COLOURS
		GBVARIABLE(Edit)
		std::vector<Colour> m_VectorOfColours;

		// OF TEXTURES
		GBVARIABLE(Edit)
		std::vector<SharedPtr<Texture2D>> m_VectorOfTextures;

		// OF CLASSES
		GBVARIABLE(Edit)
		std::vector<TestData> m_VectorOfClasses;

		GBVARIABLE(Edit)
		std::vector<TestData*> m_pVectorOfClasses;

		GBVARIABLE(Edit)
		std::vector<UniquePtr<TestData>> m_pVectorOfUniquePtrClasses;

		GBVARIABLE(Edit)
		std::vector<SharedPtr<TestData>> m_pVectorOfSharedPtrClasses;

		GBVARIABLE(Edit)
		std::vector<WeakPtr<TestData>> m_pVectorOfWeakPtrClasses;
	};
}
