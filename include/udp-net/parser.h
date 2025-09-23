/**
 * @file parser.h
 * @brief definitions for command line parser
 * @author ZASUO01
 */
#ifndef PARSER_H
#define PARSER_H

typedef struct {
    int mode;
} Params;

/** 
 * @brief Parse the command line arguments and set them into a struct.  
 * @return A struct Param containing all the parsed params. 
*/
Params parse_args(int argc, char *argv[]);

#endif