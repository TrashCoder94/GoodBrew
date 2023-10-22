#include <linalg.h>
#include <iostream>

#include "ThirdParty/Reflection/TypeDescriptor.h"

using namespace linalg::aliases;

namespace reflect
{
	//--------------------------------------------------------
	// A type descriptor for Float3
	//--------------------------------------------------------

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
}