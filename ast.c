// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header
#include <stdio.h>
#include <string.h>


CmdList* ast_commandList(Cmd* command,CmdList* list){
  if(list==0){
    // list->block.command = command;
    // list->block.next = NULL;
    CmdList* newList = (CmdList*) malloc(sizeof(CmdList));
    newList->block.command = command;
    newList->block.previous = NULL;
    return newList;
  }
  //printf("new item in list\n");
  CmdList* newList = (CmdList*)malloc(sizeof(CmdList));
  newList->block.command = command;
  newList->block.previous = list;
  return newList;
}

Cmd* ast_attrib(char *c,Expr* right){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_ATTRIB;
  node->attr.attrib.variable = strdup(c);
  node->attr.attrib.value = right;
  //printf("ATTRIB operation\n");
  //printf("the var %s\n",node->attr.attrib.variable);
  return node;
}

Cmd* ast_if(BExpr* condition,CmdList* commands){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_IF;
  node->attr.ifcmd.condition = condition;
  node->attr.ifcmd.cmdList = commands;
  return node;
}

Cmd* ast_ifelse(BExpr* condition,CmdList* commandIf,CmdList* commandElse){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_IFELSE;
  node->attr.ifelse.condition = condition;
  node->attr.ifelse.cmdleft = commandIf;
  node->attr.ifelse.cmdright = commandElse;
  return node;
}

Cmd* ast_for(BExpr* condition,CmdList* commands){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_FOR;
  node->attr.forcmd.condition = condition;
  node->attr.forcmd.cmdList = commands;
  return node;
}

Cmd* ast_forclause(Cmd* init,BExpr* condition,Expr* post,CmdList* cmdList){
  // ṕrintf("COMMAND LIST");
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_FORCLAUSE;
  node->attr.forclause.initStmt = init;
  node->attr.forclause.condition = condition;
  node->attr.forclause.postStmt = post;
  node->attr.forclause.cmdList = cmdList;
  return node;
}

Cmd* ast_sscan(char* var1,char* var2){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_SSCAN;
  node->attr.sscan.arg1 = strdup(var1);
  node->attr.sscan.arg2 = strdup(var2);
  return node;
}

Cmd* ast_sprint(char* var1){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_SPRINT;
  node->attr.sscan.arg1 = strdup(var1);
  return node;
}

Cmd* ast_post(int operator,char* var,int i){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  Expr* expr = (Expr*) malloc(sizeof(Expr));
  Expr* operand1 = (Expr*) malloc(sizeof(Expr));
  Expr* operand2 = (Expr*) malloc(sizeof(Expr));
  operand1 = ast_var(var);
  operand2 = ast_integer(i);
  expr = ast_operation(operator,operand1,operand2);
  //printExpr(expr);
  node = ast_attrib(var,expr);
  return node;
}


Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  //printf(" v : %d",v);
  return node;
}

BExpr* ast_boolean(int b){
  BExpr* node = (BExpr*) malloc(sizeof(BExpr));
  node->kind = E_BOOL;
  node->attr.value = b;
  return node;
}


Expr* ast_var(char* i){
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_VAR;
  node->attr.var = strdup(i);
  //printf(" variable name %s",node->attr.var);
  return node;
}


BExpr* ast_roperation(int operator, Expr* left, Expr* right) {
  BExpr* node = (BExpr*) malloc(sizeof(BExpr));
  node->kind = E_ROPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  // printf("the rop: %d %d %d",operator,node->attr.op.left,node->attr.op.right);
  return node;
}

BExpr* ast_rboperation(int operator, Expr* left, BExpr* right) {
  BExpr* node = (BExpr*) malloc(sizeof(BExpr));
  node->kind = E_RBOPERATION;
  node->attr.bop.operator = operator;
  //printf(" the variable %s \n",strdup(var));
  node->attr.bop.left = left;
  node->attr.bop.right = right;
  return node;
}

/*ExprList* ast_exprlist(Expr* expr,ExprList* next){
	
  ExprList* list = (ExprList*) malloc(sizeof(ExprList));
  list.expr =
}*/

void printExpr(Expr* expr){
  if(expr->kind == E_INTEGER){
    printf(" %d ",expr->attr.value);
  }
  else if(expr->kind == E_VAR){
    printf(" %s ",expr->attr.var);
  }
  else{
    printExpr(expr->attr.op.left);
    printf(" %d ",expr->attr.op.operator);
    printExpr(expr->attr.op.right);
  }
}

Expr* ast_operation
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  // printf("the op: %d %d %d",operator,node->attr.op.left,node->attr.op.right);
  return node;
}

