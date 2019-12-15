#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define MAX_STACK_SIZE 1000
#define MAX_LINE 20
#define MAX_COL 100
/*
	SIGN: 计算符
*/
typedef struct Input_//hqh
{
    char input_s[MAX_LINE][MAX_COL];
    int s_hqh;
}hqh;

hqh Input;

enum Tag {
    START, END, SIGN, INT, FLOAT
};



 
typedef struct node//变量结构体 用于存放所建立变量的相关信息
{
    char var[40] ;//存放变量的字符形式 
    int tag;//0代表整数int，1代表浮点数
    int change;//是否赋值 
    union Value//存放变量的具体值 
    {
        int i_val;
        double f_val;
    } value;
    struct node *next;//结点指针，链接下一变量 
}LinkNode;







/**
 * 加减乘除
 * LP: 左括号（Left parenthesis）
 * RP: 右括号（Right parenthesis）
 */
enum Sign {
    PLUS = '+', MINUS = '-', MUL = '*', DIV = '/', LP = '(', RP = ')'
};

/**
 * token相关数据结构和函数
 * tag表示token类型
 * value表示具体值
 */
typedef struct _Token
{
    int tag;
    union Value
    {
        int sign;
        int i_val;
        float f_val;
    } value;

} Token;

/**
 * 栈相关数据结构和函数
 */
typedef struct _Stack
{
    Token *top;
    Token *base;
    int size;
}Stack;

void init_stack(Stack *stack);
void free_stack(Stack *stack);
void push(Stack *stack, Token t);
Token* pop(Stack *stack);
Token* top(Stack *stack);
void inverse(Stack *stack);


void Input_analysis();//分析函数，对每一行字符进行扫描处理 
void source(char *filename);//读入文本数据，并把数据存储于二维数组中 
/**
 * reset:
 * scan: 扫描字符串，获取下一个token
 * cal: 计算给定表达式的结果
 * error: 输出错误信息并退出
 * cal_token: 计算两个token二元运算的结果，sign为运算符，结果输出到result参数里
 * get_op_level:获取操作符运算优先级
 */
int scan(const char* expr, int start, Token* current);
double cal(const char* expr);
void error(const char* message);
void cal_token(Token* t1, Token* t2, int sign, Token* result);
int get_op_level(int op);

char h_var[40]={'\0'};//全局变量数组，循环使用 
int e_var=0;//全局变量，供函数循环使用 
int i=0; 

LinkNode *head=(LinkNode*)malloc(sizeof(LinkNode));//建立头指针 
LinkNode *pl=NULL;//全局指针，用于函数循环调用 

//////////////////////////////////////////////
int main(int argc, char *argv[]) {
head->var[0]='\0';//头指针内容置空  
head->next=NULL;
    source(argv[1]);
    Input_analysis();
    
    return 0;
}
//////////////////////////////////////////////
void source(char *filename)
{

    FILE *filp = NULL;
    //char fileDir[] = "./test.txt";
    FILE *fp = NULL;
    fp = fopen(filename,"r");
    char buffer[256];
    int readCnt = fread(buffer,sizeof(buffer),1,fp);  	
    fclose(fp);
    int i=0;
    Input.s_hqh=0;
    int j=0;
    printf("The Inputs Are As Follows:\n\n");
     printf("------------------------------------------------------<|\n\n");
    int qp=1;
    printf("%d---<>>>>\t",qp++);
    while(i<strlen(buffer))
    {
//        printf("%d\t",i+1);
        printf("%c",buffer[i]);
        if(buffer[i]!='\n')
            Input.input_s[Input.s_hqh][j]=buffer[i];
        else{ 
             printf("%d---<>>>>\t",qp++);
		    Input.s_hqh++;
            j=-1;
        }

        i++;
        j++;
    }
    printf("\n\n------------------------------------------------------<|\n");
    printf("\n\nThe Result Are As Follows:\n\n");
    printf("\n\n----------------------------------<|>>>\n");
    Input.s_hqh++;
}




