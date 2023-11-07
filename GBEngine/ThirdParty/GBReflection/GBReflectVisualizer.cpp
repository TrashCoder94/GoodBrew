#include "GBReflectVisualizer.h"

#include <imgui_internal.h>
#include <imgui-SFML.h>
#include <imgui_stdlib.h>
#include <linalg.h>
#include <string>

#include "GBEngine/Objects/BaseObject.h"
#include "GBEngine/Renderer/Texture.h"

// TODO: Think how to abstract/display this in editor?
#include "GBEngine/Renderer/Platforms/SFML/SFMLTexture.h"

using namespace linalg::aliases;

namespace GB
{	
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

	// ===================================
	// ImGui helpers
	ImFont* GetEditorVariableButtonImGuiFont()
	{
		return ImGui::GetIO().Fonts->Fonts[0];
	}

	ImVec2 GetEditorVariableButtonSize()
	{
		const float kEditorVariableLineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		const ImVec2& kEditorVariableButtonSize = { kEditorVariableLineHeight + 3.0f, kEditorVariableLineHeight };
		return kEditorVariableButtonSize;
	}
	
	// =================================== 
	// SHARED - Used for all variable displays in the editor
	void BeginEditorVariableTable(const char* tableName)
	{
		ImGui::BeginTable("floatTable", 2);

		// First column where variable name will be.
		ImGui::TableSetupColumn("variableNameColumn", ImGuiTableColumnFlags_WidthFixed, kEditorVariableColumnWidth);

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

	void BeginEditorVariable(const char* name)
	{
		ImGui::PushID(name);
		BeginEditorVariableTable(std::string(name).append("table").c_str());
		DrawMemberName(name);
		ImGui::TableSetColumnIndex(1);
	}

	void EndEditorVariable()
	{
		EndEditorVariableTable();
		ImGui::PopID();
	}

	void DrawMember(const reflect::FieldType type, const char* name, void* memberPtr)
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
				GB::DrawFloat(name, memberPtr);
				break;
			}
			case reflect::FieldType::Float2:
			{
				GB::DrawFloat2(name, memberPtr);
				break;
			}
			case reflect::FieldType::Float3:
			{
				GB::DrawFloat3(name, memberPtr);
				break;
			}
			case reflect::FieldType::Float4:
			{
				GB::DrawFloat4(name, memberPtr);
				break;
			}
			case reflect::FieldType::Int:
			{
				GB::DrawInt(name, memberPtr);
				break;
			}
			case reflect::FieldType::Int2:
			{
				GB::DrawInt2(name, memberPtr);
				break;
			}
			case reflect::FieldType::Int3:
			{
				GB::DrawInt3(name, memberPtr);
				break;
			}
			case reflect::FieldType::Int4:
			{
				GB::DrawInt4(name, memberPtr);
				break;
			}
			case reflect::FieldType::Bool:
			{
				GB::DrawBool(name, memberPtr);
				break;
			}
			case reflect::FieldType::String:
			{
				GB::DrawString(name, memberPtr);
				break;
			}
			case reflect::FieldType::Colour:
			{
				GB::DrawColours(name, memberPtr);
				break;
			}
			case reflect::FieldType::Texture:
			{
				GB::DrawTexture(name, memberPtr);
				break;
			}
			case reflect::FieldType::Class:
			{
				GB_PTR(pClass, static_cast<BaseObject*>(memberPtr), "");
				GB::DrawClass(pClass);
				break;
			}
			case reflect::FieldType::Vector:
			{
				GB::DrawVector(name, memberPtr);
				break;
			}
			default:
			{
				GB_CORE_ASSERT(false, "FieldType not implemented in ThirdParty/GBReflection/GBTypeDescriptors.cpp");
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

	void DrawFloat(const char* name, void* memberPtr)
	{
		BeginEditorVariable(name);
		{
			float floatValue = *((float*)memberPtr);
			if (ImGui::DragFloat(name, &floatValue))
			{
				*((float*)memberPtr) = floatValue;
			}
		}
		EndEditorVariable();
	}

	void DrawFloat2(const char* name, void* memberPtr)
	{
		float2 float2Value = *((float2*)memberPtr);

		BeginEditorVariable(name);
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

	void DrawFloat3(const char* name, void* memberPtr)
	{
		float3 float3Value = *((float3*)memberPtr);

		BeginEditorVariable(name);
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

	void DrawFloat4(const char* name, void* memberPtr)
	{
		float4 float4Value = *((float4*)memberPtr);

		BeginEditorVariable(name);
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

	void DrawInt(const char* name, void* memberPtr)
	{
		BeginEditorVariable(name);
		{
			int intValue = *((int*)memberPtr);
			if (ImGui::DragInt(name, &intValue))
			{
				*((int*)memberPtr) = intValue;
			}
		}
		EndEditorVariable();
	}

	void DrawInt2(const char* name, void* memberPtr)
	{
		int2 int2Value = *((int2*)memberPtr);

		BeginEditorVariable(name);
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

	void DrawInt3(const char* name, void* memberPtr)
	{
		int3 int3Value = *((int3*)memberPtr);

		BeginEditorVariable(name);
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

	void DrawInt4(const char* name, void* memberPtr)
	{
		int4 int4Value = *((int4*)memberPtr);

		BeginEditorVariable(name);
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
	void DrawBool(const char* name, void* memberPtr)
	{
		BeginEditorVariable(name);
		{
			bool boolValue = *((bool*)memberPtr);
			if (ImGui::Checkbox(name, &boolValue))
			{
				*((bool*)memberPtr) = boolValue;
			}
		}
		EndEditorVariable();
	}
	
	// ===================================
	// STRINGS
	void DrawString(const char* name, void* memberPtr)
	{
		BeginEditorVariable(name);
		{
			std::string stringValue = *((std::string*)memberPtr);
			ImGui::InputText("Name", &stringValue);
			*((std::string*)memberPtr) = stringValue;
		}
		EndEditorVariable();
	}

	// ===================================
	// COLOURS
	void DrawColours(const char* name, void* memberPtr)
	{

	}
	
	// ===================================
	// TEXTURES
	void DrawTexture(const char* name, void* memberPtr)
	{
		BeginEditorVariable(name);
		{
			SharedPtr<Texture2D>* pSharedTextureValue = ((SharedPtr<Texture2D>*)memberPtr);
			GB_PTR(pSFMLTexture, static_cast<SFMLTexture*>(pSharedTextureValue->get()), "");

			ImGui::Image(pSFMLTexture->GetSFMLSprite(), kEditorVariableImageSize);

			// TODO: Set pSharedTextureValue once the user has selected a sprite?
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

			DrawMember(fieldType, member.name, memberPtr);
		}
	}

	void DrawClass(BaseObject* pClass)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		ImVec2 regionContentAvailable = ImGui::GetContentRegionAvail();
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
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
	void DrawVector(const char* name, void* memberPtr)
	{

	}
}