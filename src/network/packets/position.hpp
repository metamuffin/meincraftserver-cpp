
#include <stdint.h>

typedef uint64_t block_position_t;

block_position_t position_from_xyz(int x, int y, int z);

block_position_t add_position(block_position_t a, int bx, int by, int bz);
block_position_t add_position(block_position_t a, block_position_t b);
