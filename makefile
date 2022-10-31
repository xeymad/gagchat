C=cc
null_var = "Do null, write \"make compile_server\" or \"make compile_client\""
inc = include/
src = src/

server_h = $(inc)server.h
server_o = server.o
server_c = $(src)server.c
dependence_server_h = $(inc)message.h $(inc)tcp_socket.h
dependence_server_o = message.o tcp_socket.o
dependence_server_c = $(src)message.c $(src)tcp_socket.c

client_h = $(inc)client.h
client_o = client.o
client_c = $(src)client.c
dependence_client_h = $(inc)message.h $(inc)tcp_socket.h
dependence_client_o = message.o tcp_socket.o
dependence_client_c = $(src)message.c $(src)tcp_socket.c


null:
	echo 

compile_server: $(server_o) $(dependence_server_o)
	$(C) -c -I $(inc) $(server_c)
	$(C) -o server $(server_o) $(dependence_server_o)

$(server_o) : $(dependence_server_h)

$(dependence_server_o) : $(dependence_server_h) $(dependence_server_c)
	$(C) -c -I $(inc) $(dependence_server_c)

compile_client: $(client_o) $(dependence_client_o)
	$(C) -c -I $(inc) $(client_c)
	$(C) -o client $(client_o) $(dependence_client_o)

$(client_o) : $(dependence_client_h)

$(dependence_client_o) : $(dependence_client_h) $(dependence_client_c)
	$(C) -c -I $(inc) $(dependence_client_c)

compile_libraries: 
	-cd ./library && $(MAKE) all_libraries

clean:
	-rm server client *.o 
	-cd ./library && $(MAKE) clean
	
	
	