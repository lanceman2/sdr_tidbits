// Trying to figure out what a iio_device is.  For example:
//
//    bash % iio_readdev -a local <iio_device>
//
// WTF is <iio_device>
//
//
// Real running example:
//
//  lance@herbie:~/git/2021_08_saltenna/tests$ iio_readdev -a local local
//  Using auto-detected IIO context at URI "local:"
//  Device local not found
//
//
// The magic that this code did was find device IDs with
// iio_device_get_id().  We could than get a clue as to what <iio_device>
// is in the arguemnts to the iio_readdev program:
//
//   % iio_readdev -a usb <iio_device>
//
//
//  Plug in the USB plutoSDR and run:
//
//
//   %  iio_readdev -a usb iio:device3 | hexdump -v
//
//
//   iio:device3  is the device ID whatever that is.
//   The URI is like "usb:1.22.5" but this is auto finding that.
//
//
//
// So how the hell was I suppose to find the magic iio_device strings,
// given I had no clue what there where or what any thing.  i.e. The
// documentation sucked.
//
// Looking at the libiio API gave me a better feel as to what
// documentation was talking about.
//


#include <stdio.h>

#include <iio.h>


ssize_t write_attr(struct iio_device *dev, const char *attr,
        void *buf, size_t len, FILE *f) {

    fprintf(f, "  attr= %s\n", attr);
    return 0;
}



int main(void) {

    unsigned int major, minor;
    char git_tag[8];

    iio_library_get_version(&major, &minor, git_tag);

    fprintf(stderr, "iio_library_get_version()="
            "(major=%u, minor=%u, git_tag=\"%.8s\")\n",
            major, minor, git_tag);

    const char *backends[] = {
        // WTF is a good backend string:
        "local:",
        "local",
        "foo:",
        0 // null terminate
    };

    for(const char **backend = backends; *backend; ++backend)
        fprintf(stdout, "iio_has_backend(\"%s\") = %d\n",
                *backend,
                iio_has_backend(*backend));
    // Running the above showed "local" is a backend we have.
    //

    // See all backends
    fprintf(stderr, "\n List of All BACKENDs \n -----------------------\n");
    for(unsigned int i=iio_get_backends_count()-1; i!=-1; --i)
        fprintf(stderr, " \"%s\"\n",  iio_get_backend(i));
    fprintf(stderr, "\n");
    // WTF is a xml backend

    struct iio_context *ctx;

    //ctx = iio_create_default_context();
    //ctx = iio_create_local_context();

    // TODO: We got this URI "usb:1.2x.5" from running
    //
    //    iio_info -S
    //
    // We need to get it by using the libiio API in this C code.
    //
    ctx = iio_create_context_from_uri("usb:");
    //ctx = iio_create_context_from_uri("local:");


    fprintf(stderr, "dev =  iio_context_find_device(ctx, \"ad9361-phy\")=%p\n",
            iio_context_find_device(ctx, "ad9361-phy"));

    fprintf(stderr, "iio_context_find_device(ctx, \"cf-ad9361-dds-core-lpc\")=%p\n",
            iio_context_find_device(ctx, "cf-ad9361-dds-core-lpc"));

    if(!ctx) {
        fprintf(stderr, "iio_create_context_*() failed\n");
        return 1;
    }

    fprintf(stderr, "ctx=%p name=\"%s\"\ndesc=\"%s\"\n"
            "number of attrs=%u\n"
            "\n",
            ctx, iio_context_get_name(ctx),
            iio_context_get_description(ctx),
            iio_context_get_attrs_count(ctx));

    unsigned int dcount = iio_context_get_devices_count(ctx);
    struct iio_device *dev = 0;

    fprintf(stderr, "get_devices_count=%u\n", dcount);
    for(unsigned int i=0; i<dcount; ++i) {
        dev = iio_context_get_device(ctx, i);
        if(dev)
            fprintf(stderr, "%p  device_id=\"%s\"\n", dev,  iio_device_get_id(dev));
        else
            goto cleanup_dev;
         iio_device_attr_write_all(dev,
                 (ssize_t (*)(struct iio_device *dev, const char *attr,
                              void *buf, size_t len, void *d)) write_attr, stderr);
    }

    fprintf(stderr, "\n");


cleanup_dev:

    if(!dev)
        fprintf(stderr, "iio_context_get_device() failed\n");
    // WTF: is there a need to destroy a iio_device


//no_devs:

    iio_context_destroy(ctx);
    ctx = 0;

    fprintf(stderr, "DONE\n");

    return 0;
}
