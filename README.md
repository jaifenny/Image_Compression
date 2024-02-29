# Image_Compression

- 附件含三張利用將晶片高度以色彩視覺化後的圖片
- 基於Run-Length的壓縮方法，對圖檔作無失真壓縮後儲存成新檔案，並計算三張圖片的平均壓縮率(compression ratio)

## :small_blue_diamond: Environment:
* Windows 10, Visual Studio 2019, OpenCV 4.5.0, C++

## :small_blue_diamond: Method:
1. 輸入檔案名稱，判斷該檔案需壓縮還是解壓縮，讀取檔案。
2. 判斷為需做壓縮compression1(): 用兩個for迴圈並將RGB分開處理需壓縮目標圖片，計算同顏色的連續長度，儲存數值(Color Index, Number of Pixels)在compression陣列，將compression陣列輸出到文字檔(compression_img1.bmp.txt)，計算結束輸出”done”和原圖(Original)。
```
    n1 = img.at<Vec3b>(i, j)[rgb]

    n2 = img.at<Vec3b>(i, j - 1)[rgb]
```
- ![](https://github.com/jaifenny/Image_Compression/blob/main/picture/1.png)


3. 判斷為需做解壓縮unzip1(): 將文字檔內的數值儲存在unzip陣列，用兩個for迴圈並將RGB分開處理需解壓縮目標檔案，num = unzip[n3]，color = unzip[n3 + 1]，統計數量n4，如果小於num，則該圖片位置元素數值為color，否則將資料更新，元素數值為新的color，並重新統計數量n4，解壓縮結束將輸出BMP檔(unzip_compression_img1.bmp)，計算結束輸出還原圖片路徑和還原圖(Unzip)。

- ![](https://github.com/jaifenny/Image_Compression/blob/main/picture/2.png)


## :small_blue_diamond: Result:
- 由下圖可知檔案資料量，每一張圖片(img*.bmp)壓縮成文字檔(compression_img*.bmp.txt)後資料量變少，再解壓縮還原成圖片(unzip_compression_img*.bmp)後與原始圖片的內容與大小一樣，壓縮率=原始大小/壓縮大小，如統計圖表所示此作業的平均壓縮率為2.1865。 * = 1, 2, 3

- ![](https://github.com/jaifenny/Image_Compression/blob/main/picture/3.png)

## :small_blue_diamond: Compression ratio

| 圖片  | 原始大小 | 壓縮大小 | 壓縮率 |
| -------- | -------- | -------- | -------- |
| img1 | 13.9 MB | 5.66 MB  | 2.4558 |
| img2 | 13.9 MB | 9.75 MB  | 1.4256 |
| img3 | 13.9 MB | 5.19 MB  | 2.6782 |

#### 平均壓縮率: 2.1865


