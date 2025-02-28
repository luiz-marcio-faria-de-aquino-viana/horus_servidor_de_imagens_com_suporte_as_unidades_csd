#!/bin/sh
HORUSSRV_HOME=/home/lmarcio/101-UFRJ/999-Tese_Doutorado-Projeto_Horus-Luiz_Marcio_Faria_Aquino_Viana/HORUSSRV_v2.0

CFGFILE=./remoteunit_conf.cfg

SRCDIR=$HORUSSRV_HOME/Appl/Servidor/HORUSSRV
EXEFILE=$SRCDIR/horussrv
LOGFILE=$SRCDIR/horussrv-$(date +%Y%m%d_%H%M%S).log

HORUS_OPTS=-l -e

DEGUG_EXE=/usr/bin/ddd

cd $SRCDIR
echo "$EXEFILE $CFGFILE $HORUS_OPTS"
#$DEGUG_EXE $CFGFILE $HORUS_OPTS > $LOGFILE
$DEGUG_EXE $EXEFILE &
cd $SRCDIR

