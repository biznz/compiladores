
#include <stdlib.h> // for malloc
#include "code.h" // AST header
#include <stdio.h>
#include <string.h>

using namespace std;

int varCounter = 0;


Instr* mKInstr(Opkind o, Address a1, Address a2, Address a3){
  Instr* instr = (Inst*) malloc(sizeof(Instr));
  instr.op = o;
  instr.addr1 = a1;
  instr.addr2 = a2;
  instr.addr3 = a3;
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


ListCode mkList(Instr* r, ListCode* r){
  Listcode* list = (ListCode*) malloc(sizeof(Listcode));
  list.code = r;
  list.next = r;
  return list;
}

Pair* mkPair(Address* addr,Listcode* list){
  Pair* address = (Pair*) malloc(sizeof(Pair));
  address.name = addr;
  address.next = list;
  return address;
}

ListCode* append(ListCode* l1, Listcode* l2){
  Listcode* p;
  if(l1 == NULL) return l2;
  for(p=l1;p->next!=NULL;p = p->next){}
  p->next = l2;
  return l1;
}


Pair* compileExpr(Expr* e){
  Pair* result = (Pair*) malloc(sizeof(Pair));
  //Address addr = 
  if(e->kind == E_INTEGER){
    //mkPair(e,NULL);
    Address intAddress = mkAddrInt(e->value);
    return (mkPair(intAddress,NULL););
  }
  if(e->kind == E_VAR){
   Address varAddress = mkAddrVar(e->var);
    return (mkPair(varAddress,NULL);); 
  }
  //e->kind = E_VAR;
  switch(e->kind)
   cmd PLUS:  p1 = compileExpr(e->attr.left);
              p2 = compileExpr(e->attr.rigth);
              t  = mewVar();
              d  = append(p1->list, p2->list);

  Pair *p = mkPair(mkAddrVar(t), append(d, mKInstr(ADD, mkAddrVar(t), p1->name, p2->name), NULL)); 
    //return (mkPair())
  return p;
  }


  Listcode compileCmd(Cmd *cmd){
  return -1;
}

char* newVar(){
  string var = "t";
  varCounter++;
  char* c = varCounter +'0';
  var+=c;
  return var;
}