void Input_analysis()
{


//处理每一行代码
int j=0;
    for(i;i<Input.s_hqh;i++)

    {
         j=0;

        while(Input.input_s[i][j]==' ')
            j++;
        //处理int 赋值语句 
        if((Input.input_s[i][j]=='i')&&(Input.input_s[i][j+1]=='n')&&(Input.input_s[i][j+2]=='t')&&\
        (Input.input_s[i][j+3]==' '))
        {
            j=j+4;
            while(Input.input_s[i][j]==' ')j++;
            if(!(('a'<=Input.input_s[i][j]&&Input.input_s[i][j]<='z')||('A'<=Input.input_s[i][j]&&\
            Input.input_s[i][j]<='Z')))
            {
                printf("Error, wrong variable name (LINE%d)",i+1);exit(0);
            }
            else
            {
                LinkNode *new_;
                new_=(LinkNode*)malloc(sizeof(LinkNode));
                new_->tag=0;
                e_var=0;
                while(('a'<=Input.input_s[i][j]&&Input.input_s[i][j]<='z')||('A'<=Input.input_s[i][j]&&\
                Input.input_s[i][j]<='Z')||('0'<=Input.input_s[i][j]&&Input.input_s[i][j]<='9'))
                {
                    new_->var[e_var]=Input.input_s[i][j];
                    j++;e_var++;
                }
                new_->var[e_var]='\0';
                while(Input.input_s[i][j]==' ')j++;

                if(Input.input_s[i][j]!=';')
                {

                    printf("Error, wrong definition(LINE%d)",i+1);exit(0);
                }
                else{
                    pl=head->next;
                    e_var=0;
                    while(pl!=NULL)
                    {
                        e_var=0;
                        while((new_->var[e_var]==pl->var[e_var])&&(new_->var[e_var]!='\0'))e_var++;
                        if(new_->var[e_var]!=pl->var[e_var])
                        {
                            pl=pl->next;
                            continue;
                        }
                        else
                        {
                           printf("Error, Duplicate definition(LINE%d)",i+1);
                            exit(0);
                        }
                    }
                    if(pl==NULL)
                    {
                        new_->change=0;
                        new_->next=head->next;
                        head->next=new_;
                      
                        continue;
                    }
                    else
                        exit(0);

                }

            }

        }







            //处理float赋值语句	
        else if((Input.input_s[i][j]=='f')&&(Input.input_s[i][j+1]=='l')&&(Input.input_s[i][j+2]=='o')&&\
        (Input.input_s[i][j+3]=='a')&&(Input.input_s[i][j+4]=='t')&&(Input.input_s[i][j+5]==' '))
        {
            j=j+6;
            
            while(Input.input_s[i][j]==' ')j++;
             if(!(('a'<=Input.input_s[i][j]&&Input.input_s[i][j]<='z')||('A'<=Input.input_s[i][j]\
            &&Input.input_s[i][j]<='Z')))
            {
                printf("Error, wrong variable name (LINE%d)",i+1);exit(0);
            }

            else
            {
                LinkNode *new_;
                new_=(LinkNode*)malloc(sizeof(LinkNode));
                new_->tag=1;

                e_var=0;
                while(('a'<=Input.input_s[i][j]&&Input.input_s[i][j]<='z')||('A'<=Input.input_s[i][j]&&\
                Input.input_s[i][j]<='Z')||('0'<=Input.input_s[i][j]&&Input.input_s[i][j]<='9'))
                {
                    new_->var[e_var]=Input.input_s[i][j];
                    j++;e_var++;
                }
                new_->var[e_var]='\0';
                while(Input.input_s[i][j]==' ')j++;

                if(Input.input_s[i][j]!=';')
                {
				printf("Error, wrong definition(LINE%d)",i+1);exit(0);
                }
                else {
 
                    pl=head->next;
                    while(pl!=NULL)
                    {
                       
                        e_var=0;
                        while((new_->var[e_var]==pl->var[e_var])&&(new_->var[e_var]!='\0'))e_var++;

                        if(new_->var[e_var]==pl->var[e_var])
                        {         
                             printf("Error, Duplicate definition (LINE%d)",i+1);
                            exit(0);
                        }
                        else
                        {
                        	 pl=pl->next;
                            continue;
                        }

                    }
                    if(pl==NULL)
                    {
                        new_->change=0;
                        new_->next=head->next;
                        head->next=new_;
                    
                        continue;
                    }

                }

            }

        }






            //处理write语句 
        else if(Input.input_s[i][j]=='w'&&Input.input_s[i][j+1]=='r'&&Input.input_s[i][j+2]=='i'&&\
        Input.input_s[i][j+3]=='t'&&Input.input_s[i][j+4]=='e'&&Input.input_s[i][j+5]=='(')
        {
            j=j+6;
            memset(h_var, 0, sizeof h_var);
            e_var=0;
            while((Input.input_s[i][j]!=')')&&(Input.input_s[i][j]!=';')&&(Input.input_s[i][j]!='.')&&\
            (Input.input_s[i][j]!='\0'))
            {
                h_var[e_var]=Input.input_s[i][j];
                e_var++;j++;
            }
            h_var[e_var]='\0';
            if(Input.input_s[i][j]!=')')
            {
                printf("Error,Wrong code style (LINE%d)",i+1);
                exit(0);
            }
            else
            {
                j++;
               pl=head->next;
                while(pl!=NULL)
                {
                    e_var=0;
                    while((h_var[e_var]==pl->var[e_var])&&(h_var[e_var]!='\0'))e_var++;

                    if(h_var[e_var]!=pl->var[e_var])
                    {
                        pl=pl->next;
                        continue;
                    }
                    else
                  break;

                }
                if(pl==NULL)
                {
                	printf("Error, Undefinied variable(LINE%d)",i+1);
                	exit(0);
				}
				else
				  {
                        if(pl->change==0){
                            printf("Error, Unassigned Variable (LINE%d)",i+1);
                            exit(0);
                        }
                        else
                        {
                            if(pl->tag==0)
                                printf("%d\n",pl->value.i_val);
                            else
                                printf("%f\n",pl->value.f_val);
                            if(Input.input_s[i][j]==';')
                            {
                               
                                continue;
                            }
                            else if(Input.input_s[i][j]=='.')
                            {
                                   printf("----------------------------------<|>>>\n");
                            	exit(0);
							}
                              
                            else
                                printf("Error,Wrong code style (LINE%d)",i+1);
                            exit(0);
                        }
                    }



            }

        }






            //处理表达式语句 
        else if(('a'<=Input.input_s[i][j]&&Input.input_s[i][j]<='z')||('A'<=Input.input_s[i][j]&&Input.input_s[i][j]<='Z'))
        {
        
            e_var=0;
            memset(h_var, 0, sizeof h_var);
            while(('a'<=Input.input_s[i][j]&&Input.input_s[i][j]<='z')||('A'<=Input.input_s[i][j]&&\
            Input.input_s[i][j]<='Z')||('0'<=Input.input_s[i][j]&&Input.input_s[i][j]<='9'))
            {
                h_var[e_var]=Input.input_s[i][j];
                e_var++;j++;
            }
            while(Input.input_s[i][j]==' ')j++;
            if(Input.input_s[i][j]!='=')
            {
                printf("Error, writing code styles (LINE%d)",i+1);exit(0);
            }
            else
            {
                pl=head->next;;
                while(pl!=NULL)
                {
                    e_var=0;
                    while((h_var[e_var]==pl->var[e_var])&&(h_var[e_var]!='\0'))e_var++;

                    if(h_var[e_var]!=pl->var[e_var])
                    {
                        pl=pl->next;
                        continue;
                    }
                    else
                        break;
                }

                if(pl==NULL){
                    printf("Error, Undefinied Variable(LINE%d)",i+1);
                    exit(0);
                }
                else

                {
                    LinkNode *pv=pl;
                    j++;

                    while(Input.input_s[i][j]==' ')j++;

                    e_var=0;
                    memset(h_var, 0, sizeof h_var);
                    
                    char str1[40];
                    memset(str1, 0, sizeof str1);

                    while((Input.input_s[i][j]!=';')&&(Input.input_s[i][j]!='\0'))
                    {


                        while(Input.input_s[i][j]=='+'||Input.input_s[i][j]=='-'||Input.input_s[i][j]=='*'||\
                        Input.input_s[i][j]=='/'||Input.input_s[i][j]=='.'||\
                          (('0'<=Input.input_s[i][j])&&(Input.input_s[i][j]<='9'))||Input.input_s[i][j]=='('||\
						  Input.input_s[i][j]==')')
                        {

                            h_var[e_var]=Input.input_s[i][j];
                            e_var++;j++;
                        }
                        if(('a'<=Input.input_s[i][j]&&Input.input_s[i][j]<='z')||('A'<=Input.input_s[i][j]&&Input.input_s[i][j]<='Z'))
                        {
                            if(Input.input_s[i][j-1]=='.'||(('0'<=Input.input_s[i][j-1])&&(Input.input_s[i][j-1]<='9')))
                            {
                                printf("Error, Wrong expression LINE%d (LINE%d)",i+1);
                                exit(0);
                            }else;
                        
                            memset(str1, 0, sizeof str1);
                            int g;
                            g=0;
                            
                            while(('a'<=Input.input_s[i][j]&&Input.input_s[i][j]<='z')||('A'<=Input.input_s[i][j]&&\
                            Input.input_s[i][j]<='Z')||('0'<=Input.input_s[i][j]&&Input.input_s[i][j]<='9'))
                            {
                                str1[g]=Input.input_s[i][j];
                                g++;j++;
                            }
                             str1[g]='\0';

                            pl=head->next;
                            int a=0;
                            while(pl!=NULL)
                            {
                                a=0;
                                while((str1[a]==pl->var[a])&&(str1[a]!='\0'))a++;

                                if(str1[a]!=pl->var[a])
                                {
                                    pl=pl->next;
                                    continue;
                                }
                                else
                                    break;
                            }
                            if(pl==NULL)
                            {
                                printf("Error, Wrong expression (LINE%d)",i+1);
                                exit(0);
                            }
                            else
                            {
                            	if(pl->change==0)
                            	{
                            		printf("Unassigned variable (LINE%d)",i+1);
                            		exit(0);
								}
								else
							{
								
                                if((pv->tag==1)&&(pl->tag==0))
                                {
                                    printf("Error type int can not be transformed to float (LINE%d)",i+1);
                                    exit(0);
                                }else;
                                
                                char string[20];
								if(pl->tag==0)
								{
							     itoa(pl->value.i_val,string,10);
								}
								else
								{
									sprintf(string,"%f",pl->value.f_val);
								}
								
								
								int w;
								w=0;
                                while(string[w]!='\0')
                                {
                                    h_var[e_var]=string[w];
                                    e_var++;
                                    w++;
                                }
                            }
                                continue;
                            }




                        }else;
                    }






                    if(Input.input_s[i][j]!=';')
                    {
                        printf("Error,Wrong expression (LINE%d)",i+1);
                        exit(0);
                    }
                    else
                    {

                        double result= cal(h_var);
                        pv->change=1;
                        if(pv->tag==1)
                            pv->value.f_val=cal(h_var);
                        else
                            pv->value.i_val=(int)cal(h_var);
                    }
                }


            }


        }









            //其他语句 

        else
        {
            printf("Error, Wrong code style (LINE%d)",i+1);
            exit(0);
        }











    }







}


















