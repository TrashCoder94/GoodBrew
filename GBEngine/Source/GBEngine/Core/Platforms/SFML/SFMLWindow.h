#pragma once

#include "GBEngine/Core/Window.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace GB
{
	class SFMLWindow : public Window
	{
	public:
		SFMLWindow(const WindowProperties& properties);
		~SFMLWindow();

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual void* GetNativeWindow() const override;

	protected:
		virtual void Init(const WindowProperties& properties) override;
		virtual void OnBegin() override;
		virtual void OnUpdate() override;
		virtual void OnEnd() override;
		virtual void Shutdown() override;

		sf::RenderWindow* m_pWindow;
	};
}