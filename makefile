YELLOW  := \033[1;33m
GREEN   := \033[1;32m
RED     := \033[1;31m
BLUE    := \033[1;34m
CYAN    := \033[1;36m
RESET   := \033[0m

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = twixt
SRC = main.c logic.c board.c
OBJ = $(SRC:.c=.o)

all: banner $(TARGET)

banner:
	@echo "$(CYAN)======================================$(RESET)"
	@echo "$(GREEN)        Building Twixt Game...       $(RESET)"
	@echo "$(CYAN)======================================$(RESET)"

$(TARGET): $(OBJ)
	@echo "$(YELLOW)[LINK]$(RESET) $@"
	@$(CC) $(OBJ) -o $(TARGET)
	@echo "$(GREEN)✔ Build Successful$(RESET)"

%.o: %.c game.h
	@echo "$(BLUE)[CC]$(RESET) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@echo "$(CYAN)Running Twixt...$(RESET)"
	@./$(TARGET)

clean:
	@echo "$(RED)Cleaning project...$(RESET)"
	@rm -f $(OBJ) $(TARGET)
	@echo "$(GREEN)✔ Clean Done$(RESET)"