int get_op_level(int op) {
    switch (op)
    {
        case '(':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case ')':
            return 4;
        default:
            error("bad op");
            return 0;
    }
}

// ---------------------- 相关函数的实现 ----------------------

/**
 * 栈相关
 */
void init_stack(Stack *stack) {
    stack->base = (Token*)malloc(MAX_STACK_SIZE * sizeof(Stack));
    stack->size = 0;
    stack->top = NULL;
}

void free_stack(Stack *stack) {
    free(stack->base);
}

void push(Stack *stack, Token t) {
    int size = stack->size;

    if (size >= MAX_STACK_SIZE)
    {
    	printf("Error, Wrong expression(LINE%d)",i+1);
    	exit(0);
        //error("stack overflow");
    }

    stack->base[size] = t;
    stack->size++;
    stack->top = stack->base + stack->size - 1;
}

Token* pop(Stack *stack) {
    if (stack->size == 0)
    {
        printf("Error, Wrong expression(LINE%d)",i+1);
    	exit(0);
    }

    Token *top_token = top(stack);
    stack->top = stack->top - 1;
    stack->size--;
    return top_token;
}

Token* top(Stack *stack) {
    return stack->top;
}

void inverse(Stack *stack) {
    Stack s2;
    init_stack(&s2);

    for (size_t i = stack->size; i > 0; i--)
    {
        Token* t = pop(stack);
        push(&s2, *t);
    }
    free_stack(stack);
    stack->top = s2.top;
    stack->base = s2.base;
    stack->size = s2.size;
}

