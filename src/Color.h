
/******************************************************************************/
/*!
\title		Captain Stealth
\file		Color.h
\author 	Ho Yi Guan
\par    	email: Yiguan.ho@digipen.edu
\date   	April 08, 2021
\brief
			Implments a color class
			Contain common color definitions

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
namespace StarBangBang
{
	class Color
	{
	private:
		float r = 1.0f;
		float g = 1.0f;
		float b = 1.0f;
		float a = 1.0f;
	public:

		/*!*************************************************************************
		****
			\brief
				Color class constructor
			\param r
				The red component
			\param g
				The green component
			\param b
				The blue component
			\param a
				The alpha component
			\return
			  void
		****************************************************************************
		***/
		Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
		{
			this->r = r >= 0 && r <= 1.0f ? r : 1.0f;
			this->g = g >= 0 && g <= 1.0f ? g : 1.0f;
			this->b = b >= 0 && b <= 1.0f ? b : 1.0f;
			this->a = a >= 0 && a <= 1.0f ? a : 1.0f;


		}

		/*!*************************************************************************
		****
			\brief
				Get the red component's value
			\param none
				
			\return
				returns the red component's value (0.0f - 1.0f)
		****************************************************************************
		***/
		constexpr float R() const { return r; }

		/*!*************************************************************************
		****
			\brief
				Get the green component's value
			\param none

			\return
				returns the green component's value (0.0f - 1.0f)
		****************************************************************************
		***/
		constexpr float G() const { return g; }

		/*!*************************************************************************
		****
			\brief
				Get the blue component's value
			\param none

			\return
				returns the blue component's value (0.0f - 1.0f)
		****************************************************************************
		***/
		constexpr float B() const { return b; }


		/*!*************************************************************************
		****
			\brief
				Get the alpha component's value
			\param none

			\return
				returns the alpha component's value (0.0f - 1.0f)
		****************************************************************************
		***/
		constexpr float A() const { return a; }
		

	};
	
	static const Color Red	{1.0f,0.0f,0.0f,1.0f};
	static const Color White{ 1.0f, 1.0f, 1.0f, 1.0f };
	static const Color Blue	{ 0.0f, 0.0f, 1.0f, 1.0f };
	static const Color Green{ 0.0f, 1.0f, 0.0f, 1.0f };
	static const Color Black{ 0.0f, 0.0f, 0.0f, 1.0f };
	static const Color Cyan{ 0.0f, 1.0f, 1.0f, 1.0f };
	static const Color Yellow{ 1.0f, 1.0f, 0.0f, 1.0f };
	static const Color Purple{ 1.0f, 0.0f, 1.0f, 1.0f };
	static const Color Gray { 0.5f, 0.5f, 0.5f ,1.0f};
	static const Color LightGreen{ 0.5f, 0.65f, 0.0f, 1.0f};
	static const Color SkyBlue{ 0.3f, 0.6f, 1.0f,1.0f};
	

}