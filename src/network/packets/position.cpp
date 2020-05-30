
#include "position.hpp"

BlockPosition::BlockPosition(uint64_t)
{

}

BlockPosition::~BlockPosition()
{

}

uint64_t BlockPosition::getEncoded(){
    return ((x & 0x3FFFFFF) << 38) | ((z & 0x3FFFFFF) << 12) | (y & 0xFFF);
}

BlockPosition* BlockPosition::operator+(BlockPosition* other){
    return new BlockPosition(x+other->x,y+other->y,z+other->z);
}

