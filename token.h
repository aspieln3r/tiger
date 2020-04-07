/*
 * token structure definition and token types definitions
 */

typedef struct 
{
	int ival;
	char* sval;
}token;

char* tokens[] = {
	//keywords first
	"ARRAY", "BREAK", "DO", "ELSE", "END", "FOR", "FUNCTION", "IF", "IN",
	"LET", "NIL", "OF", "THEN", "TO", "TYPE", "VAR", "WHILE",
	//special characters
	"COMMA","COLON","SEMICOLON","LPAREN","RPAREN","LBRACK","RBRACK","LBRACE","RBRACE",
	"DOT","PLUS","MINUS","TIMES","DIVIDE","EQ","NEQ","LT","LE","GT","GE","AND","OR",
	"ASSIGN",
	//others
	"ID", "STRING", "INT"
};

int kcount = 17;
int scount = 23;
int tcount = sizeof(tokens)/sizeof(tokens[1]); // no of tokens in our language
//this works even though the strings are of variable length, because
//keywords is an array of addresses to strings. Not an array of strings itself.

char* tokname(int tok) {
  return tok<1 || tok>43 ? "BAD_TOKEN" : tokens[tok];
}

//------------------------------------------------------------------------------------------
# define ARRAY 0
# define BREAK 1
# define DO 2
# define ELSE 3
# define END 4
# define FOR 5
# define FUNCTION 6
# define IF 7
# define IN 8
# define LET 9
# define NIL 10
# define OF 11
# define THEN 12
# define TO 13
# define TYPE 14
# define VAR 15
# define WHILE 16
//------------------------------------------------------------------------------------------
# define COMMA 17			// ,
# define COLON 18			// :
# define SEMICOLON 19			// ;  
# define LPAREN 20			// (  
# define RPAREN 21			// )  
# define LBRACK 22			// [  
# define RBRACK 23			// ]  
# define LBRACE 24			// {  
# define RBRACE 25			// }  
# define DOT 26  			// .
# define PLUS 27 			// +
# define MINUS 28			// -
# define TIMES 29			// *
# define DIVIDE 30			// /  
# define EQ 31   			// =
# define NEQ 32  			// !=
# define LT 33   			// <
# define LE 34   			// <=
# define GT 35  			// >
# define GE 36   			// >=
# define AND 37  			// &
# define OR 38   			// |
# define ASSIGN 39			// := 
//------------------------------------------------------------------------------------------
# define ID 40				// [a-zA-Z]*[0-9]*
# define STRING 41                      // ".*"
# define INT 42                         // [0-9]*
