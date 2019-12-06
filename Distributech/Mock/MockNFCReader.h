/**
    MockNFCReader.h
    Mock the class NFCReader for tests.
    Check NFCReader.h for methods details

    @author A.C
    @version 1
*/

#ifndef MOCKNFCREADER_H_
#define MOCKNFCREADER_H_

#include "NFCReader.h"

class MockNFCReader : public NFCReader{

public:

    // Does nothing
    void Initialize() {}

    // Return a default value
    int Scan() { return -1;}

    // Does nothing
    void Stop() {}

    // Does nothing
    void Restart() {}

    /**
     * This method is only an overload test method.
     *
     * it emulates a scan with the id in parameter and start a transaction.
     *
     * @param id the id to scan.
     * @return none.
     */
    int Scan(int id) { return id;}
};


#endif // MOCKNFCREADER_H_
