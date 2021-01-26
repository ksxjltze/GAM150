#include "MessageBus.h"

StarBangBang::MessageBus::MessageBus()
{
}

StarBangBang::MessageBus::~MessageBus()
{
}

void StarBangBang::MessageBus::addReceiver(std::function<void(Message)> messageReceiver)
{
}

void StarBangBang::MessageBus::sendMessage(Message message)
{
}

void StarBangBang::MessageBus::notify()
{
}
