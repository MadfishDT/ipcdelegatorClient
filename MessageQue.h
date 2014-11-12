#ifndef _MessageQue_H
#define  _MessageQue_H

#include <unistd.h>
#include <sys/stat.h>
#include <linux/stat.h>
#include "IPCCom.h"

#define MESAGEQ_MAX_BUFFERSIZE IPCCOM_MAX_BUFFERSIZE

#define FIFO_FILE_NAME  "//opt/fifo/methoddelegator"

#define MESSAGE_F_KEY 800312

#define MESSAGE_F_TYPE 10

#define MESSAGE_W_TYPE 20

typedef struct 
{
	long mtype;     /* message type, must be > 0 */
	char mtext[MESAGEQ_MAX_BUFFERSIZE];  /* message data */
} MsgType;

class MessageQue : public IPCCom
{
public:
	MessageQue(void);
	~MessageQue(void);

	virtual bool Create();
	virtual bool ConnectClient();
	virtual bool DisconnectClient();
	virtual bool Open();
	virtual bool Write(char* lpBuffer, unsigned long nBufferLen);
	virtual unsigned long Read(char* lpBuffer);
private:

	int m_nMessageQID;
	int m_nSendType;
	int m_nReceiveType;
	
};
#endif
