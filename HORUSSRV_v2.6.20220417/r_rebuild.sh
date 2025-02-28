#!/bin/sh
HORUSSRV_HOME=/home/lmarcio/101-UFRJ/999-Tese_Doutorado-Projeto_Horus-Luiz_Marcio_Faria_Aquino_Viana/HORUSSRV_v2.0/

CFGFILE=./remoteunit_conf.cfg

SRCDIR=$HORUSSRV_HOME/Appl/Servidor/HORUSSRV
DATADIR=$HORUSSRV_HOME/Data/
EXEFILE=$SRCDIR/horussrv
LOGFILE=$SRCDIR/horussrv-$(date +%Y%m%d_%H%M%S).log

cd $SRCDIR

make clean
make all

# SAMPLE DATABASE DELETE
rm -f $DATADIR/*dat
rm -f $DATADIR/HORUSSRV11/*dat

# SAMPLE DATABASE REBUILD
HORUS_OPTS=-r

$EXEFILE $CFGFILE $HORUS_OPTS

cd $SRCDIR

