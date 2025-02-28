/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horussrv_mod_apptest.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 23/06/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSSRV_MOD_APPTEST_H
#define __HORUSSRV_MOD_APPTEST_H     "__HORUSSRV_MOD_APPTEST_H"

class CAppTest
{
private:
    void testSequences();
    void testUsers();
    void testTableSpace();
    void testTableMetadata();

public:
    CAppTest();
    ~CAppTest();

    void execute();
};

/* NEW_TYPE: CAppTest Pointer */

typedef CAppTest* CAppTestPtr_t;

#endif
