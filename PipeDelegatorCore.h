#ifndef  _PipeDelegatorCore_H
#define  _PipeDelegatorCore_H

#include "ProcPackage.h"
#include "ProcParser.h"
#include "MethodCaller.h"
#include "ObjectBinderFactory.h"


#define BUFFER_PIPE_DELEGATOR  1024

class IPCRepresent;
class RootComm;

class PipeDelegatorCore
{
public:
	
	static PipeDelegatorCore* getInstance()
	{
		static PipeDelegatorCore* pObj;

		if(!pObj)
		{
			pObj = new PipeDelegatorCore();
		}

		return pObj;
	}

	static void AcceptBuffer(void* pParam, unsigned int nParam);
	
	static void ExportBuffer(void* pParam, unsigned int nParam);

	bool StartIPCDelegator(bool bClient,bool bCreateNew);

	bool P_CallMethod(ProcParser* pParser);
	bool P_AddBinderObject(ProcParser* pParser);
	bool P_RequestObject(ProcParser* pParser);
	bool P_ResultObject(ProcParser* pParser);

	bool PK_RequestObject(string strObjectName);
	bool PK_RequestMedhodCall(string strObjectName,unsigned long uObjectAddress,string strMethod,CClArgList& args);
	bool PK_RequestMethodRes(string strObjectName,string strAddress,string strMethod,string strResType,string strResVal);

	void Packaging(char* pBuffer,unsigned int nLen);
	void Parsing(char* pBuffer,unsigned int nLen);

	ObjectBinderFactory* GetFactory();

private:

	PipeDelegatorCore(void);

	~PipeDelegatorCore(void);

	IPCRepresent* m_pIPC;

	RootComm* pRoot;

	ProcPackage m_Package;

	ProcParser m_Parser;

	MethodCaller m_Caller;

	ObjectBinderFactory m_Factory;
};
#endif