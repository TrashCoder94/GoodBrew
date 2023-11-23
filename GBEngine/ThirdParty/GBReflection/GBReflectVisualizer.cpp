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

	static constexpr int kEditorVariableIntResetValue					= 0;
	static constexpr float kEditorVariableFloatResetValue				= 0.0f;
	static constexpr float kEditorNumberVariableWidth					= 75.0f;
	static constexpr float kEditorClassSpacingMultiplier				= 0.15f;
	static constexpr float kEditorClassSpacingVectorElementMultiplier	= 0.3f;

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
	void DrawMemberName(const char* name, const float spaceAfterVariableName/* = 125.0f*/)
	{
		ImGui::TextUnformatted(name);

		// Tooltip to just display the name of the variable.
		// Could update reflection system to include comments as part of GBVARIABLE.
		// E.g. GBVARIABLE(Edit, Tooltip = "This is a comment to use as a tooltip").
		if (ImGui::BeginItemTooltip())
		{
			ImGui::TextUnformatted(name);
			ImGui::EndTooltip();
		}

		ImGui::SameLine(spaceAfterVariableName);
	}

	void BeginEditorVariable(const char* name, const float spaceAfterVariableName/* = 125.0f*/)
	{
		ImGui::PushID(name);
		DrawMemberName(name, spaceAfterVariableName);
	}

	void EndEditorVariable()
	{
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

	void DrawMember(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const float spacingAfterMemberVariables/* = 125.0f*/)
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
				GB::DrawFloat(name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::Float2:
			{
				GB::DrawFloat2(name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::Float3:
			{
				GB::DrawFloat3(name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::Float4:
			{
				GB::DrawFloat4(name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::Int:
			{
				GB::DrawInt(name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::Int2:
			{
				GB::DrawInt2(name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::Int3:
			{
				GB::DrawInt3(name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::Int4:
			{
				GB::DrawInt4(name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::Bool:
			{
				GB::DrawBool(name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::String:
			{
				GB::DrawString(name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::Colour:
			{
				GB::DrawColours(name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::Texture:
			{
				GB::DrawTexture(name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::Class:
			{
				const std::string& typeDescriptorName = pTypeDescriptor->name;

				// Bool workaround for bools within std::vector, just using a custom struct instead as a bool wrapper
				if (typeDescriptorName == "GBBool")
				{
					GB_PTR(pGBBoolTypeDescriptor, static_cast<reflect::TypeDescriptor_Struct*>(pTypeDescriptor), "");
					GB_PTR(pGBBoolStruct, static_cast<GBBool*>(memberPtr), "");
					auto& reflectedBoolMember = pGBBoolTypeDescriptor->members[0];
					void* pBoolMemberPtr = (void*)((char*)pGBBoolStruct + reflectedBoolMember.offset);

					// Just want to draw the bool directly since this "class" is just a wrapper.
					GB::DrawBool(typeDescriptorName.c_str(), pBoolMemberPtr, spacingAfterMemberVariables);
				}
				else
				{
					GB_PTR(pClass, static_cast<BaseObject*>(memberPtr), "");
					GB::DrawClass(pClass, spacingAfterMemberVariables + (spacingAfterMemberVariables * kEditorClassSpacingMultiplier));
				}
				break;
			}
			case reflect::FieldType::ClassPtr:
			{
				GB_PTR(pClass, *(BaseObject**)memberPtr, "");
				GB::DrawClass(pClass, spacingAfterMemberVariables + (spacingAfterMemberVariables * kEditorClassSpacingMultiplier));
				break;
			}
			case reflect::FieldType::Vector:
			{
				GB::DrawVector(pTypeDescriptor, name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::UniquePtr:
			{
				GB::DrawUniquePtr(pTypeDescriptor, name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::SharedPtr:
			{
				GB::DrawSharedPtr(pTypeDescriptor, name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			case reflect::FieldType::WeakPtr:
			{
				GB::DrawWeakPtr(pTypeDescriptor, name, memberPtr, spacingAfterMemberVariables);
				break;
			}
			default:
			{
				GB_CORE_ASSERT(false, "TypeDescriptor not implemented in ThirdParty/GBReflection/GBTypeDescriptors.cpp");
				break;
			}
		}
	}

	void DrawMember(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr, const float spacingAfterMemberVariables/* = 125.0f*/)
	{
		DrawMember(reflectedMemberData.type, reflectedMemberData.name, memberPtr, spacingAfterMemberVariables);
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
		ImGui::PushItemWidth(kEditorNumberVariableWidth);
		ImGui::DragFloat("##X", &value, 0.1f);
		ImGui::PopItemWidth();
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
		ImGui::PushItemWidth(kEditorNumberVariableWidth);
		ImGui::DragFloat("##Y", &value, 0.1f);
		ImGui::PopItemWidth();
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
		ImGui::PushItemWidth(kEditorNumberVariableWidth);
		ImGui::DragFloat("##Z", &value, 0.1f);
		ImGui::PopItemWidth();
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
		ImGui::PushItemWidth(kEditorNumberVariableWidth);
		ImGui::DragFloat("##W", &value, 0.1f);
		ImGui::PopItemWidth();
	}

	void DrawFloat(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 125.0f*/)
	{
		BeginEditorVariable(name, spacingAfterVariableName);
		{
			float floatValue = *((float*)memberPtr);
			std::string uniqueLabel = "##";
			uniqueLabel.append(name);
			ImGui::PushItemWidth(kEditorNumberVariableWidth);
			if (ImGui::DragFloat(uniqueLabel.c_str(), &floatValue))
			{
				*((float*)memberPtr) = floatValue;
			}
			ImGui::PopItemWidth();
		}
		EndEditorVariable();
	}

	void DrawFloat2(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 125.0f*/)
	{
		float2 float2Value = *((float2*)memberPtr);

		BeginEditorVariable(name, spacingAfterVariableName);
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 5, 5 });

			// X
			DrawXFloatValue(float2Value.x);
			ImGui::SameLine();

			// Y
			DrawYFloatValue(float2Value.y);
			ImGui::PopStyleVar();
		}
		EndEditorVariable();

		*((float2*)memberPtr) = float2Value;
	}

	void DrawFloat3(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 125.0f*/)
	{
		float3 float3Value = *((float3*)memberPtr);

		BeginEditorVariable(name, spacingAfterVariableName);
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 5, 5 });

			// X
			DrawXFloatValue(float3Value.x);
			ImGui::SameLine();

			// Y
			DrawYFloatValue(float3Value.y);
			ImGui::SameLine();

			// Z
			DrawZFloatValue(float3Value.z);
			ImGui::PopStyleVar();
		}
		EndEditorVariable();

		*((float3*)memberPtr) = float3Value;
	}

	void DrawFloat4(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 125.0f*/)
	{
		float4 float4Value = *((float4*)memberPtr);

		BeginEditorVariable(name, spacingAfterVariableName);
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 5, 5 });

			// X
			DrawXFloatValue(float4Value.x);
			ImGui::SameLine();

			// Y
			DrawYFloatValue(float4Value.y);
			ImGui::SameLine();

			// Z
			DrawZFloatValue(float4Value.z);
			ImGui::SameLine();

			// W
			DrawWFloatValue(float4Value.w);
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
		ImGui::PushItemWidth(kEditorNumberVariableWidth);
		ImGui::DragInt("##X", &value);
		ImGui::PopItemWidth();
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
		ImGui::PushItemWidth(kEditorNumberVariableWidth);
		ImGui::DragInt("##Y", &value);
		ImGui::PopItemWidth();
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
		ImGui::PushItemWidth(kEditorNumberVariableWidth);
		ImGui::DragInt("##Z", &value);
		ImGui::PopItemWidth();
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
		ImGui::PushItemWidth(kEditorNumberVariableWidth);
		ImGui::DragInt("##W", &value);
		ImGui::PopItemWidth();
	}

	void DrawInt(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 125.0f*/)
	{
		BeginEditorVariable(name, spacingAfterVariableName);
		{
			int intValue = *((int*)memberPtr);
			std::string uniqueLabel = "##";
			uniqueLabel.append(name);
			ImGui::PushItemWidth(kEditorNumberVariableWidth);
			if (ImGui::DragInt(uniqueLabel.c_str(), &intValue))
			{
				*((int*)memberPtr) = intValue;
			}
			ImGui::PopItemWidth();
		}
		EndEditorVariable();
	}

	void DrawInt2(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 125.0f*/)
	{
		int2 int2Value = *((int2*)memberPtr);

		BeginEditorVariable(name, spacingAfterVariableName);
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 5, 5 });

			// X
			DrawXIntValue(int2Value.x);
			ImGui::SameLine();

			// Y
			DrawYIntValue(int2Value.y);
			ImGui::PopStyleVar();
		}
		EndEditorVariable();

		*((int2*)memberPtr) = int2Value;
	}

	void DrawInt3(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 125.0f*/)
	{
		int3 int3Value = *((int3*)memberPtr);

		BeginEditorVariable(name, spacingAfterVariableName);
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 5, 5 });

			// X
			DrawXIntValue(int3Value.x);
			ImGui::SameLine();

			// Y
			DrawYIntValue(int3Value.y);
			ImGui::SameLine();

			// Z
			DrawZIntValue(int3Value.z);
			ImGui::PopStyleVar();
		}
		EndEditorVariable();

		*((int3*)memberPtr) = int3Value;
	}

	void DrawInt4(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 125.0f*/)
	{
		int4 int4Value = *((int4*)memberPtr);

		BeginEditorVariable(name, spacingAfterVariableName);
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 5, 5 });

			// X
			DrawXIntValue(int4Value.x);
			ImGui::SameLine();

			// Y
			DrawYIntValue(int4Value.y);
			ImGui::SameLine();

			// Z
			DrawZIntValue(int4Value.z);
			ImGui::SameLine();

			// W
			DrawWIntValue(int4Value.w);
			ImGui::PopStyleVar();
		}
		EndEditorVariable();

		*((int4*)memberPtr) = int4Value;
	}

	// ===================================
	// BOOLS
	void DrawBool(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 125.0f*/)
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
	void DrawString(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 125.0f*/)
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
	void DrawColours(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 125.0f*/)
	{
		BeginEditorVariable(name, spacingAfterVariableName);
		{
			Colour colourValue = *((Colour*)memberPtr);
			ImGui::ColorEdit4("Colour", colourValue.data());
			*((Colour*)memberPtr) = colourValue;
		}
		EndEditorVariable();
	}
	
	// ===================================
	// TEXTURES
	void DrawTexture(const char* name, void* memberPtr, const float spacingAfterVariableName/* = 125.0f*/)
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
	void DrawClassMembers(BaseObject* pClass, const float spacingAfterMemberVariables/* = 125.0f*/)
	{
		const reflect::TypeDescriptor_Struct& reflectedData = pClass->GetTypeDescription();
		for (auto& member : reflectedData.members)
		{
			GB_CHECK_PTR(member.type, "Reflected member has a nullptr type descriptor, double check variable type");

			void* memberPtr = (void*)((char*)pClass + member.offset);
			const reflect::FieldType fieldType = member.type->getFieldType();

			DrawMember(member, memberPtr, spacingAfterMemberVariables);
		}
	}

	void DrawClass(BaseObject* pClass, const float spacingAfterMemberVariables/* = 125.0f*/)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		ImVec2 regionContentAvailable = ImGui::GetContentRegionAvail();
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
		float lineHeight = GetEditorVariableLineHeight();
		bool open = ImGui::TreeNodeEx((void*)pClass, treeNodeFlags, "%s", pClass->GetTypeDescription().getFullName().c_str());
		ImGui::PopStyleVar();

		if (ImGui::BeginItemTooltip())
		{
			ImGui::TextUnformatted(pClass->GetTypeDescription().getFullName().c_str());
			ImGui::EndTooltip();
		}

		if (open)
		{
			DrawClassMembers(pClass, spacingAfterMemberVariables);
			ImGui::TreePop();
		}
	}

	void DrawClassAsVectorElement(BaseObject* pClass, const size_t index, bool& removeElement, const float spacingAfterMemberVariables)
	{
		std::string uniqueLabelForThisElement = std::to_string(index);
		uniqueLabelForThisElement.append(pClass->GetTypeDescription().name);

		std::string columnLabel = "##columnLabelForClassAsVectorElement";
		columnLabel.append(uniqueLabelForThisElement);

		bool opened = false;
		ImGui::Columns(2, columnLabel.c_str(), false);
		{
			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
			ImVec2 regionContentAvailable = ImGui::GetContentRegionAvail();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GetEditorVariableLineHeight();
			opened = ImGui::TreeNodeEx((void*)pClass, treeNodeFlags, "%d %s ##%s", index, pClass->GetTypeDescription().getFullName().c_str(), uniqueLabelForThisElement.c_str());
			ImGui::PopStyleVar();

			if (ImGui::BeginItemTooltip())
			{
				ImGui::TextUnformatted(pClass->GetTypeDescription().getFullName().c_str());
				ImGui::EndTooltip();
			}

			ImGui::NextColumn();

			// Remove element at specific index
			GB::BeginRemoveElementButtonStyle();
			{
				std::string removeElementButtonLabel = "-##RemoveElementAtIndexForClassVectorElementButton";
				removeElementButtonLabel.append(uniqueLabelForThisElement);
				const float lineHeight = GetEditorVariableLineHeight();
				if (ImGui::Button(removeElementButtonLabel.c_str(), ImVec2{ lineHeight, lineHeight }))
				{
					removeElement = true;
				}
			}
			GB::EndRemoveElementButtonStyle();
		}
		ImGui::Columns(1);

		if (opened)
		{
			DrawClassMembers(pClass, spacingAfterMemberVariables);
			ImGui::TreePop();
		}
	}

	// ===================================
	// VECTORS
	void DrawVectorElement(reflect::TypeDescriptor* pTypeDescriptor, const reflect::FieldType type, const char* name, void* memberPtr, const size_t index, bool& removeElement, const float spacingAfterVariableName/* = 125.0f*/)
	{
		bool shouldDrawRemoveVectorElement = true;
		
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
				const std::string& typeDescriptorName = pTypeDescriptor->name;

				// Bool workaround for bools within std::vector, just using a custom struct instead as a bool wrapper
				if (typeDescriptorName == "GBBool")
				{
					GB_PTR(pGBBoolTypeDescriptor, static_cast<reflect::TypeDescriptor_Struct*>(pTypeDescriptor), "");
					GB_PTR(pGBBoolStruct, static_cast<GBBool*>(memberPtr), "");
					auto& reflectedBoolMember = pGBBoolTypeDescriptor->members[0];
					void* pBoolMemberPtr = (void*)((char*)pGBBoolStruct + reflectedBoolMember.offset);

					// Just want to draw the bool directly since this "class" is just a wrapper.
					GB::DrawBool(name, pBoolMemberPtr, spacingAfterVariableName);
				}
				else
				{
					GB_PTR(pClass, static_cast<BaseObject*>(memberPtr), "");
					GB::DrawClassAsVectorElement(pClass, index, removeElement, spacingAfterVariableName + (spacingAfterVariableName * kEditorClassSpacingVectorElementMultiplier));
					shouldDrawRemoveVectorElement = false;
				}
				break;
			}
			case reflect::FieldType::ClassPtr:
			{
				GB_PTR(pClass, *(BaseObject**)memberPtr, "");
				GB::DrawClassAsVectorElement(pClass, index, removeElement, spacingAfterVariableName + (spacingAfterVariableName * kEditorClassSpacingVectorElementMultiplier));
				shouldDrawRemoveVectorElement = false;
				break;
			}
			case reflect::FieldType::Vector:
			{
				GB_CORE_ASSERT(false, "vector of vectors is not allowed!");
				break;
			}
			case reflect::FieldType::UniquePtr:
			{
				GB_PTR(pUniquePtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdUniquePtr*>(pTypeDescriptor), "");
				GB_PTR(pTargetTypeDescriptor, pUniquePtrTypeDescriptor->targetType, "");
				const float spacing = CalculateSpacingForTargetType(pTargetTypeDescriptor, spacingAfterVariableName);

				GB::DrawUniquePtrAsVectorElement(pTypeDescriptor, name, memberPtr, index, removeElement, spacing);
				shouldDrawRemoveVectorElement = false;
				break;
			}
			case reflect::FieldType::SharedPtr:
			{
				GB_PTR(pSharedPtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdSharedPtr*>(pTypeDescriptor), "");
				GB_PTR(pTargetTypeDescriptor, pSharedPtrTypeDescriptor->targetType, "");
				const float spacing = CalculateSpacingForTargetType(pTargetTypeDescriptor, spacingAfterVariableName);

				GB::DrawSharedPtrAsVectorElement(pTypeDescriptor, name, memberPtr, index, removeElement, spacing);
				shouldDrawRemoveVectorElement = false;
				break;
			}
			case reflect::FieldType::WeakPtr:
			{
				GB_PTR(pWeakPtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdWeakPtr*>(pTypeDescriptor), "");
				GB_PTR(pTargetTypeDescriptor, pWeakPtrTypeDescriptor->targetType, "");
				const float spacing = CalculateSpacingForTargetType(pTargetTypeDescriptor, spacingAfterVariableName);

				GB::DrawWeakPtrAsVectorElement(pTypeDescriptor, name, memberPtr, index, removeElement, spacing);
				shouldDrawRemoveVectorElement = false;
				break;
			}
			default:
			{
				GB_CORE_ASSERT(false, "FieldType not implemented in ThirdParty/GBReflection/GBTypeDescriptors.cpp");
				break;
			}
		}

		if (shouldDrawRemoveVectorElement)
		{
			ImGui::SameLine();

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
	}
	
	void DrawVector(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const float spacingAfterIndex/* = 125.0f*/)
	{
		GB_PTR(vectorType, static_cast<reflect::TypeDescriptor_StdVector*>(pTypeDescriptor), "");
		GB_PTR(vectorItemTypeDescriptor, vectorType->itemType, "");
		const reflect::FieldType vectorItemFieldType = vectorType->itemType->getFieldType();

		// Not const because there are Add Element and Remove Element buttons here which can alter the size of the vector.
		size_t vectorSize = vectorType->getSize(memberPtr);

		std::string vectorName = name;

		std::string columnLabel = "##" + vectorName;
		bool opened = false;

		ImGui::Columns(3, columnLabel.c_str(), false);
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GetEditorVariableLineHeight();
			opened = ImGui::TreeNodeEx(memberPtr, flags, "%s", vectorName.c_str());
			ImGui::PopStyleVar();

			if (ImGui::BeginItemTooltip())
			{
				ImGui::TextUnformatted(vectorName.c_str());
				ImGui::EndTooltip();
			}

			constexpr float kVectorButtonStartingPosition = 60.0f;
			constexpr float kVectorElementButtonOffset = 30.0f;

			ImGui::SetColumnWidth(1, 125.0f);
			ImGui::NextColumn();

			const std::string& numberOfElements = std::to_string(vectorSize) + " Elements";
			ImGui::TextUnformatted(numberOfElements.c_str());

			ImGui::NextColumn();

			// Add new elements
			GB::BeginAddElementButtonStyle();
			{
				std::string addElementButtonLabel = "+##AddElementButton";
				addElementButtonLabel.append(vectorName);
				if (ImGui::Button(addElementButtonLabel.c_str(), ImVec2{ lineHeight, lineHeight }))
				{
					vectorType->addNewItem(memberPtr);

					// Refreshing the size since the vector has been altered here, should be one new element
					vectorSize = vectorType->getSize(memberPtr);

					// Specific implementation for classes that need to manually Create (could be due to cross platform/cross renderer techniques)
					if (vectorItemFieldType == reflect::FieldType::SharedPtr)
					{
						GB_PTR(pSharedPtrAsVoid, vectorType->getItem(memberPtr, vectorSize - 1), "");
						GB_PTR(pSharedPtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdSharedPtr*>(vectorItemTypeDescriptor), "");

						if (pSharedPtrTypeDescriptor->targetType->fieldType == reflect::FieldType::Texture)
						{
							// Get the vector from the memberPtr and update the latest element to a valid SharedPtr<Texture2D> by calling ::Create()...
							// Then set the value back to memberPtr afterwards to update it properly
							GB_PTR(pSharedPtrTexture, static_cast<SharedPtr<Texture2D>*>(const_cast<void*>(pSharedPtrAsVoid)), "");
							std::vector<SharedPtr<Texture2D>> vectorOfTextures = *((std::vector<SharedPtr<Texture2D>>*)memberPtr);
							vectorOfTextures.at(vectorSize - 1) = Texture2D::Create("Assets/Textures/T_WhiteSquare.png");
							*((std::vector<SharedPtr<Texture2D>>*)memberPtr) = vectorOfTextures;
						}
					}
				}
			}
			GB::EndAddElementButtonStyle();

			ImGui::SameLine();

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

			ImGui::SameLine();

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
		}
		ImGui::Columns(1);

		if (opened)
		{
			size_t removeIndex = 0;
			bool hasSetRemoveIndexThisFrame = false;
			bool shouldRemoveIndex = false;

			for (size_t iV = 0; iV < vectorSize; ++iV)
			{
				std::string elementName = std::to_string(iV);
				void* elementPtr = const_cast<void*>(vectorType->getItem(memberPtr, iV));
				DrawVectorElement(vectorItemTypeDescriptor, vectorItemFieldType, elementName.c_str(), elementPtr, iV, shouldRemoveIndex, spacingAfterIndex);

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
	float CalculateSpacingForTargetType(const reflect::TypeDescriptor* pTargetTypeDescriptor, const float defaultSpacing /*= 125.0f*/)
	{
		const reflect::FieldType targetFieldType = pTargetTypeDescriptor->fieldType;
		const bool isPointingToClassType = (pTargetTypeDescriptor->name != "GBBool"
			&& (targetFieldType == reflect::FieldType::Class || targetFieldType == reflect::FieldType::ClassPtr));
		const float spacing = (isPointingToClassType ? (defaultSpacing + (defaultSpacing * kEditorClassSpacingMultiplier)) : (defaultSpacing));
		return spacing;
	}

	void DrawUniquePtr(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr, const float spacingAfterMemberVariables/* = 125.0f*/)
	{
		GB::DrawUniquePtr(reflectedMemberData.type, reflectedMemberData.name, memberPtr, spacingAfterMemberVariables);
	}

	void DrawSharedPtr(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr, const float spacingAfterMemberVariables/* = 125.0f*/)
	{
		GB::DrawSharedPtr(reflectedMemberData.type, reflectedMemberData.name, memberPtr, spacingAfterMemberVariables);
	}

	void DrawWeakPtr(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr, const float spacingAfterMemberVariables/* = 125.0f*/)
	{
		GB::DrawWeakPtr(reflectedMemberData.type, reflectedMemberData.name, memberPtr, spacingAfterMemberVariables);
	}

	void DrawUniquePtr(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const float spacingAfterMemberVariables/* = 125.0f*/)
	{
		GB_PTR(pUniquePtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdUniquePtr*>(pTypeDescriptor), "");
		GB_PTR(pUniquePtrValueTypeDescriptor, pUniquePtrTypeDescriptor->targetType, "");
		void* pUniquePtrValue = pUniquePtrTypeDescriptor->getTarget(memberPtr);
		GB::DrawMember(pUniquePtrValueTypeDescriptor, name, pUniquePtrValue, spacingAfterMemberVariables);
	}

	void DrawSharedPtr(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const float spacingAfterMemberVariables/* = 125.0f*/)
	{
		GB_PTR(pSharedPtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdSharedPtr*>(pTypeDescriptor), "");
		GB_PTR(pSharedPtrValueTypeDescriptor, pSharedPtrTypeDescriptor->targetType, "");
		void* pSharedPtrValue = pSharedPtrTypeDescriptor->getTarget(memberPtr);
		GB::DrawMember(pSharedPtrValueTypeDescriptor, name, pSharedPtrValue, spacingAfterMemberVariables);
	}

	void DrawWeakPtr(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const float spacingAfterMemberVariables/* = 125.0f*/)
	{
		GB_PTR(pWeakPtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdWeakPtr*>(pTypeDescriptor), "");
		GB_PTR(pWeakPtrValueTypeDescriptor, pWeakPtrTypeDescriptor->targetType, "");
		void* pWeakPtrValue = pWeakPtrTypeDescriptor->getTarget(memberPtr);
		GB::DrawMember(pWeakPtrValueTypeDescriptor, name, pWeakPtrValue, spacingAfterMemberVariables);
	}

	void DrawUniquePtrAsVectorElement(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const size_t index, bool& removeElement, const float spacingAfterMemberVariables)
	{
		GB_PTR(pUniquePtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdUniquePtr*>(pTypeDescriptor), "");
		GB_PTR(pUniquePtrValueTypeDescriptor, pUniquePtrTypeDescriptor->targetType, "");
		void* pUniquePtrValue = pUniquePtrTypeDescriptor->getTarget(memberPtr);
		GB::DrawVectorElement(pUniquePtrValueTypeDescriptor, pUniquePtrValueTypeDescriptor->fieldType, name, pUniquePtrValue, index, removeElement, spacingAfterMemberVariables);
	}
	
	void DrawSharedPtrAsVectorElement(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const size_t index, bool& removeElement, const float spacingAfterMemberVariables)
	{
		GB_PTR(pSharedPtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdSharedPtr*>(pTypeDescriptor), "");
		GB_PTR(pSharedPtrValueTypeDescriptor, pSharedPtrTypeDescriptor->targetType, "");
		void* pSharedPtrValue = pSharedPtrTypeDescriptor->getTarget(memberPtr);
		GB::DrawVectorElement(pSharedPtrValueTypeDescriptor, pSharedPtrValueTypeDescriptor->fieldType, name, pSharedPtrValue, index, removeElement, spacingAfterMemberVariables);
	}
	
	void DrawWeakPtrAsVectorElement(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const size_t index, bool& removeElement, const float spacingAfterMemberVariables)
	{
		GB_PTR(pWeakPtrTypeDescriptor, static_cast<reflect::TypeDescriptor_StdWeakPtr*>(pTypeDescriptor), "");
		GB_PTR(pWeakPtrValueTypeDescriptor, pWeakPtrTypeDescriptor->targetType, "");
		void* pWeakPtrValue = pWeakPtrTypeDescriptor->getTarget(memberPtr);
		GB::DrawVectorElement(pWeakPtrValueTypeDescriptor, pWeakPtrValueTypeDescriptor->fieldType, name, pWeakPtrValue, index, removeElement, spacingAfterMemberVariables);
	}
}