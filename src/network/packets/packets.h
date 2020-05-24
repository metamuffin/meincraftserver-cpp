#ifndef _PACKETS_H_INCLUDED
#define _PACKETS_H_INCLUDED

#include <stdint.h>

typedef struct packet_t {
    int length;
    int id;
    uint8_t* data;
} packet;

// return 1 for sucess, 0 for error
int read_packet(packet* p, int data_len, uint8_t* raw_data);

// return 1 for success, 0 for more data, and -1 for invalid
// length; parses varints as well as varlongs
int read_varint(int64_t* ret, int* offset, uint8_t* p, int max_length);

#endif

