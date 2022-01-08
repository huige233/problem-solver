#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int n, Max, Min, q[maxn], aim[maxn], rd[maxn];
bool die[maxn], undie[maxn];

int main()
{
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%d", &aim[i]);
    rd[aim[i]]++;
  }
  for (int i = 1; i <= n; ++i)
    if (rd[i] == 0)
    {               //入度为0的点进队
      Min++;        //最小存活++
      q[++Max] = i; //最大存活++
    }
  int head = 1; //模拟指针
  while (head <= Max)
  {
    int cur = q[head];
    head++; //队首出队
    if (die[aim[cur]])
      continue;               //如果队首要杀的人已经被别人杀了
    die[aim[cur]] = 1;        //标记队首要杀的人
    int live = aim[aim[cur]]; //队首目标的目标可死可不死
    rd[live]--;               //入度--
    undie[live] = 1;          //可以不死了
    if (rd[live] == 0)        //如果入度变为0了
      q[++Max] = live;        //最大存活数++，入队
  }
  //下面是处理环的
  for (int i = 1; i <= n; ++i)
    if (rd[i] && !die[i])
    {                        //如果当前位置入度不为0 并且还没死
      int len = 0, flag = 0; //len为环的长度 flag判定当前人是否可能会死
      for (int j = i; !die[j]; j = aim[j])
      {                   //遍历环
        len++;            //环长度++
        flag |= undie[j]; //当前人是否可能会死
        die[j] = 1;       //标记为已死 防止下次i到这个位置再计算
      }
      if (!flag && len > 1)
        Min++;        //如果当前点不可能会死 而且环长度>1(不是自环) ，最小存活数++
      Max += len / 2; //最大存活数加上环长度的一半
    }
  printf("%d %d", n - Max, n - Min); //要输出最小死亡数和最多死亡数
  return 0;
}