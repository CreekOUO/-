
#include <iostream>
#include "work1.h"
#include <fstream>
#include <string>
#include <sstream>
//運行不了的，跑不動很多地方有漏洞我不不知道怎麼改，總之我改的救不回來了
//可以當作我寫pseudo code嗎?

int main() {    
    TbinTree<int> tree; //我寫T報錯，那就在這個tree資料類型int
    
    ifstream in("c:\\data.txt");
    if (!in.is_open()) {
        cout << "無法打開文件！" << endl;
        return 1;
    }

    string line;
    getline(in, line);  // 讀取檔案資料
    stringstream ss(line);//用它記住轉換成int
    int num;
    // 我不會動態
    int inser[30], delet[30], search[30];
    int inserCount = 0, deletCount = 0, searchCount = 0;

    // 用 while讀取並計數，計數是為了方便後面調用函式
    bool doDele = false, doSer = false;//判斷數放哪
    while (ss >> num || ss.fail()) {
        if (ss.fail()) {
            if (ss.fail()) { // @@不是整數，會導致fail
                ss.clear(); // 清除 fail 狀態
                string temp;
                ss >> temp; // 讀取非數字內容
                if (temp == "@@") {// 遇到 @@，換要存的位置
                    if (!doDele && !doSer) {//如果都是false，就開始存要刪除的點
                        doDele = true;
                    }
                    else if (doDele && !doSer) {//開始存要查排名的點
                        doSer = true;
                    }
                    continue;
                }
            }
        }
        else {
            if (!doDele && !doSer) {
                inser[inserCount++] = num;  
            }
            else if (doDele && !doSer) {
                delet[deletCount++] = num;
            }
            else {
                search[searchCount++] = num;
            }
        }
    }
    in.close(); // 關閉檔案
    for (int i = 0;i < inserCount;i++)
    {
    
        tree.insert(inser[i]);
    }
    
     tree.inOrderTraversal(tree.getRoot());
   
    
    return 0;
}

