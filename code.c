
#include <stdlib.h> // for malloc
#include "code.h" // AST header
#include "ast.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>


int varCounter = 0;
int labelCounter =0;

/*
  new variable generator

*/
char* newVar(){
  char* dest = malloc(sizeof(char)*5);
  varCounter+=1;
  sprintf(dest,"t%d\0",varCounter);
  return dest;
}
char * newLabel(){
  char* dest = malloc(sizeof(char)*5);
  labelCounter+=1;
  sprintf(dest,"L%d\0",labelCounter);
  return dest;
}

Instr* mKInstr(Opkind o, Address* a1, Address* a2, Address* a3){
  Instr* i = (Instr*) malloc(sizeof(Instr));
  i->op = o;
  i->addr1 = a1;
  i->addr2 = a2;
  i->addr3 = a3;
  return i;
}

Address* mkAddrInt(int i){
  Address* address = (Address*) malloc(sizeof(Address));
  address->kind = INTEGER;
  address->content.value = i;
  return address; 
}

Address* mkAddrVar(char* s){
  Address* address = (Address*) malloc(sizeof(Address));
  address->kind = VARIABLE;
  address->content.variable = strdup(s);
  return address; 
}


InstrList* mkList(Instr* r, InstrList* l){
  InstrList* list = (InstrList*) malloc(sizeof(InstrList));
  list->code = r;
  list->next = l;
  list->head = list;
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
    printf("THIS INSTRUCTION IS NULL\n");
    return;
  }
  if(instr->addr1->kind == INTEGER){
      printf(" %d ",instr->addr1->content.value);
  }
  else{
      printf(" %s = ",instr->addr1->content.variable);
  }
  if(instr->addr2->kind == INTEGER){
    printf(" %d ",instr->addr2->content.value);
  }
  else{
    printf(" %s ",instr->addr2->content.variable);
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
  if(instr->addr3){
    if(instr->addr3->kind == INTEGER){
    printf(" %d ",instr->addr3->content.value);
    }
    else{
    printf(" %s ",instr->addr3->content.variable);
    }
  }

}

InstrList* append(InstrList* l1, InstrList* l2){
  //printf("append\n");
  if(!l1){
    return l2;}
  InstrList* p = (InstrList*) malloc(sizeof(InstrList));
  for(p=l1;p->next!=NULL;p = p->next){
   }
   p->next = (InstrList*) malloc(sizeof(InstrList));
   p->next->code = l2->code;
   p->next->next= l2->next;
  return p;
}



void printPair(Pair* pair){
  if(pair){
    //printf("the address----> ");
    printAddress(pair->address);
    //printf("the instruction list----> ");
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
  if(!list){
    return;
  }
  InstrList* p = (InstrList*) malloc(sizeof(InstrList));
  //printf("IN print instruction---->");
  printf("[ ");
  printInstr(list->code);
  printf(" , ");
  for(p=list;p->next!=NULL;p = p->next){
    // printf("\nwithin the for loop-->");
    printInstr(p->code);
    printf(" , ");
   }
   printf(" ];\n");
   return;
}



/*
  function creates from Expression 3
  address instructions
*/

void compileIF(Cmd* cmd){
  Pair* t1 = compileExpr(cmd->attr.ifcmd.condition->attr.op.left);
  Pair* t2 = compileExpr(cmd->attr.ifcmd.condition->attr.op.right);
  char* label1 = newLabel();
  Instr* instr;
  switch(cmd->attr.ifcmd.condition->attr.op.operator){ 
    case EQUAL:{
      // printf(" if %s EQUAL %s GOTO %s",t1->address->content.variable,
      //   t2->address->content.variable,
      //   label1);
      instr = mKInstr(EQ,t1->address,t2->address,mkAddrVar(label1));
      break;
    }
    case DIFFERENT:{
      instr = mKInstr(DIFF,t1->address,t2->address,mkAddrVar(label1));
      break;
    }
    case GT:{
      // printf(" if %s GT %s GOTO %s",t1->address->content.variable,
      //   t2->address->content.variable,
      //   label1);
      instr = mKInstr(GTHEN,t1->address,t2->address,mkAddrVar(label1));
      break;
    }
    case GTE:{
      instr = mKInstr(GTEQUAL,t1->address,t2->address,mkAddrVar(label1));
      break;
    }
    case LT:{
      printf(" if ");
      printPair(t1);
      printf(" LTHEN ");
      printPair(t2);
      printf(" GOTO %s\n",label1);
      //printf(" if %s LTHEN %s GOTO %s",t1->address->content.variable,t2->address->content.variable,label1);
      instr = mKInstr(LTHEN,t1->address,t2->address,mkAddrVar(label1));
      break;
    }
    case LTE:{
      instr = mKInstr(LTEQUAL,t1->address,t2->address,mkAddrVar(label1));
      break;
    }
  }
  printf("%s: ",label1);
  evalCmdList3_address(cmd->attr.ifcmd.cmdList,0);
}

Pair* compileExpr(Expr* e){
  if(e->kind == E_INTEGER){
    Address* intAddress = mkAddrInt(e->attr.value);
    return mkPair(intAddress,NULL);
  }
  if(e->kind == E_VAR){
    //printf("THIS IS A VARIABLE ");
    Address* varAddress = mkAddrVar(e->attr.var);
    printAddress(varAddress);
    //printf("\n");
    return mkPair(varAddress,NULL);
  }
  Pair* p1 = compileExpr(e->attr.op.left);
  Pair* p2 = compileExpr(e->attr.op.right);
  InstrList* l;
  Instr* instr;
  instr = NULL;
  l = append(p1->list,p2->list);
  char* var = newVar();
  Address* address = mkAddrVar(var);
  switch(e->attr.op.operator){
    case PLUS:{
      instr = mKInstr(ADD,address,p1->address,p2->address);
      break;
    }
    case MINUS:{
      instr = mKInstr(SUB,address,p1->address,p2->address);
      break;
    }
    case TIMES:{
      instr = mKInstr(MUL,address,p1->address,p2->address);
      break;
    }
    case DIVISION:{
      instr = mKInstr(DIV,address,p1->address,p2->address);
      break;
    }
  }
  printInstr(instr);
  printf("\n");
  InstrList* listToAppend = mkList(instr,NULL);
  l=append(l,listToAppend);
  Pair* newPair = mkPair(address,l);
  return newPair;
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
