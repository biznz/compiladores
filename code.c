
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

PairList* compileCmdFor(Cmd* cmd);
PairList* compileCmdIf(Cmd* cmd);

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

char* currentLabel(){
  char* dest = malloc(sizeof(char)*5);
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

int isLabel(Instr* instr){
  if(instr->op == LABEL){
    return 1;
  }
  return 0;
}
int isGoto(Instr* instr){
  if(instr->op == GOTO){
    return 1;
  }
  return 0;
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
   if(isLabel(instr)){
  //   //printf("got a label\n");
     printf(" %s:",instr->addr1->content.variable);
     return;
   }
  if(isGoto(instr)){
    printf(" goto %s",instr->addr1->content.variable);
  }
  else if(comparison(instr) == 1){
    //printf(" %s: \n",instr->addr3->content.variable);
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
    if(pair->address->content.variable[0]=='L'){
      printAddress(pair->address);
    printf(":\n");
  }
    if(pair->list)
      printInstrList(pair->list);
  }
}

void printAddress(Address* address){
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
      printPair(list->pair);
      printf("\n");
      printPairList(list->next);
      }
    return;
}

/*
  function creates from Expression 3
  address instructions
*/


PairList* compileCmdList(CmdList* cmdList,PairList* pairList){
  if(!cmdList){return pairList;}
  switch(cmdList->block.command->kind){
        case (E_FORCLAUSE):{
          PairList* forPairs = (PairList*) malloc(sizeof(PairList));
          forPairs = compileCmdFor(cmdList->block.command);
          pairList = appendList(pairList,forPairs);
          break;
          }
        case (E_ATTRIB):{
          Pair* pair = compileCmd(cmdList->block.command);
          PairList* result = mkPairList(pair,NULL);
          pairList = appendList(pairList,result);
          break;
        }
        case (E_IF):{
          PairList* ifPairs = (PairList*) malloc(sizeof(PairList));
          ifPairs = compileCmdIf(cmdList->block.command);
          pairList = appendList(pairList,ifPairs);
          break;
        }
  }
  return compileCmdList(cmdList->block.previous,pairList);
}

/**
  this function builds an instruction list
  from a set of instrLists of a pairLIst
**/

InstrList* buildInstrListFromPairList(PairList* list){
  InstrList* instrList = (InstrList*) malloc(sizeof(InstrList));
  Pair* pair = list->pair;
  instrList = mkList(NULL,pair->list);
  do{
      if(list->next!=0){list=list->next;}
      InstrList* holder = list->pair->list;
      instrList = append(instrList,holder);
  }while(list->next!=0);
  return instrList;
}

InstrList* gotoMkInstrList(Address* address){
  Instr* goto3 = mKInstr(GOTO,address,NULL,NULL);
  return mkList(goto3,NULL);
}

InstrList* labelMkInstrList(Address* address){
  Instr* label = mKInstr(LABEL,address,NULL,NULL);
  return mkList(label,NULL);
}


InstrList* conditionList(Address* addr1,Address* addr2){
  Instr* t1 = mKInstr(ATRIBUTION,addr1,addr2,NULL);
  InstrList* t1List = mkList(t1,NULL);
  return t1List;
}

