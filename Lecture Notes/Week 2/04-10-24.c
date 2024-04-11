//A function can have multiple return statements, only 1 will be executed and must be same type
int bigger (int a, int b){
    if (a>b){
        return 1;
    } else {
        return 0;
    }
}
/*
Function type is void IF:
return statement has no expression
return stateement not present at all
*sometimes called procedure function since nothing retured
void identifier(type,arg...typen argn){
    declarations
    statements
    return expression;
}
JIf no params required, use keyword void in place of param list when defining func

type identifier(void){
    declarartions
    statements
    return expression:
}
*/