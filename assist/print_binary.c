Displaying a Number in Binary


Introduction.

This section illustrates how a quantity may be printed to the terminal in binary format. Program BIN_PRNT.C implements functions to display one and two bytes.

Applications.

This can be a helpful debugging tool and may indeed be used in initially developing code even when the peripheral is not available.

Consider the following examples;

Example #1.

     /*  might be used in controlling a stepping motor on the 
     ** low nibble of the data port. */

     data = (data & 0xf0) | patt[index[n]];
#ifdef TEST
     bin_prnt_byte(data); /* print data in binary */
     printf("\n");
#endif              
     outportb(DATA, data);
Example #2.

     /* might be used for examining inputs.  In this case from the    
     ** control port */

     outportb(CONTROL, 0x1f ^ 0x0b); /* outputs all set to one */
           
     in = inportb(CONTROL)^ 0x0b; 
     /*fetch and compensate for the hardware inversions */
#ifdef TEST
     bin_prnt_byte(in);
     printf("\n");
#endif
     ...
Of course, in both cases, a watch could have been set using the debugger to examine the variable. Unfortunately, on my debugger, an integer is displayed in decimal, and even worse a char or unsigned char is displayed as an ASCII character. Alternatively , a printf with the %x format specifier could be used. However, after more than 30 years it still takes me some time to look at 0xce and quickly determine whether bit 5 is a zero or one.

Program BIN_PRNT.C

In function bin_prnt_byte(), the most significant bit is printed as either a "one" or "zero" and the byte is then shifted to the left. The process is continued for all eight bits. Function bin_print_int() simply isolates the high byte and prints it usin g bin_prnt_byte() and then does the same with the low byte.

/*
** Program BIN_PRNT.C
**
** Illustrates how to print an unsigned char or unsigned int in binary.
**
** Peter H. Anderson, MSU, Oct 12, '96
*/

#include <stdio.h>
#include <conio.h>
#include <dos.h>

void bin_prnt_byte(int x);
void bin_prnt_int(int x);

void main(void)
{
   clrscr();
   bin_prnt_byte(0xa3);
   printf("\n");
   bin_prnt_int(0xf23c);
   printf("\n");
}

void bin_prnt_byte(int x)
{
   int n;
   for(n=0; n<8; n++)
   {
      if((x & 0x80) !=0)
      {
         printf("1");
      }
      else
      {
         printf("0");
      }
      if (n==3)
      {
         printf(" "); /* insert a space between nybbles */
      }
      x = x<<1;
   }
}

void bin_prnt_int(int x)
{
   int hi, lo;
   hi=(x>>8) & 0xff;
   lo=x&0xff;
   bin_prnt_byte(hi);
   printf(" ");
   bin_prnt_byte(lo);
}