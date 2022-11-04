C=cc
null_var = "Do null, write \"make compile_server\" or \"make compile_client\""
inc = include/
src = src/
linc = library/include/
lsrc = library/src/

BUILD_LIBRARIES_DIR_H := ./library/include
BUILD_LIBRARIES_DIR_O := ./library/build

OBJS := $(shell find $(BUILD_LIBRARIES_DIR_O) -name '*.o')
HEADERS := $(shell find $(BUILD_LIBRARIES_DIR_H) -name '*.o')


server_h = $(inc)server.h
server_o = server.o
server_c = $(src)server.c

client_h = $(inc)client.h
client_o = client.o
client_c = $(src)client.c

compile: compile_libraries
	@$(MAKE) compile_server 
	@$(MAKE) compile_client

null:
	echo 

compile_server: $(HEADERS) 
	$(C) -c -I $(inc) -I $(linc) $(server_c)
	$(C) -o server $(server_o) $(OBJS) -lpthread -lm
	@rm $(server_o)

$(server_o) : $(HEADERS)

compile_client: $(HEADERS)
	$(C) -c -I $(inc) -I $(linc) $(client_c)
	$(C) -o client $(client_o) $(OBJS) -lpthread -lm
	@rm $(client_o)


compile_libraries: 
	-cd ./library && $(MAKE) all_libraries

clean:
	-rm -f server client *.o 
	@cd ./library && $(MAKE) clean
	
	
	