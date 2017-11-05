
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
       struct _BExpr* left;
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
    E_IFELSE
  }kind;
    union {
      struct{
        char* variable;
        struct _Expr* value;  
      }attrib;
      struct{
        struct _BExpr* condition;
        //char *keyword;
        struct _Cmd* cmdleft;
        struct _Cmd* cmdright;
      }ifelse;
      struct{
        struct _BExpr* condition;
        struct _Cmd* cmd;
      }forcmd;
      struct{
        struct _Cmd* initStmt;
        struct _BExpr* condition;
        struct _Expr* postStmt;
        struct _Cmd* cmd;
      }forclause;
      struct{
        struct _BExpr* condition;
        struct _Cmd* cmd;
      }ifcmd; // for binary expressions// for string values used in variables
  } attr;
};

struct _CmdList{
  enum{
    E_CMD
  }kind;
    struct{
      struct _Cmd* command;
      struct _CmdList* next;
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
BExpr* ast_rBoperation(int operator,BExpr* left,BExpr* right);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr* ast_var(char* i);
Cmd* ast_attrib(char* variable,Expr* rightSide);
Cmd* ast_if(BExpr* condition,Cmd* commands);
Cmd* ast_ifelse(BExpr* condition,Cmd* commandIf,Cmd* commandElse);
Cmd* ast_for(BExpr* condition,Cmd* commands);
// Cmd* ast_forclause(Cmd* initStmt,BExpr* condition,Expr* postStmt,Cmd* cmd);
Cmd* ast_forclause(Cmd* initStmt,BExpr* condition,Expr* postStmt,CmdList* cmd);
// Cmd* ast_forclause(Cmd* initStmt,BExpr* condition,Expr* postStmt,Cmd* cmd);
Cmd* ast_post(int operator,Expr* var,int i);
CmdList* ast_commandList(Cmd* command,CmdList* list);

#endif
