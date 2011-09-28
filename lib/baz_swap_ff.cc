/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*
 * config.h is generated by configure.  It contains the results
 * of probing for features, options etc.  It should be the first
 * file included in your .cc file.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <baz_swap_ff.h>
#include <gr_io_signature.h>

/*
 * Create a new instance of baz_swap_ff and return
 * a boost shared_ptr.  This is effectively the public constructor.
 */
baz_swap_ff_sptr 
baz_make_swap_ff (bool bSwap)
{
  return baz_swap_ff_sptr (new baz_swap_ff (bSwap));
}

/*
 * Specify constraints on number of input and output streams.
 * This info is used to construct the input and output signatures
 * (2nd & 3rd args to gr_block's constructor).  The input and
 * output signatures are used by the runtime system to
 * check that a valid number and type of inputs and outputs
 * are connected to this block.  In this case, we accept
 * only 1 input and 1 output.
 */
static const int MIN_IN = 1;	// mininum number of input streams
static const int MAX_IN = 1;	// maximum number of input streams
static const int MIN_OUT = 1;	// minimum number of output streams
static const int MAX_OUT = 1;	// maximum number of output streams

/*
 * The private constructor
 */
baz_swap_ff::baz_swap_ff (bool bSwap)
  : gr_sync_block ("swap_ff",
		   gr_make_io_signature (MIN_IN, MAX_IN, sizeof (float)),
		   gr_make_io_signature (MIN_OUT, MAX_OUT, sizeof (float)))
  , m_bSwap(bSwap)
{
  set_output_multiple(2);
}

/*
 * Our virtual destructor.
 */
baz_swap_ff::~baz_swap_ff ()
{
  // nothing else required in this example
}

void baz_swap_ff::set_swap(bool bSwap)
{
  m_bSwap = bSwap;
}

int 
baz_swap_ff::work (int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
{
  const float *in = (const float *) input_items[0];
  float *out = (float *) output_items[0];
  
  assert(noutput_items % 2 == 0);

  for (int i = 0; i < noutput_items; i += 2) {
	if (m_bSwap)
	{
	  out[i+0] = in[i+1];
	  out[i+1] = in[i+0];
	}
	else
	{
	  out[i+0] = in[i+0];
	  out[i+1] = in[i+1];
	}
  }

  // Tell runtime system how many output items we produced.
  return noutput_items;
}
