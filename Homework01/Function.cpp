#define _USE_MATH_DEFINES //為了能使用cmath中的M_PI
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

void buildcoordinates(int index, std::vector<char> routevector[], std::fstream routefile[], std::vector<double> coordinatesvector[]);
double Distance(double lat1, double lon1, double lat2, double lon2);
//預先宣告將會使用到的函式

int main()
{
    std::fstream routefile[2];                          //宣告要使用fstream輸入的變數
    routefile[0].open("Route.kml", std::ios::in);       //輸入Route.kml檔案
    routefile[1].open("FriendRoute.kml", std::ios::in); //輸入FriendRoute.kml檔案
    if (!routefile[0].is_open())                        //若Route.kml檔案無法開啟
    {
        std::cout << "Route.kml do not exist or can not be read." << std::endl;
        return 1;
    }
    else if (!routefile[1].is_open()) //若FriendRoute.kml檔案無法開啟
    {
        std::cout << "FriendRoute.kml do not exist or can not be read." << std::endl;
        return 2;
    }
    else
    {
        std::vector<char> routevector[2];         //宣告以vector存放剛剛讀進來的檔案內容
        std::vector<double> coordinatesvector[2]; //宣告以double轉換vector中存放的檔案內容
        buildcoordinates(0, routevector, routefile, coordinatesvector);
        buildcoordinates(1, routevector, routefile, coordinatesvector);
        routefile[0].close();                       //關閉讀進來的檔案Route.kml
        routefile[1].close();                       //關閉讀進來的檔案FriendRoute.kml
        int num0 = coordinatesvector[0].size() / 3; //從Route.kml取出的coordinates數量
        int num1 = coordinatesvector[1].size() / 3; //從FriendRoute.kml取出的coordinates數量

        double maxdistance;                                                   //宣告儲存使用者輸入變數
        std::cout << "Please input the MAX distance in meters." << std::endl; //提醒使用者輸入變數的規則
        std::cin >> maxdistance;                                              //輸入變數

        for (int i = 0; i < num0; i++) //遍例Route.kml中的所有coordinates
        {
            for (int j = 0; j < num1; j++) //遍例FriendRoute.kml中的所有coordinates
            {
                //將需要檢查之座標點傳入函式
                double D = Distance(coordinatesvector[0][3 * i], coordinatesvector[0][3 * i + 1], coordinatesvector[1][3 * j], coordinatesvector[1][3 * j + 1]);
                if (maxdistance >= D) //若發現距離比使用者規定的還要短
                {
                    std::cout << "True, Overlapping." << std::endl; //輸出True
                    system("pause");                                //為了看清楚輸出結果
                    return 0;                                       //結束程式，因為沒有規定要找完，有找到就可以結束判斷了
                }
            }
        }
        std::cout << "False, No overlapping." << std::endl; //以上情況皆無發生，輸出False
        system("pause");                                    //為了看清楚輸出結果
        return 0;
    }
    return 0;
}

// 將routefile資料取出，先以char存放於routevector，接者轉換成double存放於coordinatesvector，其中index表第幾個檔案
void buildcoordinates(int index, std::vector<char> routevector[], std::fstream routefile[], std::vector<double> coordinatesvector[])
{
    while (routefile[index].peek() != EOF) //從routefile[index]取出資料，若還未到EOF繼續執行
    {
        char tmp = routefile[index].get(); //從routefile[index]取出資料
        if (tmp != ' ')                    //若並非空格字元，此步驟為了簡化後續程式碼，所以多加上此判斷
        {
            routevector[index].push_back(tmp); //將資料放入routevector
        }
    }
    std::vector<char>::iterator it;                                                                                            //宣告iterator
    char coordinates0[] = {'<', 'c', 'o', 'o', 'r', 'd', 'i', 'n', 'a', 't', 'e', 's', '>'};                                   //宣告需要檢查的字串
    it = std::search(routevector[index].begin(), routevector[index].end(), coordinates0, coordinates0 + sizeof(coordinates0)); //使用內建函式找到需要找的字串
    routevector[index].erase(routevector[index].begin(), it + sizeof(coordinates0) + 1);                                       //並且去除前段
    char coordinates1[] = {'<', '/', 'c', 'o', 'o', 'r', 'd', 'i', 'n', 'a', 't', 'e', 's', '>'};                              //宣告需要檢查的字串
    it = std::search(routevector[index].begin(), routevector[index].end(), coordinates1, coordinates1 + sizeof(coordinates1)); //使用內建函式找到需要找的字串
    routevector[index].erase(it - 1, routevector[index].end());                                                                //並且去除後段

    int vectorsize = routevector[index].size(); //將routevector[index].size()以一個變數儲存，避免迴圈一直在計算此數值
    std::string tmp = "";                       //宣告儲存需轉換成double之資料
    for (int i = 0; i < vectorsize; i++)        //從routevector開頭開始尋找，此時存在的資料只有經度,緯度,高度\n
    {
        if (routevector[index][i] == ',' || routevector[index][i] == '\n') //依照資料內容篩選','或是'\n'
        {
            coordinatesvector[index].push_back(stod(tmp)); //依照資料內容篩選出數字並利用stod轉換
            tmp = "";                                      //清除佔存
        }
        else //若非','或是'\n'，則為數字
        {
            tmp += routevector[index][i]; //加入佔存中
        }
    }
}

//reference:"https://stackoverflow.com/questions/639695/how-to-convert-latitude-or-longitude-to-meters"
// 兩地點之經緯度座標，經過此函式轉換成距離以meter為單位
double Distance(double lat1, double lon1, double lat2, double lon2)
{
    double radius = 6378.137;                 // 地球之半徑
    double dlat = (lat2 - lat1) * M_PI / 180; // 經度差
    double dlon = (lon2 - lon1) * M_PI / 180; // 緯度差
    double tmp = sin(dlat / 2) * sin(dlat / 2) + cos(lat1 * M_PI / 180) * cos(lat2 * M_PI / 180) * sin(dlon / 2) * sin(dlon / 2);
    tmp = 2 * 1000 * radius * atan2(sqrt(tmp), sqrt(1 - tmp));
    // 此reference利用"https://en.wikipedia.org/wiki/Haversine_formula"中的公式
    return tmp; // 回傳tmp
}
