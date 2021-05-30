CC		 	:= gcc
TARGET 	:= grafo
SRCDIR 	:= src
INCDIR 	:= $(SRCDIR)
OBJDIR 	:= obj
ZIPREFIX := ExamenTC-DiegoRamos21951033
CFLAGS	:= `pkg-config libgvc --cflags` 
LDFLAGS	:= `pkg-config libgvc --libs`

SRC := $(shell find $(SRCDIR) -type f -name "*.c")
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRC:.c=.o))

all: $(TARGET) 

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@printf "Compilando 'src' al ejecutable '\033[92m$(TARGET)\033[0m'...\n"

$(OBJ): obj/%.o : src/%.c | $(OBJDIR)
	$(CC) -c $< -I$(INCDIR) -o $@

$(addprefix $(OBJDIR)/, main.o ): $(addprefix $(SRCDIR)/, grafo.h)
$(addprefix $(OBJDIR)/, grafo.o): $(addprefix $(SRCDIR)/, grafo.h common.h)

$(OBJDIR): 
	@mkdir -p $(OBJDIR)

.PHONY: clean submit

clean:
	@rm -vr $(OBJDIR)

submit: Makefile README.txt $(SRCDIR)/*
	find . -name $(ZIPREFIX).zip -exec rm {} \;
	zip -r $(ZIPREFIX).zip $^
