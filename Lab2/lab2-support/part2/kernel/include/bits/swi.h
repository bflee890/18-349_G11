/*
 * swi.h: Defines syscall numbers used in SWI instructions
 *
 * Author: Mike Kasick <mkasick@andrew.cmu.edu>
 * Date:   Sun, 07 Oct 2007 01:36:02 -0400
 */

#ifndef BITS_SWI_H
#define BITS_SWI_H

#define SWI_BASE 0x900000

#define EXIT_SWI  (SWI_BASE + 1)
#define READ_SWI  (SWI_BASE + 3)
#define WRITE_SWI (SWI_BASE + 4)

#define SDRAM_BEGIN 0xa0000000
#define SDRAM_END   0xa3ffffff
#define ROM_BEGIN   0x00000000
#define ROM_END	    0X00ffffff


#endif /* BITS_SWI_H */
