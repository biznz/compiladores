
// AST definitions
#ifndef __ast_h__
#define __ast_h__

//AST for expressionLists

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_OPERATION,
    E_VAR
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
    E_ROPERATION
  } kind;
  union{
   int value;
   struct {
       int operator; //logical and relational
       struct _Expr* left;
       struct _Expr* right;
      } op;
    } attr;
  };

//AST for commands
struct _Cmd{
  enum {
    E_ATTRIB,
    E_FOR,
    E_IF
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
        //char *keyword;
        struct _Cmd* cmd;
      }ifcmd; // for binary expressions// for string values used in variables
  } attr;
};

typedef struct _Expr Expr; // Convenience typedef
//typedef struct _Expr_List ExprList;
typedef struct _BExpr BExpr;
typedef struct _Cmd Cmd;

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
BExpr* ast_boolean(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr* ast_var(char* i);
Cmd* ast_attrib(char* variable,Expr* rightSide);
BExpr* ast_roperation(int operator,Expr* left,Expr* right);

#endif