PairList* compileCmdFor(Cmd* cmd){
      PairList* theList = (PairList*) malloc(sizeof(PairList));
      Pair * result=NULL;

      //var initialization
      Pair* init = compileCmd(cmd->attr.forclause.initStmt);
      InstrList* resultList = mkList(NULL,init->list);

      Pair* the_var = compileExpr(cmd->attr.forclause.condition->attr.op.left);
      Pair* pair = compileExpr(cmd->attr.forclause.condition->attr.op.right);

      Address* addr1 = mkAddrVar(newVar());
      Address* addr2 = mkAddrVar(newVar());
      
      InstrList* t1List = conditionList(addr1,the_var->address);
      InstrList* t2List = conditionList(addr2,pair->address);


      t1List = append(resultList,append(t1List,t2List));
      
      Pair* t1Pair = mkPair(addr1,t1List);
      Pair* t2Pair = mkPair(addr2,t2List);
      
      Instr* varInstr = mKInstr(ATRIBUTION,the_var->address,pair->address,NULL);
      
    // creates  used labels
      Address* L1 = mkAddrVar(newLabel());
      Address* L2 = mkAddrVar(newLabel());
      Address* L3 = mkAddrVar(newLabel());
      Address* L4 = mkAddrVar(newLabel());

      InstrList* labelList = labelMkInstrList(L1);

      InstrList* goto3Instrlist = gotoMkInstrList(L3);      

      Instr* instr = mKInstr(convertOp(cmd->attr.forclause.condition->attr.op.operator),t1Pair->address,t2Pair->address,L2);
      
      InstrList* ifInstrList = mkList(instr,NULL);
      
      PairList* cmd1 = compileCmdList(cmd->attr.forclause.cmdList,NULL);
      
      //adds the label to command body
      cmd1->pair->address = L2;

      InstrList* list1 = buildInstrListFromPairList(cmd1);
      
      Pair* blockCMDpair = mkPair(L2,list1);
      
      PairList* blockCMDpairList= mkPairList(blockCMDpair,NULL);
      
      ifInstrList = append(ifInstrList,goto3Instrlist);
      PairList* ifInstrPairList = mkPairList(mkPair(L1,ifInstrList),NULL);
      
      Pair* forPair = mkPair(t2Pair->address,t1List);
      theList = mkPairList(forPair,NULL);
      theList = appendList(theList,ifInstrPairList);
      
      Address* incVar = mkAddrVar(cmd->attr.forclause.postStmt->attr.attrib.variable);
      Address* incValue = mkAddrInt(1);
      Instr* clausePost = mKInstr(ATRIBUTION,incVar,incVar,incValue);

      InstrList* postList = mkList(clausePost,NULL);
      
      InstrList* goto1Instrlist = gotoMkInstrList(L1);
      InstrList* goto4Instrlist = gotoMkInstrList(L4);
      goto4Instrlist = append(goto4Instrlist,labelMkInstrList(L3));
      
      list1 = append(list1,goto4Instrlist);
      //list1 = append(list1,gotoL4List);
      postList = append(postList,goto1Instrlist);
      theList = appendList(theList,mkPairList(mkPair(L4,postList),NULL));
      theList = appendList(theList,blockCMDpairList);
      return theList;
}


PairList* compileCmdIf(Cmd* cmd){
  
  PairList* theList = (PairList*) malloc(sizeof(PairList));
  Pair * result=NULL;
      //var initialization

  Pair* the_var = compileExpr(cmd->attr.ifcmd.condition->attr.op.left);
  Pair* pair = compileExpr(cmd->attr.ifcmd.condition->attr.op.right);

  Address* addr1 = mkAddrVar(newVar());
  Address* addr2 = mkAddrVar(newVar());
      
  InstrList* t1List = conditionList(addr1,the_var->address);
  InstrList* t2List = conditionList(addr2,pair->address);

  

  //theList = mkPairList(the)
   t1List = append(t1List,t2List);
   //printInstrList(t1List);
      
  Pair* t1Pair = mkPair(addr1,t1List);
  Pair* t2Pair = mkPair(addr2,t2List);
      
  Instr* varInstr = mKInstr(ATRIBUTION,the_var->address,pair->address,NULL);

  Address* L1 = mkAddrVar(newLabel());
  Address* L2 = mkAddrVar(newLabel());
  Address* L3 = mkAddrVar(newLabel());

  InstrList* labelList = labelMkInstrList(L1);

  InstrList* goto3Instrlist = gotoMkInstrList(L3);      

  Instr* instr = mKInstr(convertOp(cmd->attr.ifcmd.condition->attr.op.operator),t1Pair->address,t2Pair->address,L2);
      
  InstrList* ifInstrList = mkList(instr,NULL);
  //printInstrList(ifInstrList);
      
  PairList* cmd1 = compileCmdList(cmd->attr.ifcmd.cmdList,NULL);
  //printPairList(cmd1);
  //     //adds the label to command body
  cmd1->pair->address = L2;

  InstrList* list1 = buildInstrListFromPairList(cmd1);
  list1 = append(list1,goto3Instrlist);
  list1 = append(list1,labelMkInstrList(L3));
      
  Pair* blockCMDpair = mkPair(L2,list1);
      
  PairList* blockCMDpairList= mkPairList(blockCMDpair,NULL);
      
  //ifInstrList = append(ifInstrList,goto3Instrlist);
  PairList* ifInstrPairList = mkPairList(mkPair(L1,ifInstrList),NULL);
      
  Pair* ifPair = mkPair(t2Pair->address,t1List);
  theList = mkPairList(ifPair,NULL);
  theList = appendList(theList,ifInstrPairList);
        
  InstrList* goto1Instrlist = gotoMkInstrList(L1);
      //list1 = append(list1,gotoL4List);
      //postList = append(postList,goto1Instrlist);
      //theList = appendList(theList,mkPairList(mkPair(L4,postList),NULL));
  theList = appendList(theList,blockCMDpairList);
  //printPairList(theList);
  return theList;

}

