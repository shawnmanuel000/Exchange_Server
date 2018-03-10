//
// Created by Shawn Manuel on 30/12/2017.
//

#ifndef SERVERPROGRAM_CLIENT_H
#define SERVERPROGRAM_CLIENT_H

#include "NetworkNode.h"

using namespace std;

class Client : public NetworkNode
{
	protected:
		static void Sender(LPVOID args);
		static void Receive(LPVOID args);
		void RegisterSender(LPTHREAD_START_ROUTINE fn, LPVOID args);
		void RegisterReceiver(LPTHREAD_START_ROUTINE fn, LPVOID args);
	private:
		HANDLE sender;
		HANDLE receiver;
    public:
		Client();
		Client(const char* IPaddress, int port);
		void ConnectToHost(const char* IPaddress, int port);
		virtual void StartClient(bool waitForAllThreads, bool registerSender);
		bool SenderActive();
		bool ReceiverActive();
		bool SendMessage(string message);
		virtual void OnNotify(void *source, string message) override;
		void Stop(DWORD returnValue);
		~Client();
};

#endif //SERVERPROGRAM_CLIENT_H
