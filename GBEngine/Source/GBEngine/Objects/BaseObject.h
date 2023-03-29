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

		virtual void Begin();
		virtual void Update(const float deltaTime);
		virtual void End();

		// When this BaseObject is being unloaded (cleaned up)
		virtual void Deinitialize();

		// For custom editor properties
		virtual void ImGuiRender();

		template<class ObjectClass>
		bool IsA()
		{
			const bool bIsSame = (dynamic_cast<ObjectClass*>(this));
			return bIsSame;
		}

		void SetOwner(BaseObject* pOwner);
		BaseObject* GetOwner();
		const BaseObject* GetOwner() const;

	private:
		BaseObject* m_pOwner;
	};
}