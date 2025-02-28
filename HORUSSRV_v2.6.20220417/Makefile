
CC = /usr/bin/gcc
#CFLAGS = -ggdb -O0 -Wall -pthread -pg --coverage
#LFLAGS = -ggdb -lstdc++ -lpthread -pg --coverage
CFLAGS = -O2 -Wall -pthread
LFLAGS = -lstdc++ -lpthread

OBJS =	horussrv_cfg_configtag.o		\
		horussrv_cfg_context.o 			\
		horussrv_cfg_hostserver.o 		\
		horussrv_cfg_listener.o 		\
		horussrv_cfg_remoteunit.o 		\
		horussrv_cfg_config.o 			\
		horussrv_mod_error.o 			\
		horussrv_mod_util.o 			\
		horussrv_mod_xmlutil.o 			\
		horussrv_mod_sequence.o 		\
		horussrv_mod_users.o 			\
		horussrv_mod_tablespace.o 		\
		horussrv_mod_tablemetadata.o 	\
		horussrv_mod_apptest.o 			\
		horussrv_mod_appmain.o 			\
		horussrv_cmd_parser.o 			\
		horussrv_cmd_response.o 		\
		horussrv_cmd_request.o 			\
		horussrv_cmd_exec.o 			\
		horussrv_cmd_dispatch.o 		\
		horussrv_cmd_cmdtest.o 			\
		horussrv_cmd_listener.o 		\
		horussrv.o

all:	$(OBJS)
		$(CC) $(OBJS) $(LFLAGS) -o horussrv

bak:
		rm -f *~

clean:
		rm -f horussrv
		rm -f *o
		rm -f *gcda
		rm -f *out

rebuild:
		make clean
		make all

log:
		rm *.log

horussrv.o: horussrv_cfg_all.h 				\
			horussrv_cfg_defs.h				\
			horussrv_cfg_configtag.h		\
			horussrv_cfg_configtag.cpp		\
			horussrv_cfg_context.h			\
			horussrv_cfg_context.cpp		\
			horussrv_cfg_hostserver.h		\
			horussrv_cfg_hostserver.cpp		\
			horussrv_cfg_listener.h			\
			horussrv_cfg_listener.cpp		\
			horussrv_cfg_remoteunit.h		\
			horussrv_cfg_remoteunit.cpp		\
			horussrv_cfg_config.h			\
			horussrv_cfg_config.cpp			\
			horussrv_mod_all.h 				\
			horussrv_mod_defs.h				\
			horussrv_mod_sampledata.h		\
			horussrv_mod_error.h			\
			horussrv_mod_error.cpp			\
			horussrv_mod_util.h				\
			horussrv_mod_util.cpp			\
			horussrv_mod_xmlutil.h			\
			horussrv_mod_xmlutil.cpp		\
			horussrv_mod_sequence.h			\
			horussrv_mod_sequence.cpp		\
			horussrv_mod_users.h			\
			horussrv_mod_users.cpp			\
			horussrv_mod_tablespace.h		\
			horussrv_mod_tablespace.cpp		\
			horussrv_mod_tablemetadata.h	\
			horussrv_mod_tablemetadata.cpp	\
			horussrv_mod_apptest.h			\
			horussrv_mod_apptest.cpp		\
			horussrv_mod_appmain.h			\
			horussrv_mod_appmain.cpp		\
			horussrv_cmd_all.h 				\
			horussrv_cmd_defs.h				\
			horussrv_cmd_rescode.h			\
			horussrv_cmd_parser.h			\
			horussrv_cmd_parser.cpp			\
			horussrv_cmd_response.h			\
			horussrv_cmd_response.cpp		\
			horussrv_cmd_request.h			\
			horussrv_cmd_request.cpp		\
			horussrv_cmd_exec.h				\
			horussrv_cmd_exec.cpp			\
			horussrv_cmd_dispatch.h			\
			horussrv_cmd_dispatch.cpp		\
			horussrv_cmd_cmdtest.h			\
			horussrv_cmd_cmdtest.cpp		\
			horussrv_cmd_listener.h			\
			horussrv_cmd_listener.cpp		\
			horussrv.cpp
			$(CC) $(CFLAGS) -c horussrv_cfg_configtag.cpp
			$(CC) $(CFLAGS) -c horussrv_cfg_context.cpp			
			$(CC) $(CFLAGS) -c horussrv_cfg_hostserver.cpp		
			$(CC) $(CFLAGS) -c horussrv_cfg_listener.cpp			
			$(CC) $(CFLAGS) -c horussrv_cfg_remoteunit.cpp	
			$(CC) $(CFLAGS) -c horussrv_cfg_config.cpp			
			$(CC) $(CFLAGS) -c horussrv_mod_error.cpp			
			$(CC) $(CFLAGS) -c horussrv_mod_util.cpp				
			$(CC) $(CFLAGS) -c horussrv_mod_xmlutil.cpp			
			$(CC) $(CFLAGS) -c horussrv_mod_sequence.cpp			
			$(CC) $(CFLAGS) -c horussrv_mod_users.cpp			
			$(CC) $(CFLAGS) -c horussrv_mod_tablespace.cpp		
			$(CC) $(CFLAGS) -c horussrv_mod_tablemetadata.cpp	
			$(CC) $(CFLAGS) -c horussrv_mod_apptest.cpp			
			$(CC) $(CFLAGS) -c horussrv_mod_appmain.cpp			
			$(CC) $(CFLAGS) -c horussrv_cmd_parser.cpp			
			$(CC) $(CFLAGS) -c horussrv_cmd_response.cpp			
			$(CC) $(CFLAGS) -c horussrv_cmd_request.cpp			
			$(CC) $(CFLAGS) -c horussrv_cmd_exec.cpp				
			$(CC) $(CFLAGS) -c horussrv_cmd_dispatch.cpp			
			$(CC) $(CFLAGS) -c horussrv_cmd_cmdtest.cpp			
			$(CC) $(CFLAGS) -c horussrv_cmd_listener.cpp			
			$(CC) $(CFLAGS) -c horussrv.cpp
