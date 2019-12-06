/**
    NFCReader.h
    A really simplistic comportment for a nfc reader

    @author A.C
    @version 1
*/
#ifndef NFCREADER_H_
#define NFCREADER_H_

class NFCReader{

public:

    /**
     * Virtual class destructor
     *
     * @param none.
     * @return none.
     */
    virtual ~NFCReader(){}

    /**
     * Initialization method
     *
     * This method is used to initialize hardware.
     *
     * @param none.
     * @return none.
     */
    virtual void Initialize() = 0;

    /**
     * Read a NFC card id.
     *
     * Use hardware to read a nfc card and start a transaction.
     *
     * @param none.
     * @return the scanned nfc id or -1.
     */
    virtual int Scan() = 0;

    /**
     * Stop NFC.
     *
     * Stop NFC read for maintenance.
     *
     * @param none.
     * @return none.
     */
    virtual void Stop() = 0;

    /**
     * Restart NFC.
     *
     * Restart NFC read after maintenance.
     *
     * @param none.
     * @return none.
     */
    virtual void Restart() = 0;

};


#endif // NFCREADER_H_
