/*
 * Copyright(C) 2020 TLMV Consultoria e Sistemas EIRELI
 *
 * horuswrk_cmd_dispatch.h
 * emissao: Luiz Marcio Faria de Aquino Viana, M.Sc. - 22/12/2020
 * revisoes: ...
 *
 */

#ifndef __HORUSWRK_CMD_DISPATCH_H
#define __HORUSWRK_CMD_DISPATCH_H               "__HORUSWRK_CMD_DISPATCH_H"

class CCmdDispatch
{
private:
    str_t m_chname;
    int m_reqnum;

public:
    CCmdDispatch(char* chname);

    ~CCmdDispatch();

    /* Local Methodes */

    int serverTerminate();

    /* Remote Unit Methodes */
    
    //MKDIR
    int doActionTS1MkDir();
    //UPLOAD
    int doActionTS1Upload();
    //DOWNLOAD
    int doActionTS1Download();
    //CONVERT_MOD
    int doActionTS1Convert();
    //REPROJ_MOD
    int doActionTS1Reproj();
    //SIMPL_MOD
    int doActionTS1Simpl();

    /* Getters/Setters */

    char* getChName();

    int getReqNum();

};

/* NEW_TYPE: CCmdDispatch Pointer */

typedef CCmdDispatch* CCmdDispatchPtr_t;

#endif
