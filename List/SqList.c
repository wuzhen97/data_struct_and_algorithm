/*线性表的顺序存储结构*/
#include <stdio.h>

// 数据结构
#define MAX_SIZE 20
typedef int ElemType;
typedef struct
{
    ElemType data[MAX_SIZE];
    int length;
} SqList;

// 数据操作
// 以下代码暗含初始条件:顺序线性表L已存在
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;

Status InitList(SqList *L)
{
    L->length = 0;
    return OK;
}

Status ListEmpty(const SqList *L)
{
    if (L->length == 0)
        return TRUE;
    else
        return FALSE;
}

Status ClearList(SqList *L)
{
    L->length = 0;
    return OK;
}

int ListLength(const SqList *L)
{
    return L->length;
}

Status GetElem(const SqList *L, int i, ElemType *e)
{
    if (L->length == 0 || i <= 0 || i > L->length)
        return ERROR;

    *e = L->data[i - 1];
    return OK;
}

int LocateElem(const SqList *L, ElemType e)
{
    for (int i = 0; i < L->length; i++)
    {
        if (L->data[i] == e)
            return i + 1;
    }

    return 0;
}

Status ListInsert(SqList *L, int i, ElemType e)
{
    if (L->length == MAX_SIZE || i < 1 || i > L->length + 1)
        return ERROR;

    for (int j = L->length - 1; j >= i - 1; j--)
    {
        L->data[j + 1] = L->data[j];
    }

    L->data[i - 1] = e;
    L->length++;
    return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e)
{
    if (L->length == 0 || i < 1 || i > L->length)
        return ERROR;

    *e = L->data[i - 1];
    for (int j = i - 1; j < L->length; j++)
    {
        L->data[j] = L->data[j + 1];
    }
    L->length--;

    return OK;
}

Status ListTraverse(const SqList *L)
{
    for (int i = 0; i < L->length; i++)
    {
        printf("%d, ", L->data[i]);
    }
    printf("\n");
    return OK;
}

void unionL(SqList *La, SqList *Lb)
{
    int La_len, Lb_len;
    ElemType e;
    La_len = La->length;
    Lb_len = Lb->length;

    for (int i = 0; i < Lb_len; i++)
    {
        GetElem(Lb, i+1, &e);
        if (!LocateElem(La, e))
        {
            ListInsert(La, ++La_len, e);
        }
    }
}

int main()
{

    SqList L;
    SqList Lb;

    ElemType e;
    Status i;
    int j, k;
    i = InitList(&L);
    printf("初始化L后:L.length=%d\n", L.length);

    for (j = 1; j <= 5; j++)
        i = ListInsert(&L, 1, j);
    printf("在L的表头依次插入1-5后:L.data=");
    ListTraverse(&L);

    printf("L.length=%d \n", L.length);
    i = ListEmpty(&L);
    printf("L是否空:i=%d(1:是 0:否)\n", i);

    i = ClearList(&L);
    printf("清空L后:L.length=%d\n", L.length);
    i = ListEmpty(&L);
    printf("L是否空:i=%d(1:是 0:否)\n", i);

    for (j = 1; j <= 10; j++)
        ListInsert(&L, j, j);
    printf("在L的表尾依次插入1-10后:L.data=");
    ListTraverse(&L);

    printf("L.length=%d \n", L.length);

    ListInsert(&L, 1, 0);
    printf("在L的表头插入0后:L.data=");
    ListTraverse(&L);
    printf("L.length=%d \n", L.length);

    GetElem(&L, 5, &e);
    printf("第5个元素的值为:%d\n", e);
    for (j = 3; j <= 4; j++)
    {
        k = LocateElem(&L, j);
        if (k)
            printf("第%d个元素的值为%d\n", k, j);
        else
            printf("没有值为%d的元素\n", j);
    }

    k = ListLength(&L); /* k为表长 */
    for (j = k + 1; j >= k; j--)
    {
        i = ListDelete(&L, j, &e); /* 删除第j个数据 */
        if (i == ERROR)
            printf("删除第%d个数据失败\n", j);
        else
            printf("删除第%d个的元素值为:%d\n", j, e);
    }
    printf("依次输出L的元素:");
    ListTraverse(&L);

    j = 5;
    ListDelete(&L, j, &e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为:%d\n", j, e);

    printf("依次输出L的元素:");
    ListTraverse(&L);

    //构造一个有10个数的Lb
    i = InitList(&Lb);
    for (j = 6; j <= 15; j++)
        i = ListInsert(&Lb, 1, j);

    unionL(&L, &Lb);

    printf("依次输出合并了Lb的L的元素:");
    ListTraverse(&L);

    return 0;
}
