/* tlgu: Translates TLG (D) / PHI text files to Unicode text
 *
 * Copyright (C) 2004, 2005, 2011 Dimitri Marinakis
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License Version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Usage:
 *	 tlgu [options] tlgu beta_code_file [unicode_text_file]
 *
 * Options:
 *	-r -- primarily Roman text (e.g. Canon, PHI); default betastate = ROMAN, reset on every ID code
 *	-v -w -x -y -z -- work reference citations are printed in the form xxx.xxx...xxx
 *	-Z <custom_citation_format_prefix> -- use reference and description citation codes in string
 *	    reference a-z, description A-Z also special codes \t(ab) \n(new line) \r(eturn)
 *	    e.g. "%A/%Z/%v/%w/%y/%z\t"
 *      -e -- companion to -Z above; a string to put out when a defined citation slot
 *	      is empty (e.g. "NONE", or "-") 
 *
 *	-b -- books are preceded by a page feed and description citations are printed
 *	-p -- pagination is observed, otherwise book lines are printed continuously
 *	-B -- output blank space (tab) after each new line (beginning of line)
 *
 *	-X -- citations are printed as they change (v, w, x)
 *	-Y -- citations are printed as they change (w, x, y)
 *	-N -- no spaces - line ends, and hyphens before an ID code, are removed
 * 
 *	-C -- citation debug information is printed
 *	-S -- special code debug information is printed
 *	-T -- bracket debug information is printed
 *	-V -- processing debug information is printed
 *	-W -- multiple output files, one for each work
 *
 * Returns: exit code 1 if unsuccesful
 *
 * Make: gcc tlgu.c -o tlgu
 *
 * History: This is a re-write of a DOS program (tlgft.asm) written several
 * years ago to translate Hellenic texts distributed on the TLG CD-ROM from
 * "beta code" to something readable, editable and printable.
 *
 * Contributors: Troy Griffitts (tg)
 *
 * Pointers / References:
 *   TLG Project - www.tlg.uci.edu
 *   PHI CD ROM Format Description, Packard Humanities Institute, 19 April 1992
 *   Beta code reference - Text versions: tlgbeta.txt, tlgcode.txt, BCM2004.pdf (23-Jun-2004)
 *
 *   ID locator reference - Text version tlgcodes.txt
 *
 * 14-Jun-2001 dm -- c port: ELOT-928 with custom dead-accent codes
 * 14-Jun-2004 dm -- Unicode
 * 26-Jun-2004 dm -- Command-line options
 * 26-Feb-2005 dm -- Output file separation (-W option)
 * 06-Mar-2005 dm -- Latin accent characters added (without parentheses)
 * 02-Aug-2005 tg -- Free-form citations (options -Z, -e) and per-line processing
 * 22-Apr-2006 dm -- Includes to make gcc (4.x) happy, final sigma fix for free text
 * 02-Oct-2011 dm -- Output written to stdout if an output file name is not provided
 * 16-Oct-2011 dm -- Code correction for lower case phi
 * 20-Nov-2011 dm -- stop processing gracefully when writing to stdout
 * 20-Nov-2011 dm -- e-book type citations (options -X -Y)
 * 
 */

#include "tlgu.h"
#include "tlgcodes.h"

/****************** PROTOTYPES FROM THE TOP DOWN *******************/

int tlgu (char * input_file, char * output_file);
void output_utf(int ucode);
void output_string(char *outstr);
int process_beta (int input_count);
void beta_code(int input_count);
int id_code(int input_count);
void store_accents(unsigned char bufferchar);
const char *resolve_cite_format(const char *cformat);

/****************** PROGRAM VERSION INFORMATION  *******************/
char *prog_version="1.6";

/****************** COMMAND LINE OPTIONS  **************************/
int opt_roman = 0;
int opt_page = 0;
int opt_blank = 0;
int opt_acit = 0;
int opt_bcit = 0;
int opt_ccit = 0;
int opt_dcit = 0;
int opt_cit_id = 0; /* combines a, b, c */
int opt_vcit = 0;
int opt_wcit = 0;
int opt_xcit = 0;
int opt_ycit = 0;
int opt_cprefix = 0;
char cformat[253];
int opt_ecit_blank = 0;
char ecite[253];
int opt_zcit = 0;
int opt_verbose = 0;
int opt_debug_bracket = 0;
int opt_debug_cit = 0;
int opt_debug_special = 0;
int opt_multiple = 0;
int opt_ebook_cit_x = 0;
int opt_ebook_cit_y = 0;
int opt_nospace = 0;

/****************** GLOBAL VARIABLES *******************************/

int iptr = 0;	/* input buffer pointer, reset before every read */
int optr = 0;	/* output buffer pointer, reset after every write */
unsigned char input_buffer[INRECSIZE];
unsigned char output_buffer[OUTRECSIZE];
#define MAXFILELEN 256
int prev_cit_w = 0;
int prev_cit_x = 0;
int prev_cit_y = 0;
/************ GLOBAL BETA CODE PROCESSING VARIABLES **************/

unsigned int outcode;
int betastate;	/* translation state machine */
int previous_state;	/* needed for symbol translations */
int start_new_line = 0;	/* needed for symbol translations */
int book_change = 0;	/* needed for symbol translations */
int accents;	/* holds accent combinations */
char *accented_chars = "AEHIOUWR";
char *accent_chars = ")(+/\\=|";
char *latin_accent_chars = "+/\\=|";
char *escape_codes = "$&%\"@#^[]<>{}";
char *punctuation_codes = " .,:;_\"%{}$&";	/* used by which_sigma */
char previous_bcit[52][32];	/* holds previous work (book) citation */

/****************** GLOBAL DESCRIPTOR  VARIABLES *****************/

