/*
 * A simple parser to parse:
 	S → if E then S else S
	S → begin S L
	S → print E
	L → end
	L → ; S L
	E → num = num
 *
 * Each grammar production is implemented as function that will call other similar functions 
 * if a non-terminal is encountered. Each terminal is stored using an enum.
 * Need to implement getToken() first
 */
