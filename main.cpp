#include "stdinc.h"
#include "RootComm.h"
#include "RPCObjectBinder.h"

#include <vector>
#include <iostream>

using namespace std;
int main()
{
 

	RootComm* pRC = RootComm::getInstance();

	pRC->StartClientType(false);
	perror("StartClientType success");
	int nVal;
	CClArgList args;
	RPCObjectBinder* pObjectApplication;

	int nRet;
	vector<int> va;
	va.push_back(1);
	va.push_back(2);
	va.push_back(3);
	va.push_back(4);
	va.push_back(5);
	va.push_back(6);

	while(1)
	{
		cin>>nVal;
		switch(nVal)
		{
		case 1:
			perror("Request Objects");
			pObjectApplication = pRC->GetFactory()->RequestObject(string("application"));
			cout<<"Object Name:"<< pObjectApplication->GetName() <<endl;
			cout<<"Object Address:"<< pObjectApplication->GetAddress()<< endl;
			break;
		case 2:
			args >> (int)1;
			args >> (float)2.0f;
			args >> string("Madfish");
			args >> va;
			args >> (unsigned int)(12312);
			args >> (unsigned long)(255255);
			pObjectApplication->InvokeCall("CreateApplication",args);
			args <<nRet;
			cout<<"CreateApplication return:"<< nRet<< endl;
		default:
			break;
		}
	}
	return 0;
}
