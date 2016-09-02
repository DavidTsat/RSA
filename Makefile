
SRCS = RSA_source/RSA.c RSA_source/RSA_without_gmp_lib/RSA_small.c
OBJS = $(patsubst %.c,%,$(SRCS))

all: $(OBJS)

% : %.c
	gcc $< -o $@ -lgmp

clean:
	rm -f $(OBJS)
