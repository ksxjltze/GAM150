#pragma once
#include <functional>
#include "MessageBus.h"

namespace StarBangBang
{
	class BusNode
	{
	public:
		BusNode(MessageBus* bus) { messageBus = bus; bus->addReceiver(this->GetNotifyFunction()); }
	protected:
		MessageBus* messageBus;
        std::function<void(Message)> GetNotifyFunction()
        {
            auto messageListener = [=](Message message) -> void {
                this->OnNotify(message);
            };
            return messageListener;
        }

        void Send(Message message)
        {
            messageBus->sendMessage(message);
        }

        virtual void OnNotify(Message message)
        {
            
        }
	};
}