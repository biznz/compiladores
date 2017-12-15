
// AST definitions
#ifndef __ast_h__
#define __ast_h__

//AST for expressionLists

// AST for expressions

struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION,
    E_VAR,
    E_POST
  } kind;
  union {
    int value; // for integer values
    char *var;
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions// for string values used in variables
  } attr;
};

//AST for bexpressions
struct _BExpr{
  enum{
    E_BOOL,
    E_ROPERATION,
    E_RBOPERATION
  } kind;
  union{
   int value;
   struct {
       int operator; //logical and relational
       struct _Expr* left;
       struct _Expr* right;
      }op;
    struct {
       int operator; //logical and relational
       struct _Expr* left;
       struct _BExpr* right;
      }bop;
    } attr;
  };

//AST for commands
struct _Cmd{
  enum {
    E_ATTRIB,
    E_FOR,
    E_FORCLAUSE,
    E_IF,
    E_IFELSE,
    E_FUNC,
    E_SSCAN,
    E_SPRINT
  }kind;
    union {
      struct{
        char* variable;
        //struct _Expr* var;
        struct _Expr* value;  
      }attrib;
      struct{
        struct _BExpr* condition;
        //char *keyword;
        struct _CmdList* cmdleft;
        struct _CmdList* cmdright;
      }ifelse;
      struct{
        struct _BExpr* condition;
        struct _CmdList* cmdList;
      }forcmd;
      struct{
        struct _Cmd* initStmt;
        struct _BExpr* condition;
        struct _Cmd* postStmt;
        struct _CmdList* cmdList;
      }forclause;
      struct{
        struct _BExpr* condition;
        struct _CmdList* cmdList;
      }ifcmd; // for binary expressions// for string values used in variables
      struct{
        char* name;
        struct _CmdList* body;
      }func;
      struct{
        char* arg1;
        struct _Expr* valueArg1;
        char* arg2;
        struct _Expr* valueArg2;
        struct _CmdList* body;
      }sscan;
      struct{
        char* arg1;
        struct _Expr* valueArg1;
        struct _CmdList* body;
      }sprint;
  } attr;
};

struct _CmdList{
  enum{
    E_CMD
  }kind;
    struct{
      struct _Cmd* command;
      struct _CmdList* previous;
      struct _CmdList* current;
    }block;
};

typedef struct _Expr Expr; // Convenience typedef
//typedef struct _Expr_List ExprList;
typedef struct _BExpr BExpr;
typedef struct _Cmd Cmd;
typedef struct _CmdList CmdList;

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
BExpr* ast_boolean(int v);
BExpr* ast_roperation(int operator,Expr* left,Expr* right);
BExpr* ast_rboperation(int operator,Expr* left,BExpr* right);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr* ast_var(char* i);
Cmd* ast_attrib(char* variable,Expr* rightSide);
Cmd* ast_if(BExpr* condition,CmdList* commands);
Cmd* ast_ifelse(BExpr* condition,CmdList* commandIf,CmdList* commandElse);
Cmd* ast_for(BExpr* condition,CmdList* commands);
// Cmd* ast_forclause(Cmd* initStmt,BExpr* condition,Expr* postStmt,Cmd* cmd);
Cmd* ast_forclause(Cmd* initStmt,BExpr* condition,Expr* postStmt,CmdList* cmd);
// Cmd* ast_forclause(Cmd* initStmt,BExpr* condition,Expr* postStmt,Cmd* cmd);
Cmd* ast_post(int operator,char* var,int i);
Cmd* ast_sscan(char* var1,char* var2);
Cmd* ast_sprint(char* var1);
CmdList* ast_commandList(Cmd* command,CmdList* list);

#endif
