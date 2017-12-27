# SourceInsight 快捷键配置

总结一下自己常用的快捷键, 说来惭愧。常用的快捷键很少的, 虽然网上找了配置文件, 但自己平时生活工作的规范性却很低。尽量的提高自己的效率。

### 01 `Ctrl + /` 进行快速注释
打开 Base 工程 -->> Project->Open Project 选择 `Base` 工程,然后将下面的代码 copy 到文末。

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

Option -> Key Assignments -> Macro:MultiLineComment 设置为快捷键 `Ctrl + /`

### 02 更换主题
如果有现成的主题是可以直接替换的, 没有的需要自己花点时间修改成自己喜欢的主题就行了。
实际上也不用自己修改, 去网上搜一下也有已经别做好了的主题。我的主题也是网上找的, 在[这里可以看到](https://github.com/AlvinMi/Note/tree/master/05_开发环境相关/Source%20Insight/SourceInsight4.0Pack)。

可以选择 `Options` -> `Load Configuration` -> Load 添加自己的主题。 
