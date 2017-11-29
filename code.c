
#include <stdlib.h> // for malloc
#include "code.h" // AST header
#include "ast.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>


int varCounter = 0;

/*
  new variable generator

*/
char* newVar(){
  //string var = "t";
  char dest[10];
  varCounter+=1;
  sprintf(dest,"t%d",varCounter);
  return dest;
}

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


InstrList* mkList(Instr* r, InstrList* l){
  InstrList* list = (InstrList*) malloc(sizeof(InstrList));
  list->code = r;
  list->next = l;
  return list;
}

Pair* mkPair(Address* addr,InstrList* list){
  Pair* pair = (Pair*) malloc(sizeof(Pair));
  pair->address = addr;
  pair->list = list;
  return pair;
}

InstrList* append(InstrList* l1, InstrList* l2){
  InstrList* p = (InstrList*) malloc(sizeof(InstrList));;
  if(l2) return l1;
  // for(p=l1;p->next!=NULL;p = p->next){}
  // p->next = l2;
  // return l1;
  return NULL;
}

/*
  function compiles an Expression into 3
  address instructions
*/

void printAddress(Address* address){
  printf("-----Address----\n");
  if(address->kind == INTEGER){
    printf(" %d ",address->content.value);
  }
  else{
    printf(" %s ",address->content.variable);
  }
}

Pair* compileExpr(Expr* e){
  // Pair* result = (Pair*) malloc(sizeof(Pair));
  // Pair* p1 = (Pair*) malloc(sizeof(Pair));
  // Pair* p2 = (Pair*) malloc(sizeof(Pair));
  // Instr* instruction = (Instr*) malloc(sizeof(Instr));
  // InstrList* list;
  // char* t;
  //Address addr = 
  if(e->kind == E_INTEGER){
    //mkPair(e,NULL);
    Address* intAddress = mkAddrInt(e->attr.value);
    printAddress(intAddress);
    result = mkPair(intAddress,NULL);
    return result;
  }
  if(e->kind == E_VAR){
    Address* varAddress = mkAddrVar(e->attr.var);
    printAddress(varAddress);
    result = mkPair(varAddress,NULL);
    return result;
  }
  switch(e->attr.op.operator){
    case PLUS:
      {
        instruction = mKInstr(ADD,mkAddrVar(t),p1->address,p2->address);
        printf("PLUS\n");
        break;
      }
      case SUB:
        {
          instruction = mKInstr(SUB,mkAddrVar(t),p1->address,p2->address);
          printf("SUB\n");
          break;
        }
    case MUL:
        {
          instruction = mKInstr(MUL,mkAddrVar(t),p1->address,p2->address);
          printf("MUL\n");
          break;
        }
    case DIV:
        {
          instruction = mKInstr(DIV,mkAddrVar(t),p1->address,p2->address);
          printf("DIV\n");
          break;
        }
  }
  append(list,mkList(instruction,NULL));
  return NULL;
  //char * newvar = newVar();
  //return mkPair(mkAddrVar(newvar),append(list,mkList(instruction,NULL)));
  // switch(e->attr.op.operator){
  //   case PLUS: 
  //       {
  //         instruction = mKInstr(ADD,mkAddrVar(t),p1->address,p2->address);
  //         break;
  //       }
  //   case SUB:
  //       {
  //         instruction = mKInstr(SUB,mkAddrVar(t),p1->address,p2->address);
  //         break;
  //       }
  //   case MUL:
  //       {
  //         instruction = mKInstr(MUL,mkAddrVar(t),p1->address,p2->address);
  //         break;
  //       }
  //   case DIV:
  //       {
  //         instruction = mKInstr(DIV,mkAddrVar(t),p1->address,p2->address);
  //         break;
  //       }
  // }
  // return mkPair(mkAddrVar(newVar()),append(list,mkList(instruction,NULL)));
  //return NULL;
}



InstrList* compileCmd(Cmd *cmd){
  return NULL;
}