/*
	Space is reserved for descriptive data as follows:

	citations, binary component -- z, y, x, w, v, n (1 to 16383)
	citations, ascii component -- a-z (1 to 15 characters + null, only a-d, n, v-z are actually used)
	descriptors, binary component -- a-z (1 to 16383)
	descriptors, ascii component -- a-z (1 to 31 characters + null)

	Citations ---
	a - author citation
	b - work citation
	c - preferred abbreviation for the work
	d - preferred abbreviation for the author

	n - if present signifies a document within a work
		when it changes, v-z are nulled but are then independent
	if n is not present, a change in an upper level nulls out the rest

	v-z hierarchical citation levels, high to low

	v
	w
	x - (chapter)
	y - (verse) (book)
	z - line

	Descriptions ---

	z - comment sequence number within a work

	In the common data structures below, citations will hold the first 26 positions (0-25)
	while descriptors will hold the next 26 positions.
*/
int icitation[52];
char citation[52][32];
int id_level;	/* holds translated current id level as an index to ID arrays */
int id_char;	/* holds the pointer for the ascii part of the ID arrays */
int id_command;	/* holds the current instruction for ID handling */
int id_process;	/* if non-zero, command must be processed */


/****************** HANDLE ARGUMENTS AND SYNTAX *******************/

void usage_info(void)
{
	printf("\ntlgu: TLG/PHI beta code file to Unicode translator ver. %s\n", prog_version);
	printf("\ntlgu: Copyright (C) 2004, 2005, 2011 Dimitri Marinakis");
	printf("\ntlgu: This program is free software; you are encouraged to redistribute it under");
	printf("\ntlgu: the terms of the GNU General Public License (version 2).\n");
	printf("\ntlgu: This program comes with ABSOLUTELY NO WARRANTY. See the GNU General Public");
	printf("\ntlgu: License in the file named `COPYING' for more details.\n");
	printf("\ntlgu: Syntax: [-options...] tlgu beta_code_file [unicode_text_file]\n");
	printf("\ntlgu: -r -- primarily Roman text (e.g. Canon, PHI); default betastate = ROMAN, reset on every ID code");
	printf("\ntlgu: -v -w -x -y -z -- work reference citations are printed in the form xxx.xxx...xxx");
	printf("\ntlgu: -Z <custom_citation_format_prefix> -- use reference and description citation codes in string");
	printf("\ntlgu:    reference a-z, description A-Z also special codes \\t(ab) \\n(new line) \\r(eturn)");
	printf("\ntlgu:    e.g. \"%%A/%%Z/%%v/%%w/%%y/%%z\\t\" \n");
	printf("\ntlgu: -e <custom_blank_citation_string> -- e.g. \"[NONE]\" instead of default \"\"");
	printf("\ntlgu: -X -- citations are printed as they change (v, w, x)");
	printf("\ntlgu: -Y -- citations are printed as they change (w, x, y)");
	printf("\ntlgu: -N -- no spaces - line ends, and hyphens before an ID code, are removed");
	printf("\n");
	printf("\ntlgu: -b -- books are preceded by a page feed and description citations are printed");
	printf("\ntlgu: -p -- pagination is observed, otherwise book lines are printed continuously");
	printf("\ntlgu: -B -- output blank space (tab) at the beginning of each line");
	printf("\n");
	printf("\ntlgu: -C -- citation debug information is printed");
	printf("\ntlgu: -S -- special code debug information is printed");
 	printf("\ntlgu: -V -- processing debug information is printed");
	printf("\ntlgu: -W -- multiple output files, one for each work (book); output filename must be specified");
	printf("\n");
}

main(int argc, char * argv[])
{
	unsigned char ucc;	/* test variable */
	int idx;

	if (sizeof(ucc) != 1) {
		printf("\ntlgu: I need 8-bit characters to work\n");
		exit(1);
	}

	if (argc < 2) {
		usage_info();
		exit(1);
	}

	--argc ;
	++argv ;

	while(argc > 1 && argv[0][0] == '-') {
		switch(argv[0][1]) {
			case 'N':
				opt_nospace = 1;
				break;
			case 'W':
				opt_multiple = 1;
				break ;
			case 'V':
				opt_verbose = 1;
				break ;
			case 'S':
				opt_debug_special = 1;
				break ;
			case 'T':
				opt_debug_bracket = 1;
				break ;
			case 'C':
				opt_debug_cit = 1;
				break ;
			case 'X':
				opt_ebook_cit_x = 1;
				opt_ebook_cit_y = 0;
				break;
			case 'Y':
				opt_ebook_cit_y = 1;
				opt_ebook_cit_x = 0;
				break;
			case 'B':
				opt_blank = 1;
				break ;
			case 'p':
				opt_page = 1;
				break ;
			case 'r':
				opt_roman = 1;
				break ;
			case 'a':
				opt_acit = 1;
				opt_cit_id = 1;
				break ;
			case 'b':
				opt_bcit = 1;
				opt_cit_id = 1;
				break ;
			case 'c':
				opt_ccit = 1;
				opt_cit_id = 1;
				break ;
			case 'd':
				opt_dcit = 1;
				opt_cit_id = 1;
				break ;
			case 'v':
				opt_vcit = 1;
				break ;
			case 'w':
				opt_wcit = 1;
				break ;
			case 'x':
				opt_xcit = 1;
				break;
			case 'y':
				opt_ycit = 1;
				break ;
			case 'z':
				opt_zcit = 1;
				break;
			case 'e':
				opt_ecit_blank = 1;
				strcpy(ecite, argv[1]);
				argc-- ;
				argv++ ;
				break;
			case 'Z':
				opt_cprefix = 1;
				strcpy(cformat, argv[1]);
				argc-- ;
				argv++ ;
				break;
			default:
				usage_info() ;
				exit(0) ;
		}
	argc-- ;
	argv++ ;
	}
	if (argc < 2) {
		return tlgu(argv[0], "");
	} else {
		return tlgu(argv[0], argv[1]);
	}
}


/****************** FILE READ-WRITE LOOP **************************/

