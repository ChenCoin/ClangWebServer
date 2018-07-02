在Web服务器的基础上，加入静态网页。

网页文件先转换为C语言的字符串格式的数据，再以include的形式加入main文件中，进而实现静态打包网页。

网页转换为字符串的工具为tool.c

编译：gcc tool.c -static -o tool

网页转换：
将index.html转换为index.html.c，命令为：./tool index.html
将404.html转换为404.html.c，命令为：./tool 404.html

静态编译：gcc main.c -static -o app
运行：./app 8080

![运行结果](https://github.com/ChenCoin/DarkHunter/blob/master/0.2/screenshot.png)
