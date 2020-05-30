
#include <stdint.h>

class BlockPosition
{
public:
    BlockPosition(uint64_t encoded);
    BlockPosition(int32_t x, int16_t y, int32_t z);
    ~BlockPosition();

    BlockPosition* operator+(BlockPosition* b);

    uint64_t getEncoded();

    int32_t x;
    int16_t y;
    int32_t z;


};