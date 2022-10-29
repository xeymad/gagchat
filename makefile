C=cc
null_var = "Do null, write \"make compile_server\" or \"make compile_client\""
inc = include/
src = src/

server_h = server.h
server_o = server.o
dependence_server_h = utils.h
dependence_server_o = utils.o

client_h = $(inc)client.h
client_o = client.o
client_c = $(src)client.c
dependence_client_h = $(inc)message.h
dependence_client_o = message.o
dependence_client_c = $(src)message.c


null:
	echo 

# compile_server: $(server_o) $(dependence_server_o)
# 	$(C) -o server $(server_o) $(dependence_server_o)

# $(server_o) : $(dependence_server_h) 

compile_client: $(client_o) $(dependence_client_o)
	$(C) -c -I $(inc) $(client_c)
	$(C) -o client $(client_o) $(dependence_client_o)

$(client_o) : $(dependence_client_h)

$(dependence_client_o) : $(dependence_client_h) $(dependence_client_c)
	$(C) -c -I $(inc) $(dependence_client_c)

clean: 
	rm server client *.o