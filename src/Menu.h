/******************************************************************************/
/*!
\title		Captain Stealth
\file		Menu.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Menu class.
			Displays a menu overlay.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include "ScriptComponent.h"
#include "GraphicsManager.h"

namespace StarBangBang
{
	class Menu : public Script
	{
	public:
		/*!*************************************************************************
		 * \brief 
		 * Script constructor.
		 * \param gameObject
		 * GameObject to attach to.
		 * \param gfx
		 * Reference to the graphics Manager.
		***************************************************************************/
		Menu(GameObject* gameObject, GraphicsManager& gfx);

		/*!*************************************************************************
		 * \brief 
		 * Init abstract function.
		 * \return
		 * void
		***************************************************************************/
		virtual void Init() = 0;

		/*!*************************************************************************
		 * \brief
		 * Toggle abstract function.
		 * \return
		 * void
		***************************************************************************/
		virtual void Toggle() = 0;

		/*!*************************************************************************
		 * \brief 
		 * Start.
		 * \return void
		***************************************************************************/
		void Start();

		/*!*************************************************************************
		 * \brief 
		 * Draw.
		 * \return void
		***************************************************************************/
		void Draw();

		/*!*************************************************************************
		 * \brief 
		 * Force Update.
		 * Forcefully updates the components of the button objects,
		 * separately from object manager.
		 * \return
		 * void
		***************************************************************************/
		void ForceUpdate();

		/*!*************************************************************************
		 * \brief 
		 * Sets the status of the menu.
		 * \param stat
		 * True if active, false otherwise.
		***************************************************************************/
		void SetStatus(bool stat);

		/*!*************************************************************************
		 * \brief 
		 * Gets the status of the menu.
		 * \return 
		 * True if active, false otherwise
		***************************************************************************/
		bool GetStatus() { return status; }
	protected:
		std::vector<GameObject*> buttonList;
		GraphicsManager& gfxMgr;
	private:
		bool status{ false };
	};
}