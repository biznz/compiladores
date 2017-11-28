
// __compiler_h__ definitions
#ifndef __compiler_h__
#define __compiler_h__

typedef struct {
  enum {
    ATRIB, 
    ADD, 
    SUB, 
    MUL, 
    DIV
  }
  op;

  Adress addr1, addr2, addr3;
} Instr;

typedef enum {
  ATRIB, ADD, SUB, MUL, DIV
} Opkind;

typedef enum {
  INT , VAR
} AddrKind;

typedef struct {
  AddrKind kind;
  union{
    int   value;
    char  *variable; 
  }content;
}Address;

typedef struct ListCode ListCode;

struct ListCode
{
  Instr* code;
  ListCode* next;
};

struct Pair
{
Adress* name;
ListCode* next;
};

// compileExpr(2*3)
// compileExpr(2) retorna pair(2,null)
// compileExpr(3) retorna pair(3,null)

Instr* mKInstr(Opkind o, Address a1, Address a2, Address a3);
Address* mkAddrInt(int i);
Address* mkAddrVar(char* c);
ListCode mkList(Instr* r, ListCode *r);
Pair* mkPair(Address* c, ListCode *l); 

ListCode* compile_Cmd (Cmd* c);
Pair* compileExpr(Expr* e);

#endif
