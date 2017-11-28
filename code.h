
// __compiler_h__ definitions
#ifndef __code_h__
#define __code_h__

#include "ast.h"

enum _Opkind{
  ATRIBUTION, ADD, SUB, MUL, DIV
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
  // enum {
  //   ATRIBUTION, 
  //   ADDTION, 
  //   SUBTRACTION, 
  //   MULTIPLICATION, 
  //   DIVISION
  // }
  // op;
  enum _Opkind op;
  struct _Address* addr1; 
  struct _Address* addr2;
  struct _Address* addr3;
};

//typedef struct ListCode ListCode;

struct _ListCode
{
  struct _Instr* code;
  struct _ListCode* next;
};

struct _Pair
{
struct _Address* address;
struct _ListCode* list;
};

typedef enum _Opkind Opkind;
typedef enum _AddrKind AddrKind;
typedef struct _Address Address;
typedef struct _Pair Pair;
typedef struct _Instr Instr;
typedef struct _ListCode ListCode;
// compileExpr(2*3)
// compileExpr(2) retorna pair(2,null)
// compileExpr(3) retorna pair(3,null)

Instr* mKInstr(Opkind o, Address* a1, Address* a2, Address* a3);
Address* mkAddrInt(int i);
Address* mkAddrVar(char* c);
ListCode* mkList(Instr* r, ListCode* l);
Pair* mkPair(Address* c, ListCode* l); 

ListCode* compile_Cmd (Cmd* c);
Pair* compileExpr(Expr* e);

#endif
