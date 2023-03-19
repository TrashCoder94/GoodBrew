#pragma once

#include <vector>
#include "GBEngine/Delegates/Delegate.h"

namespace GB
{
	class BaseObject;
	class Event;
	enum class EEventType;

	class EventSystemListener
	{
		friend class EventSystem;

	public:
		EventSystemListener();
		~EventSystemListener();

	private:
		EEventType m_EventType;
		Delegate<BaseObject, bool, Event*> m_Delegate;
	};

	class EventSystem
	{
	public:
		EventSystem();
		~EventSystem();

		static EventSystem& Get();

		void Bind(const EEventType eventType, BaseObject* pOwner, const std::function<bool(Event*)>& function);

		void Unbind(const EEventType eventType, BaseObject* pOwner);

		void Broadcast(Event* event) const;

	private:
		static EventSystem* s_pInstance;

		std::vector<EventSystemListener> m_EventListeners;
	};
}