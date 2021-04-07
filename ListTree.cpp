#include <iostream>
#include <stack>

struct node //node的組成
{
    int number;        //number表內容
    int idx;           //idx表在二元樹中的位置
    struct node *next; //此表list中下一位
};

struct node *root = NULL;      //list中第一個
std::stack<int> TraverseStack; //中序輸出要用到stack做反向輸出

//下方表先宣告有這些函式需使用
struct node *AddNodeBST(int num, int idx, struct node *ptr);
void InsertBST(int num, struct node *ptr);
int SearchBST(int num, struct node *ptr);
void TraverseBST(struct node *ptr);

int main()
{
    int a;
    //輸出輸入提示
    printf("Please input a command.\n1 is add, 2 is search, 3 is traverse, 4 is print list, 0 is end\n");
    scanf("%d", &a); //宣告指令輸入的變數
    while (a != 0)
    {
        if (a == 1) //新增數字到BST
        {
            int tmp;
            scanf("%d", &tmp);
            while (tmp != 0) //持續輸入數字
            {
                InsertBST(tmp, root); //並將數字加入BST
                scanf("%d", &tmp);
            }
        }
        else if (a == 2) //在BST中搜尋數字
        {
            int tmp;
            //輸出輸入提示
            printf("Please input a integer which you want to find in the BST.\n");
            scanf("%d", &tmp);
            int idx = SearchBST(tmp, root); //在BST中搜尋數字回傳其位置
            if (idx)
            {
                //輸出找到數字與其位置
                printf("%d is in BST at index %d.\n", tmp, idx);
            }
            else
            {
                //輸出找不到數字
                printf("Can't find %d in the BST.\n", tmp);
            }
        }
        else if (a == 3) //中序拜訪在BST中的所有數字
        {
            while (!TraverseStack.empty())
            {
                TraverseStack.pop(); //清空Stack
            }

            TraverseBST(root); //中序拜訪
            if (TraverseStack.empty())
            {
                printf("List is empty.\n"); //輸出list為空
            }
            else
            {
                printf("\n");
                while (!TraverseStack.empty())
                {
                    int tmp = TraverseStack.top();
                    printf("%d ", tmp); //反向輸出中序拜訪結果
                    TraverseStack.pop();
                }
                printf("\n");
            }
        }
        else if (a == 4) //照list順序印出在BST中的所有數字與位置(index)
        {
            struct node *now = root;
            if (now != NULL)
            {
                while (now->next != NULL)
                {
                    printf("%d %d\n", now->number, now->idx); //遍歷輸出list
                    now = now->next;
                }
                printf("%d %d\n", now->number, now->idx);
            }
            else
            {
                printf("List is empty.\n"); //輸出list為空
            }
        }
        else
        {
            //輸出輸入提示
            printf("Please input a correct command.\n");
        }
        //輸出輸入提示
        printf("Please input next command.\n1 is add, 2 is search, 3 is traverse, 4 is print list, 0 is end\n");
        scanf("%d", &a);
    }
    return 0;
}

//加入新的Node進入BST
struct node *AddNodeBST(int num, int idx, struct node *ptr)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node *)); //跟系統要空間
    newnode->number = num;                                               //存數字
    newnode->idx = idx;                                                  //存位置
    newnode->next = ptr;                                                 //存下一個指向的Node
    return newnode;                                                      //回傳要到的內容
}

void InsertBST(int num, struct node *ptr)
{
    if (ptr == NULL)
    {
        root = AddNodeBST(num, 1, ptr); //若為第一個節點，則建立第一位
    }
    else if (num < ptr->number) //若比目前數字小
    {
        struct node *leftptr = ptr;
        while (leftptr->next != NULL) //找到左子樹
        {
            if (leftptr->next->idx >= (2 * ptr->idx))
            {
                break;
            }
            leftptr = leftptr->next;
        }
        if ((leftptr->next != NULL) && (leftptr->next->idx == (2 * ptr->idx)))
        {
            InsertBST(num, leftptr->next); //若有左子樹，繼續遞迴
        }
        else
        {
            //若沒有左子樹，加入新的Node
            leftptr->next = AddNodeBST(num, 2 * ptr->idx, leftptr->next);
        }
    }
    else if (num > ptr->number) //若比目前數字大
    {
        struct node *rightptr = ptr;
        while (rightptr->next != NULL) //找到右子樹
        {
            if (rightptr->next->idx >= (2 * ptr->idx + 1))
            {
                break;
            }
            rightptr = rightptr->next;
        }
        if ((rightptr->next != NULL) && (rightptr->next->idx == (2 * ptr->idx + 1)))
        {
            InsertBST(num, rightptr->next); //若有右子樹，繼續遞迴
        }
        else
        {
            //若沒有右子樹，加入新的Node
            rightptr->next = AddNodeBST(num, 2 * ptr->idx + 1, rightptr->next);
        }
    }
    return;
}

int SearchBST(int num, struct node *ptr)
{
    if (ptr == NULL)
    {
        return 0; //找不到回傳0
    }
    else if (num < ptr->number) //若比較小，則在左樹中
    {
        struct node *leftptr = ptr;
        while (leftptr->next != NULL)
        {
            if (leftptr->next->idx >= (2 * ptr->idx))
            {
                break;
            }
            leftptr = leftptr->next;
        }
        return SearchBST(num, leftptr->next); //找到左子樹，並且繼續遞迴
    }
    else if (num > ptr->number) //若比較大，則在右樹中
    {
        struct node *rightptr = ptr;
        while (rightptr->next != NULL)
        {
            if (rightptr->next->idx >= (2 * ptr->idx + 1))
            {
                break;
            }
            rightptr = rightptr->next;
        }
        return SearchBST(num, rightptr->next); //找到右子樹，並且繼續遞迴
    }
    else if (num == ptr->number) //若相等
    {
        return ptr->idx; //回傳在二元樹的位置
    }
    return 0;
}

void TraverseBST(struct node *ptr)
{
    if (ptr == NULL) //若不存在，則不做任何事
    {
        return;
    }

    struct node *leftptr = ptr, *rightptr = ptr;

    while (true) //判斷左樹的情況
    {
        if (leftptr == NULL) //若不存在，則不做任何事
        {
            break;
        }
        else if (leftptr->idx == (2 * ptr->idx))
        {
            TraverseBST(leftptr); //若存在，則繼續遞迴
            break;
        }
        else if (leftptr->idx > (2 * ptr->idx)) //若不存在，則不做任何事
        {
            break;
        }
        leftptr = leftptr->next;
    }

    TraverseStack.push(ptr->number); //此為根結點，加入Stack之中
    printf("%d ", ptr->number);      //此為根結點，則輸出

    while (true) //判斷右樹的情況
    {
        if (rightptr == NULL) //若不存在，則不做任何事
        {
            break;
        }
        else if (rightptr->idx == (2 * ptr->idx + 1))
        {
            TraverseBST(rightptr); //若存在，則繼續遞迴
            break;
        }
        else if (rightptr->idx > (2 * ptr->idx + 1)) //若不存在，則不做任何事
        {
            break;
        }
        rightptr = rightptr->next;
    }
    return;
}