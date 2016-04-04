#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <tuple>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits.h>
#include <stdlib.h>
#include <sstream>
#include <time.h>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <stack>
using namespace std;
#define EDGE_NUM 0
#define SRC_NUM 1
#define DES_NUM 2
#define WEIGHT 3

#define TU_WEIGHT 0
#define TU_BOOL 1
#define TU_ROUTE 2

#define VEC_WEIGHT 0
#define VEC_SRC 1
#define VEC_EDGE_NUM 2

#define NODE_MAX_SIZE 600
void BFS(tuple<int, bool, vector<vector<int>>> *shortest, vector<vector<int>> *gmap, vector<int> &src_des, bool *viset, unordered_map<int, int> &routemap)
{
    queue<int> que;
    que.push(src_des[0]);

    while(!que.empty())
    {
        int src = que.front();
        que.pop();
        if(routemap.find(src) != routemap.end())
        {
            get<TU_BOOL>(shortest[src]) = true;
        }

        for(int i = 0; i < gmap[src].size(); ++i)
        {
            int temp = gmap[src][i][DES_NUM];//xu hao
            int weight = gmap[src][i][WEIGHT] + get<TU_WEIGHT>(shortest[src]);
            if(!viset[temp] || get<TU_WEIGHT>(shortest[temp]) > weight)
            {
                que.push(temp);
                get<TU_WEIGHT>(shortest[temp]) = weight;
                get<TU_ROUTE>(shortest[temp]).push_back({gmap[src][i][WEIGHT], src, gmap[src][i][EDGE_NUM]});
                if(get<TU_BOOL>(shortest[src]))
                {
                    get<TU_BOOL>(shortest[temp]) = true;
                }
                else
                {
                    get<TU_BOOL>(shortest[temp]) = false;
                }

                viset[temp] = true;
            }
            else if(get<TU_BOOL>(shortest[src]))
            {
                get<TU_ROUTE>(shortest[temp]).push_back({gmap[src][i][WEIGHT], src, gmap[src][i][EDGE_NUM]});
                if(!get<TU_BOOL>(shortest[temp]))
                {
                    get<TU_BOOL>(shortest[temp]) = true;
                    que.push(temp);
                }
            }


            //ans[gmap[src][i][2]].push_back(1);
        }
    }
}

void DFSTWO(tuple<int, bool, vector<vector<int>>> *shortest, vector<int> &src_des, unordered_map<int, int> &routemap, bool *viset, string &temp_route, vector<pair<string, int>> &res, int weight, int &min_weight, int flag)
{
    if(src_des[0] == src_des[1] && flag == 0 && min_weight > weight)
    {
        min_weight = weight;
        res.push_back({temp_route.substr(1), weight});
        return;
    }
    int src = src_des[1];
    vector<vector<int>> &vec = get<TU_ROUTE>(shortest[src]);

    if(routemap.find(src) != routemap.end())
    {
        --routemap[src];
        --flag;
        if(routemap[src] < 0)
        {
            ++routemap[src];
            return;
        }
    }

    if(viset[src])
        return;
    else
        viset[src] = true;

    for(int i = 0; i < vec.size(); ++i)
    {
        weight += vec[i][VEC_WEIGHT];
        if(weight > min_weight)
        {
            weight -= vec[i][VEC_WEIGHT];///
            continue;
        }
        src_des[1] = vec[i][1];///

        char *ch = new char[4];
        //sprintf(ch, "%d", vec[src_des[0]][j][0]);
        sprintf(ch, "%d", vec[i][VEC_EDGE_NUM]);
        string str= temp_route;
        temp_route = "|" + (string)ch + temp_route;///

        DFSTWO(shortest, src_des, routemap, viset, temp_route, res, weight, min_weight, flag);

        weight -= vec[i][VEC_WEIGHT];
        temp_route = str;
        src_des[1] = src;
    }

    viset[src] = false;
    if(routemap.find(src) != routemap.end())
    {
        ++routemap[src];
        ++flag;
    }
}
void DFS_NONRECUR(vector<vector<int>> *vec, bool* viset, boollist<int> &lroute, vector<int> &src_des, string &temp_route, vector<pair<string, int>> &res, int weight, int& min_weight, int flag)
{
    stack<int> sta;
    sta.push(src_des[0]);
    while(!sta.empty())
    {
        int src = sta.top();
        sta.pop();
        viset[src] = 1;
        for(int i = 0; i < vec[src].size(); ++i)
        {
            int des = vec[src][i][DES_NUM];
            if(viset[des] == 0)
            {
                viset[des] = 1;
                weight += vec[src_des[0]][i][WEIGHT];
                if(weight > min_weight)
                {
                    viset[des] = 0;
                    weight -= vec[src][i][WEIGHT];
                    continue;
                }
                sta.push(vec[src][i][DES_NUM]);
                int s_size = temp_route.size();

                temp_route = temp_route + to_string(vec[src][i][SRC_NUM]) + "|";
                //int temp_src = src_des[0];
                //src_des[0] = vec[src][i][2];

                //int temp_flag = flag;
                //vector<pair<list<int>::iterator, int>> temp_de;

//                for(list<int>::iterator i = lroute.begin(); i != lroute.end(); )
//                {
//                    if(vec[temp_src][j][2] == *i)
//                    {
//                        i = lroute.erase(i);
//                        temp_de.push_back({i, vec[temp_src][j][2]});
//                        --flag;
//                    }
//                    else
//                        ++i;
//                }

//                for(int i = 0; i < temp_de.size(); ++i)
//                {
//                    //lroute.insert(temp_de[i].first, temp_de[i].second);
//                    lroute.push_back(temp_de[i].second);
//                }

                temp_route = temp_route.substr(0, s_size);
//                src_des[0] = temp_src;
//                weight -= vec[src_des[0]][j][3];
//                vec[src_des[0]][j][4] = 0;

//                flag = temp_flag;


            }
        }

    }
}

