/*
 * a simple handcoded scanner for the tiger language that accepts source code from stdin
 *
 * TOKENISER ASSUMES THAT COMMENTS ARE REMOVED PRIOR TO THE TOKENISING PROCESS
 *
 */
#include "token.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>



char getnext()
{
	int ch = getchar();
	if( ch == EOF )
		exit(1);
	else
		return (char)ch;
}

int isidchar(char ch)
{
	if ( isalnum(ch) || ch == '_' )
		return 1;
	else return 0;
}

void settok( token* tok,int ival, char* buffer )
{
	tok->ival=ival;
	tok->sval=strdup(buffer);
}

int isWhiteSpace( char ch )
{
	if ( ch == ' ' || ch == '\n' || ch == '\t' )
		return 1;
	else 
		return 0;
}

token* nextToken(token *tok)
{
	char buffer[256];
	char ch;
	int i;
	while( isWhiteSpace ( buffer[0] = getnext() ) )
		;
	buffer[1] = '\0';
	if(isalpha(buffer[0]))
	{
		for( i=1; isidchar( buffer[i] = getnext() ); i++ )
			;
		ungetc( buffer[i],stdin );
		buffer[i]='\0';
		//now buffer contains a string which needs further analysis
		//we first compare all with our array of keywords and if it doesnt match with any,
		//we return token type ID
		for ( int k=0; k < kcount; k++)
		{
			if( strcasecmp( tokens[k],buffer )==0 )
			{
				tok->ival = k;
				tok->sval = strdup(buffer);//add error checking
				return tok;
			}
		}
		// program reached here means no keywords matched with buffer
		// so, buffer must contain a token type ID
		settok( tok, ID,buffer );
		return tok;
	}
	// digit checking
	else if(isdigit(buffer[0]))
	{
		// read till last digit and return digit token
		// if the input is of the form 435sdfasdf, which is invalid, exit with error code
		// use fprintf for printing to stderr and exit
		// so, read till next white-space or special character
		// ie, real all alnums
		for( i=1; isalnum( buffer[i] = getnext() ); i++ )
			;
		ungetc( buffer[i],stdin );
		buffer[i]='\0';
		for ( int k=1; k<i; k++ )
		{
			if( ! isdigit(buffer[k]) )
			{
				fprintf(stderr,"Invalid token: \"%s\" \n exiting...\n",buffer);
				exit(1);
			}
		}
		// control reacing here indicates a valid integer token
		settok( tok, INT,buffer);
		return tok;
	}

	else //it is a special character and need figuring out which one and return token
	// it is better to create an inline function to assign correct values to token struct because 
	// there is a lot of typing to do otherwise
	{
		switch(buffer[0])
		{
			
			case ',':settok( tok, COMMA, buffer );
				 return tok;
			case ':':buffer[1] = getnext();
				buffer[2] = '\0';
				 if ( buffer[1] == '=' )
					settok( tok, ASSIGN, buffer );
				 else
				 {
					ungetc(buffer[1],stdin);
					buffer[1] = '\0';
					settok( tok, COLON, buffer );
				 }
				 return tok;
			case ';':settok( tok, SEMICOLON, buffer );
				 return tok;
			case '(':settok( tok, LPAREN, buffer );
				 return tok;
			case ')':settok( tok, RPAREN, buffer );
				 return tok;
			case '[':settok( tok, LBRACK, buffer );
				 return tok;
			case ']':settok( tok, RBRACK, buffer );
				 return tok;
			case '{':settok( tok, LBRACE, buffer );
				 return tok;
			case '}':settok( tok, RBRACE, buffer );
				 return tok;
			case '.':settok( tok, DOT, buffer );
				 return tok;
			case '+':settok( tok, PLUS, buffer );
				 return tok;
			case '-':settok( tok, MINUS, buffer );
				 return tok;
			case '*':settok( tok, TIMES, buffer );
				 return tok;
			case '/':settok( tok, DIVIDE, buffer );
				 return tok;
			case '=':settok( tok, EQ, buffer );
				 return tok;
			case '!':buffer[1]=getnext();
				 buffer[2] = '\0';
				 if( buffer[1] == '=' )
					 settok( tok, NEQ,buffer );
				 else
				 {
					fprintf(stderr,"Invalid token: \"%s\" \n exiting...",buffer);
					exit(1);
				 }
				 return tok;
			case '<':buffer[1] = getnext();
				 buffer[2] = '\0';
				 if ( buffer[1] == '=' )
					settok( tok, LE, buffer );
				 else
				 {
					ungetc(buffer[1],stdin);
				 	buffer[1] = '\0';
					settok( tok, LT, buffer );
				 }
				 return tok;
			case '>':buffer[1] = getnext();
				 buffer[2] = '\0';
				 if ( buffer[1] == '=' )
					settok( tok, GE, buffer );
				 else
				 {
					ungetc(buffer[1],stdin);
					buffer[1] = '\0';
					settok( tok, GT, buffer );
				 }
				 return tok;
			case '&':settok( tok, AND, buffer );
				 return tok;
			case '|':settok( tok, OR, buffer );
				 return tok;
			case '\"':buffer[1]=getnext();
				 for (i=2; i<256 && buffer[i-1] != '\"' ; i++)
					buffer[i]=getnext() ;
				 buffer[i]='\0';
				 if(i == 256)
				 {
					fprintf(stderr,"max string size is 256\nstring not dequoted");
					exit(1);
				 }
				 settok( tok, STRING,buffer );
				 return tok;
			default: fprintf(stderr,"Invalid token: \"%s\" \n exiting...",buffer);
				 exit(1);
		} // switch
	}//else
}// nextToken()

int main()
{
	token newt;
	token *tok=&newt;
	token *mai;
	while(1)
	{
		mai=nextToken(tok);
		printf("%s ==> %s\n",mai->sval,tokens[mai->ival]);
	}
	return 0;
}


