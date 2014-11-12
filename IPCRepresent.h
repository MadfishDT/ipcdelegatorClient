#ifndef _IPCRepresent_H
#define  _IPCRepresentt_H

#include "./IPCS/IPCCom.h"

#ifdef IPCDELECATOR_OS_LINUX
#include "./IPCS/Linux/NamedPipe.h"
#include "./IPCS/Linux/MessageQue.h"
#include "./Thread/Linux/ThreadRepresent.h"
#endif

#ifdef IPCDELECATOR_OS_WIN
#include "./IPCS/Window/NamedPipe.h"
#include "./Thread/Window/ThreadRepresent.h"
#endif


#define IPCR_MAX_BUFFER NP_MAX_BUFFERSIZE
#define IPCR_MAX_CHANCE 50

#define IPCR_ERROR_UKNOWN 0
#define IPCR_ERROR_LOST 1
#define IPCR_ERROR_TIMEOUT 2
#define IPCR_ERROR_LOWMEM 3
#define IPCR_SUCESS 100

#define IPCR_NAMEDPIPE 1
#define IPCR_MESSAGEQUE 2



typedef void (*FnResp)(void* p, unsigned int q);
class IPCRepresent
{
public:
	
	IPCRepresent(bool bClient = false,unsigned int nMode = IPCR_NAMEDPIPE);

	~IPCRepresent(void);

	/*proc thread for ipc running*/
	static unsigned long IPCProcFunc(void* pParam);

	void ProcIPC();

	void SetType(bool bClient);

	int Read(unsigned char* pBuffer/*out param*/);

	bool Write(unsigned char* pBuffer/*in param*/,unsigned int nLen);

	bool Init();

	bool Connect();

	bool Disconnect();

	bool Restore();

	unsigned long GetLastError();

	unsigned long ServerProc();

	unsigned long ClientProc();

	void RegisterIPCFunc(FnResp,FnResp);

private:
	
	unsigned long m_nLastError;

	IPCCom* m_ipc;

	bool m_bClient;
	
	unsigned long m_trdConnetID;

	ThreadRepresent m_TrdConnection;

	ThreadRepresent m_TrdRead;

	FnResp m_fnAcceptBuffer;

	FnResp m_fnExport;

	void* m_fnpParam;
};

#endif
