#include <linalg.h>
#include <iostream>

#include "ThirdParty/Reflection/TypeDescriptor.h"
#include "GBEngine/Renderer/Texture.h"

using namespace linalg::aliases;

namespace reflect
{
	//--------------------------------------------------------
	// Type descriptor for Ints
	//--------------------------------------------------------

	struct TypeDescriptor_Int2 : TypeDescriptor {
		TypeDescriptor_Int2() : TypeDescriptor{ "Int2", sizeof(int2), FieldType::Int2 } {
		}
		virtual void dump(const void* obj, int /* unused */) const override {
			const int2* value = (const int2*)obj;
			std::cout << "Int2{" << value->x << ", " << value->y << "}";
		}
	};

	template <>
	TypeDescriptor* getPrimitiveDescriptor<int2>() {
		static TypeDescriptor_Int2 typeDesc;
		return &typeDesc;
	}

	struct TypeDescriptor_Int3 : TypeDescriptor {
		TypeDescriptor_Int3() : TypeDescriptor{ "Int3", sizeof(int3), FieldType::Int3 } {
		}
		virtual void dump(const void* obj, int /* unused */) const override {
			const int3* value = (const int3*)obj;
			std::cout << "Int3{" << value->x << ", " << value->y << ", " << value->z << "}";
		}
	};

	template <>
	TypeDescriptor* getPrimitiveDescriptor<int3>() {
		static TypeDescriptor_Int3 typeDesc;
		return &typeDesc;
	}

	struct TypeDescriptor_Int4 : TypeDescriptor {
		TypeDescriptor_Int4() : TypeDescriptor{ "Int4", sizeof(int4), FieldType::Int4 } {
		}
		virtual void dump(const void* obj, int /* unused */) const override {
			const int4* value = (const int4*)obj;
			std::cout << "Int4{" << value->x << ", " << value->y << ", " << value->z << ", " << value->w << "}";
		}
	};

	template <>
	TypeDescriptor* getPrimitiveDescriptor<int4>() {
		static TypeDescriptor_Int4 typeDesc;
		return &typeDesc;
	}

	//--------------------------------------------------------
	// Type descriptor for Floats
	//--------------------------------------------------------

	struct TypeDescriptor_Float2 : TypeDescriptor {
		TypeDescriptor_Float2() : TypeDescriptor{ "Float2", sizeof(float2), FieldType::Float2 } {
		}
		virtual void dump(const void* obj, int /* unused */) const override {
			const float2* value = (const float2*)obj;
			std::cout << "Float2{" << value->x << ", " << value->y << "}";
		}
	};

	template <>
	TypeDescriptor* getPrimitiveDescriptor<float2>() {
		static TypeDescriptor_Float2 typeDesc;
		return &typeDesc;
	}

	struct TypeDescriptor_Float3 : TypeDescriptor {
		TypeDescriptor_Float3() : TypeDescriptor{ "Float3", sizeof(float3), FieldType::Float3 } {
		}
		virtual void dump(const void* obj, int /* unused */) const override {
			const float3* value = (const float3*)obj;
			std::cout << "Float3{" << value->x << ", " << value->y << ", " << value->z << "}";
		}
	};

	template <>
	TypeDescriptor* getPrimitiveDescriptor<float3>() {
		static TypeDescriptor_Float3 typeDesc;
		return &typeDesc;
	}

	struct TypeDescriptor_Float4 : TypeDescriptor {
		TypeDescriptor_Float4() : TypeDescriptor{ "Float4", sizeof(float4), FieldType::Float4 } {
		}
		virtual void dump(const void* obj, int /* unused */) const override {
			const float4* value = (const float4*)obj;
			std::cout << "Float4{" << value->x << ", " << value->y << ", " << value->z << ", " << value->w << "}";
		}
	};

	template <>
	TypeDescriptor* getPrimitiveDescriptor<float4>() {
		static TypeDescriptor_Float4 typeDesc;
		return &typeDesc;
	}

	//--------------------------------------------------------
	// Type descriptor for Textures
	//--------------------------------------------------------

	struct TypeDescriptor_Texture : TypeDescriptor {
		TypeDescriptor_Texture() : TypeDescriptor{ "Texture", sizeof(GB::Texture2D), FieldType::Texture } {
		}
		virtual void dump(const void* obj, int /* unused */) const override {
			const GB::SharedPtr<GB::Texture2D>* pTexture = (const GB::SharedPtr<GB::Texture2D>*)obj;
			std::cout << "Texture{" << (*pTexture)->GetRendererID() << "}";
		}
	};

	template <>
	TypeDescriptor* getPrimitiveDescriptor<GB::SharedPtr<GB::Texture2D>>() {
		static TypeDescriptor_Texture typeDesc;
		return &typeDesc;
	}

}