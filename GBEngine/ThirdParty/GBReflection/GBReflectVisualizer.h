#pragma once

#include <imgui.h>
#include "ThirdParty/Reflection/FieldType.h"

namespace GB
{
	class BaseObject;

	// ===================================
	// ImGui helper functions for consistency across different editor variable widgets
	ImFont* GetEditorVariableButtonImGuiFont();
	ImVec2 GetEditorVariableButtonSize();

	// ===================================
	// SHARED - Used for all variable displays in the editor.
	
	// Used for formatting variables in the editor:
	// VariableName | VariableValue
	void BeginEditorVariableTable(const char* tableName);
	void EndEditorVariableTable();

	// This will draw the variable name before 
	void DrawMemberName(const char* name);

	void BeginEditorVariable(const char* name);
	void EndEditorVariable();

	void DrawMember(const reflect::FieldType type, const char* name, void* memberPtr);

	// ===================================
	// FLOATS
	// Helpers
	void DrawXFloatValue(float& value);
	void DrawYFloatValue(float& value);
	void DrawZFloatValue(float& value);
	void DrawWFloatValue(float& value);

	// Float variable display in editor
	void DrawFloat(const char* name, void* memberPtr);
	void DrawFloat2(const char* name, void* memberPtr);
	void DrawFloat3(const char* name, void* memberPtr);
	void DrawFloat4(const char* name, void* memberPtr);

	// ===================================
	// INTS
	// Int variable helpers
	void DrawXIntValue(int& value);
	void DrawYIntValue(int& value);
	void DrawZIntValue(int& value);
	void DrawWIntValue(int& value);

	// These functions are the ones that will display the int variable name and value in the editor
	// This will be same convention/setup for the other variable types as well...
	void DrawInt(const char* name, void* memberPtr);
	void DrawInt2(const char* name, void* memberPtr);
	void DrawInt3(const char* name, void* memberPtr);
	void DrawInt4(const char* name, void* memberPtr);

	// ===================================
	// BOOLS
	void DrawBool(const char* name, void* memberPtr);

	// ===================================
	// STRINGS
	void DrawString(const char* name, void* memberPtr);

	// ===================================
	// COLOURS
	void DrawColours(const char* name, void* memberPtr);

	// ===================================
	// TEXTURES
	void DrawTexture(const char* name, void* memberPtr);

	// ===================================
	// CLASSES
	void DrawClassMembers(BaseObject* pClass);
	void DrawClass(BaseObject* pClass);

	// ===================================
	// VECTORS
	void DrawVector(const char* name, void* memberPtr);
}