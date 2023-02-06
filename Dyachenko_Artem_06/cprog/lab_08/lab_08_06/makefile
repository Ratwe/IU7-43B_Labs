INCDIR := ./inc
SRCDIR := ./src
OUTDIR := ./out
UNITDIR := ./unit_tests

vpath %.c $(SRCDIR) $(UNITDIR)

CC := gcc
CFLAGS := -std=c99 -I $(INCDIR) -Werror -Wall -Wextra -Wfloat-equal -Wfloat-conversion -Wvla
LDFLAGS := -lm

SRCS := $(wildcard $(SRCDIR)/*.c)  # список файлов .c из src
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.o)  # список файлов .o из src

TEST_SRCS := $(wildcard $(UNITDIR)/*.c)
ALL_OBJS := $(OBJS) $(TEST_SRCS:$(UNITDIR)/%.c=$(OUTDIR)/%.o)
DEPS := $(ALL_OBJS:.o=.d)
TEST_OBJS := $(filter-out $(OUTDIR)/main.o, $(ALL_OBJS))

.PHONY: release
release: app.exe

.PHONY: debug
debug: CFLAGS += -O0 -g3 -fsanitize=address -DDEBUG
debug: LDFLAGS += -fsanitize=address -static-libsan
debug: app.exe

.PHONY: address
address: CFLAGS += -O0 -g3 -fsanitize=address
address: LDFLAGS += -fsanitize=address -static-libsan
address: app.exe

.PHONY: gcov
gcov: CFLAGS += -O0 -g3 --coverage
gcov: LDFLAGS += --coverage
gcov: app.exe

.PHONY: func
func:
	./func_tests/scripts/func_tests.sh

.PHONY: collect_coverage
collect_coverage:
	cd out && gcov -o ./ ../$(SRCDIR)/*.c

.PHONY: unit
unit: unit_tests.exe

.PHONY: all
all: debug
all: func
all: unit
all:
	./unit_tests.exe

app.exe: $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

unit_tests.exe: $(TEST_OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OUTDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUTDIR)/%.d: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -M $< > $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -fr $(OUTDIR)
	rm -f ./*.exe
