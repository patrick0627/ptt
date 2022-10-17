資料庫分級儲存 概況
*******************************************
		        (id)
./DataBase /UserInfo	/Patrick/user.txt  //檔案要包含密碼、權限級別 、自己曾經發過的文章路徑)
		   	/Brandon
			/Weiting
		
	   /BoardInfo	/Favorite	/Tech	/1.txt	(artical_ID.txt包含標題 內文 留言)
						/2.txt
			   		/NBA
		       			/Gossiping
========================================================


使用者資料存檔格式
*******************************************
user.txt 			//檔名統一用user.txt

password xxxxxx
level x 						//guest=1,member=2,adimin=3
post x							//x = 發文的文章數
./DataBase/BoardInfo/Favorite/Gossiping/1.txt FuckYourPtt 	//文章的資料絕對路徑 文章標題 
========================================================


文章檔案存檔格式
*****************************************************
1.txt			//檔名用數字代碼存就好了 

title FuckYourPTT 	// 標題
-STARTARTICAL-		//文章自以下開始
FUCK YOU PTT		//內文





-ENDARTICAL-		//文章結束
message 3		//留言數
3 xxx agree			//第一個字用來分辨 推噓 1推2噓3留言(->)
1 xxx Push~				
2 xxx piece of cake   
========================================================
