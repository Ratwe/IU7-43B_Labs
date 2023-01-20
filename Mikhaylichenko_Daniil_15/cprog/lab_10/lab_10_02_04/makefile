# Компилятор
CC := gcc

# Опции
CFLAGS := -std=c99 -Wall -Werror -pedantic
UFLAGS := -std=c99 -lcheck -lpthread -lrt

# Директории
SRC_DIR = ./src
OUT_DIR = ./out
UNIT_DIR = ./unit_tests

# Файлы для удаления
RM_FILES := $(OUT_DIR)/* app.exe unit_tests.exe clear_out.txt val.txt out.txt

# Общие Объектные файлы
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OUT_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c))
OBJS := $(filter-out $(OUT_DIR)/main.o,$(OBJS))
TEST_OBJS := $(patsubst $(UNIT_DIR)/%.c,$(OUT_DIR)/%.o,$(wildcard $(UNIT_DIR)/*.c))

.PHONY: release debug create_out_dir clean

# Релизная сборка
release: CFLAGS += -g0
release: app.exe

# Отладочная сбока
debug: CFLAGS += -g3 -DDEBUG
debug: app.exe

# Запуск модульных тестов
unit: UFLAGS += -lsubunit -lm
unit: CFLAGS += -g3
unit: unit_tests.exe
	./unit_tests.exe

# Компиляция программа
app.exe: $(OBJS) $(OUT_DIR)/main.o
	$(CC) $(CFLAGS) $(OBJS) $(OUT_DIR)/main.o -o $@

# Компиляция модульных тестов
unit_tests.exe: $(OBJS) $(TEST_OBJS)
	$(CC) $^ -o $@ $(UFLAGS)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c create_out_dir
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/%.o: $(UNIT_DIR)/%.c create_out_dir
	$(CC) $(CFLAGS) -c $< -o $@

create_out_dir:
	mkdir -p $(OUT_DIR)

clean:
	$(RM) $(RM_FILES)
