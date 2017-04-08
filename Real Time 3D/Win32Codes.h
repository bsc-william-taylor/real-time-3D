
/* -------------------------------------------------
  
 @Filename  : Win32Codes.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: Simple include file when reading 
			  states.

 ------------------------------------------------- */

#pragma once

// Usual Key MACROS.

#define A_KEY           30											
#define S_KEY           31											
#define D_KEY           32											
#define F_KEY           33											
#define G_KEY           34											
#define H_KEY           35											
#define J_KEY           36											
#define K_KEY           37											
#define L_KEY           38											
#define Q_KEY           16											
#define W_KEY           17											
#define E_KEY           18											
#define R_KEY           19											
#define T_KEY           20										
#define Y_KEY           21											
#define U_KEY           22											
#define I_KEY           23											
#define O_KEY           24											
#define P_KEY           25										
#define Z_KEY           44											
#define X_KEY           45											
#define C_KEY           46											
#define V_KEY           47											
#define B_KEY           48											
#define N_KEY           49											
#define M_KEY           50

// Other Key MACROS

#define ESCAPE          1	
#define ONE             2		
#define TWO             3											
#define THREE           4											
#define FOUR            5											
#define FIVE            6											
#define SIX             7											
#define SEVEN           8											
#define EIGHT           9											
#define NINE            10											
#define ZERO            11											
#define MINUS           12											
#define EQUALS          13	
#define BACKSPACE       14											
#define TAB             15											
#define LBRACKET        16											
#define RBRACKET        17											
#define RETURN          18											
#define LCONTROL        19											
#define SEMICOLON       39											
#define APOSTROPHE      40											
#define LSHIFT          42											
#define BACKSLASH       43											
#define COMMA           51											
#define SLASH           53											
#define RSHIFT          54											
#define MULTIPLY        55											
#define LEFT_ALT        56																					
#define CAPS_LOCK       58	

// Function Keys.

#define F1              59											
#define F2              60											
#define F3              61											
#define F4              62											
#define F5              63											
#define F6              64											
#define F7              65											
#define F8              66											
#define F9              67											
#define F10             68										
#define F11             87											
#define F12             88											
#define F13             100											
#define F14             101											
#define F15             102		

// Calculater Keys.

#define NUMLOCK         69											
#define SCROLL          70											
#define NUMPAD7         71											
#define NUMPAD8         72											
#define NUMPAD9         73											
#define SUBTRACT        74											
#define NUMPAD4         75											
#define NUMPAD5         76											
#define NUMPAD6         77		
#define ADD             78											
#define NUMPAD1         79											
#define NUMPAD2         80											
#define NUMPAD3         81											
#define NUMPAD0         82		

// Other Keys.

#define FULLSTOP        83	
#define NUMPAD_ENTER    156			
#define RCONTROL        157											
#define MUTE            160											
#define VOLUME_DOWN     174											
#define VOLUME_UP       176											
#define DIVIDE          181											
#define RIGHT_ALT       184											
#define PAUSE           197											
#define HOME            199	
#define SPACE           57	
#define ARROW_UP        200											
#define PAGE_UP         201											
#define ARROW_LEFT      203											
#define ARROW_RIGHT     205											
#define END             207											
#define ARROW_DOWN      208											
#define NEXT            209											
#define INSERT          210											
#define DEL				211											
#define LEFT_WINDOWS    219											
#define RIGHT_WINDOWS   220											
#define ENTER			28	

// Get Function MACROS.

#define WINDOW_WIDTH	100
#define WINDOW_HEIGHT   101
#define MOUSE_X			102
#define MOUSE_Y			103
#define WINDOW_RATIO	104
#define INVALID_PARAM	1

// Mouse Buttons Macros.

#define NOT_PRESSED		4	
#define MOUSE_MIDDLE	2													
#define MOUSE_1			0														
#define MOUSE_2			1

/*
	Keys states macros used for identifying
	different types of key interaction.
*/
				
#define RELEASED		1														
#define HOLDING			3														
#define PRESSED			0	

/*
	Useful check funtions
*/

#define KEY_HOLDING(k, i, b)( b == HOLDING && k == i ) ? true : false
#define KEY_DOWN(k, i, b)( b == PRESSED && k == i ) ? true : false
#define KEY_UP(k, i, b)( b == RELEASED && k == i ) ? true : false

// END