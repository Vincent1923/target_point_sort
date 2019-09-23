#include<cstdio>
#include<cstring>
#include<algorithm>
#include <iostream>

#define MAX 1000
#define INF 10000

using namespace std;

struct Point
{
  double x;
  double y;
};

// 邻接矩阵
typedef struct _graph
{
    int vexs[MAX];        // 顶点集合
    int vexnum;           // 顶点数
    int edgnum;           // 边数
    double matrix[MAX][MAX];  // 邻接矩阵
}Graph, *PGraph;

// 边的结构体
typedef struct _EdgeData
{
    char start;  // 边的起点
    char end;    // 边的终点
    int weight;  // 边的权重
}EData;

/*
 * Dijkstra最短路径。
 * 即，统计图(G)中"顶点vs"到其它各个顶点的最短路径。
 *
 * 参数说明：
 *     G    -- 图
 *     vs   -- 起始顶点(start vertex)。即计算"顶点vs"到其它顶点的最短路径。
 *     prev -- 前驱顶点数组。即，prev[i]的值是"顶点vs"到"顶点i"的最短路径所经历的全部顶点中，位于"顶点i"之前的那个顶点。
 *     dist -- 长度数组。即，dist[i]是"顶点vs"到"顶点i"的最短路径的长度。
 */
Point *Dijkstra(Point target_point[], int point_num, int vs, int prev[], double dist[])
{
  Point *result = new Point[point_num];
  result[0].x = target_point[vs].x;
  result[0].y = target_point[vs].y;

  Graph G;
  int i,j,k;
  int min;
  int tmp;
  int flag[MAX];  // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。

  std::cout << "start Dijkstra" << std::endl;

  // 对G初始化
  G.vexnum = point_num;
  for (int i = 0; i < G.vexnum; i++)
  {
    G.vexs[i] = i;
  }
  for (int i = 0; i < G.vexnum; i++)  // 对邻接矩阵初始化
  {
    for (int j = 0; j < G.vexnum; j++)
    {
      double dis = (target_point[i].x - target_point[j].x) * (target_point[i].x - target_point[j].x) +
                   (target_point[i].y - target_point[j].y) * (target_point[i].y - target_point[j].y);
      G.matrix[i][j] = dis;
      std::cout << "G.matrix[" << i << "][" << j << "]: " << G.matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // 初始化
  for (i = 0; i < G.vexnum; i++)
  {
    flag[i] = 0;                // 顶点i的最短路径还没获取到。
    prev[i] = 0;                // 顶点i的前驱顶点为0。
    dist[i] = G.matrix[vs][i];  // 顶点i的最短路径为"顶点vs"到"顶点i"的权。
  }

  // 对"顶点vs"自身进行初始化
  flag[vs] = 1;
  dist[vs] = 0;

  // 遍历G.vexnum-1次；每次找出一个顶点的最短路径。
  for (i = 1; i < G.vexnum; i++)
  {
    // 寻找当前最小的路径；
    // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
    min = INF;
    for (j = 0; j < G.vexnum; j++)
    {
      if (flag[j] == 0 && dist[j] < min)
      {
        min = dist[j];
        k = j;
      }
    }
    // 标记"顶点k"为已经获取到最短路径
    flag[k] = 1;
    result[i].x = target_point[k].x;
    result[i].y = target_point[k].y;
    std::cout << "k = " << k << std::endl;
    std::cout << "target_point["<< k << "].x = " << target_point[k].x << std::endl;
    std::cout << "target_point["<< k << "].y = " << target_point[k].y << std::endl;
    std::cout << "result["<< i << "].x = " << result[i].x << std::endl;
    std::cout << "result["<< i << "].y = " << result[i].y << std::endl;

    // 修正当前最短路径和前驱顶点
    // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
    for (j = 0; j < G.vexnum; j++)
    {
      tmp = (G.matrix[k][j]==INF ? INF : (min + G.matrix[k][j]));  // 防止溢出
      if (flag[j] == 0 && (tmp  < dist[j]) )
      {
        dist[j] = tmp;
        prev[j] = k;
      }
    }

    for (int j = 0; j < G.vexnum; j++)
    {
      std::cout << "dist: " << dist[j] << " ";
    }
    std::cout << std::endl;
  }

  // 打印dijkstra最短路径的结果
  printf("dijkstra(%d): \n", G.vexs[vs]);
  for (i = 0; i < G.vexnum; i++)
      printf("  shortest(%d, %d) = %f\n", G.vexs[vs], G.vexs[i], dist[i]);

  return result;
}

void TargetPointSort(Point target_point[], int point_num)
{
  Graph G;
  G.vexnum = point_num;
//  G.vexs[0] = 'A';
//  G.vexs[1] = 'B';
//  G.vexs[2] = 'C';
//  G.vexs[3] = 'D';
//  G.vexs[4] = 'E';
//  G.vexs[5] = 'F';

  // 对邻接矩阵初始化
  for (int i = 0; i < point_num; i++)
  {
    for (int j = 0; j < point_num; j++)
    {
      double dis = (target_point[i].x - target_point[j].x) * (target_point[i].x - target_point[j].x) +
                   (target_point[i].y - target_point[j].y) * (target_point[i].y - target_point[j].y);
      G.matrix[i][j] = dis;
      std::cout << "G.matrix[" << i << "][" << j << "]: " << G.matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }

  int prev[MAX];
  double dist[MAX];

  for (int i = 0; i < MAX; i++)
  {
    prev[i] = 0;
    dist[i] = 0.0;
  }
}

int main()
{
  int point_num = 6;
  Point target_point[6];
  target_point[0].x = 0;  target_point[0].y = 0;
  target_point[1].x = 10; target_point[1].y = 7;
  target_point[2].x = 5;  target_point[2].y = 8;
  target_point[3].x = 2;  target_point[3].y = 2;
  target_point[4].x = 12; target_point[4].y = 9;
  target_point[5].x = 3;  target_point[5].y = 7;

  int prev[MAX];
  double dist[MAX];

  for (int i = 0; i < MAX; i++)
  {
    prev[i] = 0;
    dist[i] = 0.0;
  }

  Point *result = Dijkstra(target_point, point_num, 0, prev, dist);

  for (int i = 0; i < point_num; i++)
  {
    std::cout << "result[" << i << "]: " << result[i].x << " " << result[i].y << std::endl;
  }

  for (int i = 0; i < point_num; i++)
  {
    std::cout << "dist: " << dist[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
