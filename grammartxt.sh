>> "ASSUMPTIONS"
1.	All declaration statements before assignment statements.
2.  List of variables may have only one identifier
3.  Jagged array initialization cannot use variables for values.

>> "PROGRAM BODY"
PROGRAM program cr_op PROGRAMBODY cr_cl
PROGRAMBODY DECLARATION_LIST ASSIGNMENT_LIST
DECLARATION_LIST DECLARATION_STMT DECLARATION_LIST
DECLARATION_LIST DECLARATION_STMT
ASSIGNMENT_LIST ASSIGNMENT_STMT ASSIGNMENT_LIST
ASSIGNMENT_LIST ASSIGNMENT_STMT

>> "DECLARATION STATEMENTS"
DECLARATION_STMT PRIM_DECLARATION_STMT
DECLARATION_STMT RECTARR_DECLARATION_STMT
DECLARATION_STMT JAGGARR_DECLARATION_STMT
>>>>"PRIMITIVE"
PRIM_DECLARATION_STMT declare ID colon PRIM_TYPE semicolon
PRIM_DECLARATION_STMT declare list of variables ID_LIST colon PRIM_TYPE semicolon
ID_LIST ID ID_LIST
ID_LIST ID
PRIM_TYPE integer
PRIM_TYPE real
PRIM_TYPE boolean
>>>> "RECTANGULAR ARRAYS"
RECTARR_DECLARATION_STMT declare ID colon array RANGE_LIST of PRIM_TYPE semicolon
RECTARR_DECLARATION_STMT declare list of variables ID_LIST colon array RANGE_LIST of PRIM_TYPE semicolon
RANGE_LIST RANGE RANGE_LIST
RANGE_LIST RANGE 				
RANGE sq_op RANGE_VAL .. RANGE_VAL sq_cl
RANGE_VAL ID
RANGE_VAL const
>>>> "JAGGED ARRAYS"
JAGGARR_DECLARATION_STMT JAGGARR2D_DECLARATION_STMT
JAGGARR_DECLARATION_STMT JAGGARR3D_DECLARATION_STMT
>>>>>> "2D JAGGED ARRAYS"
JAGGARR2D_DECLARATION_STMT declare ID colon jagged array RANGE sq_op sq_cl of PRIM_TYPE semicolon JAGGARR2D_INIT_LIST
JAGGARR2D_DECLARATION_STMT declare list of variables ID_LIST colon jagged array RANGE sq_op sq_cl of PRIM_TYPE semicolon JAGGARR2D_INIT_LIST
JAGGARR2D_INIT_LIST JAGGARR2D_INIT_STMT JAGGARR2D_INIT_LIST
JAGGARR2D_INIT_LIST JAGGARR2D_INIT_STMT
JAGGARR2D_INIT_STMT R1 sq_op const sq_cl colon size const : values cr_op JAGGARR2D_VAL_LIST cr_cl
JAGGARR2D_VAL_LIST const semicolon JAGGARR2D_VAL_LIST
JAGGARR2D_VAL_LIST const
>>>>>> "3D JAGGED ARRAYS"
JAGGARR3D_DECLARATION_STMT declare ID colon jagged array RANGE sq_op sq_cl sq_op sq_cl of PRIM_TYPE semicolon JAGGARR3D_INIT_LIST
JAGGARR3D_DECLARATION_STMT declare list of variables ID_LIST colon jagged array RANGE sq_op sq_cl sq_op sq_cl of PRIM_TYPE semicolon JAGGARR3D_INIT_LIST
JAGGARR3D_INIT_LIST JAGGARR3D_INIT_STMT JAGGARR3D_INIT_LIST
JAGGARR3D_INIT_LIST JAGGARR3D_INIT_STMT
JAGGARR3D_INIT_STMT R1 sq_op const sq_cl colon size const : values cr_op JAGGARR3D_ROW_LIST cr_cl
JAGGARR3D_ROW_LIST JAGGARR3D_VAL_LIST semicolon JAGGARR3D_VAL_LIST
JAGGARR3D_ROW_LIST JAGGARR3D_VAL_LIST
JAGGARR3D_VAL_LIST const JAGGARR3D_VAL_LIST
JAGGARR3D_VAL_LIST const

>> "ASSIGNMENT STATEMENTS"
ASSIGNMENT_STMT ID equals EXPRESSION semicolon
EXPRESSION BOOL_EXPRESSION
EXPRESSION TERM plus EXPRESSION
EXPRESSION TERM minus EXPRESSION
EXPRESSION TERM
TERM FACTOR * TERM
TERM FACTOR / TERM
TERM FACTOR
FACTOR ID
FACTOR ID sq_op INDEX_LIST sq_cl
INDEX_LIST INDEX INDEX_LIST
INDEX_LIST INDEX
INDEX ID
INDEX const
BOOL_EXPRESSION BOOL_TERM logical_or BOOL_EXPRESSION
BOOL_EXPRESSION BOOL_TERM
BOOL_TERM FACTOR logical_and BOOL_TERM
BOOL_TERM FACTOR