
#include "position.hpp"

block_position_t position_from_xyz(int x, int y, int z) {
    // from https://wiki.vg/Protocol#Position
    return ((x & 0x3FFFFFF) << 38) | ((z & 0x3FFFFFF) << 12) | (y & 0xFFF);
}

block_position_t add_position(block_position_t a, int bx, int by, int bz){
    uint64_t c = a;
    int ccx = (c >> 38);
    int ccy = (c & 0xFFF);
    int ccz = (c << 26 >> 38);
    c |= (ccx | (ccx + bx) & 0x3FFFFFF) << 38;
    c |= (ccy | (ccy + by) & 0xFFF    );
    c |= (ccz | (ccz + bz) & 0x3FFFFFF) << 38;
    return c;
}

