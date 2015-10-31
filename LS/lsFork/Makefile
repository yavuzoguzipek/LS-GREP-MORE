CC          = gcc
CFLAGS      = -c
LDFLAGS     =
SOURCES     = lsFork.c 
OBJECTS     = $(SOURCES:.c=.o)
LIBRARIES   =
EXECUTABLE  = lsFork

.PHONY:         all clean

all: $(SOURCES) $(EXECUTABLE) $(LIBRARIES)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)
