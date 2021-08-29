// Reads bits in like for example /dev/urandom
//
// Writes floats converted from 8 signed bit chunks with max and min like
// +1.0 and -1.0
//
// Reads and converts every bit that comes in.  The float will have what
// looks like 8 bit resolution in the range -1.0 and +1.0
//
//
//     UINT8_MAX = 255
//
//
// Runnable shell examples:
//
//   ./8bitsToEachFloat < /dev/urandom | hexdump -v
//
//   ./8bitsToEachFloat < /dev/urandom | grrun ./scope.py
//
//   airspyhf_rx -r stdout | grrun ./scope.py
//

#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>


int main(void) {

    size_t i;
    const size_t len = 1024;
    const float scale = UINT8_MAX/2.0F;
    uint8_t in[len];
    float out[len];
    // Read until we can't:
    while((i = fread(in, sizeof(*in), len, stdin)) == len) {
        for(i=0; i < len; ++i) {
            // We transform the bits to a float this way:
            out[i] = in[i];
            // Now we have  float, so scale it now.
            out[i] -= scale;
            out[i] /= scale;
            // TODO: Can the floating point round off make the values
            // larger than 1.0 or smaller than -1.0.  That could be easy
            // to test, but may be architecture dependent.
        }
        if(len != fwrite(out, sizeof(*out), len, stdout))
            // failure:
            return 3;
    }

    return 0;
}
