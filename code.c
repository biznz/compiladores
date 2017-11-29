
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
  char* dest = malloc(sizeof(char)*5);
  varCounter+=1;
  sprintf(dest,"t%d\0",varCounter);
  // printf("%s\n",dest );
  // return dest;
  return dest;
}

Instr* mKInstr(Opkind o, Address* a1, Address* a2, Address* a3){
  //printf("GETS HERE to mkinstr\n");
  Instr* instr = (Instr*) malloc(sizeof(Instr));
  instr->op = o;
  instr->addr1 = a1;
  printAddress(instr->addr1);
  printf("\n");
  instr->addr2 = a2;
  printAddress(instr->addr2);
  printf("\n");
  instr->addr3 = a3;
  printAddress(instr->addr3);
  printf("\n");
  //printf("FINISHES THE FUNCTION\n");
  return instr;
}

Address* mkAddrInt(int i){
  Address* address = (Address*) malloc(sizeof(Address));
  address->kind = INTEGER;
  address->content.value = i;
  return address; 
}

Address* mkAddrVar(char* s){
  Address* address = (Address*) malloc(sizeof(Address));
  //printf(" the variable to make an address with: %s\n",s);
  address->kind = VARIABLE;
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


void printInstr(Instr* instr){
  if(!instr){
    printf("caught null in list instr\n");
    return;
  }
  else if(instr->addr1->kind == INTEGER){
    printf(" %d ",instr->addr1->content.value);
  }
  else{
    printf(" %s ",instr->addr1->content.variable);
  }
  switch(instr->op){
    case ATRIBUTION:
      {
        printf(" = " );
        break;
      }
    case ADD:
      {
        printf(" + " );
        break;
      }
    case SUB:
      {
        printf(" - " );
        break;
      }
    case DIV:
      {
        printf(" / " );
        break;
      }
    case MUL:
      {
        printf(" * " );
        break;
      }
  }
  if(instr->addr2->kind == INTEGER){
    printf(" %d ",instr->addr2->content.value);
  }
  else{
    printf(" %s ",instr->addr2->content.variable);
  }
  if(instr->addr3->kind == INTEGER){
    printf(" %d \n",instr->addr3->content.value);
  }
  else{
    printf(" %s \n",instr->addr3->content.variable);
  }

}

InstrList* append(InstrList* l1, InstrList* l2){
  InstrList* p = (InstrList*) malloc(sizeof(InstrList));;
  if(!l1) return l2;
  for(p=l1;p->next!=NULL;p = p->next){
    p->next = l2;
  }
  return p;
}



void printPair(Pair* pair){
  if(pair){
    printAddress(pair->address);
    printInstrList(pair->list);
  }
  else{
    printf("got a null pair");
  }
}

void printAddress(Address* address){
  //printf("-----Address----\n");
  if(address->kind == INTEGER){
    printf(" %d ",address->content.value);
  }
  else{
    printf(" %s ",address->content.variable);
  }
}

void printInstrList(InstrList* list){
  if(!list) printf("List is NULL\n");
  else{
    InstrList* p = (InstrList*) malloc(sizeof(InstrList));;
    for(p=list;p->next!=NULL;p = p->next){
    printInstr(p->code);
    p->next = list->next;
    }
  }
}



/*
  function compiles an Expression into 3
  address instructions
*/


Pair* compileExpr(Expr* e){
  if(e->kind == E_INTEGER){
    Address* intAddress = mkAddrInt(e->attr.value);
    return mkPair(intAddress,NULL);
  }
  if(e->kind == E_VAR){
    Address* varAddress = mkAddrVar(e->attr.var);
    return mkPair(varAddress,NULL);
  }
  Pair* p1 = compileExpr(e->attr.op.left);
  //printPair(p1);
  Pair* p2 = compileExpr(e->attr.op.right);
  //printPair(p2);
  //printInstrList(append(p1->list,p2->list));
  InstrList* l;
  Instr* instr;
  l = append(p1->list,p2->list);
  printInstrList(l);
  char* var = newVar();
  switch(e->attr.op.operator){
    case PLUS:{
      // Address* address = mkAddrVar(test);
      // printAddress(address);
      instr = mKInstr(ADD,mkAddrVar(var),p1->address,p2->address);
      break;
    }
    case SUB:{
      instr = mKInstr(SUB,mkAddrVar(var),p1->address,p2->address);
      break;
    }
    case MUL:{
      instr = mKInstr(MUL,mkAddrVar(var),p1->address,p2->address);
      break;
    }
    case DIV:{
      instr = mKInstr(DIV,mkAddrVar(var),p1->address,p2->address);
      break;
    }
  }
  //return NULL;
  printInstr(instr);
  return mkPair(mkAddrVar(newVar()),append(l,mkList(instr,NULL)));
}

// Pair* compileExpr(Expr* e){
//   // Pair* result = (Pair*) malloc(sizeof(Pair));
//   // Pair* p1 = (Pair*) malloc(sizeof(Pair));
//   // Pair* p2 = (Pair*) malloc(sizeof(Pair));
//   // Instr* instruction = (Instr*) malloc(sizeof(Instr));
//   // InstrList* list;
//   // char* t;
//   //Address addr = 
//   if(e->kind == E_INTEGER){
//     //mkPair(e,NULL);
//     Address* intAddress = mkAddrInt(e->attr.value);
//     printAddress(intAddress);
//     result = mkPair(intAddress,NULL);
//     return result;
//   }
//   if(e->kind == E_VAR){
//     Address* varAddress = mkAddrVar(e->attr.var);
//     printAddress(varAddress);
//     result = mkPair(varAddress,NULL);
//     return result;
//   }
//   switch(e->attr.op.operator){
//     case PLUS:
//       {
//         instruction = mKInstr(ADD,mkAddrVar(t),p1->address,p2->address);
//         printf("PLUS\n");
//         break;
//       }
//       case SUB:
//         {
//           instruction = mKInstr(SUB,mkAddrVar(t),p1->address,p2->address);
//           printf("SUB\n");
//           break;
//         }
//     case MUL:
//         {
//           instruction = mKInstr(MUL,mkAddrVar(t),p1->address,p2->address);
//           printf("MUL\n");
//           break;
//         }
//     case DIV:
//         {
//           instruction = mKInstr(DIV,mkAddrVar(t),p1->address,p2->address);
//           printf("DIV\n");
//           break;
//         }
//   }
//   append(list,mkList(instruction,NULL));
//   return NULL;
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
//}



InstrList* compileCmd(Cmd *cmd){
  return NULL;
}
