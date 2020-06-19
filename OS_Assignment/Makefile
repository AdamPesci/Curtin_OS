#Compiler and Flags
CC = gcc
CFLAGS = -Wall

#Targets
EXEC := scheduler
DEBUG := scheduler_debug
DIR := Directories

#all .o files 
all_OBS := ./src/linked_list.o ./src/ready_queue.o ./src/data.o ./src/data_debug.o ./src/driver.o
#all .o files used by EXEC
exec_OBS := ./src/linked_list.o ./src/ready_queue.o ./src/data.o ./src/driver.o
#all .o files used by DEBUG
debug_OBS := ./src/linked_list.o ./src/ready_queue.o ./src/data_debug.o ./src/driver.o

############################################################

#all command to create all programs and move into directories
all: $(EXEC) $(DEBUG) $(DIR)
	mv -v $(all_OBS) ./build
	mv -v $(EXEC) ./dist
	mv $(DEBUG) ./dist
	cp -rv ./resources/* ./dist/ 

#Command to create main driver program Scheduler
$(EXEC) : $(exec_OBS)
	$(CC) $(CFLAGS) $(exec_OBS) -lpthread -o $(EXEC)


#Command to create a debug version of Scheduler
$(DEBUG): $(debug_OBS)
	$(CC) $(CFLAGS) $(debug_OBS) -lpthread -o $(DEBUG)

#Command to create directories "build" and "dist"
$(DIR):
	mkdir -p build
	mkdir -p dist

############################################################

#Command to create linked list object file
linked_list.o: ./src/linked_list.c ./src/linked_list.h
	$(CC) -c ./src/linked_list.c $(CFLAGS)

#Command to create ready_queue object file
ready_queue.o: ./src/ready_queue.c ./src/ready_queue.h ./src/linked_list.h
	$(CC) -c ./src/ready_queue.c $(CFLAGS)

#Command to create data object file
data.o: ./src/data.c ./src/data.h ./src/ready_queue.h ./src/linked_list.h
	$(CC) -c ./src/data.c $(CFLAGS)
#Command to create data_debug object file
data_debug.o: ./src/data_debug.c ./src/data.h ./src/ready_queue.h ./src/linked_list.h
	$(CC) -c ./src/data_debug.c $(CFLAGS)

#Command to create main driver for scheduler object file
driver.o: ./src/driver.c ./src/linked_list.h ./src/ready_queue.h ./src/data.h
	$(CC) -c ./src/driver.c $(CFLAGS)

############################################################

#Command to clean directories which contain all object and executable files
clean:
	rm -rf dist build



