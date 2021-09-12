# ASCII
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](./LICENSE)

Command line tool for printing entire ASCII Table or a selection of the table.

## Example

```
$ ascii 50 80
  | CHAR | HEX  | DEC |  BINARY  |  | CHAR | HEX  | DEC |  BINARY  |
  +------+------+-----+----------+  +------+------+-----+----------+
  | '2'  |  32  | 050 | 00110010 |  | '8'  |  38  | 056 | 00111000 |
  | '3'  |  33  | 051 | 00110011 |  | '9'  |  39  | 057 | 00111001 |
  | '4'  |  34  | 052 | 00110100 |  | ':'  |  3A  | 058 | 00111010 |
  | '5'  |  35  | 053 | 00110101 |  | ';'  |  3B  | 059 | 00111011 |
  | '6'  |  36  | 054 | 00110110 |  | '<'  |  3C  | 060 | 00111100 |
  | '7'  |  37  | 055 | 00110111 |
  
$ ascii -c @
  | CHAR | HEX  | DEC |  BINARY  |
  +------+------+-----+----------+
  | '@'  |  40  | 064 | 01000000 |
```
