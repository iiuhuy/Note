# SourceInsight 快捷键配置

总结一下自己常用的快捷键, 说来惭愧。常用的快捷键很少的, 虽然网上找了配置文件, 但自己平时生活工作的规范性却很低。

* `Ctrl + /` 进行快速注释
	* 打开 Base 工程 -->> Project->Open Project 选择 `Base` 工程,然后将下面的代码 copy 到文末。

		macro MultiLineComment()  
		{  
	    hwnd = GetCurrentWnd()  
	    selection = GetWndSel(hwnd)  
	    LnFirst =GetWndSelLnFirst(hwnd)    
	    LnLast =GetWndSelLnLast(hwnd)     
	    hbuf = GetCurrentBuf()  
	    if(GetBufLine(hbuf, 0) =="//magic-number:tph85666031")  
	    {  
	        stop  
	    }  
	    Ln = Lnfirst  
	    buf = GetBufLine(hbuf, Ln)  
	    len = strlen(buf)  
	    while(Ln <= Lnlast)   
	    {  
	        buf = GetBufLine(hbuf, Ln) 
	        if(buf =="")  
	        {                  
	            Ln = Ln + 1  
	            continue  
	        }  
	        if(StrMid(buf, 0, 1) == "/")  
	        {  
	            if(StrMid(buf, 1, 2) == "/")  
	            {  
	                PutBufLine(hbuf, Ln, StrMid(buf, 2, Strlen(buf)))  
	            }  
	        }  
	        if(StrMid(buf,0,1) !="/")  
	        { 
	            PutBufLine(hbuf, Ln, Cat("//", buf))  
	        }  
	        Ln = Ln + 1  
	    }  
	    SetWndSel(hwnd, selection)  
		}

	* Option -> Key Assignments -> Macro:MultiLineComment 设置为快捷键 `Ctrl + /`