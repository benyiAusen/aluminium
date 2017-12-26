//aluminium: Super Mario World ROM title string changer
//2017 benjausen

//Usage: aluminium rom.sfc -option
//Valid options:
//-r: Restore the target ROM's original "SUPER MARIOWORLD" title. Needed for Lunar Magic!
//-t <TITLE>: Write a custom title string into the target ROM.
//-d: Show some key information about the target ROM.

//Info retrieved from:
//http://patpend.net/technical/snes/sneskart.html
//https://www.smwcentral.net/?p=map&type=rom

#ifndef main_h
#define main_h

#define VERSION "1.1"

#ifdef _WIN32
#define MY_ENV "Windows"
#define _CRT_SECURE_NO_WARNINGS

#elif __linux__
#define MY_ENV "Linux"

#elif __apple__
#define MY_ENV "macOS"

#elif __unix__
#define MY_ENV "Unix"

#endif

#include <stdio.h>
#include <string.h>

FILE *file_ptr = NULL;
char input[0xFF];
const char orig_title[21] = { 'S','U','P','E','R',' ','M','A','R','I','O','W','O','R','L','D',' ',' ',' ',' ',' ' };

enum countries
{
	JPN,
	USA,
	EUR,
	SWE,
	FIN,
	DEN,
	FRA,
	NETHERLANDS,
	SPA,
	GER,
	ITA,
	HK_CHINA,
	INDONESIA,
	KOR
};

int address_ROMinfo  = 0x081C0;  //Location of $00:FFC0 (ROM title)
int address_SMWbegin = 0x00200;  //Location of $00:8000 (Beginning of SMW)

int check_rom_header(FILE *ptr)
{
	const char reference[8] = { 0x78,0x9C,0x00,0x42,0x9C,0x0C,0x42,0x9C };
	int j = 0;

	for (int i=0; i < 8; i++)
	{
		fseek(ptr, address_SMWbegin + i, SEEK_SET);
		char current_byte = fgetc(ptr);

		if (current_byte == reference[i])
			j += 0;
		else
			j += 1;
	}

	if (!j)
		return 1;
	return 0;
}

int get_rom_size(FILE *ptr)
{
	int i, j;

	fseek(ptr, address_SMWbegin, SEEK_SET);
	i = ftell(ptr);

	fseek(ptr, 0, SEEK_END);
	j = ftell(ptr);

	return (j - i) / 125000;
}

int get_rom_checksum(FILE *ptr, char mode)
{
	int chksum[2], i = 2;
	if (!mode) i = 0;

	fseek(ptr, address_ROMinfo + 30 - i, SEEK_SET);
	chksum[0] = fgetc(ptr);

	fseek(ptr, address_ROMinfo + 31 - i, SEEK_SET);
	chksum[1] = fgetc(ptr);

	return chksum[0] + 0x100 * chksum[1];
}

char *get_rom_country(FILE *ptr)
{
	fseek(ptr, address_ROMinfo + 26, SEEK_SET);
	char country = fgetc(ptr);

	switch (country)
	{
	case JPN:
		return "Japan [NTSC]";

	case USA:
		return "North America [NTSC]";

	case EUR:
		return "Asia/Australia/Europe/Oceania [PAL]";

	case SWE:
		return "Sweden [PAL]";

	case FIN:
		return "Finland [PAL]";

	case DEN:
		return "Denmark [PAL]";

	case FRA:
		return "France [PAL]";

	case NETHERLANDS:
		return "Netherlands [PAL]";

	case SPA:
		return "Spain [PAL]";

	case GER:
		return "Austria/Germany/Switzerland [PAL]";

	case ITA:
		return "Italy [PAL]";

	case HK_CHINA:
		return "China/Hong Kong [PAL]";

	case INDONESIA:
		return "Indonesia [PAL]";

	case KOR:
		return "Korea [PAL]";

	default:
		return "Unknown [???]";
	}
}

void write_data(char data[21], FILE *ptr)
{
	for (int i = 0; i < 20; i++)
	{
		fseek(ptr, address_ROMinfo + i, SEEK_SET);

		if (data[i] != '\0')
			putc(data[i], ptr);
		else
			putc(' ', ptr);
	}

	fseek(ptr, address_ROMinfo + 20, SEEK_SET);
	putc(' ', ptr);
}

void print_usage()
{
	printf("\nUsage: aluminium rom.sfc -option\nValid options:\n-r: Restore the target ROM's original \"SUPER MARIOWORLD\" title. Needed for Lunar Magic!\n-t <TITLE>: Write a custom title string into the target ROM.\n-d: Show some key information about the target ROM\n");
}

#endif
