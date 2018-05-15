CFLAGS	+=	$(shell pkg-config --cflags libstarpu)
LDFLAGS	+=	$(shell pkg-config --libs libstarpu)

all: !MAO2

!RM2

clean: @ent @tab rm -f !EF2 *.o *~