void DFS(vector<vector<int>> *vec, list<int> &lroute, vector<int> &src_des, string &temp_route, vector<pair<string, int>> &res, int weight, int& min_weight, int flag, int diedai)
{
    if(diedai > 23)
    {
        return ;
    }
    if(flag == 0 && src_des[0] == src_des[1] && min_weight > weight)
    {
        min_weight = weight;
        res.push_back({temp_route.substr(0, temp_route.size() - 1), weight});
    }
    else
    {
        for(int j = 0; j < vec[src_des[0]].size(); ++j)
        {
            if(vec[src_des[0]][j][4] == 0)
            {
                weight += vec[src_des[0]][j][3];
                if(weight > min_weight)
                {
                    weight -= vec[src_des[0]][j][3];
                    continue;
                }
                vec[src_des[0]][j][4] = 1;
                int s_size = temp_route.size();

                char *ch = new char[4];
                sprintf(ch, "%d", vec[src_des[0]][j][0]);

                temp_route = temp_route + (string)ch + "|";
                int temp_src = src_des[0];
                src_des[0] = vec[src_des[0]][j][2];


                int temp_flag = flag;
                vector<pair<list<int>::iterator, int>> temp_de;

                for(list<int>::iterator i = lroute.begin(); i != lroute.end(); )
                {
                    if(vec[temp_src][j][2] == *i)
                    {
                        i = lroute.erase(i);
                        temp_de.push_back({i, vec[temp_src][j][2]});
                        --flag;
                    }
                    else
                        ++i;
                }

                DFS(vec, lroute, src_des, temp_route, res, weight, min_weight, lroute.size(), ++diedai);

                for(int i = 0; i < temp_de.size(); ++i)
                {
                    //lroute.insert(temp_de[i].first, temp_de[i].second);
                    lroute.push_back(temp_de[i].second);
                }

                temp_route = temp_route.substr(0, s_size);
                src_des[0] = temp_src;
                weight -= vec[src_des[0]][j][3];
                vec[src_des[0]][j][4] = 0;

                flag = temp_flag;
            }

//            if(vec[src_des[0]][j][2] == route[i].first)
//            {
//                weight += vec[src_des[0]][j][3];
//                if(weight > min_weight)
//                {
//                    weight -= vec[src_des[0]][j][3];
//                    continue;
//                }
//                string s = temp_route;

//                char *ch = new char[4];
//                sprintf(ch, "%d", vec[src_des[0]][j][0]);
//                temp_route = temp_route + (string)ch + "|";
//                int temp_src = src_des[0];
//                src_des[0] = route[i].first;
//                route[i].second = 1;
//                --flag;


//                DFS(vec, route, src_des, temp_route, res, weight, min_weight, flag);

//                temp_route = s;
//                src_des[0] = temp_src;
//                weight -= vec[src_des[0]][j][3];
//                route[i].second = 0;
//                ++flag;
//            }
        }


//        for(int i = 0; i < route.size(); ++i)
//        {
//            if(!route[i].second)
//            {

//            }
//        }
    }

//    int node = route.back();
//    for(int i = 0; i < route.size(); ++i)
//    {
//        for(int j = 0; j < vec[node].size(); ++j)
//        {
//            if(route[i] == vec[node][j][])
//            {

//            }
//        }
//    }
}


