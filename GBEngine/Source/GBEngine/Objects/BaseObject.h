#pragma once

#include "GBEngine/Core/Base.h"

namespace GB
{
	class BaseObject
	{
	protected:
		BaseObject();
		virtual ~BaseObject();
	
	public:
		// When this BaseObject is first loaded up
		virtual void Initialize();

		// Gameplay/runtime related functions
		virtual void Begin();
		virtual void Update(const float deltaTime);
		virtual void End();

		// When this BaseObject is being unloaded (cleaned up)
		virtual void Deinitialize();

#if GB_IMGUI_ENABLED
		// For custom editor properties
		virtual void ImGuiRender();
#endif

		template<class ObjectClass>
		bool IsA()
		{
			const bool bIsSame = (dynamic_cast<ObjectClass*>(this));
			return bIsSame;
		}

		void SetBaseObjectOwner(BaseObject* pOwner);
		BaseObject* GetBaseObjectOwner();
		const BaseObject* GetBaseObjectOwner() const;

	private:
		BaseObject* m_pOwner;
	};
}