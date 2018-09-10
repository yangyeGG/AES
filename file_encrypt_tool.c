#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/aes.h>

/*
*基于AES加密解密小工具
*参数描述：
*加密：第一个参数：需要加密的文件 第二个参数：加密后生成的二进制文件名 第三个参数：加密的秘钥  第四个参数：-e 表示加密
*解密：第一个参数：加密的文件 第二个参数：解密后生成的文件名 第三个参数：秘钥  第四个参数：-d 表示解密
*作者：yy
*时间：18-9-10
*/


int main(int argc,char** argv)
{
	if(argc != 5)
	{
		printf("参数错误!\n");
		exit(1);
	}
	if(strcmp(argv[4],"-e") == 0)
	{
		FILE* fp_plain =NULL;
		FILE* fp_encrypt = NULL;
		unsigned char plain_data[16],encrypt_data[16];
		int ret,file_size=0;
		char user_key[17]="";
		AES_KEY key;

		strcpy(user_key,argv[3]);	
		AES_set_encrypt_key(user_key,128,&key);	

		fp_plain = fopen(argv[1],"rb");
		if(fp_plain==NULL)
		{
			perror("fopen");
			exit(2);
		}
		fp_encrypt = fopen(argv[2],"wb");
		if(fp_encrypt==NULL)
		{
			perror("fopen");
			exit(2);
		}
		
		while(ret=fread(plain_data,1,16,fp_plain))
		{
			AES_encrypt(plain_data,encrypt_data,&key);
			fwrite(encrypt_data,1,16,fp_encrypt);
			if(ret < 16) break;
		}
		
		fwrite(&ret,1,1,fp_encrypt);

		fclose(fp_plain);
		fclose(fp_encrypt);
	}
	
	if(strcmp(argv[4],"-d")==0)
	{
		FILE* fp_plain =NULL;
		FILE* fp_encrypt = NULL;
		unsigned char plain_data[16],encrypt_data[18];
		int ret;
		char user_key[17]="";
		AES_KEY key;

		strcpy(user_key,argv[3]);	
		AES_set_decrypt_key(user_key,128,&key);	

		fp_encrypt = fopen(argv[1],"rb");
		if(fp_encrypt==NULL)
		{
			perror("fopen");
			exit(2);
		}
		
		fp_plain = fopen(argv[2],"wb");
		if(fp_plain==NULL)
		{
			perror("fopen");
			exit(2);
		}
		
		while(ret=fread(encrypt_data,1,18,fp_encrypt))
		{
			AES_decrypt(encrypt_data,plain_data,&key);
			if(ret < 18)
			{	
				fwrite(plain_data,1,encrypt_data[16] ? encrypt_data[16]:16,fp_plain);
				break;
			}
			
			fwrite(plain_data,1,16,fp_plain);
		
			 fseek(fp_encrypt,-2,SEEK_CUR);

		}
		
		fclose(fp_plain);
		fclose(fp_encrypt);
	}

	return 0;
}
