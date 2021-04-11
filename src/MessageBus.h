/******************************************************************************/
/*!
\title		Captain Stealth
\file		MessageBus.h
\author 	Lee Jia Keat
\par    	email: l.jiakeat\@digipen.edu
\date   	April 09, 2021
\brief		MessageBus class:
			Static class that can be accessed globally.
			Is responsible for receiving and dispatching events.

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
*/
/******************************************************************************/

#pragma once
#include <vector>
#include <queue>
#include "Event.h"

namespace StarBangBang
{
	class Listener;

	class MessageBus
	{
	public:
		/*!*************************************************************************
		 * \brief
		 * Resets the event system, clearing all listeners from the list and events from the queue.
		 ****************************************************************************/
		static void Reset();

		/*!*************************************************************************
		* \brief
		 * Registers a listener that will persist throughout the whole program (e.g. AudioEngine).
		 * \param listener Pointer to the listener to register.
		 ***************************************************************************/
		static void RegisterGlobalListener(Listener* listener);

		/*!*************************************************************************
		 * \brief 
		 * Checks if an event is in the queue.
		 * \param id
		 * Event id
		 * \return 
		 * True if the event is the in queue, false otherwise.
		***************************************************************************/
		static bool IsEventInQueue(EventId id);

		/*!*************************************************************************
		 * \brief 
		 * Update function that is called once a frame.
		 * Dispatches all events from the event queue to each listener.
		***************************************************************************/
		static void Update();

		/*!*************************************************************************
		 * \brief
		 * Adds an event to the event queue.
		 * 
		 * \param e
		 * Event to add
		 ***************************************************************************/
		static void Notify(Event e);

		friend class Listener;

	private:
		/*!*************************************************************************
		 * \brief 
		 * Registers a listener.
		 * \param listener
		 * Pointer to the listener object to register
		***************************************************************************/
		static void RegisterListener(Listener* listener);
		inline static std::queue<Event> eventQueue;
		inline static std::vector<Listener*>listenerList;
		inline static std::vector<Listener*>globalListenerList;
	};
}