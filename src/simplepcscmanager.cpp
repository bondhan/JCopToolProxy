#include "simplepcscmanager.h"

SimplePCSCManager::SimplePCSCManager()
{

}

LONG SimplePCSCManager::EstablishContext(QString *status, SCARDCONTEXT *m_hSC, DWORD SCOPE)
{
    LONG lReturn = SCARD_S_SUCCESS;

    status->append("Establishing Context\n");

    // Calling PCSC low level functions
    lReturn = SCardEstablishContext(SCOPE,
                                    NULL,
                                    NULL,
                                    m_hSC);

    if ( lReturn != SCARD_S_SUCCESS )
        status->append("Failed to establish context with SCardEstablishContext\n");
    else
        status->append("SCardEstablishContext established successfully \n");

    return lReturn;
}

LONG SimplePCSCManager::ListReaders(QString *status, SCARDCONTEXT m_hSC, QStringList *readerList)
{
    LPTSTR          pmszReaders = NULL;
    LONG            lReturn, lReturn2;
    DWORD           cch = SCARD_AUTOALLOCATE;

    // Retrieve the list the readers.
    // hSC was set by a previous call to SCardEstablishContext (during object creation).
    lReturn = SCardListReaders(m_hSC,
                               NULL,
                               (LPTSTR)&pmszReaders,
                               &cch );

    switch( lReturn )
    {
    case SCARD_E_NO_READERS_AVAILABLE:
        status->append("No Readers Available \n");
        break;

    case SCARD_S_SUCCESS:
        // Do something with the multi string of readers.
        // A double-null terminates the list of values.
        readerList->clear();

        // if in case ther reader are more than 1
        LPTSTR	pReader;
        pReader = pmszReaders;

        while ( '\0' != *pReader )
        {
            QString tmp;
            tmp.clear();

            while ('\0' != *pReader)
            {
                tmp.append(*pReader);
                pReader++;
            }

            pReader++;  // skip null

            // save to the list
            readerList->append(tmp);
        }

        // Free the memory.
        lReturn2 = SCardFreeMemory(m_hSC,
                                   pmszReaders );

        if ( SCARD_S_SUCCESS != lReturn2 )
            status->append("Failed to free memory \n");
        break;

    default:
        status->append("SCardListReaders Failed \n");
        break;
    }

    return lReturn;
}

LONG SimplePCSCManager::ReleaseContext(QString *status, SCARDCONTEXT m_hSC)
{
    LONG lReturn;

    status->append("Releasing Context \n");

    // Free the context.
    lReturn = SCardReleaseContext(m_hSC);

    if ( SCARD_S_SUCCESS != lReturn )
        status->append("Failed SCardReleaseContext\n");
    else
    {
        status->append("SCardReleaseContext is successfully released\n");
    }

    return lReturn;
}


bool SimplePCSCManager::Connect(QString reader, SCARDCONTEXT hSc, DWORD ShareMode, DWORD PreferredProtocols,
                                DWORD *activeProtocol, SCARDHANDLE *cardHandle)
{
    LPTSTR reader_name;

    if(sizeof(TCHAR) == 1)
    {
        reader_name = (LPTSTR) reader.toLatin1().constData();
    }
    else
        reader_name = (LPTSTR) reader.utf16();

    LONG ris = SCardConnect(hSc, reader_name, ShareMode,
                            PreferredProtocols, cardHandle, activeProtocol);

    if (ris != 0)
        return false;

    return true;
}

BYTE *SimplePCSCManager::GetAttrib(QString *status_message, DWORD dwAttrib, SCARDHANDLE hCard)
{

    LONG        lReturn;
    BYTE        *bBuffer;
    DWORD       dwLen;

    dwLen = 0x0000;

    lReturn = SCardGetAttrib(   hCard,
                                dwAttrib,
                                NULL,
                                &dwLen);

    if (lReturn != SCARD_S_SUCCESS)
    {
        status_message->append("SCARD_ATTR_ATR_STRING : "+GetPCSCErrorString(lReturn) +"\n");

        return NULL;
    }


    bBuffer = new BYTE[dwLen];

    lReturn = SCardGetAttrib(   hCard,
                                dwAttrib,
                                (LPBYTE) bBuffer,
                                &dwLen);

    if (lReturn != SCARD_S_SUCCESS)
    {
        status_message->append("SCARD_ATTR_CHANNEL_ID : "+GetPCSCErrorString(lReturn) +"\n");

        return NULL;
    }


    return bBuffer;
}


