CC          = gcc
CFLAGS      = -c
LDFLAGS     =
SOURCES     = grepMeFork.c 
OBJECTS     = $(SOURCES:.c=.o)
LIBRARIES   =
EXECUTABLE  = grepMeFork

.PHONY:         all clean

all: $(SOURCES) $(EXECUTABLE) $(LIBRARIES)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)
