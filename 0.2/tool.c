# include <stdio.h>
# include <string.h>
# include <stdlib.h>

int main(int argc, char **argv){
	FILE *source = fopen(argv[1],"r");
	char targetPath[128];
	strcpy(targetPath, argv[1]);
	strcat(targetPath, ".c");
	FILE *target = fopen(targetPath, "w");

	fputs("char* data = \"", target);
	char text[1024];
	while(fgets(text, 1024, source)!=NULL)
	{
		int length = strlen(text);
		/* 不考虑一行字符超过1024个的情况
		 * html文件的末尾必须有一个空行
		 * 
		*/
		text[length-1] = '\\';
		text[length] = 'n';
		text[length+1] = 0;
		char tmp[2048];
		int point = 0;
		for(int i=0; i<length+2; i++){
			if(text[i]=='\"'){
				tmp[point] = '\\';
				point++;
			}
			tmp[point] = text[i];
			point++;
		}
		fputs(tmp, target);
	}
	fputs("\";", target);

	fclose(source);
	fclose(target);
	return 0;
}
