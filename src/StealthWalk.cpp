/*!*********************************************************************
\title	  Captain Stealth
\file     StealthWalk.cpp
\author   Sim Chin Hin
\par      DP email: s.chinhin\@digipen.edu
\date     11/04/2021

\brief
		  This file contains script class for stealthwalk

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
***********************************************************************/
#include "StealthWalk.h"
#include "globals.h"
#include "Collider.h"
#include "ObjectManager.h"
#include <iomanip>
#include <sstream>
#include "UIComponent.h"


namespace StarBangBang
{
	
	/*!*********************************************************************
	\brief
		Non-default constructor

	\param gameObject
		The game object that will use this script
	***********************************************************************/
	StealthWalk::StealthWalk(GameObject* gameObject) : Script(gameObject), 
		image{ nullptr }, cd_txt{nullptr}, timer{ 0.0f }, cooldown{ 0.0f }
	{
		icon_image = nullptr;
	}
	/*!*********************************************************************
	\brief
		Initialise stealth walk
	***********************************************************************/
	void StealthWalk::Start()
	{
		
		cd_txt = objMgr->Find("Stealth_Txt")->GetComponent<Text>();
		assert(cd_txt);

		cd_txt->SetScale(0.4f);
		
		image = gameObject->GetComponent<ImageComponent>();

		GameObject* ui = objMgr->Find("Stealth_UI");

		icon_image = ui->GetComponent<UIComponent>();
		assert(icon_image);
	
	}
	/*!*********************************************************************
	\brief
		Updates stealth walk status
	***********************************************************************/
	void StealthWalk::Update()
	{	


		if (AEInputCheckTriggered(AEVK_Q) && cooldown <= 0)
		{
			invisible = true;
			image->SetTransparency(0.4f);
			icon_image->SetTransparency(0.4f);
			timer = 10.0f;
			cooldown = 10.0f;

		}

		if (timer > EPSILON)
		{
			timer -= g_dt;
			if (timer <= EPSILON)
			{
				invisible = false;
				image->SetTransparency(1.0f);
			}
			
		}
		else if (cooldown > EPSILON)
		{
			
			cooldown -= g_dt;

			if (cooldown < 0.0f)
			{
				cooldown = 0.0f;

			}
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << cooldown;
			std::string cd_str = stream.str();
			cd_txt->SetText(cd_str);

		}
		
		if (cooldown == 0.0f)
		{
			icon_image->SetTransparency(0.8f);
			cd_txt->SetText("Q");
		}
			
		

		
		
	}

}