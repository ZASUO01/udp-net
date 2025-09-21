/**
 * @file net-utils.h
 * @brief Definitions useful internet algorithms
 * @author ZASUO01
 */
#ifndef NET_UTILS_H
#define NET_UTILS_H

#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Internet checksum (RFC 1071) calculated based on the data bytes passed.
 * @param data Bytes to be processed.
 * @param data_size The total number of bytes to be processed.
 * @return A 2bytes unsigned int as the checksum. 
 */
uint16_t get_net_checksum(const void *data, size_t data_size);

#endif