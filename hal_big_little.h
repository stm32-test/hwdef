/*
 * hal_big_little.h
 *
 *  Created on: Nov 11, 2019
 *      Author: caijie
 */

#ifndef BIG_LITTLE_H_
#define BIG_LITTLE_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "hwdef.h"


#ifdef HAL_BIG_LITTLE
#if NATIVE_BIG_ENDIAN


/**
 * ����ֽ���һλ
 */
static inline void byte_swap_1(void *dst, const uint8_t *src, uint16_t *ofs)
{
    uint8_t *buf = (uint8_t *)dst;
    buf[0] = src[0];
    *ofs = *ofs + 1;
}
/**
 * ����ֽ����λ
 */
static inline void byte_swap_2(void *dst, const uint8_t *src, uint16_t *ofs)
{
    uint8_t *buf = (uint8_t *)dst;
    buf[0] = src[1];
    buf[1] = src[0];
    *ofs = *ofs + 2;
}
/**
 * ����ֽ�����λ
 */
static inline void byte_swap_4(void *dst, const uint8_t *src, uint16_t *ofs)
{
    uint8_t *buf = (uint8_t *)dst;
    buf[0] = src[3];
    buf[1] = src[2];
    buf[2] = src[1];
    buf[3] = src[0];
    *ofs = *ofs + 4;
}
/**
 * ����ֽ����λ
 */
static inline void byte_swap_8(void *dst, const uint8_t *src, uint16_t *ofs)
{
    uint8_t *buf = (uint8_t *)dst;
    buf[0] = src[7];
    buf[1] = src[6];
    buf[2] = src[5];
    buf[3] = src[4];
    buf[4] = src[3];
    buf[5] = src[2];
    buf[6] = src[1];
    buf[7] = src[0];
    *ofs = *ofs + 8;
}
#else
/**
 * С���ֽ���1һλ
 */
static inline void byte_copy_1(void *dst, const uint8_t *src, uint16_t *ofs)
{
    uint8_t *buf = (uint8_t *)dst;
    buf[0] = src[0];
    *ofs = *ofs + 1;
}
/**
 * С���ֽ���2λ
 */
static inline void byte_copy_2(void *dst, const uint8_t *src, uint16_t *ofs)
{
    uint8_t *buf = (uint8_t *)dst;
    buf[0] = src[0];
    buf[1] = src[1];
    *ofs = *ofs + 2;
}
/**
 * С���ֽ���4λ
 */
static inline void byte_copy_4(void *dst, const uint8_t *src, uint16_t *ofs)
{
    uint8_t *buf = (uint8_t *)dst;
    buf[0] = src[0];
    buf[1] = src[1];
    buf[2] = src[2];
    buf[3] = src[3];
    *ofs = *ofs + 4;
}
/**
 * С���ֽ���8��λ
 */
static inline void byte_copy_8(void *dst, const uint8_t *src, uint16_t *ofs)
{
    memcpy(dst, src, 8);
    *ofs = *ofs + 8;
}


#endif
#if NATIVE_BIG_ENDIAN
    #define _put_char(buf, wire_offset, b)     byte_swap_1(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_int8_t(buf, wire_offset, b)   byte_swap_1(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_uint8_t(buf, wire_offset, b)  byte_swap_1(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_uint16_t(buf, wire_offset, b) byte_swap_2(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_int16_t(buf, wire_offset, b)  byte_swap_2(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_uint32_t(buf, wire_offset, b) byte_swap_4(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_int32_t(buf, wire_offset, b)  byte_swap_4(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_uint64_t(buf, wire_offset, b) byte_swap_8(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_int64_t(buf, wire_offset, b)  byte_swap_8(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_float(buf, wire_offset, b)    byte_swap_4(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_double(buf, wire_offset, b)   byte_swap_8(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
#else
    #define _put_char(buf, wire_offset, b)     byte_copy_1(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_int8_t(buf, wire_offset, b)   byte_copy_1(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_uint8_t(buf, wire_offset, b)  byte_copy_1(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_uint16_t(buf, wire_offset, b) byte_copy_2(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_int16_t(buf, wire_offset, b)  byte_copy_2(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_uint32_t(buf, wire_offset, b) byte_copy_4(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_int32_t(buf, wire_offset, b)  byte_copy_4(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_uint64_t(buf, wire_offset, b) byte_copy_8(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_int64_t(buf, wire_offset, b)  byte_copy_8(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_float(buf, wire_offset, b)    byte_copy_4(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
    #define _put_double(buf, wire_offset, b)   byte_copy_8(&buf[*wire_offset], (const uint8_t *)&b, wire_offset)
#endif

#define _MAV_PAYLOAD(msg) ((const uint8_t *)(&(msg[0])))
#if NATIVE_BIG_ENDIAN
#define _mav_msg_return_type(type, SIZE) \
static inline type _mav_return_## type(const uint8_t *msg, uint16_t *ofs) \
{ type r; byte_swap_## SIZE((uint8_t*)&r, &_MAV_PAYLOAD(msg)[*ofs], ofs); return r; }

_mav_msg_return_type(uint8_t,  1)   /*!< ת��uint8_t  */
_mav_msg_return_type(char,     1)   /*!< ת��char  */
_mav_msg_return_type(int8_t,   1)   /*!< ת��int8_t  */
_mav_msg_return_type(uint16_t, 2)   /*!< ת��uint16_t  */
_mav_msg_return_type(int16_t,  2)   /*!< ת��int16_t  */
_mav_msg_return_type(uint32_t, 4)   /*!< ת��uint32_t  */
_mav_msg_return_type(int32_t,  4)   /*!< ת��int32_t  */
_mav_msg_return_type(uint64_t, 8)   /*!< ת��uint64_t  */
_mav_msg_return_type(int64_t,  8)   /*!< ת��int64_t  */
_mav_msg_return_type(float,    4)   /*!< ת��float  */
_mav_msg_return_type(double,   8)   /*!< ת��double  */

#else
#define _mav_msg_return_type(TYPE, SIZE) \
static inline TYPE _mav_return_## TYPE(const uint8_t *msg, uint16_t *ofs) \
{ TYPE r; byte_copy_## SIZE((uint8_t*)&r, &_MAV_PAYLOAD(msg)[*ofs], ofs); return r; }

_mav_msg_return_type(uint8_t,  1)   /*!< ת��uint8_t  */
_mav_msg_return_type(char,     1)   /*!< ת��char  */
_mav_msg_return_type(int8_t,   1)   /*!< ת��int8_t  */
_mav_msg_return_type(uint16_t, 2)   /*!< ת��uint16_t  */
_mav_msg_return_type(int16_t,  2)   /*!< ת��int16_t  */
_mav_msg_return_type(uint32_t, 4)   /*!< ת��uint32_t  */
_mav_msg_return_type(int32_t,  4)   /*!< ת��int32_t  */
_mav_msg_return_type(uint64_t, 8)   /*!< ת��uint64_t  */
_mav_msg_return_type(int64_t,  8)   /*!< ת��int64_t  */
_mav_msg_return_type(float,    4)   /*!< ת��float  */
_mav_msg_return_type(double,   8)   /*!< ת��double  */
#endif // MAVLINK_NEED_BYTE_SWAP


#endif
#endif /* PROTOCOL_H_ */
