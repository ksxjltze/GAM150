#include "MessageBus.h"

StarBangBang::MessageBus::MessageBus()
{
}

StarBangBang::MessageBus::~MessageBus()
{
}

void StarBangBang::MessageBus::addReceiver(std::function<void(Message)> messageReceiver)
{
	receivers.push_back(messageReceiver);
}

void StarBangBang::MessageBus::sendMessage(Message message)
{
	messages.push(message);
}

void StarBangBang::MessageBus::notify()
{
	while (!messages.empty())
	{
		for (auto iter = receivers.begin(); iter != receivers.end(); iter++)
		{
			(*iter)(messages.front());
		}
		messages.pop();
	}
}
