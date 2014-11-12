#ifndef _NamedPipe_H
#define  _NamedPipe_H

#include <unistd.h>
#include <sys/stat.h>
#include <linux/stat.h>
#include "IPCCom.h"

#define NP_MAX_BUFFERSIZE IPCCOM_MAX_BUFFERSIZE

class NamedPipe : public IPCCom
{

public:
	NamedPipe(void);
	~NamedPipe(void);

	virtual bool Create();
	virtual bool ConnectClient();
	virtual bool DisconnectClient();
	virtual bool Open();
	virtual bool Write(char* lpBuffer, unsigned long nBufferLen);
	virtual unsigned long Read(char* lpBuffer);
private:

	FILE* m_pfPipe;
	FILE* m_pwPipe;
	
	int m_nfFile;
	int m_nwFile;
	
	//HANDLE m_hPipe;

};
#endif
