#include <stdio.h>
#include "parser.h"
#include "code.h"
#include "ast.h"

// evalInstr(Instr* instr){
//   switch(instr->op){
//     case ATRIBUTION:
//       printf("ATRIBUTION ");
//       break;
//     case ATRIBUTION:
//       printf("ATRIBUTION ");
//       break;
//     case ADD:
//       printf("ADD ");
//       break;
//     case SUB:
//       printf("SUB ");
//       break;
//     case MUL:
//       printf("MUL ");
//       break;
//     case DIV:
//       printf("DIV ");
//       break;
//   }

// }

void evalCmdList3_address(CmdList* cmdList,int spacing){
    //evalCmd(cmdList->block.command,spacing);
   evalCmd3_address(cmdList->block.command,spacing);
   //printTabs(spacing);
   //printf(";\n");
   //cmdList;
   if(cmdList->block.previous!=0){
      //printf("there is a next command\n");
      evalCmdList3_address(cmdList->block.previous,spacing);
   }
}

void evalCmd3_address(Cmd* cmd, int spacing){
  if(cmd == 0){
    printf("Null expression!!");
  }
  else if(cmd->kind == E_ATTRIB){
    Pair* left = compileExpr(ast_var(cmd->attr.attrib.variable));
    Pair* right = compileExpr(cmd->attr.attrib.value);
  }
}

void printPair(Pair* pair){
  if(pair->name->kind==INTEGER)
    printf("%d ",pair->name->content.value);
  else if(pair->name->kind==VARIABLE)
    printf("%s ",pair->name->content.variable);
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
      //printf("func main()\n");
      //evalCmdList(cmdList,spacing);
      evalCmdList3_address(cmdList,spacing);
    }
  }while(!feof(yyin));
  printf("Exiting\n");
  return 0;
}