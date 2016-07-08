/*
 * EL7373 (Fall 2015) High Performance Switches and Routers
 *
 * Lab 3 - Single String Matching
 *
 * TA: Kuan-yin Chen (kyc257@nyu.edu)
 *     Cing-yu Chu ()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define MAX_TEXT_LEN            10000000                    /* Largest possible text length (chars) */
#define MAX_PATTERN_LEN         1000                        /* Largest possible pattern length (chars)*/


typedef struct
{
    size_t      n_match;        /* # of pattern matches found */
    size_t      n_compare;      /* # of character comparisons performed */
}MatchResult;

int max(int a, int b)
{
    return (a > b) ? a : b;
}


void badCharacters(char* pat,int m, int* badChars)
{
   
   for (int i = 0; i < 256 ; i++) {
	badChars[i] = -1;
   }
 
   for (int i = 0; i < m ; i++) {
	badChars[pat[i]] = i;
   }
}

void suffixes(char *pat, int m, int *suff) 
{
    int a, b, i;
    suff[m - 1] = m;
    b = m - 1;

    for (i = m - 2; i >= 0; --i)
    {
	if (i > b && suff[i + m - 1 - a] < i - b)
        	suff[i] = suff[i + m - 1 - a];
		//printf("Suffixes - suff[%d] = %d a= %d b= %d\n",i,suff[i],a,b);}
	else
	{
         	if (i < b)
            	   b = i;
         	a = i;
         	while (b >= 0 && pat[b] == pat[b + m - 1 - a])
            	   --b;
         	suff[i] = a - b;
		//printf("Suffixes(else) - suff[%d] = %d a= %d b= %d\n",i,suff[i],a,b);
      	}
    }
}

void goodSuffixes(char* pat,int psize, int* goodSuff)
{
    int i,j;
    int suff[MAX_PATTERN_LEN];

    suffixes(pat, psize, suff);
    
    for (i= 0; i < psize; ++i) 
	goodSuff[i] = psize;
	//printf("goodSuffixes - goodSuff[%d] = %d\n",i,goodSuff[i]);        
	
    j = 0;
    for (i = psize - 1; i >= 0; --i)
	if (suff[i] == i + 1)
		for ( ; j < psize - 1 - i; ++j)
            		if (goodSuff[j] == psize)
               		goodSuff[j] = psize - 1 - i;
    			//printf("goodSuffixes(if)i=%d - goodSuff[%d] = %d\n",i,j,goodSuff[j]);}
    for (i = 0; i <= psize - 2; ++i)
    	goodSuff[psize - 1 - suff[i]] = psize - 1 - i;
	//printf("goodSuffixes(for2) i=%d - goodSuff[%d] = %d\n",i,psize - 1 - suff[i],goodSuff[psize - 1 - suff[i]]);}

/*for(i = 0;i<psize;i++)
	printf("goodSuff[%d] = %d\n",i,goodSuff[i]);*/
}



MatchResult boyer_moore(char* text, char* pat)
{
   size_t n = strlen(text);
   size_t m = strlen(pat);

   int i =0;
 
   int shift = 0;
   int goodSuff[MAX_PATTERN_LEN];
   int badChars[256];

/* declare a return structure and initialize */
    MatchResult ret;
    ret.n_match = 0;
    ret.n_compare = 0;

   badCharacters(pat,m,badChars);
   goodSuffixes(pat,m,goodSuff);

   
    while (shift <= (n - m))
    {
	int match = 1;
	int j = m - 1;	
        for(; j >= 0; j--)
	{
	    ret.n_compare ++;	    
	    if (pat[j] != text[shift + j])
	    {
	    	match = 0;
		break;
	    }
	}
 
	
        if (j < 0 && match == 1)
        {
            ret.n_match ++;
	    //printf("A Pattern match is found at location : %d\n", shift); 
            shift += goodSuff[0];	    
        }
 
        else
            shift += max(goodSuff[j], (badChars[text[j + shift]] - n + 1 + j));
    }
	return ret;

}
   
/*
 * main function
 */
int main(int argc, char **argv)
{
    int     ret;                            /* return code */
    double  t0;                             /* clock timer */

    /* argc < 3 means no filename is input from the command line. */
    if( argc < 3 ){
        printf("You forgot to enter trace file and keyword file name!\n");
        exit(1);
    }

    /* Read text from text file. */
    FILE *text_file     = fopen(argv[1], "r");      /* open the text file */
    char* text_str = (char *) malloc (MAX_TEXT_LEN);                    /* string for reading text file */
    size_t text_len = fread(text_str, sizeof(char), MAX_TEXT_LEN, text_file);   /* read file into string */
    if (text_len == 0)                              /* sanity check */
    {
        printf("Text is empty or cannot read text file!\n");
        exit(1);
    }

    printf("Text length = %lu characters\n", text_len);

    /* read pattern from pattern file. */
    FILE *pattern_file  = fopen(argv[2], "r");      /* open the pattern file */
    char pattern_str[MAX_PATTERN_LEN];              /* string for reading text file */
    size_t pattern_len = fread(pattern_str, sizeof(char), MAX_PATTERN_LEN, pattern_file);
                                                    /* read file into string */
    if (pattern_len == 0)                           /* sanity check */
    {
        printf("Pattern is empty or cannot read pattern file!\n");
        exit(1);
    }

    if (pattern_str[pattern_len-1] == '\n')         /* remove trailing newline character */
    {
        pattern_str[pattern_len-1] = '\0';
        pattern_len = strlen(pattern_str);
    }

    printf("Pattern is %s. Pattern length = %lu characters\n", pattern_str, pattern_len);

    t0 = clock();                       /* Record start time */

    /* Run boyer moore string matching */
    MatchResult res = boyer_moore(text_str, pattern_str);

    /* print results */
    printf("Number of matches found = %lu\n", res.n_match);
    printf("Number of character comparison performed = %lu\n", res.n_compare);
    printf("duration: %f sec\n", (clock()-t0)/(double)CLOCKS_PER_SEC );

    return 0;
}
