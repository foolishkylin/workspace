#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/********************************************************************
Thought:
    1. use the symbol stack and see through the expression to get
the postfix.
    2. use the digit stack and see through the postfix to get the
result.
********************************************************************/

typedef struct StackNodeDigit{
	double digit;
	struct StackNodeDigit *next;
}StackNodeDigit, *StackDigit;
// the digit stack

typedef struct StackNodeSymbol{
	char symbol;
	struct StackNodeSymbol *next;
}StackNodeSymbol, *StackSymbol;
// the symbol stack

typedef struct Stack{
    StackDigit  TopD;
    StackSymbol TopS;
}*Stack;
// the stack pointer

const char Priority[3][3] = {
// show the Priority between exp and top
       // -   /    (   // top
/* + */  {'=', '<', '>'},
/* * */  {'>', '=', '>'},
/* ( */  {'>', '>', '>'},
// expression
};

char GetPriority(char str, char top);
// get the priority

int Pretreatment(char *str);
// check if the expression is correct and do some pretreatment to the expression

void InsertZero(char *str, int position);
// add some zero to deal with the minus cases

double TopDigit(Stack s);
char TopSymbol(Stack s);
// return the top

void Push(Stack s, double digit, char symbol);
// if symbol == 0 means push digit otherwise push symbol

void Pop(Stack s, char which);
// if which == S, pop symbol otherwise pop digit

int IsEmpty(Stack s, char which);
// check if the stack is empty

char *GetPostfix(Stack s, char *str, char *postfix);
// get the postfix expression

double GetAnswer(Stack s, char *postfix);
// get the answer

double Calculate(double a, char b, double c);
// input the operator and 2 aim and than return the answer

void Do(Stack s, char* str);
// call on other function and give the result out

int main()
{
    char exp[100]; int Isend = 0;
    Stack s = (Stack) malloc (sizeof(struct Stack));
    s->TopD = NULL;
    s->TopS = NULL;

    while (!Isend)
    {
        puts("\n\nPlease enter a expression(q to leave)");
        puts("Such \"-1+2/3\" ");
        if(gets(exp) == NULL)
        {
            puts("Input ERROR");
            while(getchar() != '\n');
        }
        else if(strcmp(exp, "q") == 0) Isend = 1;
        else Do(s, exp);
    }

    return 0;
}

void Do(Stack s, char *str)
{
    char postfix[100] = "";

    if (! Pretreatment(str))
    // check if the exp is right and do some Pretreatment
    {
        puts("ERROR expression");
        return ;
    }
    GetPostfix(s, str, postfix);
    printf("The postfix expression is %s\n", postfix);
    printf("The answer is %.4lf\n", GetAnswer(s, postfix));

    while(s->TopS)
    // clean the stack
    {
        StackSymbol ptr1= s->TopS->next;
        // record the next pointer before it changed
        free(s->TopS);
        s->TopS = ptr1;
    }
    while(s->TopD)
    {
        StackDigit ptr2= s->TopD->next;
        // record the next pointer before it changed
        free(s->TopD);
        s->TopD = ptr2;
    }
    s->TopD = NULL;
    s->TopS = NULL;
}

double GetAnswer(Stack s, char *postfix)
{
    char part[2] = "0";
    // use it to strcat the number string and than use atof to get the double type
    int bit = 0; double data, a, b;
    // a, b are the digit elements pop from the digit stack and use them to cal the result
    for(; postfix[bit]; bit++)
    {
        if (postfix[bit] == ' ') continue;
        if (isdigit(postfix[bit]))
        // digit case
        {
            char snum[10]="";
			int bit_copy = bit;
			while(isdigit(postfix[++bit]) || postfix[bit] == '.');    // see through all digit bit
            bit--;                                                    // prevent cross-border
			for(; bit_copy <= bit; bit_copy++)
			{
				part[0]=postfix[bit_copy];
				strcat(snum,part);
				// add the pieces of number
			}
            data = atof(snum);
            Push(s, data, 0);
        }
        else
        {
            b = TopDigit(s); Pop(s, 'D');
            a = TopDigit(s); Pop(s, 'D');
            Push(s, Calculate(a, postfix[bit], b), 0);
        }
    }
    return TopDigit(s);
}

double Calculate(double a, char b, double c)
{
    double answer;
    switch (b)
    {
        case '+':   answer = a + c; break;
        case '-':   answer = a - c; break;
        case '*':   answer = a * c; break;
        case '/':   if(c == 0)
                    {
                        puts("The dividend cannot be zero");
                        return 0;
                    }
                    answer = a / c; break;
        default:    puts("ERROR in cal");
    }
    return answer;
}

