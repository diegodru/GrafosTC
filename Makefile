CC		 	:= gcc
TARGET 	:= regex
SRCDIR 	:= src
INCDIR 	:= $(SRCDIR)
OBJDIR 	:= obj
ZIPREFIX := ExamenTC-DiegoRamos21951033

SRC := $(shell find $(SRCDIR) -type f -name "*.c")
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRC:.c=.o))

all: $(TARGET) 

$(TARGET): $(OBJ)
	$(CC) -o $@ $^
	@printf "Compilando 'src' al ejecutable '\033[92m$(TARGET)\033[0m'...\n"

$(OBJ): obj/%.o : src/%.c | $(OBJDIR)
	$(CC) -c $< -I$(INCDIR) -o $@

$(addprefix $(OBJDIR)/, main.o verificaciones.o menu.o): $(addprefix $(SRCDIR)/, defs.h common.h)
$(addprefix $(OBJDIR)/, menu.o): $(addprefix $(SRCDIR)/, menu.h common.h)

$(OBJDIR): 
	@mkdir -p $(OBJDIR)

.PHONY: clean submit

clean:
	@rm -vr $(OBJDIR)

submit: Makefile README.txt $(SRCDIR)/*
	find . -name $(ZIPREFIX).zip -exec rm {} \;
	zip -r $(ZIPREFIX).zip $^
