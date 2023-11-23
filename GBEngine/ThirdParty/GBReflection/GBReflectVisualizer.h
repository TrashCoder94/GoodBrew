#pragma once

#include <imgui.h>
#include "FieldType.h"
#include "TypeDescriptorStruct.h"

namespace GB
{
	class BaseObject;

	// ===================================
	// ImGui helper functions for consistency across different editor variable widgets
	ImFont* GetEditorVariableButtonImGuiFont();
	ImVec2 GetEditorVariableButtonSize();
	float GetEditorVariableLineHeight();

	// ===================================
	// SHARED - Used for all variable displays in the editor.
	// This will draw the variable name before 
	void DrawMemberName(const char* name, const float spaceAfterVariableName = 125.0f);

	void BeginEditorVariable(const char* name, const float spaceAfterVariableName = 125.0f);
	void EndEditorVariable();

	void BeginAddElementButtonStyle();
	void EndAddElementButtonStyle();

	void BeginRemoveElementButtonStyle();
	void EndRemoveElementButtonStyle();

	void DrawMember(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const float spacingAfterMemberVariables = 125.0f);
	void DrawMember(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr, const float spacingAfterMemberVariables = 125.0f);

	// ===================================
	// FLOATS
	// Helpers
	void DrawXFloatValue(float& value);
	void DrawYFloatValue(float& value);
	void DrawZFloatValue(float& value);
	void DrawWFloatValue(float& value);

	// Float variable display in editor
	void DrawFloat(const char* name, void* memberPtr, const float spacingAfterVariableName = 125.0f);
	void DrawFloat2(const char* name, void* memberPtr, const float spacingAfterVariableName = 125.0f);
	void DrawFloat3(const char* name, void* memberPtr, const float spacingAfterVariableName = 125.0f);
	void DrawFloat4(const char* name, void* memberPtr, const float spacingAfterVariableName = 125.0f);

	// ===================================
	// INTS
	// Int variable helpers
	void DrawXIntValue(int& value);
	void DrawYIntValue(int& value);
	void DrawZIntValue(int& value);
	void DrawWIntValue(int& value);

	// These functions are the ones that will display the int variable name and value in the editor
	// This will be same convention/setup for the other variable types as well...
	void DrawInt(const char* name, void* memberPtr, const float spacingAfterVariableName = 125.0f);
	void DrawInt2(const char* name, void* memberPtr, const float spacingAfterVariableName = 125.0f);
	void DrawInt3(const char* name, void* memberPtr, const float spacingAfterVariableName = 125.0f);
	void DrawInt4(const char* name, void* memberPtr, const float spacingAfterVariableName = 125.0f);

	// ===================================
	// BOOLS
	void DrawBool(const char* name, void* memberPtr, const float spacingAfterVariableName = 125.0f);

	// ===================================
	// STRINGS
	void DrawString(const char* name, void* memberPtr, const float spacingAfterVariableName = 125.0f);

	// ===================================
	// COLOURS
	void DrawColours(const char* name, void* memberPtr, const float spacingAfterVariableName = 125.0f);

	// ===================================
	// TEXTURES
	void DrawTexture(const char* name, void* memberPtr, const float spacingAfterVariableName = 125.0f);

	// ===================================
	// CLASSES
	void DrawClassMembers(BaseObject* pClass, const float spacingAfterMemberVariables = 125.0f);
	void DrawClass(BaseObject* pClass, const float spacingAfterMemberVariables = 125.0f);
	
	// Different to the function above because vector elements need to draw the "-" button to remove individual elements
	// The class remove button should be placed onto the class bar
	void DrawClassAsVectorElement(BaseObject* pClass, const size_t index, bool& removeElement, const float spacingAfterMemberVariables = 125.0f);

	// ===================================
	// VECTORS
	void DrawVectorElement(reflect::TypeDescriptor* pTypeDescriptor, const reflect::FieldType type, const char* name, void* memberPtr, const size_t index, bool& removeElement, const float spacingAfterVariableName = 125.0f);
	void DrawVector(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const float spacingAfterIndex = 125.0f);

	// ===================================
	// SMART PTRS
	float CalculateSpacingForTargetType(const reflect::TypeDescriptor* pTargetTypeDescriptor, const float defaultSpacing = 125.0f);

	void DrawUniquePtr(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr, const float spacingAfterMemberVariables = 125.0f);
	void DrawSharedPtr(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr, const float spacingAfterMemberVariables = 125.0f);
	void DrawWeakPtr(const reflect::TypeDescriptor_Struct::Member& reflectedMemberData, void* memberPtr, const float spacingAfterMemberVariables = 125.0f);

	void DrawUniquePtr(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const float spacingAfterMemberVariables = 125.0f);
	void DrawSharedPtr(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const float spacingAfterMemberVariables = 125.0f);
	void DrawWeakPtr(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const float spacingAfterMemberVariables = 125.0f);

	void DrawUniquePtrAsVectorElement(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const size_t index, bool& removeElement, const float spacingAfterMemberVariables = 125.0f);
	void DrawSharedPtrAsVectorElement(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const size_t index, bool& removeElement, const float spacingAfterMemberVariables = 125.0f);
	void DrawWeakPtrAsVectorElement(reflect::TypeDescriptor* pTypeDescriptor, const char* name, void* memberPtr, const size_t index, bool& removeElement, const float spacingAfterMemberVariables = 125.0f);
}
