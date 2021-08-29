
CFLAGS := -Wall -Werror -g


iio_CFLAGS := $(shell pkg-config --cflags libiio)
iio_LDFLAGS := $(shell pkg-config --libs libiio)

airspyhf_CFLAGS := $(shell pkg-config --cflags libairspyhf)
airspyhf_LDFLAGS := $(shell pkg-config --libs libairspyhf)



bin := iio_context iio-monitor ad9361-iiostream airspyhf_rx

iio_context.o_CFLAGS := $(iio_CFLAGS)
iio_context_LDFLAGS := $(iio_LDFLAGS)
iio-monitor.o_CFLAGS := $(iio_CFLAGS)
iio-monitor_LDFLAGS := $(iio_LDFLAGS) -lcdk -lcurses -lpthread
ad9361-iiostream_CFLAGS := $(iio_CFLAGS)
ad9361-iiostream_LDFLAGS := $(iio_LDFLAGS)
airspyhf_rx.o_CFLAGS := $(airspyhf_CFLAGS)
airspyhf_rx_LDFLAGS := $(airspyhf_LDFLAGS) -lm



build: $(bin)

$(bin): %: %.o
	$(CC) $(CFLAGS) $($@_CFLAGS) -o $@ $^ $($@_LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $($@_CFLAGS) -c -o $@ $<


cleaner: clean

clean:
	rm -f *.o $(bin)

