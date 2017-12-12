
// __compiler_h__ definitions
#ifndef __code_h__
#define __code_h__

#include "ast.h"

enum _Opkind{
  ATRIBUTION, 
  ADD, 
  SUB, 
  MUL, 
  DIV,
  GOTO,
  LABEL,
  LTHEN,
  LTEQUAL,
  GTHEN,
  GTEQUAL,
  EQ,
  DIFF
};

enum _AddrKind{
  INTEGER , VARIABLE
};

struct _Address {
  enum _AddrKind kind;
  union{
    int   value;
    char  *variable; 
  }content;
};

struct _Instr {
  enum _Opkind op;
  struct _Address* addr1;
  struct _Address* addr2;
  struct _Address* addr3;
};

//typedef struct InstrList InstrList;

struct _InstrList
{
  struct _Instr* code;
  struct _InstrList* next;
  struct _InstrList* head;
};

struct _Pair
{
struct _Address* address;
struct _InstrList* list;
};

typedef enum _Opkind Opkind;
typedef enum _AddrKind AddrKind;
typedef struct _Address Address;
typedef struct _Pair Pair;
typedef struct _Instr Instr;
typedef struct _InstrList InstrList;
// compileExpr(2*3)
// compileExpr(2) retorna pair(2,null)
// compileExpr(3) retorna pair(3,null)

Instr* mKInstr(Opkind o, Address* a1, Address* a2, Address* a3);
Address* mkAddrInt(int i);
Address* mkAddrVar(char* c);
InstrList* mkList(Instr* r, InstrList* l);
Pair* mkPair(Address* c, InstrList* l); 
void printInstr(Instr* instr);
void printInstrList(InstrList* list);
InstrList* append(InstrList* l1, InstrList* l2);
InstrList* compile_Cmd (Cmd* c);
Pair* compileExpr(Expr* e);

#endif