int tlgu(char *input_file, char *output_file)
{
	int i;      /* counter */
	int j;      /* counter */
	int infile; /* input file descriptor */
	int outfile;/* output file descriptor */

	int icnt;   /* input file bytes read in input buffer */
	int ocnt;   /* output file bytes written */
	int bytes_to_process;	/* bytes read minus bytes already processed */

	int wehaveinput;    /* flag for while */
	int beta_return;    /* process beta return code */

	char new_file[MAXFILELEN];
	struct stat filestat;
	
	/* Open input and output files
	 */
	infile = open(input_file, O_RDONLY);
	if (infile < 0) {
		perror("\ntlgu input file open");
		return(1);
	} else {
		if (strlen(output_file) == 0) {
			outfile = STDOUT_FILENO;
		} else {
			if (strlen(output_file) < MAXFILELEN-5) {
				strcpy(new_file, output_file);
			} else {
				printf("\ntlgu output filename too long - exiting\n");
				return(1);
			}
			outfile = open(new_file, O_WRONLY | O_CREAT | O_TRUNC);
		}
		if (outfile < 0) {
			perror("\ntlgu output file create");
			close(infile);
			return(1);
		}
	}

	/* Initialize citation
	 * and descriptor indicators
	 */
	for (i = 0; i < 52; i++) {
		icitation[i] = 0;
		for (j = 0; j < 32; j++) {
			citation[i][j]=0;
		}
	}

	/* Initialize beta processing defaults
	 * e.g. The TLG Canon needs ROMAN as default
	 * Hellenic should be reset at each ID CODE
	 */
	if (opt_roman) betastate = ROMAN;
	else betastate = HELLENIC;

	/*  Read, process and write file blocks,
	 *  Optionally create one file per book (-W), unless no output file name is specified
	 *  Change file mode (equivalent to chmod 644 output_file),
	 *  and return.
	 *  Note:  Local deblocking usually yields higher speeds
	 */
	wehaveinput = 1;
	while (wehaveinput) {
		/* Read and process beta code in input_buffer */
		icnt = read(infile, input_buffer, sizeof(input_buffer));
		if (icnt == 0) wehaveinput = 0;

		iptr = 0;
		while ((icnt > 0) && (iptr < icnt)) {
			bytes_to_process = icnt - iptr;
			beta_return = process_beta(bytes_to_process);

			/* Write processed data and reset output buffer pointer */
			if (optr > 0) {
				ocnt = write(outfile, output_buffer, optr);
				optr = 0;
				if (ocnt < 0) {
					perror("\ntlgu output file write");
					wehaveinput = 0;
				}
			} else if (beta_return != -2) {  /* no more bytes to write, no book change request */
				if (opt_verbose) printf("\ntlgu: no more bytes to write");
				wehaveinput = 0;    /* signal no more input */
			}
			if ((beta_return == -2) && (outfile != STDOUT_FILENO)) {
			 	/* book change request, close current file and open a new one */
				if (opt_verbose) printf("\ntlgu: book change request: %s", previous_bcit[1]);
				if (close(outfile)) return(1);
				if (chmod(new_file, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) return(1);

				/* request file information and delete zero-length files
				 */
				stat(new_file, &filestat);
				if (filestat.st_size == 0) unlink(new_file);

				sprintf(new_file, "%s-%s.txt", output_file, previous_bcit[1]);
				outfile = open(new_file, O_WRONLY | O_CREAT | O_TRUNC);
				if (outfile < 0) {
					perror("\ntlgu: new_file create");
					close(infile);
					return(1);
				}
			}
		}
	}

	/* Close input and output files,
	 * make output file readable
	 */
	close(infile);
	
	if (opt_verbose) printf("\ntlgu: processing complete\n");
	if (outfile == STDOUT_FILENO) printf("\n");

	if (close(outfile)) {
		perror("\ntlgu output file close");
		return(1);
	}
	if (outfile != STDOUT_FILENO) {
		if (chmod(new_file, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) {
			perror("\ntlgu output file chmod");
			return(1);
		}
	}
	return(0);
}

/****************** PROCESSING *************************************/

/* process_beta:
 * Processes <input_count> bytes in <input_buffer>
 * Returns: -1 for EOF, -2 for book change
 * Changes: iptr
 */
int process_beta (int input_count)
{
	unsigned char inchar;
	unsigned int outcode;
	int processing;
	int iptr_max;       /* holds the calculated maximum input pointer value */
	int return_code;    /* id_code and beta_code bytes written; error if negative */
	char outstring[511];
	char nstring[253];

	return_code = 0;
	/* A beta code stream includes two kinds of data:
	 *   ID data - always has the high bit set.
	 *   Text data - always has the high bit reset.
	 */
	processing = 1;
	iptr_max = iptr + input_count;
	if (opt_verbose) printf("\n\ntlgu: process_beta - %d bytes, iptr = %4.4x, iptr_max = %4.4x", input_count, iptr, iptr_max);
	while (processing) {
		if ((iptr < INRECSIZE) && (iptr < iptr_max)) {
			inchar = input_buffer[iptr++];
			if (optr < OUTRECSIZE) {
				if (inchar == 0) {
					/* do nothing for null characters */
				} else if (inchar > 0x7F) {
					/* ID data - decrement input pointer before processing */
					--iptr;

					/* Reset beta decoding state if roman option specified */
					if (opt_roman) betastate = ROMAN;

					/* Process ID code */
					return_code = id_code(input_count);
					if (return_code == -1) {
						if (opt_verbose) printf("\ntlgu: EOF while processing id code");
						processing = 0;
					} else if (return_code == -2) {
						if (opt_verbose) printf("\ntlgu: book change request");
						processing = 0;
					}
					start_new_line = 1;
				} else {
					/* text data < 0x80 - decrement input pointer before processing */
					--iptr;
					if (start_new_line) {
								/* Write info on (book) citation change */
								if (book_change) {
									if (opt_cit_id) {
										sprintf(outstring, "\n\f[%s]  ", citation[0]);
										output_string(outstring);
										sprintf(outstring, "[%s]  ", citation[1]);
										output_string(outstring);
										sprintf(outstring, "[%s]  ", citation[2]);
										output_string(outstring);
										sprintf(outstring, "[%s]\n", citation[3]);
										output_string(outstring);
									}
									book_change = 0;
								}
								if (opt_nospace) {
									outstring[0] = 0x0;
								}
								else {
									sprintf(outstring, "\n");
								}

								if (opt_blank)
									strcat(outstring, "\t");
								else if (opt_cprefix) {
									strcat(outstring, resolve_cite_format(cformat));
								}
 								else if (opt_ebook_cit_x) {
									if (prev_cit_x != icitation[23]) {
										prev_cit_x = icitation[23];
										if (prev_cit_w != icitation[22]) {
											prev_cit_w = icitation[22];
											sprintf(nstring, "\n[%d.%d] ", icitation[22], icitation[23]);
										} 
										else {
											sprintf(nstring, "\n[%d] ", icitation[23]);
										}
										strcat(outstring, nstring);
									}
								}
 								else if (opt_ebook_cit_y) {
									if (prev_cit_y != icitation[24]) {
										prev_cit_y = icitation[24];
										if (prev_cit_x != icitation[23]) {
											prev_cit_x = icitation[23];
											sprintf(nstring, "\n[%d.%d] ", icitation[23], icitation[24]);
										} 
										else {
											sprintf(nstring, "\n[%d] ", icitation[24]);
										}
										strcat(outstring, nstring);
									}
								}
								else if (opt_vcit || opt_wcit || opt_xcit || opt_ycit || opt_zcit) {
									if (opt_vcit) {
										if (icitation[21] == 0) sprintf(nstring, "%s.", citation[21]);
										else sprintf(nstring, "%d%s.", icitation[21], citation[21]);
										if ((opt_ecit_blank) && (!*nstring)) strcpy(nstring, ecite);
										strcat(outstring, nstring);
									}
									if (opt_wcit) {
										if (icitation[22] == 0) sprintf(nstring, "%s.", citation[22]);
										else sprintf(nstring, "%d%s.", icitation[22], citation[22]);
										if ((opt_ecit_blank) && (!*nstring)) strcpy(nstring, ecite);
										strcat(outstring, nstring);
									}
									if (opt_xcit) {
										if (icitation[23] == 0) sprintf(nstring, "%s.", citation[23]);
										else sprintf(nstring, "%d%s.", icitation[23], citation[23]);
										if ((opt_ecit_blank) && (!*nstring)) strcpy(nstring, ecite);
										strcat(outstring, nstring);
									}
									if (opt_ycit) {
										if (icitation[24] == 0) sprintf(nstring, "%s.", citation[24]);
										else sprintf(nstring, "%d%s.", icitation[24], citation[24]);
										if ((opt_ecit_blank) && (!*nstring)) strcpy(nstring, ecite);
										strcat(outstring, nstring);
									}
									if (opt_zcit) {
										if (icitation[25] == 0) sprintf(nstring, "%s.", citation[25]);
										else sprintf(nstring, "%d%s", icitation[25], citation[25]);
										if ((opt_ecit_blank) && (!*nstring)) strcpy(nstring, ecite);
										strcat(outstring, nstring);
									}
									/* Separate text from citation using a tab character */
									strcat(outstring, "\t");
								}
								if (input_buffer[iptr] < 0x80) {
									/* Print only if not followed by another ID byte */
									output_string(outstring);
								}
						start_new_line = 0;
						if (opt_roman) betastate = ROMAN;
						else betastate = HELLENIC;
					}
					beta_code(input_count);
				}
			} else {
				/* Output size is greater than input -- intermediate write */
				printf("\ntlgu: FIXME -- DATA LOSS: ERROR output size iptr - %x optr - %x", iptr, optr);
				processing = 0;
			}
		} else {
			/* Finished processing all input */
			processing = 0;
		}
	} /* end while processing*/

	if (opt_verbose) printf("\ntlgu: iptr - %4.4x, optr - %4.4x ", iptr, optr);
	return return_code;
}
/****************** LIBRARY FUNCTIONS ******************************/
/* get_acents:
 * gets accents in <accents>
 * Returns: number of accents found or zero
 * Changes: accents, iptr
 */
int get_accents(void)
{
	unsigned char bufferchar;
	int processing = 1;
	int number_of_accents = 0;

	accents = 0;

	while (processing) {
		if (iptr < INRECSIZE) {
			bufferchar = input_buffer[iptr++];
			if (betastate == ROMAN) {
				if (strchr(latin_accent_chars, bufferchar)) {
					store_accents(bufferchar);
					number_of_accents++;
				} else {
					--iptr;
					processing = 0;
				}
			} else if (strchr(accent_chars, bufferchar)) {
					store_accents(bufferchar);
					number_of_accents++;
				} else {
					--iptr;
					processing = 0;
				}
		} else {
			processing = 0;
		}
	}
	return number_of_accents;
}

/* store_accents:
 * Stores accent character passed as a parameter to <accents>
 * 0 00 00 --- 0 00 00 no accent
 * |  |  |
 * |  |   ---- 01 psili, 10 dasia, 11 dialytika
 * |   ------- 01 varia, 10 oxia,  11 perispomeni
 * -----------  1 ypogegrammeni
 * Changes: accents
 * Caveat: currently only ORs new accent... expects an all-zero accent variable
 */
void store_accents(unsigned char bufferchar)
{
	switch (bufferchar)
	{
		case ')':
			accents = accents | 1;
			break;
		case '(':
			accents = accents | 2;
			break;
		case '+':
			accents = accents | 3;
			break;
		case '\\':
			accents = accents | 4;
			break;
		case '/':
			accents = accents | 8;
			break;
		case '=':
			accents = accents | 0xc;
			break;
		case '|':
			accents = accents | 0x10;
			break;
		default:
			break;
	}
	accents &= 0x1f;
}

/* output_accents:
 * Input: <accents>
 * 0 00 00 --- 0 00 00 no accent
 * |  |  |
 * |  |   ---- 01 psili, 10 dasia, 11 dialytika
 * |   ------- 01 varia, 10 oxia,  11 perispomeni
 * -----------  1 ypogegrammeni
 * Changes: optr (output_utf)
 */
void output_accents(void)
{
	int paccents;

	paccents = accents & 3;
	if (paccents == 1)
		output_utf(PSILI);
	else if (paccents == 2)
		output_utf(DASIA);
	else if (paccents == 3)
		output_utf(DIALYTIKA);

	paccents = (accents & 0xc) >> 2;
	if (paccents == 1)
		output_utf(VARIA);
	else if (paccents == 2)
		output_utf(OXIA);
	else if (paccents == 3) {
		if (betastate == ROMAN)
			output_utf(CARET);
		else
			output_utf(PERISPOMENI);
	}
	paccents = accents & 0x10;
	if (paccents)
		output_utf(YPOGEGRAMMENI);
}


/* getnum:
 * Collects a non-zero number from the current <input_buffer> position.
 * Returns: an integer or zero if no number found, -1 on end of buffer
 * Changes: iptr
 * 22-Apr-2006 dm - dropped unsigned attribute from bufferchar and modnumber
 */
 int getnum(void)
{
	#define MAXNUMBERS 32
	char bufferchar;
	char modnumber[MAXNUMBERS];	/* symbol or font modifier number string */
	int imodnumber = 0;	/* index to modnumber */
	int convnumber = 0;	/* converted modnumber string */
	int processing = 1;

	modnumber[0] = 0;

	while (processing) {
		if ( (iptr < INRECSIZE) && (imodnumber < MAXNUMBERS) ) {
			bufferchar = input_buffer[iptr++];
			if (isdigit(bufferchar)) {
				modnumber[imodnumber++] = bufferchar;
			} else {
				--iptr;
				modnumber[imodnumber] = 0;
				sscanf(modnumber, "%d", &convnumber);
				processing = 0;
			}
		} else {
			convnumber = -1;
			processing = 0;
		}
	}
	if (convnumber < 0) perror("\ndid not complete number\n");
	return convnumber;
}

/* output_utf:
 * Converts the input code into a UTF-8 byte sequence in output_buffer
 * Changes: optr, output_buffer
 */
void output_utf(int ucode)
{
	if ((optr+3) > OUTRECSIZE) {
		perror("\noptr out of range");
	} else if (ucode == 0){
		/* do nothing */
	} else if (ucode < 0x80) {
		output_buffer[optr++] = ucode;
	} else if (ucode < 0x800) {
		output_buffer[optr++] = (ucode >> 6) | 0xc0;
		output_buffer[optr++] = (ucode & 0x3f) | 0x80;
	} else if (ucode <= 0xffff) {
		output_buffer[optr++] = ((ucode & 0xf000) >> 12) | 0xe0;
		output_buffer[optr++] = ((ucode & 0x0fc0) >>  6) | 0x80;
		output_buffer[optr++] = (ucode & 0x3f) | 0x80;
	} else {
		/* higher unicodes are ignored */
	}
}

/* output_string:
 * Calls output_utf to write a string in <output_buffer>
 * Returns: the number of bytes written
 * Changes: optr, output_buffer
 */
void output_string(char *outstr)
{
	int nextchar;
	int cnt;

	for (cnt = 0; cnt < strlen(outstr); cnt++) {
		output_utf(outstr[cnt]);
	}
}

/* handle_escape_codes:
 * Formatting and character output based on escape codes: $&%"@#^[]<>{}
 * Input: escape code, optional number
 * Changes: optr, output_buffer
 */
void handle_escape_codes(unsigned char beta, int number)
{
	int temp = 0;

	switch (beta)
	{
		case '$':
			betastate = HELLENIC;
			accents = 0;
			break;
		case '&':
			betastate = ROMAN;
			accents = 0;
			break;
		case '%':
			if (opt_debug_special) printf("%%%d -- %s %d.%d.%d\n", number, citation[1], icitation[23], icitation[24], icitation[25]);
			if (number < MAX_PUNCTUATION)
				output_utf(punctuation[number]);
			break;
		case '\"':
			if (opt_debug_special) printf("\"%d -- %s %d.%d.%d\n", number, citation[1], icitation[23], icitation[24], icitation[25]);
			if (number < MAX_QUOTATION) {
				if (quotation_open[number]) {
					output_utf(quotation_close_symbol[number]);
					quotation_open[number] = 0;
				} else {
					output_utf(quotation_open_symbol[number]);
					quotation_open[number] = 1;
				}
			}
			break;
		case '@':
			/* FIXME: If citations are active, paging should be disabled */
			if (opt_debug_special) printf("@%d -- %s %d.%d.%d\n", number, citation[1], icitation[23], icitation[24], icitation[25]);
			/* Page formats -- FIXME: incomplete */
			if (number == 0) {
				output_utf(0x20);
				output_utf(0x20);
			} else if (number == 1) {
				if (opt_page) output_utf(0xc);
//FIXME: reinstate				else output_utf(0xa);
			} //fixme: reinstate else output_utf(0xa);
			break;
		case '#':
			if (opt_debug_special) printf("#%d -- %s %d.%d.%d\n", number, citation[1], icitation[23], icitation[24], icitation[25]);
			if (number < MAX_TEXT_SYMBOLS) {
				output_utf(text_symbols[number]);
			}
			break;
		case '^':
			/* quarter-spaces: will output at least one space */
			if (number > 0) temp = number / 4;
			while (temp >= 0) {
				output_utf(0x20);
				temp--;
			}
			break;
		case '[':
			if (opt_debug_bracket) printf("[%d -- %s %d.%d.%d\n", number, citation[1], icitation[23], icitation[24], icitation[25]);
			if (number < MAX_BRACKET) {
				output_utf(bracket_open_symbol[number]);
			}
			break;
		case ']':
			if (opt_debug_bracket) printf("]%d -- %s %d.%d.%d\n", number, citation[1], icitation[23], icitation[24], icitation[25]);
			if (number < MAX_BRACKET) {
				output_utf(bracket_close_symbol[number]);
			}
			break;
		case '<':
			if (opt_debug_bracket) printf("<%d -- %s %d.%d.%d\n", number, citation[1], icitation[23], icitation[24], icitation[25]);
			if (number < MAX_QUASI_BRACKET) {
				output_utf(quasi_bracket_open_symbol[number]);
			}
			break;
		case '>':
			if (opt_debug_bracket) printf(">%d -- %s %d.%d.%d\n", number, citation[1], icitation[23], icitation[24], icitation[25]);
			if (number < MAX_QUASI_BRACKET) {
				output_utf(quasi_bracket_close_symbol[number]);
			}
			break;
		case '{':
			if (opt_debug_bracket) printf("{%d -- %s %d.%d.%d\n", number, citation[1], icitation[23], icitation[24], icitation[25]);
			if (number < MAX_NON_TEXT) {
				output_utf(non_text_open_symbol[number]);

			}
			break;
		case '}':
			if (opt_debug_bracket) printf("{%d -- %s %d.%d.%d\n", number, citation[1], icitation[23], icitation[24], icitation[25]);
			if (number < MAX_NON_TEXT) {
				output_utf(non_text_close_symbol[number]);
			}
			break;
		default:
			break;
	}
}

/* which_sigma:
 * Tries to decide on which sigma form to use.
 * Input: index of input_buffer (iptr) after the sigma
 * Returns: output character code
 * 22-Apr-2006 dm -- nextcode less than space will now produce a final sigma, as well
 */
int which_sigma(int nextptr)
{
	int scanning;
	int nextcode;
	/* If the next character is a hyphen, it is a medial sigma
	 * Otherwise, a few characters are examined in the input buffer:
	 * if an alphabetic character is found before we hit a space, or
	 * other punctuation character, it is a medial sigma
	 * otherwise it is a final sigma (there is one exception in 4085 - POS(.))
	 */
	if (input_buffer[iptr] == '-')
		return(SIGMEDIAL);
	else {
		scanning = 10;
		while(scanning) {
			nextcode = input_buffer[nextptr++];
			if (isalpha(nextcode))
				return(SIGMEDIAL);
			if ((nextcode > 0x7f) || (nextcode < 0x20))
				return(SIGFINAL);
			if (strchr(punctuation_codes, nextcode))
				return(SIGFINAL);
			scanning--;
		}
		return(SIGMEDIAL);
	}
}

/* beta_code:
 * Processes <input_count> characters in <input_buffer> and
 * writes processed output to output_buffer>
 * Changes: optr, output_buffer
 * 27-Nov-2011 hyphen handling at the end of a line (opt_nospace)
 */
void beta_code(int input_count)
{
	int processing;
	int input_pointer_max;
	unsigned char betachar;
	unsigned int outputchar;
	int tmp;
	int tmp_iptr;

	input_pointer_max = iptr + input_count;
	processing = 1;

	while (processing) {
		if ( (iptr < INRECSIZE) && (iptr < input_pointer_max) ) {
			betachar = input_buffer[iptr++];
			
			/* Skip hyphen if next character is ID data or spaces */
			if ((betachar == '-') && (opt_nospace)) {
				tmp_iptr = iptr;
				while (input_buffer[iptr] == 0x20) {
					iptr++;
				}
				if (input_buffer[iptr] > 0x7F) {
					betachar = input_buffer[iptr++];
				} else {
					/* Not a space, not an ID code, restore pointer */
					iptr=tmp_iptr;
				}
			}
			if ((betachar > 0x7F)) {
				/* ID data found - restore pointer and stop processing*/
				--iptr;
				processing = 0;
			} else {
				outputchar = 0;

				if (strchr(escape_codes, betachar)) {
					/* Handle escape codes */
					handle_escape_codes(betachar, getnum());
				} else if (betastate == HELLENIC && betachar == '*') {
					/* Handle Hellenic uppercase character */
					get_accents();
					betachar = input_buffer[iptr++];
					if (accents == 0) get_accents(); //FIXME: handle suffix accents differently
					if (strchr(accented_chars, betachar)) {
						switch (betachar) {
							case 'A':
								outputchar = Alpha[accents];
								break;
							case 'E':
								outputchar = Epsilon[accents];
								break;
							case 'H':
								outputchar = Eta[accents];
								break;
							case 'I':
								outputchar = Iota[accents];
								break;
							case 'O':
								outputchar = Omicron[accents];
								break;
							case 'U':
								outputchar = Ypsilon[accents];
								break;
							case 'W':
								outputchar = Omega[accents];
								break;
							case 'R':
								outputchar = Rho[accents];
								break;
							default:
								break;
						}
					} else if (betachar == 'S') {
						tmp = getnum();
						if (tmp == 3) outputchar = SIGLUNATEUPPER;
						else outputchar = SIGMEDIALUPPER;
					} else if (isalpha(betachar)) {
						/* not an accented character */
						outputchar = hellenic[betachar];
					} else {
						outputchar = hellenic[betachar - 0x20];
					}
					if (outputchar == 0) outputchar = hellenic[betachar]; /* error condition */
					output_utf(outputchar);
				} else if (betastate == HELLENIC && isalpha(betachar)) {
					/* Handle hellenic lower case:
					 * Get default character and then try to pin accents
					 */
					if (strchr(accented_chars, betachar)) {
						get_accents();
						switch (betachar) {
							case 'A':
								outputchar = alpha[accents];
								break;
							case 'E':
								outputchar = epsilon[accents];
								break;
							case 'H':
								outputchar = eta[accents];
								break;
							case 'I':
								outputchar = iota[accents];
								break;
							case 'O':
								outputchar = omicron[accents];
								break;
							case 'U':
								outputchar = ypsilon[accents];
								break;
							case 'W':
								outputchar = omega[accents];
								break;
							case 'R':
								outputchar = rho[accents];
								break;
							default:
								break;
						}
					} else if (betachar == 'S') {
						tmp = getnum();
						if (tmp == 1) outputchar = SIGMEDIAL;
						else if (tmp == 2)outputchar = SIGFINAL;
						else if (tmp == 3) outputchar = SIGLUNATE;
						if (outputchar == 0) {
							outputchar = which_sigma(iptr);
						}
					}

					if (outputchar == 0) outputchar = hellenic[betachar - 0x20];
					output_utf(outputchar);
				} else if (betastate == ROMAN && isalpha(betachar)) {
					/* Handle Roman characters */
					//FIXME: need to process roman characters
					if (isalpha(betachar)) get_accents();
					outputchar = betachar;
					output_utf(outputchar);
					/* ROMAN uses combining accent forms */
					output_accents();
				} else {
					//FIXME: placeholder
					if (betachar != '`') outputchar = betachar;
					output_utf(outputchar);
				}
			}
		} else {
			/* Requested number of characters have been processed
			 * or no more characters available in buffer
			 */
			processing = 0;
        	}
	}
}


const char *resolve_cite_format(const char *cformat) {
	static char *outbuf[511];
	char nstring[253];
	*outbuf = 0;
	const char *c;
	for (c = cformat; *c; c++) {
		if (*c == '%') {
			const char c2 = *(c+1);
			signed char cstart = -1;
			if ((c2 >= 'a') && (c2 <= 'z')) {
				cstart = c2 - 'a';
			}
			else if ((c2 >= 'A') && (c2 <= 'Z')) {
				cstart = 26 + (c2 - 'A');
			}
			else if (c2 == '%') {
				*nstring = '%'; nstring[1] = 0; strcat((char *)outbuf, nstring);
			}
			else {
				fprintf(stderr, "unknown escape sequence: %%%c\n", c2);
			}
			c++;		//skip both our '%' and following character (by loop inc);

			if (cstart > 20) {
				if (icitation[cstart] == 0) sprintf(nstring, "%s",citation[cstart]);
				else sprintf(nstring, "%d%s", icitation[cstart], citation[cstart]);
				if ((opt_ecit_blank) && (!*nstring)) strcpy(nstring, ecite);
				strcat((char *)outbuf, nstring);
			}
			else if (cstart > -1) {
				if (!citation[cstart] || !citation[cstart][0]) {
					if (opt_ecit_blank) strcat((char *)outbuf, ecite);
				}
				else {
					strcat((char *)outbuf, citation[cstart]);
				}
			}
		}
		else if (*c == '\\') {
			switch (*(c+1)) {
			case 't': strcat((char *)outbuf, "\t"); break;
			case 'n': strcat((char *)outbuf, "\n"); break;
			case 'r': strcat((char *)outbuf, "\r"); break;
			default: *nstring = *(c+1); nstring[1] = 0; strcat((char *)outbuf, nstring); break;
			}
			c++;		//skip both our '%' and following character (by loop inc);
		}
		else {
			*nstring = *c; nstring[1] = 0; strcat((char *)outbuf, nstring);
		}
	}
	return (char *)outbuf;
}


/* id_code:
 * <iptr> points to the next character in the <input_buffer> to process;
 * <optr> points to the next empty <output_buffer position.
 * Returns: 0 or -1 for EOF
 * 20-Nov-2011 dm -- citation output for e-book option
 */
int id_code(int input_count)
{
	int input_pointer_max;
	int return_code;
	int scratch;
	int processing;
	unsigned char idchar;
	unsigned char outcode;

	return_code = 0;
	input_pointer_max = iptr + input_count;
	processing = 1;
	while (processing) {
		if ((iptr < INRECSIZE) && (iptr < input_pointer_max)) {
			outcode = 0;
			idchar = input_buffer[iptr++];
			if ((idchar < 0x80)) { /* text data - restore pointer and return*/
				--iptr;
				processing = 0;
			} else {  /* ID data - translate and write */
				if (optr < OUTRECSIZE) {
					id_process = 0; /* we don't have a command yet */
					if (idchar >= 0xF0) {
						switch (idchar)
						{
							case 0xF0:  /* EOF */
								return_code = -1; /* indicate EOF */
								processing = 0;
								break;
							case 0xFE:  /* End of block -- block is padded with nulls */
								while (!input_buffer[iptr] && iptr<INRECSIZE) {
									iptr++;
								}
								if (opt_debug_cit) printf("tlgu: EOB %x\n", iptr-1);
								break;
							case 0xFF:  /* End of ASCII string */
								if (opt_debug_cit) printf("tlgu: %d %s\n", id_level, citation[id_level]);
								if (opt_debug_cit) printf("tlgu: EOS %x\n ", iptr-1);
								break;
							case 0xF8:  /* Exception start */
								if (opt_debug_cit) printf("tlgu: Exc start %x\n", iptr-1);
								break;
							case 0xF9:  /* Exception end */
								if (opt_debug_cit) printf("tlgu: Exc end %x\n", iptr-1);
								break;
							default:
								break;
						}
					} else if (idchar >= 0xE0) {
						/* The byte following an escape code is an ID byte
						 * Citation IDs can only be 0=a, 1=b, 2=c and 4=d
						 */
						if (opt_debug_cit) printf("tlgu: Escape %x", idchar);
						id_command = idchar & 0xF;  /* get "command" nybble */
						idchar = input_buffer[iptr++] & 0x7F;  /* get ID level byte */
						if (idchar >= 97) { /* descriptors hold the upper part of the array */
							id_level = idchar - 97 + 26; /* create an index offset */
							if (id_level > 51) {id_level = 51;} /* default to z */
						} else {
							id_level = idchar & 7;    /* must be 0 - 4 */
							if (id_level == 4) {id_level = 3;}    /* adjust d level */
						}
						if (opt_debug_cit) printf(" ID level: %d\n", id_level);
						id_process = 1; /* command must be processed */
					} else if ((idchar >= 0x80) && (id_process == 0)) {
						id_command = idchar & 0xF;  /* get command first */
						scratch = (idchar >> 4) & 0x7;    /* try to create an offset */
						//printf(" %x %x ", idchar, scratch);
						switch (scratch)
						{
							case 0:
								id_level = 25;  /* z */
								id_process = 1; /* command must be processed */
								break;
							case 1:
								id_level = 24;  /* y */
								id_process = 1; /* command must be processed */
								break;
							case 2:
								id_level = 23;  /* x */
								id_process = 1; /* command must be processed */
								break;
							case 3:
								id_level = 22;  /* w */
								id_process = 1; /* command must be processed */
								break;
							case 4:
								id_level = 21;  /* v */
								id_process = 1; /* command must be processed */
								break;
							case 5:
								id_level = 13;  /* n */
								id_process = 1; /* command must be processed */
								break;
							default:
								break;
						}

					}
					if (id_process) {
						switch (id_command)
						{
							case 0:
								icitation[id_level]++;  /* increment ID */
								break;
							case 1:
								icitation[id_level] = 1;  /* literal value */
								break;
							case 2:
								icitation[id_level] = 2;  /* literal value */
								break;
							case 3:
								icitation[id_level] = 3;  /* literal value */
								break;
							case 4:
								icitation[id_level] = 4;  /* literal value */
								break;
							case 5:
								icitation[id_level] = 5;  /* literal value */
								break;
							case 6:
								icitation[id_level] = 6;  /* literal value */
								break;
							case 7:
								icitation[id_level] = 7;  /* literal value */
								break;
							case 8:
								idchar = input_buffer[iptr++];  /* 7 bit binary value */
								icitation[id_level] = idchar & 0x7F;
								break;
							case 9:
								idchar = input_buffer[iptr++];  /* 7 bit binary value */
								icitation[id_level] = idchar & 0x7F;
								idchar = input_buffer[iptr++];  /* single character */
								citation[id_level][0] = idchar & 0x7F;
								citation[id_level][1] = 0;
								break;
							case 0xa:
								idchar = input_buffer[iptr++];  /* 7 bit binary value */
								icitation[id_level] = idchar & 0x7F;
								for (id_char=0; id_char < 31; id_char++) {
									idchar = input_buffer[iptr++];  /* string */
									if (idchar == 0xFF) {
										citation[id_level][id_char] = 0;    /* end of string */
										break;
									} else {
										citation[id_level][id_char] = idchar & 0x7F;
									}
								}
								break;
							case 0xb:
								idchar = input_buffer[iptr++];  /* 14 bit binary value */
								scratch = (idchar & 0x7F) << 7; /* shift upper */
								idchar = input_buffer[iptr++];  /* 14 bit binary value */
								idchar &= 0x7F; /* mask sign bit */
								scratch = scratch | idchar; /* combine */
								icitation[id_level] = scratch;
								break;
							case 0xc:
								idchar = input_buffer[iptr++];  /* 14 bit binary value */
								scratch = (idchar & 0x7F) << 7; /* shift upper */
								idchar = input_buffer[iptr++];  /* 14 bit binary value */
								idchar &= 0x7F; /* mask sign bit */
								scratch = scratch | idchar; /* combine */
								icitation[id_level] = scratch;
								idchar = input_buffer[iptr++];  /* single character */
								citation[id_level][0] = idchar & 0x7F;
								citation[id_level][1] = 0; /* end of string */
								break;
							case 0xd:
								idchar = input_buffer[iptr++];  /* 14 bit binary value */
								scratch = (idchar & 0x7F) << 7; /* shift upper */
								idchar = input_buffer[iptr++];  /* 14 bit binary value */
								idchar &= 0x7F; /* mask sign bit */
								scratch = scratch | idchar; /* combine */
								icitation[id_level] = scratch;
								for (id_char=0; id_char < 31; id_char++) {
									idchar = input_buffer[iptr++];  /* string */
									if (idchar == 0xFF) {
										citation[id_level][id_char] = 0;    /* end of string */
										break;
									} else {
										citation[id_level][id_char] = idchar & 0x7F;
									}
								}
								break;
							case 0xe:
								/* same binary value, single character */
								idchar = input_buffer[iptr++];  /* single character */
								citation[id_level][0] = idchar & 0x7F;
								citation[id_level][1] = 0; /* end of string */
								break;
							case 0xf:
								icitation[id_level] = 0;    /* no binary value */
								for (id_char=0; id_char < 31; id_char++) {
									idchar = input_buffer[iptr++];  /* string */
									if (idchar == 0xFF) {
										citation[id_level][id_char] = 0;    /* end of string */
										break;
									} else {
										citation[id_level][id_char] = idchar & 0x7F;
									}
								}

								/* Keep tab of book changes, optionally split into books */
								if (id_level == 1) {
									if (strncmp(citation[1], previous_bcit[1], 31)) {
										if (opt_multiple) {
											/* Signal outer loop to stop
											 * after processing citation change
											 */
											return_code = -2;
											processing = 0;
											if (opt_verbose) printf("\ntlgu: book citation: %s, previous: %s", citation[1], previous_bcit[1]);
										}
										strncpy(previous_bcit[1], citation[1], 31);
										previous_bcit[1][31] = 0;
									}
									book_change = 1;
								}
								break;
							default:
								printf("tlgu: Unknown id_command: %x, iptr %x\n", id_command, iptr);
								break;
						}
						if (opt_debug_cit) printf("tlgu: Command: %x ID level: %d, Binary: %d, ASCII: %s iptr++ %x\n",\
						id_command, id_level,icitation[id_level], citation[id_level], iptr);

						/* Adjust lower citation levels */
						switch (id_level)
						{
							case 21:
								icitation[22] = 1;
							case 22:
								icitation[23] = 1;
							case 23:
								icitation[24] = 1;
							case 24:
								icitation[25] = 1;
							case 25:
								outcode = 0;
								break;
							default:
								break;
						}
					} /* id_process */

					if (outcode) {
						output_utf(outcode);
					}

				} else {
					--iptr; /* output buffer full - restore pointer and return */
					processing = 0;
				}
			} /* ID data processing */
		} else {     /* Finished processing all input */
			processing = 0;
		}
	} /* while processing loop */
	return return_code;
}
