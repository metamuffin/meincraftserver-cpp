#include "packets.hpp"

#include <stdint.h>

int read_packet(packet* p, int data_len, uint8_t* raw_data) {
    int64_t packet_id = -1;
    int64_t packet_length = 0;
    int data_offset = 0;
    int packet_length_read_status = read_varint(&packet_length, &data_offset, raw_data, data_len);
    if (packet_length_read_status < 1) return packet_length_read_status;
    int packet_id_read_status = read_varint(&packet_id, &data_offset, raw_data, data_len);
    if (packet_id_read_status < 1) return packet_length_read_status;
    
}

int read_varint(int64_t* ret, int* offset, uint8_t* p, int max_length) {
    int num_read = 0;
    *ret = 0;
    uint8_t read;
    do {
        if (num_read >= max_length) return 0;
        if (num_read >= 10) return -1;
        read = p[num_read];
        int val = (read & 0x7F);
        *ret |= (val << (7 * num_read));
        num_read += 1;
    } while ((read & 0x80) != 0);
    return 1;
}

void write_varint(int64_t value, uint8_t* target, int* bytes_written) {
    *bytes_written = 0;
    do {
        uint8_t t = (uint8_t) (value & 0x7F);
        value >>= 7;
        if (value != 0) {
            t |= 0x80;
        }
        target[*bytes_written] = t;
        *bytes_written += 1;
    } while(value != 0);
}

