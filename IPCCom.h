#ifndef _IPCCom_H
#define  _IPCCom_H


#define IPCCOM_MAX_BUFFERSIZE 4096

class IPCCom
{
public:
	
	IPCCom(void);
	~IPCCom(void);

	virtual bool Create() = 0;
	virtual bool ConnectClient() = 0;
	virtual bool DisconnectClient() = 0;
	virtual bool Open() = 0;
	virtual bool Write(char* lpBuffer, unsigned long nBufferLen) = 0;
	virtual unsigned long Read(char* lpBuffer) = 0;

};
#endif
