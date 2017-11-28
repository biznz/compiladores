
#include <stdlib.h> // for malloc
#include "code.h" // AST header
#include "ast.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>


int varCounter = 0;


Instr* mKInstr(Opkind o, Address* a1, Address* a2, Address* a3){
  Instr* instr = (Instr*) malloc(sizeof(Instr));
  instr->op = o;
  instr->addr1 = a1;
  instr->addr2 = a2;
  instr->addr3 = a3;
  return instr;
}

Address* mkAddrInt(int i){
  Address* address = (Address*) malloc(sizeof(Address));
  address->content.value = i;
  return address; 
}

Address* mkAddrVar(char* s){
  Address* address = (Address*) malloc(sizeof(Address));
  address->content.variable = strdup(s);
  return address; 
}


ListCode* mkList(Instr* r, ListCode* l){
  ListCode* list = (ListCode*) malloc(sizeof(ListCode));
  list->code = r;
  list->next = l;
  return list;
}

Pair* mkPair(Address* addr,ListCode* list){
  Pair* pair = (Pair*) malloc(sizeof(Pair));
  pair->address = addr;
  pair->list = list;
  return pair;
}

ListCode* append(ListCode* l1, ListCode* l2){
  ListCode* p;
  if(l1 == NULL) return l2;
  for(p=l1;p->next!=NULL;p = p->next){}
  p->next = l2;
  return l1;
}



Pair* compileExpr(Expr* e){
  Pair* result = (Pair*) malloc(sizeof(Pair));
  Pair* p1 = (Pair*) malloc(sizeof(Pair));
  Pair* p2 = (Pair*) malloc(sizeof(Pair));
  Instr* intruction = (Instr*) malloc(sizeof(Instr));
  char* t;
  //Address addr = 
  if(e->kind == E_INTEGER){
    //mkPair(e,NULL);
    Address* intAddress = mkAddrInt(e->attr.value);
    Pair* pair = mkPair(intAddress,NULL);
    return pair;
  }
  if(e->kind == E_VAR){
    Address* varAddress = mkAddrVar(e->attr.var);
    Pair* pair = mkPair(varAddress,NULL);
    return pair;
  }
  //e->kind = E_VAR;

  switch(e->attr.op.operator){
    case PLUS: {
              p1 = compileExpr(e->attr.op.left);
              p2 = compileExpr(e->attr.op.right);
              t  = mewVar();
              result  = append(p1->list, p2->list);
              instr = mKInstr(ADD,mkAddrVar(t),p1->address,p2->address);
              break;
              }
  }
  result = mkPair(mkAddrVar(t), append(result, mKInstr(ADD, mkAddrVar(t), p1->address, p2->address)), NULL)); 
    //return (mkPair())
  return result;
  }


  ListCode* compileCmd(Cmd *cmd){
  return NULL;
}

char* newVar(){
  //string var = "t";
  char dest[5];
  char* var="t";
  varCounter++;
  char* c = varCounter +'0';
  strcpy(dest,var);
  strcat(dest,c);
  return dest;
}