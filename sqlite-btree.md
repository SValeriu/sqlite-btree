﻿==File Format==
Table - B+trees
Index - B-trees
元信息(page 1 of each table)是在sqlite\_master table中存储的

## Other ##
**sqlite3Moveto相当于find，只不过没有找到它返回的是临近位置** BtCursor 可以算是带额外信息的pageno
## cell ##
## B-Tree ##
payload = B-Tree record = (key,data)
key = ROWID or primary key

## B+Tree ##

cell = record = tuple = 变长字符串
### Cellno ###
编号从0起
### Cell Content ###
```
	The content of a cell looks like this:
    SIZE    DESCRIPTION
      4     Page number of the left child. Omitted if leaf flag is set.
     var    Number of bytes of data. Omitted if the zerodata flag is set.
     var    Number of bytes of key. Or the key itself if intkey flag is set.
      *     Payload
      4     First page of the overflow chain.  Omitted if no overflow
```
### Pagno ###
编号从1起
0表示not a page,
1表示root page

Mempage{

> int leaf;
> int leafdata;

}