/**
 * 计算表达式相关函数
 * 主要使用的方法是中缀表达式转后缀表达式，再计算后缀表达式
 */
double cal(const char* expr) {
    int len = strlen(expr);
    int location = 0; // 下标
    Token current;

    // 167-252行：中缀转后缀
    Stack post;
    Stack ops;

    current.tag = START;

    init_stack(&post);
    init_stack(&ops);

    while (current.tag != END)
    {
        location = scan(expr, location, &current);
        switch (current.tag)
        {
            case START:
                //unexpected case
                printf("Error, Wrong expression(LINE%d)",i+1);
    	        exit(0);
                break;
            case END:
                break;
            case INT:
            case FLOAT:
                push(&post, current);
                break;
            case SIGN: {
                int sign = current.value.sign;
                switch (sign)
                {
                    case LP:
                        push(&ops, current);
                        break;
                    case RP:
                        do
                        {
                            Token* op;
                            if (ops.size == 0)
                            {
                               printf("Error, Wrong expression(LINE%d)",i+1);
    	                       exit(0);
                            }
                            op = pop(&ops);
                            push(&post, *op);

                        } while (top(&ops)->value.sign != LP);
                        pop(&ops);
                        break;
                    case PLUS:
                    case MINUS:
                    case MUL:
                    case DIV: {
                        if (ops.size == 0)
                        {
                            push(&ops, current);
                            break;
                        }
                        int top_op = top(&ops)->value.sign;
                        if (get_op_level(sign) > get_op_level(top_op))
                        {
                            push(&ops, current);
                            break;
                        }
                        else {
                            while (ops.size != 0)
                            {
                                int top_op = top(&ops)->value.sign;
                                Token* op;
                                if (get_op_level(sign) <= get_op_level(top_op))
                                {
                                    op = pop(&ops);
                                    push(&post, *op);
                                }
                                else {
                                    break;
                                }
                            }
                            push(&ops, current);
                            break;
                        }
                    }
                    default:
                        break;
                }
                break;
            }
            default:
                //unexpected case
                printf("Error, Wrong expression(LINE%d)",i+1);
    	        exit(0);
                break;
        }
    }


    while (ops.size != 0)
    {
        Token* op = pop(&ops);
        push(&post, *op);
    }

    free_stack(&ops);

    // 转换的后缀里的元素是相反的，所以需要反转栈中数据
    inverse(&post);

    // 计算后缀表达式
    Stack tmp;
    init_stack(&tmp);

    while (post.size != 0) {
        int tag = top(&post)->tag;
        switch (tag)
        {
            case INT:
            case FLOAT:
                push(&tmp, *pop(&post));
                break;
            case SIGN: {
                Token t;
                int sign = pop(&post)->value.sign;
                switch (sign) {
                    case '+':
                    case '-':
                    case '*':
                    case '/': {
                        Token* value2 = pop(&tmp);
                        Token* value1 = pop(&tmp);
                        cal_token(value1, value2, sign, &t);
                        push(&tmp, t);
                        break;
                    }
                }
                break;
            }
            default:
                printf("Error, Wrong expression(LINE%d)",i+1);
    	        exit(0);
                break;
        }
    }
    if (tmp.size != 1) {
        printf("%d\n", tmp.size);
        printf("Error, Wrong expression(LINE%d)",i+1);
        exit(0);
    }

    // 计算的结果
    Token* cal_result = pop(&tmp);

    if (cal_result->tag == INT)
    {
        //printf("%d\n", cal_result->value.i_val);
        return (cal_result->value.i_val);//v
    }
    else if (cal_result->tag == FLOAT) {
        //printf("%.2f\n", cal_result->value.f_val);
        return(cal_result->value.f_val); //v
    }

}

