//aluminium: Super Mario World ROM title string changer
//2017 benjausen

//Usage: aluminium rom.sfc -option
//Valid options:
//-r: Restore the target ROM's original "SUPER MARIOWORLD" title. Needed for Lunar Magic!
//-t <TITLE>: Write a custom title string into the target ROM.
//-d: Show some key information about the target ROM.

//Some info retrieved from:
//http://patpend.net/technical/snes/sneskart.html
//https://www.smwcentral.net/?p=map&type=rom

#include "main.h"

int main(int argc, char **argv)
{

	printf("aluminium %s, running on %s. ", VERSION, MY_ENV);

	//part 0: operation under arguments
	
	if (argc == 2 || argc > 4)
	{
		print_usage();
		return 0;
	}

	if (argc > 2)
	{
		file_ptr = fopen(argv[1], "r+b");

		if (!file_ptr)
		{
			printf("\ninvalid file name or file is busy. ");
			return 0;
		}

		char *is_headered = "YES";

		if (!check_rom_header(file_ptr))
		{
			is_headered = "NO";
			address_ROMinfo -= 0x200;
			address_SMWbegin -= 0x200;
		}

		if (!strcmp(argv[2], "-r"))
		{
			printf("\nrestoring original title...\n");
			write_data((char*)orig_title, file_ptr);
			fclose(file_ptr);
			return 0;
		}

		else if (!strcmp(argv[2], "-t"))
		{
			if (!argv[3])
			{
				print_usage();
				fclose(file_ptr);
				return 0;
			}
			
			char title[21] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' };
			for (int i = 0; i < strlen(argv[3]); i++)
			{
				title[i] = argv[3][i];
			}

			printf("\ncopying custom title into ROM...\n");
			write_data(title, file_ptr);
			fclose(file_ptr);
			return 0;
		}

		else if (!strcmp(argv[2], "-d"))
		{
			printf("\nInformation about \"%s\": \nROM 512 Byte Header: %s\nROM Size: %d Mbits\nROM Internal Checksum: $%x\nROM Internal Inverse Checksum: $%x\nROM Region: %s\n", argv[1], is_headered, get_rom_size(file_ptr), get_rom_checksum(file_ptr, 0), get_rom_checksum(file_ptr, 1), get_rom_country(file_ptr));
			fclose(file_ptr);
			return 0;
		}

		else
		{
			print_usage();
			fclose(file_ptr);
		}

		return 0;

	}

	//part 1: open ROM
	while (1)
	{
		printf("input ROM filename: ");

		for (int i = 0; i < 0xFF; i++) input[i] = 0;

		fgets(input, sizeof(input), stdin);
		input[strlen(input) - 1] = '\0';

		if (!strcmp(input, "exit"))
		{
			printf("\ngoodbye.\n");
			return 0;
		}

		file_ptr = fopen(input, "r+b");

		if (!file_ptr)
			printf("\ninvalid file name or file is busy. ");
		else
			break;
	}

	//part 2: display ROM info
	printf("\nROM successfully opened.");

	if (!check_rom_header(file_ptr))
	{
		address_ROMinfo -= 0x200;
		address_SMWbegin -= 0x200;
	}

	//part 3: get new title or command
	printf("\ninput new 20-byte ROM title or \"restore\" to restore the original title: ");

	for (int i = 0; i < 0xFF; i++) input[i] = 0;

	fgets(input, sizeof(input), stdin);
	input[strlen(input) - 1] = '\0';

	if (!strcmp(input, "exit"))
	{
		printf("\ngoodbye.");
		fclose(file_ptr);
		return 0;
	}

	//part 4: apply new title
	if (!strcmp(input, "exit"))
	{
		printf("\ngoodbye\n");
		fclose(file_ptr);
		return 0;
	}
	else if (!strcmp(input, "restore"))
	{
		printf("\nAre you sure? (type \"yes\")");

		for (int i = 0; i < 0xFF; i++) input[i] = 0;

		fgets(input, sizeof(input), stdin);
		input[strlen(input) - 1] = '\0';

		if (strcmp(input, "yes"))
		{
			fclose(file_ptr);
			return 0;
		}

		printf("\nrestoring original title...\n");
		write_data((char*)orig_title, file_ptr);

		fclose(file_ptr);
		return 0;
	}
	else
	{
		char title[21] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' };

		for (int i = 0; i < 21; i++)
		{
			title[i] = input[i];
		}

		printf("\nAre you sure? A ROM with a custom title will refuse to open in Lunar Magic! (type \"yes\")");

		for (int i = 0; i < 0xFF; i++) input[i] = 0;

		fgets(input, sizeof(input), stdin);
		input[strlen(input) - 1] = '\0';

		if (strcmp(input, "yes"))
		{
			fclose(file_ptr);
			return 0;
		}

		printf("\ncopying custom title into ROM...\n");
		write_data(title, file_ptr);

		fclose(file_ptr);
		return 0;
	}
}
