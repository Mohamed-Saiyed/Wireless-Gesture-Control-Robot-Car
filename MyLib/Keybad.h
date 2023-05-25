#ifndef Keybad
#define Keybad


#define KEYBAD_PORT_DDR  DDRC
#define KEYBAD_PORT_OUT  PORTC
#define KEYBAD_PORT_PIN  PINC
#define N_COL 4
#define N_ROW 4
#if (N_COL == 4)
static uint8_t KeyPad_4x4_adjustKeyNumber(uint8_t button_number);
#elif (N_COL == 3)
static uint8_t Keybad_4x3_adjust_keynumbers(uint8_t button_number);
#endif
int  Get_Keybad_pressed_key()
{
	while(1)
	{
		for(uint8_t col = 0 ; col < N_COL ; col++ )
		{
			KEYBAD_PORT_DDR = (0b00010000 << col);
			
			KEYBAD_PORT_OUT =(~(0b00010000 << col));
			
			for (uint8_t row = 0 ; row < N_ROW ; row++)
			{
				if (bit_is_clear(KEYBAD_PORT_PIN,row))
				{
					#if (N_COL == 3)
					return Keybad_4x3_adjust_keynumbers((row*N_COL)+col+1);
					#elif (N_COL == 4)
					return KeyPad_4x4_adjustKeyNumber((row*N_COL)+col+1);
					#endif
				}
			}
			
		}
	}
	
}
#if (N_COL == 3)
static uint8_t Keybad_4x3_adjust_keynumbers(uint8_t button_number)
{
	switch(button_number)
	{
		case 10 : return '*';
		break;
		case 11 : return 0;
		break;
		case 12 : return '#';
		break;
		default: return button_number ;
		break;
	}
}
#elif (N_COL == 4)
static uint8_t KeyPad_4x4_adjustKeyNumber(uint8_t button_number)
{
	switch(button_number)
	{
		case 1: return 7;
		break;
		case 2: return 8;
		break;
		case 3: return 9;
		break;
		case 4: return '%'; // ASCII Code of %
		break;
		case 5: return 4;
		break;
		case 6: return 5;
		break;
		case 7: return 6;
		break;
		case 8: return '*'; /* ASCII Code of '*' */
		break;
		case 9: return 1;
		break;
		case 10: return 2;
		break;
		case 11: return 3;
		break;
		case 12: return '-'; /* ASCII Code of '-' */
		break;
		case 13: return 13;  /* ASCII of Enter */
		break;
		case 14: return 0;
		break;
		case 15: return '='; /* ASCII Code of '=' */
		break;
		case 16: return '+'; /* ASCII Code of '+' */
		break;
		default: return button_number;
	}
}
#endif
#endif