int scan(const char* expr, int start, Token* current) {
    int len = strlen(expr);
    int offset = start;
    char curr_char = expr[offset];
    while (offset < len)
    {
        // 跳过空格
        if (curr_char == ' ')
        {
            curr_char = expr[++offset];
            continue;
        }

        if (curr_char == '\0')
        {
            current->tag = END;
            return offset + 1;
        }

        // 解析计算符
        if (curr_char == '+' || curr_char == '-' || curr_char == '*' || curr_char == '/'
            || curr_char == '(' || curr_char == ')')
        {
            current->tag = SIGN;
            current->value.sign = curr_char;
            return offset + 1;
        }

        // 解析数字
        if (curr_char >= '0' && curr_char <= '9')
        {
            int is_float = 0;
            int int_val = 0;
            float float_val;

            do
            {
                int_val = int_val * 10 + (curr_char - '0');
                curr_char = expr[++offset];
            } while (curr_char >= '0' && curr_char <= '9');

            // 如果有小数点，则为float
            if (curr_char == '.')
            {
                float_val = int_val;
                curr_char = expr[++offset];
                float times = 10.0f;

                int overflow = 0;
                while (curr_char >= '0' && curr_char <= '9') {
                    if (overflow)
                    {
                        curr_char = expr[++offset];
                        continue;
                    }

                    float_val += (curr_char - '0') / times;
                    curr_char = expr[++offset];
                    times *= 10;
                    // 防止溢出
                    if (times > 0xffffffffu / 10)
                    {
                        overflow = 1;
                    }
                }

                current->tag = FLOAT;
                current->value.f_val = float_val;
                return offset;
            }

            current->tag = INT;
            current->value.i_val = int_val;
            return offset;
        }

    }
    if (curr_char == '\0')
    {
        current->tag = END;
        return offset;
    }
}


