// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header
#include <stdio.h>
#include <string.h>


CmdList* ast_commandList(Cmd* command,CmdList* list){
  printf("gets here!!!!\n\n");
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

Cmd* ast_if(BExpr* condition,Cmd* commands){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_IF;
  node->attr.ifcmd.condition = condition;
  node->attr.ifcmd.cmd = commands;
  return node;
}

Cmd* ast_ifelse(BExpr* condition,Cmd* commandIf,Cmd* commandElse){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_IFELSE;
  node->attr.ifelse.condition = condition;
  node->attr.ifelse.cmdleft = commandIf;
  node->attr.ifelse.cmdright = commandElse;
  return node;
}

Cmd* ast_for(BExpr* condition,Cmd* commands){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_FOR;
  node->attr.forcmd.condition = condition;
  node->attr.forcmd.cmd = commands;
  return node;
}

Cmd* ast_forclause(Cmd* init,BExpr* condition,Expr* post,CmdList* cmd){
  // ṕrintf("COMMAND LIST");
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  // node->kind = E_FORCLAUSE;
  // node->attr.forclause.initStmt = init;
  // node->attr.forclause.condition = condition;
  // node->attr.forclause.postStmt = post;
  // node->attr.forclause.cmd = cmd;
  return node;
}

Cmd* ast_post(int operator,Expr* var,int i){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  Expr* expr = (Expr*) malloc(sizeof(Expr));
  Expr* operand1 = (Expr*) malloc(sizeof(Expr));
  Expr* operand2 = (Expr*) malloc(sizeof(Expr));

  operand1->kind = E_INTEGER;
  operand1->attr.value = var->attr.value;
  operand2->kind = E_INTEGER;
  operand2->attr.value = i;
  
  expr->kind = E_OPERATION;
  expr->attr.op.operator = operator;
  expr->attr.op.left = operand1;
  expr->attr.op.right = operand2;
  node->attr.attrib.value = expr;
  node->kind = E_ATTRIB;
  node->attr.attrib.variable = strdup(var->attr.var);
  printf("%s = %d %d %i\n",strdup(var->attr.var),var->attr.value,operator,i);
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

BExpr* ast_rBoperation(int operator, BExpr* left, BExpr* right) {
  BExpr* node = (BExpr*) malloc(sizeof(BExpr));
  node->kind = E_RBOPERATION;
  node->attr.bop.operator = operator;
  node->attr.bop.left = left;
  node->attr.bop.right = right;
  return node;
}

/*ExprList* ast_exprlist(Expr* expr,ExprList* next){
	
  ExprList* list = (ExprList*) malloc(sizeof(ExprList));
  list.expr =
}*/

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