char *GetPostfix(Stack s, char *str, char *postfix)
{
    char part[2] = "0", divide[2] = " ";
    // use divide to add spaces after bits so that the postfix will be more pretty to see
    int bit = 0;
    for (; str[bit]; bit++)
    {
        if (str[bit] == ' ') continue;
        if (isdigit(str[bit]))
        // digit case
        {
            char snum[10]="";
			int bit_copy = bit;
			while(isdigit(str[++bit]) || str[bit] == '.');
            bit--;
			for(; bit_copy <= bit; bit_copy++)
			{
				part[0]=str[bit_copy];
				strcat(snum,part);
			}
			strcat(postfix, snum);
            strcat(postfix, divide);
        }
        else if (str[bit] == '+' || str[bit] == '-' || str[bit] == '*' ||
                 str[bit] == '/' || str[bit] == '(' || str[bit] == ')'  )
        // symbol case
        {
            if (IsEmpty(s, 'S'))
            // if the stack symbol is empty
                Push(s, 0, str[bit]);
            else
            {
                if (str[bit] == ')')
                // if the bit is ), pop until (
                {
                    while(TopSymbol(s) != '(')
                    {

                        part[0] = TopSymbol(s);
                        strcat(postfix, part);
                        strcat(postfix, divide);
                        Pop(s, 'S');
                    }
                    Pop(s, 'S');
                }
                else
                    switch (GetPriority(str[bit], TopSymbol(s)))
                    {
                        case '>' :  Push(s, 0, str[bit]); break;
                        case '=' :
                        case '<' :  part[0] = TopSymbol(s);
                                    strcat(postfix, part);
                                    strcat(postfix, divide);
                                    if(!IsEmpty(s, 'S')) Pop(s, 'S');
                                    bit--; break;
                        default :puts("ERROR in get postfix"); return 0;
                    }
            }
        }

    }
    while(!IsEmpty(s, 'S'))
    {
        part[0] = TopSymbol(s);
        strcat(postfix, part);
        strcat(postfix, divide);
        Pop(s, 'S');
    }
    return postfix;
}

char GetPriority(char str, char top)
{
    int raw, col;
    switch (str)
    {
        case '+':
        case '-': raw = 0; break;
        case '*':
        case '/': raw = 1; break;
        case '(': raw = 2; break;
        default :puts("ERROR in GetPriority"); return 0;
    }
    switch (top)
    {
        case '+':
        case '-': col = 0; break;
        case '*':
        case '/': col = 1; break;
        case '(': col = 2; break;
        default :puts("ERROR in get GetPriority"); return 0;
    }
    return Priority[raw][col];
}

int IsEmpty(Stack s, char which)
{
    if (which == 'D')
        return s->TopD == NULL;
    else
        return s->TopS == NULL;
}

int Pretreatment(char *str)
{
    int pos, len = strlen(str);
    if (!isdigit(str[len-1])) return 0;
    for (pos = 0; pos < len; pos++)
        if(! ((str[pos] >= '0' && str[pos] <= '9') || str[pos] == '+' || str[pos] == '('
            || str[pos] == '-' || str[pos] == '*'  || str[pos] == '/' || str[pos] == ')'
            || str[pos] == '.' || str[pos] == ' '  ))
            return 0;
    pos = 0;
    while(str[pos] == ' ') pos++;
    if (str[pos] == '-')
        InsertZero(str, pos);
    // add 0 before - to deal with the minus case
    for (pos = 0; str[pos]; pos++)
    {
        if(str[pos] == '(' && str[pos+1] == '-')
           InsertZero(str, pos+1);
    }

    return 1;
}

void InsertZero(char *str, int position)
{
    int len = strlen(str);
    str[len+1] = 0;
    while(len--)
    {
        str[len+1] = str[len];
        if(position == len) break;
    }
    str[position] = '0';
}

void Push(Stack s, double digit, char symbol)
{
    if (symbol == 0)
    // push in stack digit
    {
        StackDigit ptr1 = s->TopD;

        s->TopD = (StackDigit) malloc (sizeof(StackNodeDigit));
        s->TopD->digit = digit;
        s->TopD->next = ptr1;
    }
    else
    // push in stack symbol
    {
        StackSymbol ptr2 = s->TopS;

        s->TopS = (StackSymbol) malloc (sizeof(StackNodeSymbol));
        s->TopS->symbol = symbol;
        s->TopS->next = ptr2;
    }
}

double TopDigit(Stack s)
{
    if(s->TopD == NULL)
    {
        puts("ERROR in top d");
        return 0;
    }
    return s->TopD->digit;
}

char TopSymbol(Stack s)
{
    if(s->TopS == NULL)
    {
        puts("ERROR in top s");
        return 0;
    }
    return s->TopS->symbol;
}

void Pop(Stack s, char which)
{
    if (which == 'D')
    {
        if(s->TopD == NULL)
        {
            puts("ERROR in pop d");
            return ;
        }
        StackDigit ptr = s->TopD;

        s->TopD = s->TopD->next;
        free(ptr);
    }
    else if (which == 'S')
    {
        if(s->TopS == NULL)
        {
            puts("ERROR in pop d");
            return ;
        }
        StackSymbol ptr = s->TopS;

        s->TopS = s->TopS->next;
        free(ptr);
    }
}


