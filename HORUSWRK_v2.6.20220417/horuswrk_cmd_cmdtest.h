/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_cmdtest.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 22/12/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CMD_CMDTEST_H
#define __HORUSWRK_CMD_CMDTEST_H                 "__HORUSWRK_CMD_CMDTEST_H"

class CCmdTest
{
private:
    CCmdDispatch* m_pDispatch;
    str_t m_session;

    // Main Tests
    //
    void testMkDir();
    void testUpload();
    void testDownload();
    void testConvert();
    void testReproj();
    void testSimpl();

    void testTerminate();

public:
    CCmdTest();
    ~CCmdTest();

    /* Methodes */

    void execute();

};

/* NEW_TYPE: CCmdTest Pointer */

typedef CCmdTest* CCmdTestPtr_t;

#endif