Pair* compileCmd(Cmd *cmd){
  if(cmd == 0){
    printf("Null expression!!");
  }
  else if(cmd->kind == E_IF){
    printf("IF--------------IF\n");
    // condition compile left and right side
    Pair* the_var = compileExpr(cmd->attr.ifcmd.condition->attr.op.left);
    Pair* pair = compileExpr(cmd->attr.ifcmd.condition->attr.op.right);
    
    char* var1 = newVar();
    Address* addr1 = mkAddrVar(var1);
    char* var2 = newVar();
    Address* addr2 = mkAddrVar(var2);
    
    // creates a new instruction for left and right addresses
    Instr* t1 = mKInstr(ATRIBUTION,addr1,the_var->address,NULL);
    Instr* t2 = mKInstr(ATRIBUTION,addr2,pair->address,NULL);

    InstrList* t1List = mkList(t1,NULL);
    t1List = append(the_var->list,t1List);
    Pair* t1Pair = mkPair(addr1,t1List);

    InstrList* t2List = mkList(t2,NULL);
    t1List = append(t1List,t2List);
    Pair* t2Pair = mkPair(addr2,t2List);

    // creates a new attributuion
    Instr* varInstr = mKInstr(ATRIBUTION,the_var->address,pair->address,NULL);
    InstrList* list = mkList(varInstr,NULL);
    
    list = append(pair->list,list);
    //printInstrList(list);
    Pair* new_pair = mkPair(the_var->address,list);

    char* label1 = newLabel(); //Lx label
    Address* labelAddress = mkAddrVar(label1);

    //creates the if (tx op ty) then C1 instruction (op,tx,ty,label)
    Instr* instr = mKInstr(convertOp(cmd->attr.ifcmd.condition->attr.op.operator),t1Pair->address,t2Pair->address,labelAddress);
    PairList* cmd1 = compileCmdList(cmd->attr.ifcmd.cmdList,NULL);

    //gets a pair list from each pair in if cmdList
    InstrList* list1 = buildInstrListFromPairList(cmd1);

    
    //creates a resulting list with if instr and cmdist body
    InstrList* result = mkList(instr,list1);

    //appends this list to var initialization list
    t1List = append(t1List,result);
    
    //creates the pair (label, ifcmd)
    Pair* ifPair = mkPair(labelAddress,t1List);
    printf("FI--------------FI\n");
    return ifPair;
  }
  else if(cmd->kind == E_ATTRIB){
    //printf("HERE attrib\n");
    Pair* pair = compileExpr(cmd->attr.attrib.value);
    //printPair(pair);
    Expr* variable = ast_var(cmd->attr.attrib.variable);
    Pair* the_var = compileExpr(variable);
    //printPair(the_var);
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
