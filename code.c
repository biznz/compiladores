
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

PairList* mkPairList(Pair* pair,PairList* list){
  PairList* pairList= (PairList*) malloc(sizeof(PairList));
  pairList->pair = pair;
  pairList->next = list;
}

Pair* mkPair(Address* addr,InstrList* list){
  Pair* pair = (Pair*) malloc(sizeof(Pair));
  pair->address = addr;
  pair->list = list;
  return pair;
}


Opkind convertOp(int op){
  switch(op){
    case EQUAL:{
      //printf("EQUAL\n");
      return EQ;
    }
    case DIFFERENT:{
      //printf("DIFF\n");
      return DIFF;
    }
    case GT:{
      //printf("GT\n");
      return GTHEN;
    }
    case GTE:{
      //printf("GTE\n");
      return GTEQUAL;
    }
    case LT:{
      //printf("LT\n");
      return LTHEN;
    }
    case LTE:{
      //printf("LTE\n");
      return LTEQUAL;
    }
  }
}


int comparison(Instr* instr){
  switch(instr->op){
    case ATRIBUTION:
      {
        return 0;
        break;
      }
    case ADD:
      {
        return 0;
        break;
      }
    case SUB:
      {
        return 0;
        break;
      }
    case DIV:
      {
        return 0;
        break;
      }
    case MUL:
      {
        return 0;
        break;
      }
    default:
      return 1;
  }
}

void printOpKind(Instr* instr){
  switch(instr->op){
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
    case LTHEN:
      {
        printf(" lthen");
        break;
      }
    case LTEQUAL:
      {
        printf(" lthen");
        break;
      }
    case GTHEN:
      {
        printf(" lthen");
        break;
      }
    case GTEQUAL:
      {
        printf(" lthen");
        break;
      }
    case EQ:
      {
        printf(" lthen");
        break;
      }
    case DIFF:
      {
        printf(" lthen");
        break;
      }
    }
}

//Instr* createInstruction()


void printInstr(Instr* instr){
  if(!instr){
    //printf("THIS INSTRUCTION IS NULL\n");
    return;
  }
  if(comparison(instr) == 1){
    printf(" %s: \n",instr->addr3->content.variable);
    printf(" if ");
    if(instr->addr1->kind == INTEGER){
      //print
      printf(" %d ",instr->addr1->content.value);
    }
    else{
      printf(" %s ",instr->addr1->content.variable);
    }
    printOpKind(instr);
    if(instr->addr2->kind == INTEGER){
      printf(" %d ",instr->addr2->content.value);
    }
    else{
      printf(" %s ",instr->addr2->content.variable);
    }
    printf(" goto ");
    printf(" %s ",instr->addr3->content.variable);
    //printOpKind(instr);

  }
   else{
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
    printOpKind(instr);
    if(instr->addr3){
      if(instr->addr3->kind == INTEGER){
    printf(" %d ",instr->addr3->content.value);
      }
    else{
    printf(" %s ",instr->addr3->content.variable);
      }
    }
  }

}

InstrList* append(InstrList* l1, InstrList* l2){
  if(!l1){
    return l2;}
  InstrList* p;
  for(p=l1;p->next!=NULL;p = p->next);
    p->next = l2;
  return l1;
}

PairList* appendList(PairList* l1, PairList* l2){
  if(!l1){return l2;}
  PairList* p;
  for(p=l1;p->next!=NULL;p = p->next);
    p->next = l2;
  return l1;
}



