#include <stdio.h>
#include "parser.h"


void printTabs(int s){
  int a;
  for(a=0;a<s;a++){
    printf(" ");
  }
}

Expr* evalExpr(Expr* expr,int nTabs){
  int result = 0;
  if (expr == 0) {
    printf("NULL");
    //yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER){
  //else if (expr->kind == E_INTEGER || expr->kind == E_BOOL) {
    // result = expr->attr.value;
    printTabs(nTabs); 
    printf("%d",expr->attr.value);
  }
  else if(expr->kind == E_VAR){
    printTabs(nTabs);
    printf("%s",expr->attr.var);
  }
  else if(expr->kind == E_OPERATION){
    Expr* vLeft = (Expr*) malloc(sizeof(Expr));
    Expr* vRight = (Expr*) malloc(sizeof(Expr));
    vLeft= expr->attr.op.left;
    vRight = expr->attr.op.right;
    // Expr* vLeft = evalExpr(expr->attr.op.left);
    // Expr* vRight = evalExpr(expr->attr.op.right);
    switch (expr->attr.op.operator) {
      case PLUS:
        printTabs(nTabs); 
        printf("+\n");
        evalExpr(vLeft,nTabs-1);
        evalExpr(vRight,nTabs+1);
        break;
      case MINUS:
        printTabs(nTabs);
        printf("-\n");
        evalExpr(vLeft,nTabs-1);
        evalExpr(vRight,nTabs+1);
        break;
      case TIMES:
        printTabs(nTabs);
        printf("*\n");
        evalExpr(vLeft,nTabs-1);
        evalExpr(vRight,nTabs+1);
        break;
      case DIVISION:
        printTabs(nTabs);
        printf("/\n");
        evalExpr(vLeft,nTabs-1);
        evalExpr(vRight,nTabs+1);
        break;
      case MOD:
        printTabs(nTabs);
        printf("mod\n");
        evalExpr(vLeft,nTabs-1);
        evalExpr(vRight,nTabs+1);
        break;
      // case AND:
      //   printf("result should be %d, %d, %d",vLeft,vRight,(vLeft && vRight));
      //   result = vLeft && vRight;
      //   break;
      // case OR:
      //   result = vLeft || vRight;
      //   break;
      // case ATTRIB:
      //   result = vRight;
      //   break;

      // TODO Other cases here ...
      default: yyerror("Unknown operator!");
    }
  }
  return ;

}

void evalCmd(Cmd* cmd,int nTabs){
  if(cmd == 0){
    printf("CMD is 0\n");
    //yyerror("Null expression!!");
  }
  else if(cmd->kind == E_ATTRIB){
    
    // Expr* exprLeft = (Expr*) malloc(sizeof(Expr));
    // Expr* exprRight = (Expr*) malloc(sizeof(Expr));
    Expr* exprLeft = ast_var(cmd->attr.attrib.variable);
    exprLeft->kind = E_VAR;
    Expr* exprRight = cmd->attr.attrib.value;
    // exprLeft->attr.var = cmd->attr.attrib.value->attr.var;
    // exprRight = cmd->attr.attrib.value;
    //expr->attr.value = cmd->attr.attrib.value.value;
    printTabs(nTabs);
    printf("=\n");
    //printTabs(nTabs-1);
    //printf("/");
    //printTabs(5);
    //printf("\\\n");
    evalExpr(exprLeft,(nTabs-3));
    //printTabs(nTabs);
    evalExpr(exprRight,2);
  }
}

// int eval(BExpr* bexpr) {
//   int result = 0;
//   if (bexpr == 0) {
//     yyerror("Null expression!!");
//   }
//   else if (bexpr->kind == E_BOOL){
//   //else if (expr->kind == E_INTEGER || expr->kind == E_BOOL) {
//     result = bexpr->attr.value; 
//   }
//   // else if(expr->kind = E_ATTRIB){
//   //   result = expr->attr.varValue;
//   // }
//   // else if(expr->kind = E_VAR){
//   //   result = sym[expr->attr.varValue];
//   // }
//   else if(bexpr->kind == E_ROPERATION){
//     int vLeft = eval(bexpr->attr.op.left);
//     switch (expr->attr.op.operator) {
//   //     case PLUS: 
//   //       result = vLeft + vRight; 
//   //       break;
//   //     case MINUS:
//   //       result = vLeft - vRight;
//   //       break;
//   //     case TIMES:
//   //       result = vLeft * vRight;
//   //       break;
//   //     case DIVISION:
//   //       result = vLeft / vRight;
//   //       break;
//   //     case MOD:
//   //       result = vLeft % vRight;
//   //       break;
//   //     case AND:
//   //       printf("result should be %d, %d, %d",vLeft,vRight,(vLeft && vRight));
//   //       result = vLeft && vRight;
//   //       break;
//   //     case OR:
//   //       result = vLeft || vRight;
//   //       break;
//   //     case ATTRIB:
//   //       result = vRight;
//   //       break;
//    }
//   }
//   // else if (expr->kind == E_OPERATION) {
//   //   int vLeft = eval(expr->attr.op.left);
//   //   int vRight = eval(expr->attr.op.right);
//   //   switch (expr->attr.op.operator) {
//   //     case PLUS: 
//   //       result = vLeft + vRight; 
//   //       break;
//   //     case MINUS:
//   //       result = vLeft - vRight;
//   //       break;
//   //     case TIMES:
//   //       result = vLeft * vRight;
//   //       break;
//   //     case DIVISION:
//   //       result = vLeft / vRight;
//   //       break;
//   //     case MOD:
//   //       result = vLeft % vRight;
//   //       break;
//   //     case AND:
//   //       printf("result should be %d, %d, %d",vLeft,vRight,(vLeft && vRight));
//   //       result = vLeft && vRight;
//   //       break;
//   //     case OR:
//   //       result = vLeft || vRight;
//   //       break;
//   //     case ATTRIB:
//   //       result = vRight;
//   //       break;

//   //     // TODO Other cases here ...
//   //     default: yyerror("Unknown operator!");
//   //   }
//   //}
//   return result;
// }
int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      yyin = stdin;
      /*printf("'%s': could not open file\n", *argv);
      return 1;*/
    }
  } //  yyin = stdin
  else{
      printf("needs input\n");
      return 0;
  }
  do{
    if(yyparse()==0){
      printf("****START*****\n");
      //evalCmd(cmd);
      evalCmd(cmd,20);
      printf("\n****END*****\n");
    }
  }
    while(!feof(yyin));
  // while(!feof(yyin)){
  //     if (yyparse()==0){
  //       printf("****START*****\n");
  //       // printf(" is it a command? %d",(cmd->kind == E_ATTRIB));
  //       evalCmd(cmd);
  //       printf("****END*****\n");
  //   }
  // }
  printf("Exiting\n");
  return 0;
}
