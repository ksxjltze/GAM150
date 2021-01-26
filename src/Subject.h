#pragma once
#include <vector>
#include "Observer.h"

namespace StarBangBang
{
	class Subject
	{
	public:
		void notify(const GameObject& obj, Event event);
		void addObserver(Observer* observer);
		void removeObserver(Observer* observer);
	private:
		std::vector<Observer*> observerList;
	};
}