void cal_token(Token* t1, Token* t2, int sign, Token* result) {
    if (t1->tag == FLOAT || t2->tag == FLOAT)
    {
        result->tag = FLOAT;
        float v1, v2;
        v1 = t1->tag == FLOAT ? t1->value.f_val : t1->value.i_val;
        v2 = t2->tag == FLOAT ? t2->value.f_val : t2->value.i_val;

        switch (sign)
        {
            case '+':
                result->value.f_val = v1 + v2;
                return;
            case '-':
                result->value.f_val = v1 - v2;
                return;
            case '*':
                result->value.f_val = v1 * v2;
                return;
            case '/':
                if (v2 == 0.0f)
                {
                    printf("Error, Wrong expression(LINE%d)",i+1);
    	            exit(0);
                }
                result->value.f_val = v1 / v2;
                return;
            default:
                return;
        }
    }
    else {
        result->tag = INT;
        int v1, v2;
        v1 = t1->value.i_val;
        v2 = t2->value.i_val;
        switch (sign)
        {
            case '+':
                result->value.i_val = v1 + v2;
                return;
            case '-':
                result->value.i_val = v1 - v2;
                return;
            case '*':
                result->value.i_val = v1 * v2;
                return;
            case '/':
                if (v2 == 0)
                {
                    printf("Error, Wrong expression(LINE%d)",i+1);
    	            exit(0);
                }
                result->value.i_val = v1 / v2;
                return;
            default:
                return;
        }
    }
}

// 错误消息
void error(const char* message) {

    fprintf(stderr, "%s\n", message);

    exit(1);
}

