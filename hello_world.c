/*
 * "Small Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It requires a STDOUT  device in your system's hardware.
 *
 * The purpose of this example is to demonstrate the smallest possible Hello
 * World application, using the Nios II HAL library.  The memory footprint
 * of this hosted application is ~332 bytes by default using the standard
 * reference design.  For a more fully featured Hello World application
 * example, see the example titled "Hello World".
 *
 * The memory footprint of this example has been reduced by making the
 * following changes to the normal "Hello World" example.
 * Check in the Nios II Software Developers Manual for a more complete
 * description.
 *
 * In the SW Application project (small_hello_world):
 *
 *  - In the C/C++ Build page
 *
 *    - Set the Optimization Level to -Os
 *
 * In System Library project (small_hello_world_syslib):
 *  - In the C/C++ Build page
 *
 *    - Set the Optimization Level to -Os
 *
 *    - Define the preprocessor option ALT_NO_INSTRUCTION_EMULATION
 *      This removes software exception handling, which means that you cannot
 *      run code compiled for Nios II cpu with a hardware multiplier on a core
 *      without a the multiply unit. Check the Nios II Software Developers
 *      Manual for more details.
 *
 *  - In the System Library page:
 *    - Set Periodic system timer and Timestamp timer to none
 *      This prevents the automatic inclusion of the timer driver.
 *
 *    - Set Max file descriptors to 4
 *      This reduces the size of the file handle pool.
 *
 *    - Check Main function does not exit
 *    - Uncheck Clean exit (flush buffers)
 *      This removes the unneeded call to exit when main returns, since it
 *      won't.
 *
 *    - Check Don't use C++
 *      This builds without the C++ support code.
 *
 *    - Check Small C library
 *      This uses a reduced functionality C library, which lacks
 *      support for buffering, file IO, floating point and getch(), etc.
 *      Check the Nios II Software Developers Manual for a complete list.
 *
 *    - Check Reduced device drivers
 *      This uses reduced functionality drivers if they're available. For the
 *      standard design this means you get polled UART and JTAG UART drivers,
 *      no support for the LCD driver and you lose the ability to program
 *      CFI compliant flash devices.
 *
 *    - Check Access device drivers directly
 *      This bypasses the device file system to access device drivers directly.
 *      This eliminates the space required for the device file system services.
 *      It also provides a HAL version of libc services that access the drivers
 *      directly, further reducing space. Only a limited number of libc
 *      functions are available in this configuration.
 *
 *    - Use ALT versions of stdio routines:
 *
 *           Function                  Description
 *        ===============  =====================================
 *        alt_printf       Only supports %s, %x, and %c ( < 1 Kbyte)
 *        alt_putstr       Smaller overhead than puts with direct drivers
 *                         Note this function doesn't add a newline.
 *        alt_putchar      Smaller overhead than putchar with direct drivers
 *        alt_getchar      Smaller overhead than getchar with direct drivers
 *
 */

#include "sys/alt_stdio.h"
#include "system.h"
#include <unistd.h>

	unsigned char	seven_seg_table[] =
				{0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07,
			  	 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };
	char	hex_segments[] = { 0, 0, 0, 0, 0, 0, 0, 0 };


  	volatile int * green_LED_ptr = (int *) LEDG_BASE;		// green LED address
  	volatile int * pushbutton_ptr = (int *) KEY_BASE; // KEY address
  	volatile int * sw_ptr = (int *) SW_BASE; // KEY address

  	int hh = 15;
  	int mm = 45;
  	int ss = 0;
  	int uu = 0;
  	int horloge = 0;
  	int press = 0;
  	int crono = -1;
  	int uuuu = 0;
  	int ssss = 0;
  	int mmmm = 0;
  	int cronometre = 0;
  	int sw = 0;

  	static unsigned int uint2bcd(unsigned int ival){
  		return ((ival /10)<<4)|(ival%10);
  	}
  	void Update_HEX_display(int buffer)
  	{
  		volatile int * HEX3_HEX0_ptr = (int *) HEX_BASE;
  		int shift_buffer, nibble;
  		char code;
  		int i;

  		shift_buffer = buffer;

  		//shift_buffer = uint2bcd(shift_buffer);
  		for ( i = 0; i < 8; ++i )
  		{
  			nibble = shift_buffer & 0x0000000F;		// character is in rightmost nibble
  			code = seven_seg_table[nibble];
  			hex_segments[i] = code;
  			shift_buffer = shift_buffer >> 4;
  		}

  		*(HEX3_HEX0_ptr) = *(int *) hex_segments; 		// drive the hex displays
  		return;
  	}
int main()
{
	alt_putstr("Hello from Nios II!\n");

	while (1){
	  press = *(pushbutton_ptr);
	  sw    = *(sw_ptr);
	  horloge =0;
	  uu++;
	  if (uu==100){
		  ss++;uu=0;
	  }
	  if (ss==61){
		  mm++;ss=0;
	  }
	  if (mm==61){
		  hh++;mm=0;
	  }
	  if (hh==24){
		  ss=0;
	  }
	  int hh_a=uint2bcd(hh);
	  int mm_a=uint2bcd(mm);
	  horloge = ((hh_a<<8)&0x0000FF00)|(mm_a&0x000000FF);
	  //printf("%d:%d:%d  (%d)\n",hh,mm,ss,horloge);
	  //horloge = 0x00002456;//hh<<8&mm;

	  if ((press&0x2) && crono ==-1) {
		  crono=0;
	  }
	  if (press&0x4)
		  if(crono ==0){
		      crono=1;
		  }else{
			  crono=0;}
	  if (press&0x8)
		  if (crono==0){
			  crono=-1;
		  }
	  if (crono==0){
		  uuuu++;
		  if (uuuu==100){
			  ssss++;uuuu=0;
		  }
		  if (ssss==61){
			  mmmm++;ssss=0;
		  }
		  if (mmmm==61){
			  mmmm=0;
		  }
	  }
	  hh_a=uint2bcd(ssss);
	  mm_a=uint2bcd(uuuu);
	  cronometre = ((hh_a<<8)&0x0000FF00)|(mm_a&0x000000FF);
	  if (sw==0){
		  Update_HEX_display(horloge);
	  }else{
		  Update_HEX_display(cronometre);}
	  usleep(900);
  };

  return 0;
}

