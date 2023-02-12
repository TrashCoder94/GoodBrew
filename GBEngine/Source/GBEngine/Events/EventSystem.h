#pragma once

#include <functional>

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
		BaseObject* m_pOwner;
		std::function<bool(Event*)> m_Function;
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