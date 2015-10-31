CC          = gcc
CFLAGS      = -c
LDFLAGS     =
SOURCES     = myMore.c 
OBJECTS     = $(SOURCES:.c=.o)
LIBRARIES   =
EXECUTABLE  = myMore

.PHONY:         all clean

all: $(SOURCES) $(EXECUTABLE) $(LIBRARIES)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o $(EXECUTABLE)
