C=cc
null_var = "Do null, write \"make compile_server\" or \"make compile_client\""
inc = include/
src = src/
linc = library/include/
lsrc = library/src/

server_h = $(inc)server.h
server_o = server.o
server_c = $(src)server.c
dependence_server_h = $(linc)message.h $(linc)tcp_socket.h $(linc)hashtable.h $(linc)infoList.h $(linc)infoHashtable.h $(linc)list.h $(linc)TBST.h $(linc)TInfoBST.h
dependence_server_o = message.o tcp_socket.o hashtable.o infoList.o infoHashtable.o list.o TBST.o TInfoBST.o
dependence_server_c = $(lsrc)message.c $(lsrc)tcp_socket.c $(lsrc)hashtable.c $(lsrc)infoList.c $(lsrc)infoHashtable.c $(lsrc)list.c $(lsrc)TBST.c $(lsrc)TInfoBST.c

client_h = $(inc)client.h
client_o = client.o
client_c = $(src)client.c
dependence_client_h = $(linc)message.h $(linc)tcp_socket.h
dependence_client_o = message.o tcp_socket.o
dependence_client_c = $(lsrc)message.c $(lsrc)tcp_socket.c

compile: compile_client compile_server compile_libraries

null:
	echo 

compile_server: $(server_o) $(dependence_server_o)
	$(C) -c -I $(inc) -I $(linc) $(server_c)
	$(C) -o server $(server_o) $(dependence_server_o) -lpthread

$(server_o) : $(dependence_server_h)

$(dependence_server_o) : $(dependence_server_h) $(dependence_server_c)
	$(C) -c -I $(inc) -I $(linc) $(dependence_server_c)

compile_client: $(client_o) $(dependence_client_o)
	$(C) -c -I $(inc) -I $(linc) $(client_c)
	$(C) -o client $(client_o) $(dependence_client_o) -lpthread

$(client_o) : $(dependence_client_h)

$(dependence_client_o) : $(dependence_client_h) $(dependence_client_c)
	$(C) -c -I $(inc) -I $(linc) $(dependence_client_c)

compile_libraries: 
	-cd ./library && $(MAKE) all_libraries

clean:
	-rm server client *.o 
	-cd ./library && $(MAKE) clean
	
	
	