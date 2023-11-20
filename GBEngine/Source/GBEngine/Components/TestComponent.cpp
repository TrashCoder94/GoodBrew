#include "gbpch.h"
#include "TestComponent.h"

namespace GB
{
	TestData::TestData() : BaseObject(),
		m_Float(0.0f),
		m_Float2(0.0f),
		m_Float3(0.0f),
		m_Float4(0.0f),
		m_Int(0),
		m_Int2(0),
		m_Int3(0),
		m_Int4(0),
		m_Bool(false),
		m_String(""),
		m_Colour(),
		m_pTexture(Texture2D::Create("Assets/Textures/Checkerboard.png")),
		m_VectorOfFloats(),
		m_VectorOfFloat2s(),
		m_VectorOfFloat3s(),
		m_VectorOfFloat4s(),
		m_VectorOfInts(),
		m_VectorOfInt2s(),
		m_VectorOfInt3s(),
		m_VectorOfInt4s(),
		m_VectorOfBools(),
		m_VectorOfStrings(),
		m_VectorOfColours(),
		m_VectorOfTextures()
	{}

	TestComponent::TestComponent() : Component(),
		m_Float(0.0f),
		m_Float2(0.0f),
		m_Float3(0.0f),
		m_Float4(0.0f),
		m_Int(0),
		m_Int2(0),
		m_Int3(0),
		m_Int4(0),
		m_Bool(false),
		m_String(""),
		m_Colour(),
		m_pTexture(Texture2D::Create("Assets/Textures/Checkerboard.png")),
		m_Class(TestData()),
		m_pClass(new TestData()),
		m_pUniquePtrClass(new TestData()),
		m_pSharedPtrClass(new TestData()),
		m_pSharedPtrClassForWeakPtrClass(new TestData()),
		m_pWeakPtrClass(m_pSharedPtrClassForWeakPtrClass),
		m_VectorOfFloats(),
		m_VectorOfFloat2s(),
		m_VectorOfFloat3s(),
		m_VectorOfFloat4s(),
		m_VectorOfInts(),
		m_VectorOfInt2s(),
		m_VectorOfInt3s(),
		m_VectorOfInt4s(),
		m_VectorOfBools(),
		m_VectorOfStrings(),
		m_VectorOfColours(),
		m_VectorOfTextures(),
		m_VectorOfClasses(),
		m_pVectorOfClasses(),
		m_pVectorOfUniquePtrClasses(),
		m_pVectorOfSharedPtrClasses()
	{}

	TestComponent::~TestComponent()
	{
		// NORMAL VARIABLES
		if (m_pClass)
		{
			m_pClass->Deinitialize();
			delete m_pClass;
			m_pClass = nullptr;
		}

		// VECTOR VARIABLES
		for (size_t iC = 0; iC < m_pVectorOfClasses.size(); ++iC)
		{
			if (TestData* pClass = m_pVectorOfClasses[iC])
			{
				pClass->Deinitialize();
				delete pClass;
				pClass = nullptr;
			}
		}

		m_VectorOfFloats.clear();
		m_VectorOfFloat2s.clear();
		m_VectorOfFloat3s.clear();
		m_VectorOfFloat4s.clear();
		m_VectorOfInts.clear();
		m_VectorOfInt2s.clear();
		m_VectorOfInt3s.clear();
		m_VectorOfInt4s.clear();
		m_VectorOfBools.clear();
		m_VectorOfStrings.clear();
		m_VectorOfColours.clear();
		m_VectorOfTextures.clear();
		m_VectorOfClasses.clear();
		m_pVectorOfClasses.clear();
		m_pVectorOfUniquePtrClasses.clear();
		m_pVectorOfSharedPtrClasses.clear();
	}
}