#pragma once
#include <functional>
#include <queue>
#include <vector>
#include "Message.h"

//Adapted from https://seanballais.github.io/blog/implementing-a-simple-message-bus-in-cpp/
namespace StarBangBang
{
	class MessageBus
	{
	public:
		MessageBus();
		~MessageBus();

		void addReceiver(std::function<void(Message)> messageReceiver);
		void sendMessage(Message message);
		void notify();
	private:
		std::vector<std::function<void(Message)>> receivers;
		std::queue<Message> messages;
	};
}