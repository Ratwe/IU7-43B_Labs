# Компилятор
CC := gcc

# Опции
CFLAGS := -std=gnu99 -Wall -Werror -pedantic

# Директории
SRC_DIR = ./src
OUT_DIR = ./out

# Файлы для удаления
RM_FILES := $(OUT_DIR)/* *.exe

# Общие Объектные файлы
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OUT_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c))
OBJS := $(filter-out $(OUT_DIR)/main.o,$(OBJS))

.PHONY: release debug create clean

# Релизная сборка
release: CFLAGS += -g0
release: app.exe

# Отладочная сбока
debug: CFLAGS += -g3 -DDEBUG
debug: app.exe

# Запуск модульных тестов
unit: unit_tests.exe
	./unit_tests.exe

# Компиляция программа
app.exe: create_out_dir $(OBJS) $(OUT_DIR)/main.o
	$(CC) $(CFLAGS) $(OBJS) $(OUT_DIR)/main.o -o $@

# Компиляция модульных тестов
unit_tests.exe: $(OBJS) $(TEST_OBJS)
	$(CC) $^ -o $@ $(UFLAGS)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: $(UNIT_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

create_out_dir:
	mkdir -p $(OUT_DIR)

clean:
	$(RM) $(RM_FILES)
