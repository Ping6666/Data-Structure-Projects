# Data-Structure-Projects
108-02 NCU CO2012 Data Structure

## Homework01

### 壓縮檔案檔案說明
Route.kml      ：為我的kml
FriendRoute.kml：為朋友的kml
備註：因為我手機並沒有開放權限給Google Map紀錄資料，所以我是自己使用Google Map的內建功能將kml創建出來的，且我朋友不願意給我他的kml檔案，所以我只好再創建另一個kml。

### function使用說明
此function首先會自動讀入檔案，接著輸出"Please input the MAX distance in meters."。
此時使用者應輸入，短於多少公尺就算重疊的公尺數。
程式會判斷，若重疊發生輸出"True, Overlapping."；反之輸出"False, No overlapping."。

### function中的buildcoordinates說明
此函式將kml資料輸入，以char為資料型態存入vector中。
接者使用內建函式search出目標字串<coordinates>與</coordinates>。
將座標取出，並以double為資料型態存入另一個vector之中。

### function中的Distance說明
以輸入的經緯度*2換算成距離差並以meter為單位。
備註：此段程式碼參考 "https://stackoverflow.com/questions/639695/how-to-convert-latitude-or-longitude-to-meters" ，且他參考 "https://en.wikipedia.org/wiki/Haversine_formula" 中的公式。

### function複雜度
function中的buildcoordinates，複雜度應該是O(n)，n為檔案大小。
function中的Distance，複雜度應該是O(1)，因為只是簡單的套用公式。
function中的main，複雜度應該是O(m*n)，其中m,n皆分別表不同檔案中coordinate的數量。
整體複雜度應該是O(m*n)，其中m,n皆分別表不同檔案中coordinate的數量。

### function結果與實用度說明
我嘗試過此function，其中80.755輸出為False, No overlapping.；而80.76輸出為True, Overlapping.。
而透過 "http://kmlviewer.nsspot.net/" 或是Google Map的功能檢查，最近距離大約為98.5(公尺)，因此這表示我使用的reference低估了距離，不過我覺得低估總比高估還好，我認為其中的誤差應該來自於，radius(地球半徑)的經度不夠，且經由一次一次的數學運算將誤差擴大，而我認為還存在一個問題內建函式stod(string to double)轉換過程產生極大的誤差，所以計算出的結果才有誤差。

### 程式編輯說明
我沒有使用using namespace std;是因為非常容易使用到其中的保留字，所以我的習慣是不要使用using namespace std;，而使用"std::"在需要的地方。
我習慣將所有函式都丟到最後面，並且在程式開頭進行宣告。
備註：若有此README敘述不清之處，請參考程式碼中的註解。

## Homework02

### 程式使用方式：
case 1
可以一次輸入多筆數字(正數、負數皆可)以空白做間格，並以0為結束，可以重複進入此階段，不過輸入重複數字會跳過，不加入二元樹。 \
case 2
若此數存在的話會輸出其在二元樹中的index，不存在則輸出沒找到。 \
case 3
輸出兩行，第一行為小到大第二行為大到小。 \
case 4
表依照list順序輸出內容。 \
case 0
則結束程式。

備註：如有何不清，請見程式簡介PDF或是詳見程式碼中註解內容。

## final

我們這組繳交兩份程式碼，其中"final_API.cpp"，有做好漂亮的執行畫面，如此就不需要計算需要出牌的編號，不過只能有一位人類玩家與其他三位電腦玩家；另外"final_noAPI.cpp"，雖然沒有漂亮的執行畫面，也需要自己計算出牌的編號，但是可以自訂人類玩家數量，也就是說可以四個人類玩家對戰。

> 操作說明：

- "final_API.cpp"
因為只有一名人類玩家，所以不需要輸入人類玩家數量。首先螢幕呈現遊玩遊戲為"POKER"，接者，接著程式會自動決定出牌順序，與目前出牌玩家，若換到人類玩家，螢幕會輸出剩餘手牌狀況，接者玩家便能輸入指令。
1.鍵盤"A"、"D"左右控制
2.鍵盤"SPACE"選擇游標所在處的牌
3.鍵盤"Backspace"取消選牌
4.鍵盤"ENTER"表出牌，若不選擇表過牌，並且螢幕會輸出出牌狀況，接者若玩家有此牌、出牌不重複、出牌合法且出牌比前玩家大，則可以順利出牌
並繼續進行遊戲，直到有人手牌數量歸零，表此玩家勝出。

- "final_noAPI.cpp"
首先執行需要輸入人類玩家數量，接著程式會自動決定出牌順序，與目前出牌玩家，若換到人類玩家，螢幕會輸出剩餘手牌狀況，接者玩家需要輸入出牌編號，編號為牌的數字大小與牌面花色決定，數字從小到大，花色從梅花、方塊、紅心到黑桃，舉例來說梅花3為編號"2"、黑桃2為編號"40"，出完牌後需要加上"-1"表出牌結束，若不打編號只有打"-1"表過牌，並且螢幕會輸出出牌狀況，接者若玩家有此牌、出牌不重複、出牌合法且出牌比前玩家大，則可以順利出牌，並繼續進行遊戲，直到有人手牌數量歸零，表此玩家勝出。
