#pragma once

#include <functional>

namespace GB
{
	template<typename DelegateOwnerClass, typename ReturnType, typename... Args>
	class Delegate
	{
	public:
		void Bind(DelegateOwnerClass* pOwner, const std::function<ReturnType(Args...)>& function)
		{
			m_pOwner = pOwner;
			m_Function = function;
		}

		bool Unbind(DelegateOwnerClass* pOwner)
		{
			if (m_pOwner == pOwner)
			{
				m_pOwner = nullptr;
				m_Function = nullptr;
				return true;
			}
			return false;
		}

		ReturnType operator() (Args ... args)
		{
			const ReturnType returnValue = m_Function(args...);
			return returnValue;
		}

		ReturnType operator() (Args ... args) const
		{
			const ReturnType returnValue = m_Function(args...);
			return returnValue;
		}

	private:
		DelegateOwnerClass* m_pOwner = nullptr;
		std::function<ReturnType(Args...)> m_Function = nullptr;
	};
}