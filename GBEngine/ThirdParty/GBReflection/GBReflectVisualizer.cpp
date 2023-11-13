#include "GBReflectVisualizer.h"

#include <imgui_internal.h>
#include <imgui-SFML.h>
#include <imgui_stdlib.h>
#include <linalg.h>
#include <string>

#include "TypeDescriptorVector.h"
#include "GBEngine/Core/Colour.h"
#include "GBEngine/Objects/BaseObject.h"
#include "GBEngine/Renderer/Texture.h"

// TODO: Think how to abstract/display this in editor?
#include "GBEngine/Renderer/Platforms/SFML/SFMLTexture.h"

using namespace linalg::aliases;

namespace GB
{	
	// Add element button colours
	static const ImVec4& kAddElementButtonColourIdle			= ImVec4{ 0.0f, 0.5f, 0.0f, 1.0f };
	static const ImVec4& kAddElementButtonColourHover			= ImVec4{ 0.0f, 0.39f, 0.0f, 1.0f };
	static const ImVec4& kAddElementButtonColourActive			= ImVec4{ 0.0f, 0.39f, 0.0f, 1.0f };

	// Remove element button colours
	static const ImVec4& kRemoveElementButtonColourIdle			= ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f };
	static const ImVec4& kRemoveElementButtonColourHover		= ImVec4{ 0.39f, 0.0f, 0.0f, 1.0f };
	static const ImVec4& kRemoveElementButtonColourActive		= ImVec4{ 0.39f, 0.0f, 0.0f, 1.0f };

	// X button colours
	static const ImVec4& kEditorVariableXButtonColour			= ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f };
	static const ImVec4& kEditorVariableXButtonHoveredColour	= ImVec4{ 0.9f, 0.2f, 0.25f, 1.0f };
	static const ImVec4& kEditorVariableXButtonActiveColour		= ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f };

	// Y button colours
	static const ImVec4& kEditorVariableYButtonColour			= ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f };
	static const ImVec4& kEditorVariableYButtonHoveredColour	= ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f };
	static const ImVec4& kEditorVariableYButtonActiveColour		= ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f };

	// Z button colours
	static const ImVec4& kEditorVariableZButtonColour			= ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f };
	static const ImVec4& kEditorVariableZButtonHoveredColour	= ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f };
	static const ImVec4& kEditorVariableZButtonActiveColour		= ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f };

	// W button colours
	static const ImVec4& kEditorVariableWButtonColour			= ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f };
	static const ImVec4& kEditorVariableWButtonHoveredColour	= ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f };
	static const ImVec4& kEditorVariableWButtonActiveColour		= ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f };

	// Sprite image size
	static const ImVec2& kEditorVariableImageSize				= ImVec2{ 50.0f, 50.0f };

	static constexpr int kEditorVariableIntResetValue			= 0;
	static constexpr float kEditorVariableFloatResetValue		= 0.0f;
	static constexpr float kEditorVariableColumnWidth			= 100.0f;
	static constexpr float kEditorVectorSpacingAfterIndex		= 20.0f;

	// ===================================
	// ImGui helpers
	ImFont* GetEditorVariableButtonImGuiFont()
	{
		return ImGui::GetIO().Fonts->Fonts[0];
	}

	ImVec2 GetEditorVariableButtonSize()
	{
		const float kEditorVariableLineHeight = GetEditorVariableLineHeight();
		const ImVec2& kEditorVariableButtonSize = { kEditorVariableLineHeight + 3.0f, kEditorVariableLineHeight };
		return kEditorVariableButtonSize;
	}

	float GetEditorVariableLineHeight()
	{
		return (GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f);
	}
	
	// =================================== 
	// SHARED - Used for all variable displays in the editor
	void BeginEditorVariableTable(const char* tableName, const float spaceAfterVariableName/* = 100.0f*/)
	{
		ImGui::BeginTable("floatTable", 2);

		// First column where variable name will be.
		ImGui::TableSetupColumn("variableNameColumn", ImGuiTableColumnFlags_WidthFixed, spaceAfterVariableName);

		// Second column where the values will be.
		ImGui::TableSetupColumn("variableValuesColumn");

		// This is the first row of the table (only have 1 row in this table and make use of multiple columns).
		ImGui::TableNextRow();

		// First column for variable name.
		ImGui::TableSetColumnIndex(0);
	}

	void EndEditorVariableTable()
	{
		ImGui::EndTable();
	}

	void DrawMemberName(const char* name)
	{
		ImGui::TextUnformatted(name);
		const ImVec2& textWidth = ImGui::CalcTextSize(name, nullptr, true);
		ImGui::SameLine(textWidth.x);
	}

	void BeginEditorVariable(const char* name, const float spaceAfterVariableName/* = 100.0f*/)
	{
		ImGui::PushID(name);
		BeginEditorVariableTable(std::string(name).append("table").c_str(), spaceAfterVariableName);
		DrawMemberName(name);
		ImGui::TableSetColumnIndex(1);
	}

	void EndEditorVariable()
	{
		EndEditorVariableTable();
		ImGui::PopID();
	}

	void BeginAddElementButtonStyle()
	{
		ImGui::PushStyleColor(ImGuiCol_Button, kAddElementButtonColourIdle);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kAddElementButtonColourHover);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, kAddElementButtonColourActive);
	}

	void EndAddElementButtonStyle()
	{
		ImGui::PopStyleColor(3);
	}

	void BeginRemoveElementButtonStyle()
	{
		ImGui::PushStyleColor(ImGuiCol_Button, kRemoveElementButtonColourIdle);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kRemoveElementButtonColourHover);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, kRemoveElementButtonColourActive);
	}

	void EndRemoveElementButtonStyle()
	{
		ImGui::PopStyleColor(3);
	}

	void DrawMember(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr)
	{
		switch (reflectedMemberData.type->getFieldType())
		{
			case reflect::FieldType::None:
			{
				GB_CORE_ASSERT(false, "TypeDescriptor not implemented in ThirdParty/GBReflection/GBTypeDescriptors.cpp");
				break;
			}
			case reflect::FieldType::Float:
			{
				GB::DrawFloat(reflectedMemberData.name, memberPtr);
				break;
			}
			case reflect::FieldType::Float2:
			{
				GB::DrawFloat2(reflectedMemberData.name, memberPtr);
				break;
			}
			case reflect::FieldType::Float3:
			{
				GB::DrawFloat3(reflectedMemberData.name, memberPtr);
				break;
			}
			case reflect::FieldType::Float4:
			{
				GB::DrawFloat4(reflectedMemberData.name, memberPtr);
				break;
			}
			case reflect::FieldType::Int:
			{
				GB::DrawInt(reflectedMemberData.name, memberPtr);
				break;
			}
			case reflect::FieldType::Int2:
			{
				GB::DrawInt2(reflectedMemberData.name, memberPtr);
				break;
			}
			case reflect::FieldType::Int3:
			{
				GB::DrawInt3(reflectedMemberData.name, memberPtr);
				break;
			}
			case reflect::FieldType::Int4:
			{
				GB::DrawInt4(reflectedMemberData.name, memberPtr);
				break;
			}
			case reflect::FieldType::Bool:
			{
				GB::DrawBool(reflectedMemberData.name, memberPtr);
				break;
			}
			case reflect::FieldType::String:
			{
				GB::DrawString(reflectedMemberData.name, memberPtr);
				break;
			}
			case reflect::FieldType::Colour:
			{
				GB::DrawColours(reflectedMemberData.name, memberPtr);
				break;
			}
			case reflect::FieldType::Texture:
			{
				GB::DrawTexture(reflectedMemberData.name, memberPtr);
				break;
			}
			case reflect::FieldType::Class:
			{
				GB_PTR(pClass, static_cast<BaseObject*>(memberPtr), "");
				GB::DrawClass(pClass);
				break;
			}
			case reflect::FieldType::ClassPtr:
			{
				GB_PTR(pClass, *(BaseObject**)memberPtr, "");
				GB::DrawClass(pClass);
				break;
			}
			case reflect::FieldType::Vector:
			{
				GB::DrawVector(reflectedMemberData, memberPtr);
				break;
			}
			case reflect::FieldType::UniquePtr:
			{
				GB::DrawUniquePtr(reflectedMemberData.type, memberPtr);
				break;
			}
			case reflect::FieldType::SharedPtr:
			{
				GB::DrawSharedPtr(reflectedMemberData.type, memberPtr);
				break;
			}
			case reflect::FieldType::WeakPtr:
			{
				GB::DrawWeakPtr(reflectedMemberData.type, memberPtr);
				break;
			}
			default:
			{
				GB_CORE_ASSERT(false, "TypeDescriptor not implemented in ThirdParty/GBReflection/GBTypeDescriptors.cpp");
				break;
			}
		}
	}

	void DrawMember(reflect::TypeDescriptor* pTypeDescriptor, void* memberPtr)
	{
		switch (pTypeDescriptor->getFieldType())
		{
			case reflect::FieldType::None:
			{
				GB_CORE_ASSERT(false, "TypeDescriptor not implemented in ThirdParty/GBReflection/GBTypeDescriptors.cpp");
				break;
			}
			case reflect::FieldType::Float:
			{
				GB::DrawFloat(pTypeDescriptor->name, memberPtr);
				break;
			}
			case reflect::FieldType::Float2:
			{
				GB::DrawFloat2(pTypeDescriptor->name, memberPtr);
				break;
			}
			case reflect::FieldType::Float3:
			{
				GB::DrawFloat3(pTypeDescriptor->name, memberPtr);
				break;
			}
			case reflect::FieldType::Float4:
			{
				GB::DrawFloat4(pTypeDescriptor->name, memberPtr);
				break;
			}
			case reflect::FieldType::Int:
			{
				GB::DrawInt(pTypeDescriptor->name, memberPtr);
				break;
			}
			case reflect::FieldType::Int2:
			{
				GB::DrawInt2(pTypeDescriptor->name, memberPtr);
				break;
			}
			case reflect::FieldType::Int3:
			{
				GB::DrawInt3(pTypeDescriptor->name, memberPtr);
				break;
			}
			case reflect::FieldType::Int4:
			{
				GB::DrawInt4(pTypeDescriptor->name, memberPtr);
				break;
			}
			case reflect::FieldType::Bool:
			{
				GB::DrawBool(pTypeDescriptor->name, memberPtr);
				break;
			}
			case reflect::FieldType::String:
			{
				GB::DrawString(pTypeDescriptor->name, memberPtr);
				break;
			}
			case reflect::FieldType::Colour:
			{
				GB::DrawColours(pTypeDescriptor->name, memberPtr);
				break;
			}
			case reflect::FieldType::Texture:
			{
				GB::DrawTexture(pTypeDescriptor->name, memberPtr);
				break;
			}
			case reflect::FieldType::Class:
			{
				GB_PTR(pClass, static_cast<BaseObject*>(memberPtr), "");
				GB::DrawClass(pClass);
				break;
			}
			case reflect::FieldType::ClassPtr:
			{
				GB_PTR(pClass, *(BaseObject**)memberPtr, "");
				GB::DrawClass(pClass);
				break;
			}
			case reflect::FieldType::Vector:
			{
				// TODO: Implement void DrawVector(reflect::TypeDescriptor* pTypeDescriptor, void* memberPtr);
				GB_CORE_ASSERT(false, "Drawing std::vector based on TypeDescriptor alone is not supported");
				break;
			}
			case reflect::FieldType::UniquePtr:
			{
				GB::DrawUniquePtr(pTypeDescriptor, memberPtr);
				break;
			}
			case reflect::FieldType::SharedPtr:
			{
				GB::DrawSharedPtr(pTypeDescriptor, memberPtr);
				break;
			}
			case reflect::FieldType::WeakPtr:
			{
				GB::DrawWeakPtr(pTypeDescriptor, memberPtr);
				break;
			}
			default:
			{
				GB_CORE_ASSERT(false, "TypeDescriptor not implemented in ThirdParty/GBReflection/GBTypeDescriptors.cpp");
				break;
			}
		}
	}

	// ===================================
	// FLOATS
	void DrawXFloatValue(float& value)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, kEditorVariableXButtonColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kEditorVariableXButtonHoveredColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, kEditorVariableXButtonActiveColour);
		ImGui::PushFont(GetEditorVariableButtonImGuiFont());
		if (ImGui::Button("X", GetEditorVariableButtonSize()))
		{
			value = kEditorVariableFloatResetValue;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##X", &value, 0.1f);
	}

	void DrawYFloatValue(float& value)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, kEditorVariableYButtonColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kEditorVariableYButtonHoveredColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, kEditorVariableYButtonActiveColour);
		ImGui::PushFont(GetEditorVariableButtonImGuiFont());
		if (ImGui::Button("Y", GetEditorVariableButtonSize()))
		{
			value = kEditorVariableFloatResetValue;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &value, 0.1f);
	}

	void DrawZFloatValue(float& value)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, kEditorVariableZButtonColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kEditorVariableZButtonHoveredColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, kEditorVariableZButtonActiveColour);
		ImGui::PushFont(GetEditorVariableButtonImGuiFont());
		if (ImGui::Button("Z", GetEditorVariableButtonSize()))
		{
			value = kEditorVariableFloatResetValue;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &value, 0.1f);
	}

	void DrawWFloatValue(float& value)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, kEditorVariableWButtonColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kEditorVariableWButtonHoveredColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, kEditorVariableWButtonActiveColour);
		ImGui::PushFont(GetEditorVariableButtonImGuiFont());
		if (ImGui::Button("W", GetEditorVariableButtonSize()))
		{
			value = kEditorVariableFloatResetValue;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##W", &value, 0.1f);
	}

	void DrawFloat(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 100.0f*/)
	{
		BeginEditorVariable(name, spacingAfterVariableName);
		{
			float floatValue = *((float*)memberPtr);
			std::string uniqueLabel = "##";
			uniqueLabel.append(name);
			if (ImGui::DragFloat(uniqueLabel.c_str(), &floatValue))
			{
				*((float*)memberPtr) = floatValue;
			}
		}
		EndEditorVariable();
	}

	void DrawFloat2(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 100.0f*/)
	{
		float2 float2Value = *((float2*)memberPtr);

		BeginEditorVariable(name, spacingAfterVariableName);
		{
			ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			// X
			DrawXFloatValue(float2Value.x);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			// Y
			DrawYFloatValue(float2Value.y);
			ImGui::PopItemWidth();
			ImGui::PopStyleVar();
		}
		EndEditorVariable();

		*((float2*)memberPtr) = float2Value;
	}

	void DrawFloat3(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 100.0f*/)
	{
		float3 float3Value = *((float3*)memberPtr);

		BeginEditorVariable(name, spacingAfterVariableName);
		{
			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			// X
			DrawXFloatValue(float3Value.x);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			// Y
			DrawYFloatValue(float3Value.y);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			// Z
			DrawZFloatValue(float3Value.z);
			ImGui::PopItemWidth();
			ImGui::PopStyleVar();
		}
		EndEditorVariable();

		*((float3*)memberPtr) = float3Value;
	}

	void DrawFloat4(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 100.0f*/)
	{
		float4 float4Value = *((float4*)memberPtr);

		BeginEditorVariable(name, spacingAfterVariableName);
		{
			ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			// X
			DrawXFloatValue(float4Value.x);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			// Y
			DrawYFloatValue(float4Value.y);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			// Z
			DrawZFloatValue(float4Value.z);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			// W
			DrawWFloatValue(float4Value.w);
			ImGui::PopItemWidth();
			ImGui::PopStyleVar();
		}
		EndEditorVariable();

		*((float4*)memberPtr) = float4Value;
	}

	// ===================================
	// INTS
	void DrawXIntValue(int& value)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, kEditorVariableXButtonColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kEditorVariableXButtonHoveredColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, kEditorVariableXButtonActiveColour);
		ImGui::PushFont(GetEditorVariableButtonImGuiFont());
		if (ImGui::Button("X", GetEditorVariableButtonSize()))
		{
			value = kEditorVariableIntResetValue;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragInt("##X", &value);
	}

	void DrawYIntValue(int& value)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, kEditorVariableYButtonColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kEditorVariableYButtonHoveredColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, kEditorVariableYButtonActiveColour);
		ImGui::PushFont(GetEditorVariableButtonImGuiFont());
		if (ImGui::Button("Y", GetEditorVariableButtonSize()))
		{
			value = kEditorVariableIntResetValue;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragInt("##Y", &value);
	}

	void DrawZIntValue(int& value)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, kEditorVariableZButtonColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kEditorVariableZButtonHoveredColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, kEditorVariableZButtonActiveColour);
		ImGui::PushFont(GetEditorVariableButtonImGuiFont());
		if (ImGui::Button("Z", GetEditorVariableButtonSize()))
		{
			value = kEditorVariableIntResetValue;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragInt("##Z", &value);
	}

	void DrawWIntValue(int& value)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, kEditorVariableWButtonColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kEditorVariableWButtonHoveredColour);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, kEditorVariableWButtonActiveColour);
		ImGui::PushFont(GetEditorVariableButtonImGuiFont());
		if (ImGui::Button("W", GetEditorVariableButtonSize()))
		{
			value = kEditorVariableIntResetValue;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragInt("##W", &value);
	}

	void DrawInt(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 100.0f*/)
	{
		BeginEditorVariable(name, spacingAfterVariableName);
		{
			int intValue = *((int*)memberPtr);
			std::string uniqueLabel = "##";
			uniqueLabel.append(name);
			if (ImGui::DragInt(uniqueLabel.c_str(), &intValue))
			{
				*((int*)memberPtr) = intValue;
			}
		}
		EndEditorVariable();
	}

	void DrawInt2(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 100.0f*/)
	{
		int2 int2Value = *((int2*)memberPtr);

		BeginEditorVariable(name, spacingAfterVariableName);
		{
			ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			// X
			DrawXIntValue(int2Value.x);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			// Y
			DrawYIntValue(int2Value.y);
			ImGui::PopItemWidth();
			ImGui::PopStyleVar();
		}
		EndEditorVariable();

		*((int2*)memberPtr) = int2Value;
	}

	void DrawInt3(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 100.0f*/)
	{
		int3 int3Value = *((int3*)memberPtr);

		BeginEditorVariable(name, spacingAfterVariableName);
		{
			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			// X
			DrawXIntValue(int3Value.x);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			// Y
			DrawYIntValue(int3Value.y);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			// Z
			DrawZIntValue(int3Value.z);
			ImGui::PopItemWidth();
			ImGui::PopStyleVar();
		}
		EndEditorVariable();

		*((int3*)memberPtr) = int3Value;
	}

	void DrawInt4(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 100.0f*/)
	{
		int4 int4Value = *((int4*)memberPtr);

		BeginEditorVariable(name, spacingAfterVariableName);
		{
			ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			// X
			DrawXIntValue(int4Value.x);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			// Y
			DrawYIntValue(int4Value.y);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			// Z
			DrawZIntValue(int4Value.z);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			// W
			DrawWIntValue(int4Value.w);
			ImGui::PopItemWidth();
			ImGui::PopStyleVar();
		}
		EndEditorVariable();

		*((int4*)memberPtr) = int4Value;
	}

	// ===================================
	// BOOLS
	void DrawBool(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 100.0f*/)
	{
		BeginEditorVariable(name, spacingAfterVariableName);
		{
			bool boolValue = *((bool*)memberPtr);
			std::string uniqueLabel = "##";
			uniqueLabel.append(name);
			if (ImGui::Checkbox(uniqueLabel.c_str(), &boolValue))
			{
				*((bool*)memberPtr) = boolValue;
			}
		}
		EndEditorVariable();
	}
	
	// ===================================
	// STRINGS
	void DrawString(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 100.0f*/)
	{
		BeginEditorVariable(name, spacingAfterVariableName);
		{
			std::string stringValue = *((std::string*)memberPtr);
			std::string uniqueLabel = "##";
			uniqueLabel.append(name);
			ImGui::InputText(uniqueLabel.c_str(), &stringValue);
			*((std::string*)memberPtr) = stringValue;
		}
		EndEditorVariable();
	}

	// ===================================
	// COLOURS
	void DrawColours(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 100.0f*/)
	{
		BeginEditorVariable(name, spacingAfterVariableName);
		{
			Colour colourValue = *((Colour*)memberPtr);
			// TODO: See if the data() function works as expected
			// If not, then manually setup a float array with the float4 values from colour
			// Then pass it into ColorEdit4 and then loop over them and reassign them to colourValue
			ImGui::ColorEdit4("Colour", colourValue.data());
			*((Colour*)memberPtr) = colourValue;
		}
		EndEditorVariable();
	}
	
	// ===================================
	// TEXTURES
	void DrawTexture(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 100.0f*/)
	{
		BeginEditorVariable(name, spacingAfterVariableName);
		{
			GB_PTR(pTexture2D, static_cast<Texture2D*>(memberPtr), "");
			GB_PTR(pSFMLTexture, static_cast<SFMLTexture*>(pTexture2D), "");

			ImGui::Image(pSFMLTexture->GetSFMLSprite(), kEditorVariableImageSize);
		}
		EndEditorVariable();
	}

	// ===================================
	// CLASSES
	void DrawClassMembers(BaseObject* pClass)
	{
		const reflect::TypeDescriptor_Struct& componentReflectedData = pClass->GetTypeDescription();
		for (auto& member : componentReflectedData.members)
		{
			GB_CHECK_PTR(member.type, "Reflected member has a nullptr type descriptor, double check variable type");

			void* memberPtr = (void*)((char*)pClass + member.offset);
			const reflect::FieldType fieldType = member.type->getFieldType();

			DrawMember(member, memberPtr);
		}
	}

	void DrawClass(BaseObject* pClass)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		ImVec2 regionContentAvailable = ImGui::GetContentRegionAvail();
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
		float lineHeight = GetEditorVariableLineHeight();
		bool open = ImGui::TreeNodeEx((void*)pClass, treeNodeFlags, "%s", pClass->GetTypeDescription().getFullName().c_str());
		ImGui::PopStyleVar();

		if (open)
		{
			DrawClassMembers(pClass);
			ImGui::TreePop();
		}
	}

	// ===================================
	// VECTORS
	void DrawVectorElement(reflect::TypeDescriptor* pTypeDescriptor, const reflect::FieldType type, const char* name, void* memberPtr, bool& removeElement, const float spacingAfterVariableName/* = 100.0f*/)
	{
		switch (type)
		{
			case reflect::FieldType::None:
			{
				GB_CORE_ASSERT(false, "FieldType not implemented in ThirdParty/GBReflection/GBTypeDescriptors.cpp");
				break;
			}
			case reflect::FieldType::Float:
			{
				GB::DrawFloat(name, memberPtr, spacingAfterVariableName);
				break;
			}
			case reflect::FieldType::Float2:
			{
				GB::DrawFloat2(name, memberPtr, spacingAfterVariableName);
				break;
			}
			case reflect::FieldType::Float3:
			{
				GB::DrawFloat3(name, memberPtr, spacingAfterVariableName);
				break;
			}
			case reflect::FieldType::Float4:
			{
				GB::DrawFloat4(name, memberPtr, spacingAfterVariableName);
				break;
			}
			case reflect::FieldType::Int:
			{
				GB::DrawInt(name, memberPtr, spacingAfterVariableName);
				break;
			}
			case reflect::FieldType::Int2:
			{
				GB::DrawInt2(name, memberPtr, spacingAfterVariableName);
				break;
			}
			case reflect::FieldType::Int3:
			{
				GB::DrawInt3(name, memberPtr, spacingAfterVariableName);
				break;
			}
			case reflect::FieldType::Int4:
			{
				GB::DrawInt4(name, memberPtr, spacingAfterVariableName);
				break;
			}
			case reflect::FieldType::Bool:
			{
				GB::DrawBool(name, memberPtr, spacingAfterVariableName);
				break;
			}
			case reflect::FieldType::String:
			{
				GB::DrawString(name, memberPtr, spacingAfterVariableName);
				break;
			}
			case reflect::FieldType::Colour:
			{
				GB::DrawColours(name, memberPtr, spacingAfterVariableName);
				break;
			}
			case reflect::FieldType::Texture:
			{
				GB::DrawTexture(name, memberPtr, spacingAfterVariableName);
				break;
			}
			case reflect::FieldType::Class:
			{
				GB_PTR(pClass, static_cast<BaseObject*>(memberPtr), "");
				GB::DrawClass(pClass);
				break;
			}
			case reflect::FieldType::ClassPtr:
			{
				GB_PTR(pClass, *(BaseObject**)memberPtr, "");
				GB::DrawClass(pClass);
				break;
			}
			case reflect::FieldType::Vector:
			{
				GB_CORE_ASSERT(false, "vector of vectors is not allowed!");
				break;
			}
			case reflect::FieldType::UniquePtr:
			{
				GB::DrawUniquePtr(pTypeDescriptor, memberPtr);
				break;
			}
			case reflect::FieldType::SharedPtr:
			{
				GB::DrawSharedPtr(pTypeDescriptor, memberPtr);
				break;
			}
			case reflect::FieldType::WeakPtr:
			{
				GB::DrawWeakPtr(pTypeDescriptor, memberPtr);
				break;
			}
			default:
			{
				GB_CORE_ASSERT(false, "FieldType not implemented in ThirdParty/GBReflection/GBTypeDescriptors.cpp");
				break;
			}
		}

		ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 60.0f);

		// Remove element at specific index
		GB::BeginRemoveElementButtonStyle();
		{
			std::string removeElementButtonLabel = "-##RemoveElementAtIndexButton";
			removeElementButtonLabel.append(name);
			const float lineHeight = GetEditorVariableLineHeight();
			if (ImGui::Button(removeElementButtonLabel.c_str(), ImVec2{ lineHeight, lineHeight }))
			{
				removeElement = true;
			}
		}
		GB::EndRemoveElementButtonStyle();
	}
	
	void DrawVector(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr)
	{
		reflect::TypeDescriptor_StdVector* vectorType = (reflect::TypeDescriptor_StdVector*)reflectedMemberData.type;
		reflect::TypeDescriptor* vectorItemTypeDescriptor = vectorType->itemType;
		const reflect::FieldType vectorItemFieldType = vectorType->itemType->getFieldType();

		// Not const because there are Add Element and Remove Element buttons here which can alter the size of the vector.
		size_t vectorSize = vectorType->getSize(memberPtr);

		std::string vectorName = "";
		vectorName.append(reflectedMemberData.name);
		vectorName.append(" " + std::to_string(vectorSize) + " Elements");

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
		float lineHeight = GetEditorVariableLineHeight();
		const bool opened = ImGui::TreeNodeEx(memberPtr, flags, "%s", vectorName.c_str());
		ImGui::PopStyleVar();

		constexpr float kVectorButtonStartingPosition = 60.0f;
		constexpr float kVectorElementButtonOffset = 30.0f;

		ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - (kVectorButtonStartingPosition + (kVectorElementButtonOffset * 2.0f)));

		// Add new elements
		GB::BeginAddElementButtonStyle();
		{
			std::string addElementButtonLabel = "+##AddElementButton";
			addElementButtonLabel.append(vectorName);
			if (ImGui::Button(addElementButtonLabel.c_str(), ImVec2{ lineHeight, lineHeight }))
			{
				// Adds a new empty element to the vector.
				vectorType->addNewItem(memberPtr);
				// Refreshing the size since the vector has been altered here, should be one new element
				vectorSize = vectorType->getSize(memberPtr);
			}
		}
		GB::EndAddElementButtonStyle();

		ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - (kVectorButtonStartingPosition + kVectorElementButtonOffset));

		// Remove last element
		GB::BeginRemoveElementButtonStyle();
		{
			std::string removeElementButtonLabel = "-##RemoveElementButton";
			removeElementButtonLabel.append(vectorName);
			if (ImGui::Button(removeElementButtonLabel.c_str(), ImVec2{ lineHeight, lineHeight }))
			{
				if (vectorSize > 0)
				{
					// Always remove the last element with this button
					vectorType->removeItem(memberPtr, vectorSize - 1);
					vectorSize = vectorType->getSize(memberPtr);
				}
			}
		}
		GB::EndRemoveElementButtonStyle();

		ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - kVectorButtonStartingPosition);

		// Clear all elements
		GB::BeginRemoveElementButtonStyle();
		{
			std::string clearAllElementsButtonLabel = "Clear##ClearAllElementsButton";
			clearAllElementsButtonLabel.append(vectorName);
			if (ImGui::Button(clearAllElementsButtonLabel.c_str(), ImVec2{ 60.0f, lineHeight }))
			{
				if (vectorSize > 0)
				{
					// Always remove the last element with this button
					vectorType->clearAllItems(memberPtr);
					vectorSize = vectorType->getSize(memberPtr);
				}
			}
		}
		GB::EndRemoveElementButtonStyle();

		if (opened)
		{
			size_t removeIndex = 0;
			bool hasSetRemoveIndexThisFrame = false;
			bool shouldRemoveIndex = false;

			for (size_t iV = 0; iV < vectorSize; ++iV)
			{
				std::string elementName = std::to_string(iV);
				void* elementPtr = const_cast<void*>(vectorType->getItem(memberPtr, iV));
				DrawVectorElement(vectorItemTypeDescriptor, vectorItemFieldType, elementName.c_str(), elementPtr, shouldRemoveIndex, kEditorVectorSpacingAfterIndex);

				if (!hasSetRemoveIndexThisFrame)
				{
					if (shouldRemoveIndex)
					{
						removeIndex = iV;
						hasSetRemoveIndexThisFrame = true;
					}
				}
			}

			// If the user pressed on the "-" button next to a specific element in the vector, remove it now
			if (shouldRemoveIndex)
			{
				vectorType->removeItem(memberPtr, removeIndex);
			}

			ImGui::TreePop();
		}
	}

	// ===================================
	// SMART PTRS
	void DrawUniquePtr(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr)
	{
		GB_PTR(pUniquePtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdUniquePtr*>(reflectedMemberData.type), "");
		void* pUniquePtrValue = pUniquePtrTypeDescriptor->getTarget(memberPtr);
		DrawMember(reflectedMemberData, pUniquePtrValue);
	}

	void DrawSharedPtr(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr)
	{
		GB_PTR(pSharedPtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdSharedPtr*>(reflectedMemberData.type), "");
		void* pSharedPtrValue = pSharedPtrTypeDescriptor->getTarget(memberPtr);
		DrawMember(reflectedMemberData, pSharedPtrValue);
	}

	void DrawWeakPtr(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr)
	{
		GB_PTR(pWeakPtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdWeakPtr*>(reflectedMemberData.type), "");
		void* pWeakPtrValue = pWeakPtrTypeDescriptor->getTarget(memberPtr);
		DrawMember(reflectedMemberData, pWeakPtrValue);
	}

	void DrawUniquePtr(reflect::TypeDescriptor* pTypeDescriptor, void* memberPtr)
	{
		GB_PTR(pUniquePtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdUniquePtr*>(pTypeDescriptor), "");
		GB_PTR(pUniquePtrValueTypeDescriptor, pUniquePtrTypeDescriptor->targetType, "");
		void* pUniquePtrValue = pUniquePtrTypeDescriptor->getTarget(memberPtr);
		DrawMember(pUniquePtrValueTypeDescriptor, pUniquePtrValue);
	}

	void DrawSharedPtr(reflect::TypeDescriptor* pTypeDescriptor, void* memberPtr)
	{
		GB_PTR(pSharedPtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdSharedPtr*>(pTypeDescriptor), "");
		GB_PTR(pSharedPtrValueTypeDescriptor, pSharedPtrTypeDescriptor->targetType, "");
		void* pSharedPtrValue = pSharedPtrTypeDescriptor->getTarget(memberPtr);
		DrawMember(pSharedPtrValueTypeDescriptor, pSharedPtrValue);
	}

	void DrawWeakPtr(reflect::TypeDescriptor* pTypeDescriptor, void* memberPtr)
	{
		GB_PTR(pWeakPtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdWeakPtr*>(pTypeDescriptor), "");
		GB_PTR(pWeakPtrValueTypeDescriptor, pWeakPtrTypeDescriptor->targetType, "");
		void* pWeakPtrValue = pWeakPtrTypeDescriptor->getTarget(memberPtr);
		DrawMember(pWeakPtrValueTypeDescriptor, pWeakPtrValue);
	}
}