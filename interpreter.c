#include <stdio.h>
#include "parser.h"


void printTabs(int s){
  int a;
  for(a=0;a<s;a++){
    printf(" ");
  }
}

Expr* evalExpr(Expr* expr,int spacing){
  int result = 0;
  if (expr == 0) {
    return NULL;
    //printf("Null expression!!");
  }
  if (expr->kind == E_INTEGER){
    printTabs(spacing);
    printf("%d\n",expr->attr.value);
  }
  if(expr->kind == E_VAR){
    printTabs(spacing);
    printf("%s\n",expr->attr.var);
  }
  Expr* vLeft = (Expr*) malloc(sizeof(Expr));
  Expr* vRight = (Expr*) malloc(sizeof(Expr));
  vLeft= expr->attr.op.left;
  vRight = expr->attr.op.right;
  if(expr->kind == E_OPERATION){
    printTabs(spacing);
    // printf("left:%d ",vLeft->attr.value);
    // printf("right:%d\n",vRight->attr.value);
    switch (expr->attr.op.operator) {
      case PLUS:
        printf("+\n");
        break;
      case MINUS:
        printf("-\n");
        break;
      case TIMES:
        printf("*\n");
        break;
      case DIVISION:
        printf("/\n");
        break;
      case MOD:
        printf("%%\n");
        break;
      case LT:
        printf("<\n");
        break;
      case LTE:
        printf("<=\n");
        break;
      case GT:
        printf(">\n");
        break;
      case GTE:
        printf(">=\n");
        break;
      default: yyerror("Unknown operator!");
    }
    if(vLeft->kind == E_OPERATION || E_ROPERATION){
      evalExpr(vRight,spacing +2);
      evalExpr(vLeft,spacing +2);
    }
    else{
      evalExpr(vLeft,spacing +2);
      evalExpr(vRight,spacing +2);
    }
  }
}

BExpr* evalBExpr(BExpr* bexpr,int spacing){
  // if(bexpr->kind = E_BOOL){
  //   printTabs(spacing);
  //   if()
  //   printf("%d\n",bexpr->attr.value);
  // }
  // if(bexpr->kind == E_VAR){
  //   printTabs(spacing);
  //   printf("%s\n",bexpr->attr.var);
  // }
  if(bexpr->kind == E_ROPERATION){
    Expr* vLeft = (Expr*) malloc(sizeof(Expr));
    Expr* vRight = (Expr*) malloc(sizeof(Expr));
    vLeft= bexpr->attr.op.left;
    vRight = bexpr->attr.op.right;
    printTabs(spacing);
    // printf("left:%d ",vLeft->attr.value);
    // printf("right:%d\n",vRight->attr.value);
    switch (bexpr->attr.op.operator) {
      case LT:
        printf("<\n");
        break;
      case LTE:
        printf("<=\n");
        break;
      case GT:
        printf(">\n");
        break;
      case GTE:
        printf(">=\n");
        break;
      default: yyerror("Unknown operator!");
    }
    if(vLeft->kind == E_ROPERATION){
      evalExpr(vRight,spacing +2);
      evalExpr(vLeft,spacing +2);
    }
    else{
      evalExpr(vLeft,spacing +2);
      evalExpr(vRight,spacing +2);
    }
  }
}

void evalCmd(Cmd* cmd, int spacing){
  if(cmd == 0){
    printf("Null expression!!");
  }
  else if(cmd->kind == E_IF|| cmd->kind == E_FOR){
    if(cmd->kind == E_IF){
      printf("if\n");
    }
    else{
      printf("for\n");
    }
    BExpr* bexpr = cmd->attr.ifcmd.condition;
    Cmd* command = cmd->attr.ifcmd.cmd;
    evalBExpr(bexpr,spacing+2);
    evalCmd(command,spacing +2);

  }
  else if(cmd->kind == E_ATTRIB){
    Expr* exprLeft = ast_var(cmd->attr.attrib.variable);
    exprLeft->kind = E_VAR;
    Expr* exprRight = cmd->attr.attrib.value;
    printTabs(spacing);
    printf("=\n");
    // printf("left:%d ",exprLeft->attr.value);
    // printf("right:%d\n",exprRight->attr.value);
    evalExpr(exprLeft,spacing+2);
    evalExpr(exprRight,spacing+2);
  }
}

int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      yyin = stdin;
    }
  }
  else{
      printf("needs input\n");
      return 0;
  }
  do{
    if(yyparse()==0){
      int spacing = 0;
      evalCmd(cmd,spacing);
    }
  }while(!feof(yyin));
  printf("Exiting\n");
  return 0;
}
