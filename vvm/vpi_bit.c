/*
 * Copyright (c) 2000 Stephen Williams (steve@icarus.com)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */
#if !defined(WINNT) && !defined(macintosh)
#ident "$Id: vpi_bit.c,v 1.3 2000/05/07 04:37:56 steve Exp $"
#endif

# include  "vpi_priv.h"
# include  <stdio.h>

/*
 * A signal value is unambiguous if the top 4 bits and the bottom 4
 * bits are identical. This means that the VSSSvsss bits of the 8bit
 * value have V==v and SSS==sss.
 */
#define UNAMBIG(v) (((v)&0x0f) == (((v)>>4)&0x0f))


# define STREN1(v) ( ((v)&0x80)? ((v)&0xf0) : (0x70 - ((v)&0xf0)) )
# define STREN0(v) ( ((v)&0x08)? ((v)&0x0f) : (0x07 - ((v)&0x0f)) )

vpip_bit_t vpip_bits_resolve(const vpip_bit_t*bits, unsigned nbits)
{
      unsigned idx;
      vpip_bit_t res = bits[0];

      idx = 1;
      while ((idx < nbits) && B_ISZ(res)) {
	    res = bits[idx];
	    idx += 1;
      }

      for ( ;  idx < nbits ;  idx += 1) {
	      /* High-impedence drives do not affect the result. */
	    if (bits[idx] == HiZ)
		  continue;

	    if (UNAMBIG(res) && UNAMBIG(bits[idx])) {

		    /* If both signals are unambiguous, simply choose
		       the stronger. If they have the same strength
		       but different values, then this becomes
		       ambiguous. */

		  if (bits[idx] == res) {

			  /* values are equal. do nothing. */

		  } else if ((bits[idx]&0x07) > (res&0x07)) {

			  /* New value is stronger. Take it. */
			res = bits[idx];

		  } else if ((bits[idx]&0x77) == (res&0x77)) {

			  /* Strengths are the same. Make value ambiguous. */
			res = (res&0x70) | (bits[idx]&0x07) | 0x80;

		  } else {

			  /* Must be res is the stronger one. */
		  }

	    } else if (UNAMBIG(res) || UNAMBIG(bits[idx])) {

		    /* If one of the signals is unambiguous, then it
		       will sweep up the weaker parts of the ambiguous
		       signal. The result may be ambiguous, or maybe
		       not. */

		  vpip_bit_t tmp = 0;

		  if ((res&0x70) > (bits[idx]&0x70))
			tmp |= res&0xf0;
		  else
			tmp |= bits[idx]&0xf0;

		  if ((res&0x07) > (bits[idx]&0x07))
			tmp |= res&0x0f;
		  else
			tmp |= bits[idx]&0x0f;

	    } else {

		    /* If both signals are ambiguous, then the result
		       has an even wider ambiguity. */

		  vpip_bit_t tmp = 0;

		  if (STREN1(bits[idx]) > STREN1(res))
			tmp |= bits[idx]&0xf0;
		  else
			tmp |= res&0xf0;

		  if (STREN0(bits[idx]) < STREN0(res))
			tmp |= bits[idx]&0x0f;
		  else
			tmp |= res&0x0f;

		  res = tmp;
	    }

      }

      if ((res&0x77) == 0)
	    res = HiZ;

      return res;
}

/*
 * $Log: vpi_bit.c,v $
 * Revision 1.3  2000/05/07 04:37:56  steve
 *  Carry strength values from Verilog source to the
 *  pform and netlist for gates.
 *
 *  Change vvm constants to use the driver_t to drive
 *  a constant value. This works better if there are
 *  multiple drivers on a signal.
 *
 * Revision 1.2  2000/03/22 05:16:38  steve
 *  Integrate drive resolution function.
 *
 * Revision 1.1  2000/03/22 04:26:40  steve
 *  Replace the vpip_bit_t with a typedef and
 *  define values for all the different bit
 *  values, including strengths.
 *
 */