int main(int argc, char** argv)
{
    clock_t start, end;
    start = clock();

    vector<vector<int>> *gmap = new vector<vector<int>>[NODE_MAX_SIZE];
    //vector<vector<int>> *vec = new vector<vector<int>>[NODE_MAX_SIZE];


    string str;
    ifstream fin;
    fin.open(argv[1]);

    string pattern = ",";
//cout << std::get<0>(vec[0][1]) << endl;
    while(fin >> str)
    {
        str += pattern;
        int size = str.size();
        //cout << str << endl;
        int pos = 0;
        vector<int> temp;
        for(int i = 0; i < size; ++i)
        {
            pos = str.find(pattern, i);
            if(pos < size)
            {
                string s = str.substr(i, pos - i);
                //cout << stoi(s) << " ";
                temp.push_back(stoi(s));
                i = pos + pattern.size() - 1;
            }
        }
        temp.push_back(0);


//        cout << temp[1] << endl;
        gmap[temp[1]].push_back(temp);
//        for(int i = 0; i < temp.size(); ++i)
//        {
//            cout << temp[i] << " ";
//        }
//        cout << endl;
    }
    fin.close();
    fin.clear();

//    for(int i = 0; i < 600; ++i)
//    {
//        for(int j = 0; j < vec[i].size(); ++j)
//        {
//            for(int k = 0; k < vec[i][j].size(); ++k)
//            {
//                cout << vec[i][j][k] << " ";
//            }
//            cout << endl;
//        }
//    }

    fin.open(argv[2]);
    vector<int> src_des;
    list<int> lroute;
    unordered_map<int, int> routemap;
    while(fin >> str)
    {
//        cout << str << endl;
        str += "|";
        int size = str.size();
        int pos = 0;
        for(int i = 0; i < size; ++i)
        {
            pos = str.find(pattern, i);
            if(pos < 0)
            {
                pos = str.find("|", i);
                if(pos < 0)
                {
                    break;
                }
                else if(pos < size)
                {
                    string s = str.substr(i, pos - i);
                    lroute.push_back(stoi(s));
                    routemap[stoi(s)]++;
                    i = pos + pattern.size() - 1;
                }
            }
            else if(pos < size)
            {
                string s = str.substr(i, pos - i);
                src_des.push_back(stoi(s));
                i = pos + pattern.size() - 1;
            }
        }
    }

    lroute.sort();




    cout << "src and des:" << endl;
    for(int i = 0; i < src_des.size(); ++i)
    {
        cout << src_des[i] << " ";
    }
    cout << endl;
    cout << "should pass this node:" << endl;
    for(list<int>::iterator i = lroute.begin(); i != lroute.end(); ++i)
    {
        cout << *i << " ";
    }

//    for(unordered_map<int, int>::iterator i = routemap.begin(); i != routemap.end(); ++i)
//    {
//        if(i->second > 0)
//        cout << i->first << " ";
//    }
    cout << endl;
    cout << "unordered_map size:" << routemap.size() << endl;


    tuple<int, bool, vector<vector<int>>> *shortest = new tuple<int, bool, vector<vector<int>>>[NODE_MAX_SIZE];
    get<0>(shortest[src_des[0]]) = 0;

    bool *viset = new bool[NODE_MAX_SIZE];


    //int route_size = routemap.size();

    //BFS(shortest, gmap, src_des, viset, routemap);
    memset(viset, 0, NODE_MAX_SIZE);

    cout<<"test" << endl;
    cout << get<0>(shortest[3]) << endl;
    cout << "unordered_map size:" << routemap.size() << endl;

    vector<pair<string, int>> res;
    string temp_route = "";
    //temp_route.push_back(src_des[0]);
    int min_weight = INT_MAX;
    DFS(gmap, lroute, src_des, temp_route, res, 0, min_weight, lroute.size(), 0);
    //DFSTWO(shortest, src_des, routemap, viset, temp_route, res, 0, min_weight, routemap.size());


    end = clock();
    cout << "runtime = " << (end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
//    cout << "fdsgds" << endl;
    cout << "res size=" << res.size() << endl;
    for(int i = 0; i < res.size(); ++i)
    {
        cout << res[i].first << "  " << res[i].second << endl;
    }

    ofstream fout(argv[3]);
    if(res.size() == 0)
    {
        fout << "NA" << endl;
    }
    else
    {
        fout << res.back().first << endl;
    }

    return 0;
}



//int main()
//{
//    int *num = new int[MAX_SIZE * 4], row = 0;
//    char *str = new char[8];
//    FILE *fp = fopen("test.csv", "r");
//    if(!fp)
//    {
//        printf("can't open file\n");
//        return -1;
//    }

//    while(!feof(fp))
//    {

//        fgets(str, 8, fp);
////        printf("%s\n", str);
////        cout << str << endl;
//        char *p;
//        const char* d = ",\n";
//        p = strtok(str, d);

//        int col = 0;
//        while(p)
//        {

//            num[row * 4 + col] = *p - '0';
////            cout << num[row * 4 + col] << " ";
//            p = strtok(NULL, d);
//        }
////        cout << endl;


//    }



//    fclose(fp);
//    return 0;
//}

