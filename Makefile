CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./include
SRCDIR = src
OBJDIR = obj
TARGET = sistema

SOURCES = main.c $(SRCDIR)/menu.c $(SRCDIR)/usuario.c $(SRCDIR)/paciente.c \
          $(SRCDIR)/medico.c $(SRCDIR)/consulta.c $(SRCDIR)/arquivo.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build complete! Run with: ./$(TARGET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Cleaned!"

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