QString SimplePCSCManager::GetPCSCErrorString(LONG lReturn)
{
    switch(lReturn)
    {
    case 0x80100001:
        return "SCARD_F_INTERNAL_ERROR";
        break;

    case 0x80100002:
        return "SCARD_E_CANCELLED";
        break;

    case 0x80100003:
        return "SCARD_E_INVALID_HANDLE";
        break;

    case 0x80100004:
        return "SCARD_E_INVALID_PARAMETER";
        break;

    case 0x80100005:
        return "SCARD_E_INVALID_TARGET";
        break;

    case 0x80100006:
        return "SCARD_E_NO_MEMORY";
        break;

    case 0x80100007:
        return "SCARD_F_WAITED_TOO_LONG";
        break;

    case 0x80100008:
        return "SCARD_E_INSUFFICIENT_BUFFER";
        break;

    case 0x80100009:
        return "SCARD_E_UNKNOWN_READER";
        break;

    case 0x8010000A:
        return "SCARD_E_TIMEOUT";
        break;

    case 0x8010000B:
        return "SCARD_E_SHARING_VIOLATION";
        break;

    case 0x8010000C:
        return "SCARD_E_NO_SMARTCARD";
        break;

    case 0x8010000D:
        return "SCARD_E_UNKNOWN_CARD";
        break;

    case 0x8010000E:
        return "SCARD_E_CANT_DISPOSE";
        break;

    case 0x8010000F:
        return "SCARD_E_PROTO_MISMATCH";
        break;

    case 0x80100010:
        return "SCARD_E_NOT_READY";
        break;

    case 0x80100011:
        return "SCARD_E_INVALID_VALUE";
        break;

    case 0x80100012:
        return "SCARD_E_SYSTEM_CANCELLED";
        break;

    case 0x80100013:
        return "SCARD_F_COMM_ERROR";
        break;

    case 0x80100014:
        return "SCARD_F_UNKNOWN_ERROR";
        break;

    case 0x80100015:
        return "SCARD_E_INVALID_ATR";
        break;

    case 0x80100016:
        return "SCARD_E_NOT_TRANSACTED";
        break;

    case 0x80100017:
        return "SCARD_E_READER_UNAVAILABLE";
        break;

    case 0x80100018:
        return "SCARD_P_SHUTDOWN";
        break;

    case 0x80100019:
        return "SCARD_E_PCI_TOO_SMALL";
        break;

    case 0x8010001A:
        return "SCARD_E_READER_UNSUPPORTED";
        break;

    case 0x8010001B:
        return "SCARD_E_DUPLICATE_READER";
        break;

    case 0x8010001C:
        return "SCARD_E_CARD_UNSUPPORTED";
        break;

    case 0x8010001D:
        return "SCARD_E_NO_SERVICE";
        break;

    case 0x8010001E:
        return "SCARD_E_SERVICE_STOPPED";
        break;

    case 0x8010001F:
        return "SCARD_E_UNEXPECTED";
        break;

    case 0x80100020:
        return "SCARD_E_ICC_INSTALLATION";
        break;

    case 0x80100021:
        return "SCARD_E_ICC_CREATEORDER";
        break;

    case 0x80100022:
        return "SCARD_E_UNSUPPORTED_FEATURE";
        break;

    case 0x80100023:
        return "SCARD_E_DIR_NOT_FOUND";
        break;

    case 0x80100024:
        return "SCARD_E_FILE_NOT_FOUND";
        break;

    case 0x80100025:
        return "SCARD_E_NO_DIR";
        break;

    case 0x80100026:
        return "SCARD_E_NO_FILE";
        break;

    case 0x80100027:
        return "SCARD_E_NO_ACCESS";
        break;

    case 0x80100028:
        return "SCARD_E_WRITE_TOO_MANY";
        break;

    case 0x80100029:
        return "SCARD_E_BAD_SEEK";
        break;

    case 0x8010002A:
        return "SCARD_E_INVALID_CHV";
        break;

    case 0x8010002B:
        return "SCARD_E_UNKNOWN_RES_MNG";
        break;

    case 0x8010002C:
        return "SCARD_E_NO_SUCH_CERTIFICATE";
        break;

    case 0x8010002D:
        return "SCARD_E_CERTIFICATE_UNAVAILABLE";
        break;

    case 0x8010002E:
        return "SCARD_E_NO_READERS_AVAILABLE";
        break;

    case 0x80100065:
        return "SCARD_W_UNSUPPORTED_CARD";
        break;

    case 0x80100066:
        return "SCARD_W_UNRESPONSIVE_CARD";
        break;

    case 0x80100067:
        return "SCARD_W_UNPOWERED_CARD";
        break;

    case 0x80100068:
        return "SCARD_W_RESET_CARD";
        break;

    case 0x80100069:
        return "SCARD_W_REMOVED_CARD";
        break;

    case 0x8010006A:
        return "SCARD_W_SECURITY_VIOLATION";
        break;

    case 0x8010006B:
        return "SCARD_W_WRONG_CHV";
        break;

    case 0x8010006C:
        return "SCARD_W_CHV_BLOCKED";
        break;

    case 0x8010006D:
        return "SCARD_W_EOF";
        break;

    case 0x8010006E:
        return "SCARD_W_CANCELLED_BY_USER";
        break;

    case 0x0000007B:
        return "INACCESSIBLE_BOOT_DEVICE";
        break;
    case SCARD_E_CANNOT_CONNECT:
        return "SCARD_E_CANNOT_CONNECT";
        break;
    case SCARD_E_SEND_APDU_FAILED:
        return "SCARD_E_SEND_APDU_FAILED";
        break;
    default:
        return "Invalid Error Code";

    }
}