void printPair(Pair* pair){
  if(pair){
    //printf("the address----> ");
    //printAddress(pair->address);
    //printf("the instruction list----> ");
    if(pair->list)
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
  for(p=list;p!=NULL;p = p->next){
    printInstr(p->code);
    printf("\n");
   }
   return;
}


void printPairList(PairList* list){
    if(list){

      //printf(" pair List not null \n");
      printPair(list->pair);
      printf("\n");
      printPairList(list->next);
      }
    //printPairList(list->next);
    return;
}

/*
  function creates from Expression 3
  address instructions
*/


PairList* compileCmdList(CmdList* cmdList){
  PairList* pairList = (PairList*) malloc(sizeof(PairList));
  Cmd* cmd = (Cmd*) malloc(sizeof(Cmd*));
  cmd = cmdList->block.command;
  Pair* pair = compileCmd(cmd);
  //printPair(pair);
  PairList* newList = mkPairList(pair,NULL);
  //printPairList(newList);
  pairList = appendList(NULL,newList);
  //printPairList(pairList);
  do{
    if(cmdList->block.previous!=0){cmdList=cmdList->block.previous;}
    pair = compileCmd(cmdList->block.command);
    newList = mkPairList(pair,NULL);
    pairList = appendList(pairList,newList);
  }while(cmdList->block.previous!=0);
  return pairList;
}

/**
  this function builds an instruction list
  from a set of instrLists of a pairLIst
**/

InstrList* buildInstrListFromPairList(PairList* list){
  printf("building instruction List\n");
  InstrList* instrList = (InstrList*) malloc(sizeof(InstrList));
  //instrList = mkList(NULL,NULL);
  Pair* pair = list->pair;
  //printPair(pair);
  //return;
  instrList = mkList(NULL,pair->list);
  //printInstrList(instrList);
  do{
      if(list->next!=0){list=list->next;}
      InstrList* holder = list->pair->list;
      instrList = append(instrList,holder);
      //printInstrList(instrList);
  }while(list->next!=0);
  //printInstrList(instrList);
  printf("Exiting building instruction list\n");
  return instrList;
}

Pair* compileCmd(Cmd *cmd){
  if(cmd == 0){
    printf("Null expression!!");
  }
  else if(cmd->kind == E_IF){
    //printf("starts building the if\n");
    Pair* the_var = compileExpr(cmd->attr.ifcmd.condition->attr.op.left);
    Pair* pair = compileExpr(cmd->attr.ifcmd.condition->attr.op.right);
    
    char* var1 = newVar();
    Address* addr1 = mkAddrVar(var1);
    char* var2 = newVar();
    Address* addr2 = mkAddrVar(var2);
    
    Instr* t1 = mKInstr(ATRIBUTION,addr1,the_var->address,NULL);
    Instr* t2 = mKInstr(ATRIBUTION,addr2,pair->address,NULL);

    InstrList* t1List = mkList(t1,NULL);
    t1List = append(the_var->list,t1List);
    Pair* t1Pair = mkPair(addr1,t1List);

    InstrList* t2List = mkList(t2,NULL);
    t1List = append(pair->list,t2List);
    Pair* t2Pair = mkPair(addr2,t1List);


    //printPair(t1Pair);
    //printPair(t2Pair);

    //printPair(the_var);
    //printPair(pair);
    //printf("\n");

    Instr* varInstr = mKInstr(ATRIBUTION,the_var->address,pair->address,NULL);
    InstrList* list = mkList(varInstr,NULL);
    list = append(pair->list,list);
    Pair* new_pair = mkPair(the_var->address,list);
    //printPair(new_pair);


    char* label1 = newLabel();
    Address* labelAddress = mkAddrVar(label1);
    //printf("if ");
    Instr* instr = mKInstr(convertOp(cmd->attr.ifcmd.condition->attr.op.operator),t1Pair->address,t2Pair->address,labelAddress);
    PairList* cmd1 = compileCmdList(cmd->attr.ifcmd.cmdList);
    //printPairList(cmd1);

    InstrList* list1 = buildInstrListFromPairList(cmd1);
    
    //Instr* gotoI = mKInstr()
    InstrList* result = mkList(instr,list1);
    Pair* ifPair = mkPair(labelAddress,result);
    //printf("returns the if pair\n");
    return ifPair;
    //printInstrList(result);
    //printf("------------------\n");

    //evalCmdList3_address(cmd->attr.ifcmd.cmdList,0);
  }
  else if(cmd->kind == E_ATTRIB){
    //printf("HERE attrib\n");
    Pair* pair = compileExpr(cmd->attr.attrib.value);
    Expr* variable = ast_var(cmd->attr.attrib.variable);
    Pair* the_var = compileExpr(variable);
    //printf("HERE attrib\n");
    Instr* varInstr = mKInstr(ATRIBUTION,the_var->address,pair->address,NULL);
    InstrList* list = mkList(varInstr,NULL);
    //printInstrList(list);
    list = append(pair->list,list);
    Pair* new_pair = mkPair(the_var->address,list);
    return new_pair;
  }
}


Pair* compileExpr(Expr* e){
  //printf("compileExpr int\n");
  if(e->kind == E_INTEGER){
    Address* intAddress = mkAddrInt(e->attr.value);
    return mkPair(intAddress,NULL);
  }
  if(e->kind == E_VAR){
    //printf("compileExpr char\n");
    Address* varAddress = mkAddrVar(e->attr.var);
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
  InstrList* listToAppend = mkList(instr,NULL);
  InstrList * l3;
  l3=append(l,listToAppend);
  Pair* newPair = mkPair(address,l3);
  return newPair;
}
