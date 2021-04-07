#include "StealthWalk.h"
#include "globals.h"
#include "Collider.h"
#include "ObjectManager.h"
#include <iomanip>
#include <sstream>
#include "UIComponent.h"


namespace StarBangBang
{
	

	StealthWalk::StealthWalk(GameObject* gameObject) : Script(gameObject), 
		image{ nullptr }, cd_txt{nullptr}, timer{ 0.0f }, cooldown{ 0.0f }
	{
		icon_image = nullptr;
	}

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