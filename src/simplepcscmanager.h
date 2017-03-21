#ifndef SIMPLEPCSCMANAGER_H
#define SIMPLEPCSCMANAGER_H

#include <winscard.h>
#include <QStringList>

#define	SCARD_E_CANNOT_CONNECT		0x80200001
#define	SCARD_E_SEND_APDU_FAILED	SCARD_E_CANNOT_CONNECT+1
#define	SCARD_E_GET_ATR_ERROR		SCARD_E_CANNOT_CONNECT+2

class SimplePCSCManager
{

public:
    SimplePCSCManager();
    LONG ListReaders(QString *status, SCARDCONTEXT m_hSC, QStringList *readerList);
    LONG EstablishContext(QString *status, SCARDCONTEXT *m_hSC, DWORD SCOPE);
    LONG ReleaseContext(QString *status, SCARDCONTEXT m_hSC);
    bool Connect(QString reader, SCARDCONTEXT hSc, DWORD ShareMode, DWORD PreferredProtocols,
                 DWORD *activeProtocol, SCARDHANDLE *cardHandle);
    BYTE *GetAttrib(QString *status_message, DWORD dwAttrib, SCARDHANDLE hCard);
    QString GetPCSCErrorString(LONG lReturn);
};

#endif // SIMPLEPCSCMANAGER_H
