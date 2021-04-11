/******************************************************************************/
/*!
\title		Captain Stealth
\file		ListenerComponent.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		ListenerComponent virtual component class.
			Implements the Listener interface.

			Enables game objects to receive events
			from the global message bus.

			Is intended to be further inherited and extended
			by more specialized listeners.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include "ComponentCRTP.h"
#include "Event.h"
#include "Listener.h"

namespace StarBangBang
{
	class ListenerComponent : public Component<ListenerComponent>, public Listener
	{
		public:
			/*!*************************************************************************
			 * \brief
			 * Component Constructor.
			 * Attaches the component to a game object.
			 * \param gameObject
			 * GameObject to attach to.
			***************************************************************************/
			ListenerComponent(GameObject* gameObject) : Component(gameObject) {};

			/*!*************************************************************************
			 * \brief
			 * Listener callback. Invoked when an event is received from the Message Bus.
			 * \param e Event data.
			***************************************************************************/
			virtual void onNotify(Event e) {};
	};
}