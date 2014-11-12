#include "stdinc.h"
#include "IPCRepresent.h"

IPCRepresent::IPCRepresent(bool bClient, unsigned int nMode)
{
	m_bClient = bClient;
	
	m_nLastError = IPCR_ERROR_UKNOWN;

	if(nMode == IPCR_NAMEDPIPE)
	{
		m_ipc = new NamedPipe();
	}
#ifdef IPCDELECATOR_OS_LINUX
	else if(nMode == IPCR_MESSAGEQUE)
	{  
		m_ipc = new MessageQue();
	}
#endif
}

IPCRepresent::~IPCRepresent(void)
{
	delete m_ipc;
}

void IPCRepresent::RegisterIPCFunc(FnResp fa,FnResp fe)
{
	m_fnAcceptBuffer = fa;
	m_fnExport = fe;
}

void IPCRepresent::SetType(bool bClient)
{
	m_bClient = bClient;
}

unsigned long IPCRepresent::IPCProcFunc(void* pParam)
{

	perror("IPCProcFunc::run end");      
	IPCRepresent* pThis = (IPCRepresent*)pParam;

	pThis->ProcIPC();

	return IPCR_SUCESS;
}

void IPCRepresent::ProcIPC()
{
	if(m_bClient)
	{	
		if(m_ipc->Open())
		{
			m_nLastError = ClientProc();	
		}
	}
	else
	{	
		if(m_ipc->Create())
		{
			m_nLastError = ServerProc();
		}
	}
	m_nLastError = IPCR_ERROR_UKNOWN;
}


unsigned long IPCRepresent::ServerProc()
{

	unsigned char pBuffer[IPCR_MAX_BUFFER];
	bool bConnected = false;
	bool bRead = true;
	int nReadSize = 0;

	int nConnectionCount = 0;
	

	while(true)
	{
		bConnected = Connect();

		if(bConnected)
		{
			while(bRead)
			{
				nReadSize = Read(pBuffer);
				if(nReadSize == 0)
				{
					bRead = false;

					bConnected = false;
					
					return IPCR_ERROR_LOST; /*disconnect or exception*/
				}
				else
				{
					(*m_fnAcceptBuffer)(pBuffer,nReadSize);
				}
				
			}
		}

		nConnectionCount ++;

		if(IPCR_MAX_CHANCE < nConnectionCount)
		{
			return IPCR_ERROR_TIMEOUT;
		}
	}	

	return IPCR_ERROR_UKNOWN;

}

unsigned long IPCRepresent::ClientProc()
{
	
	bool bConnected = false;

	bConnected = Connect();

	return 0;
}

unsigned long IPCRepresent::GetLastError()
{
	return m_nLastError;
}


bool IPCRepresent::Restore()
{

	return Init();
}

bool IPCRepresent::Init()
{
	m_ipc->DisconnectClient();

	m_TrdConnection.RegisterThreadFunc(IPCRepresent::IPCProcFunc,(void*)this);

	m_TrdConnection.MakeThread();

	perror("IPCRepresent::Init end");
	return true;
}

bool IPCRepresent::Connect()
{
	return m_ipc->ConnectClient();
}

bool IPCRepresent::Disconnect()
{
	return m_ipc->DisconnectClient();
}

int IPCRepresent::Read(unsigned char* pBuffer/*out param*/)
{
	return m_ipc->Read((char*)pBuffer);
}

bool IPCRepresent::Write(unsigned char* pBuffer/*in param*/,unsigned int nLen)
{
	m_ipc->Write((char*)pBuffer,nLen);
	
	bool bRead = true;
	int nReadSize = 0;
	unsigned char pReadBuffer[IPCR_MAX_BUFFER];

	/*client seq write->read, sync call*/
	if(m_bClient)
	{	

		nReadSize = m_ipc->Read((char*)pReadBuffer);
		
		if(nReadSize)
		{
			(*m_fnAcceptBuffer)(pReadBuffer,nReadSize);/*notification Read Data to Root*/
		}
		else
		{
			return false;
		}
	}
	return true;
}

