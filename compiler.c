#include <stdio.h>
#include "parser.h"
#include "code.h"
#include "ast.h"

InstrList* globalList;




void evalCmdList3(CmdList* cmdList,int spacing){
  PairList* newList = (PairList*) malloc(sizeof(PairList));
  newList = mkPairList(NULL,NULL);
  PairList* list = compileCmdList(cmdList,newList);
  printPairList(list);
}

void evalCmd3_address(Cmd* cmd, int spacing){ //compileCmd
  Pair* result = compileCmd(cmd);
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
      printf("\n");
      evalCmdList3(cmdList,spacing);
      //evalCmdList3_address(cmdList,spacing);
    }
  }while(!feof(yyin));
  printf("\n");
  printf("Exiting\n");
  return 0;
}