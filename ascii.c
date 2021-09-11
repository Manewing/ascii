#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

const char AsciiTableHeaderStr[] = "  | CHAR | HEX  | DEC |  BINARY  |";
const char AsciiTableHeaderSep[] = "  +------+------+-----+----------+";
unsigned int AsciiTableHeaderStrLen =
    sizeof(AsciiTableHeaderStr) / sizeof(char);

struct ScreenSize {
  int Columns;
  int Rows;
};

struct ScreenSize getScreenSizeOrDefault() {
  struct winsize Ws;
  struct ScreenSize Ret = {80, 24};
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &Ws)) {
    return Ret;
  }
  Ret.Columns = Ws.ws_col;
  Ret.Rows = Ws.ws_row;
  return Ret;
}

void printBits(unsigned char Value) {
  for (int Shift = 0; Shift < 8; Shift++) {
    printf("%c", ((Value << Shift) & 0x80) ? '1' : '0');
  }
}

const char *getAsciiCharRepr(unsigned char Value) {
  if (Value < 33) {
    static const char *AsciiRepr[33] = {
        "NULL",  "SOH ",  "STX ",  "ETX ",  "EOT ",  "ENQ ",  "ACK ",
        "'\\a'", "'\\b'", "'\\t'", "'\\n'", "'\\v'", "'\\f'", "'\\r'",
        "SO  ",  "SI  ",  "DLE ",  "DC1 ",  "DC2 ",  "DC3 ",  "DC4 ",
        "NAK ",  "SYN ",  "ETB ",  "CAN ",  "EM  ",  "SUB ",  "ESC ",
        "FS  ",  "GS  ",  "RS  ",  "US  ",  "' ' "};
    return AsciiRepr[Value];
  }
  if (Value < 127) {
    static char Buf[] = "'c' ";
    Buf[1] = Value;
    return Buf;
  }
  if (Value == 127) {
    return "DEL ";
  }
  return "'.' ";
}

void printChar(unsigned char Value) { printf("%s", getAsciiCharRepr(Value)); }

void printTableHeader(int NumTables) {
  for (int Idx = 0; Idx < NumTables; Idx++) {
    printf("%s", AsciiTableHeaderStr);
  }
  printf("\n");
  for (int Idx = 0; Idx < NumTables; Idx++) {
    printf("%s", AsciiTableHeaderSep);
  }
  printf("\n");
}

void printTableRow(unsigned char Value) {
  printf("  | ");
  printChar(Value);
  printf(" |  %02X  | %03d | ", Value, Value);
  printBits(Value);
  printf(" |");
}

void printTableRows(int NumTables, int Start, int End) {
  const int RowsPerTable = (End - Start) / NumTables + 1;

  for (int Value = Start; Value < Start + RowsPerTable; Value++) {
    for (int TableIdx = 0; (Value + RowsPerTable * TableIdx) <= End;
         TableIdx++) {
      printTableRow(Value + RowsPerTable * TableIdx);
    }
    printf("\n");
  }
}

void printAsciiTable(int MaxNumTables, int Start, int End) {
  const int MinRowsPerTable = (End - Start) / MaxNumTables + 1;
  const int NumTables = (End - Start) / MinRowsPerTable + 1;

  printTableHeader(NumTables);
  printTableRows(NumTables, Start, End);
}

int main(int Argc, char *Argv[]) {
  int CharStart = 0, CharEnd = 127;
  if (Argc == 2) {
    if (strcmp(Argv[1], "-h") == 0) {
      printf("usage:\n"
             "   ascii -h             - Print this help screen\n"
             "   ascii                - Print entire table [0, 127]\n"
             "   ascii <char value>   - Print only character with given value\n"
             "   ascii <start> <end>  - Print table for [start, end]\n"
             "   ascii -c <char>      - Print value for given character\n");
      return 0;
    }
    CharStart = CharEnd = atoi(Argv[1]);
  } else if (Argc == 3) {
    if (strcmp(Argv[1], "-c") == 0) {
      CharStart = CharEnd = (unsigned char)Argv[2][0];
    } else {
      CharStart = atoi(Argv[1]);
      CharEnd = atoi(Argv[2]);
    }
  }
  if (CharStart < 0 || CharStart > 255 || CharEnd < 0 || CharEnd > 255 ||
      CharStart > CharEnd) {
    CharStart = 0;
    CharEnd = 127;
  }

  struct ScreenSize Size = getScreenSizeOrDefault();
  const int MaxNumTables = Size.Columns / AsciiTableHeaderStrLen;
  printAsciiTable(MaxNumTables, CharStart, CharEnd);
  return 0;
}
