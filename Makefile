
SRCS = RSA_new.c RSA_small.c
OBJS = $(patsubst %.c,%,$(SRCS))

all: $(OBJS)

% : %.c
	gcc $< -o $@ -lgmp

clean:
	rm -f $(OBJS)
