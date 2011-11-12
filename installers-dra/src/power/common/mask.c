/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

    
    
    
    
    


/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:48:57 $
$Revision: 1.2 $
$Log: mask.c,v $
 * Revision 1.2  1998/02/04  15:48:57  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:02:24  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "mask.h"

int right_of_mask(unsigned int m)
{
  int r;
  unsigned int mask = 1;
  for (r = 0;r<=31;r++)
  {
    if ((m & mask)!=0)
    {
      return r;
    }
    mask = mask<<1;
  }
  return 0;
}

int left_of_mask(unsigned int m)
{
  int r;
  unsigned int mask =0x80000000;
  for (r = 31;r>=0;r--)
  {
    if ((m & mask)!=0)
    {
      return r;
    }
    mask = mask>>1;
  }
  return 0;
}

int is_a_mask(unsigned int m)
{
  unsigned int j,k;
  /* If m is a mask then one is returned */
  /* The definition of a mask is an unbroken series of 1's */
  if(m==0)
  {
    return 0;
  }
  j=( (m-1) ^ m )>>1 ;
  k=j+m;
  return (k&(k+1))==0;
}
