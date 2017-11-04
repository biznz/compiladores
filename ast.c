// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header
#include <stdio.h>
#include <string.h>

Cmd* ast_attrib(char *c,Expr* right){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = E_ATTRIB;
  node->attr.attrib.variable = strdup(c);
  node->attr.attrib.value = right;
  //printf("ATTRIB operation\n");
  //printf("the var %s\n",node->attr.attrib.variable);
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

// Expr* ast_attrib(int v){
//     printf("\nCALLED ATTRIB AST whit value %s\n",v);
//     Expr* node = (Expr*)malloc(sizeof(Expr));
//     node->kind = E_ATTRIB;
//     node->attr.value = v;
//     return node;
// }

Expr* ast_var(char* i){
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_VAR;
  node->attr.var = strdup(i);
  //printf(" variable name %s",node->attr.var);
  return node;
}

// Expr* ast_var(char* v){
//     printf("\nvariabale %s\n",v);
//     Expr* node = (Expr*)malloc(sizeof(Expr));
//     node->kind = E_VAR;
//     node->attr.varValue = v;
//     return node;
// }

BExpr* ast_roperation(int operator, Expr* left, Expr* right) {
  BExpr* node = (BExpr*) malloc(sizeof(BExpr));
  node->kind = E_ROPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
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
  //printf("the op: %d %d %d",operator,node->attr.op.left,node->attr.op.right);
  return node;
}
