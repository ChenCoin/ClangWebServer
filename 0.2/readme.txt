gcc tool.c -static -o tool
./tool index.html
./tool 404.html

gcc main.c -static -o app
./app 8080