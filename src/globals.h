/******************************************************************************/
/*!
\title		Captain Stealth
\file		globals.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		Global variables.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once

namespace StarBangBang
{
	extern float g_dt;
	extern s8 fontId;
	extern s8 fontId2;

	/*!*************************************************************************
	 * \brief
	 * Checks if the game is in debug mode.
	 * \return
	 * True if in debug mode, false otherwise.
	***************************************************************************/
	bool IsDebug();

	/*!*************************************************************************
	 * \brief
	 * Checks if the game window is in focus (not iconic).
	 * \return
	 * True if focused, false otherwise
	***************************************************************************/
	bool LostFocus();
}