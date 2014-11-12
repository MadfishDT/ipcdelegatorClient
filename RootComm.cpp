#include "stdinc.h"
#include "RootComm.h"


RootComm::RootComm(void)
{
	
}

RootComm::~RootComm(void)
{
	
}



iObject_glue* RootComm::CreateCommObject(string strName)
{
	/*add create object code*/

	return new iObject_glue();
}

void RootComm::StartServerType(bool bCreateNew)
{
	IPCDelegatorCore::getInstance()->StartIPCDelegator(false,bCreateNew);
}

void RootComm::StartClientType(bool bCreateNew)
{
	IPCDelegatorCore::getInstance()->StartIPCDelegator(true,bCreateNew);
}

void RootComm::Stop()
{
	
}

ObjectBinderFactory* RootComm::GetFactory()
{
	return IPCDelegatorCore::getInstance()->GetFactory();
}

