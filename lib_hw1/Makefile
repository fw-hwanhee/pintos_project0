TARGET = testlib
OBJECTS = list.o hash.o bitmap.o testlib.o

all: $(TARGET)

$(TARGET): $(OBJECTS) 
	$(CC) -o $@ $^

clear:
	rm -rf $(OBJECTS) $(TARGET)

new:
	$(MAKE) clear
	$(MAKE)
