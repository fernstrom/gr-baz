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
#ifndef INCLUDED_BAZ_CC_H
#define INCLUDED_BAZ_CC_H

#include <gr_sync_block.h>

class baz_pow_cc;

/*
 * We use boost::shared_ptr's instead of raw pointers for all access
 * to gr_blocks (and many other data structures).  The shared_ptr gets
 * us transparent reference counting, which greatly simplifies storage
 * management issues.  This is especially helpful in our hybrid
 * C++ / Python system.
 *
 * See http://www.boost.org/libs/smart_ptr/smart_ptr.htm
 *
 * As a convention, the _sptr suffix indicates a boost::shared_ptr
 */
typedef boost::shared_ptr<baz_pow_cc> baz_pow_cc_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of baz_pow_cc.
 *
 * To avoid accidental use of raw pointers, baz_pow_cc's
 * constructor is private.  howto_make_square2_ff is the public
 * interface for creating new instances.
 */
baz_pow_cc_sptr baz_make_pow_cc (float exponent);

/*!
 * \brief square2 a stream of floats.
 * \ingroup block
 *
 * This uses the preferred technique: subclassing gr_sync_block.
 */
class baz_pow_cc : public gr_sync_block
{
private:
  // The friend declaration allows howto_make_square2_ff to
  // access the private constructor.

  friend baz_pow_cc_sptr baz_make_pow_cc (float exponent);

  baz_pow_cc (float exponent);  	// private constructor
  
  float d_exponent;

 public:
  ~baz_pow_cc ();	// public destructor

  void set_exponent(float exponent);
  inline float exponent() const
  { return d_exponent; }

  int work (int noutput_items,
	    gr_vector_const_void_star &input_items,
	    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_BAZ_CC_H */
