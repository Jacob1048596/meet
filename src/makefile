LDFLAGS=-L /usr/lib64/mysql
BIN=ais_svr
CC=g++
.PHONY:$(BIN)
$(BIN):ais_system.cpp
	$(CC) $^ -o $@ $(LDFLAGS) -lmysqlclient -std=c++11

.PHONY:clean
