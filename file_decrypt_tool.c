#include<stdio.h>
#include<string.h>
#include<openssl/aes.h>


int main(int argc,char** argv)
{
/*	char use_key[AES_BLOCK_SIZE]="abcqwre";
	AES_KEY key;

	char plain_msg[16]="a, i love you!";
	char encrypted_msg[17]="";

	AES_set_encrypt_key(use_key,AES_BLOCK_SIZE * 8,&key);

	AES_encrypt(plain_msg,encrypted_msg,&key);

	printf("%s\n",encrypted_msg);

	
	char msg2[16];

	AES_set_decrypt_key(use_key,AES_BLOCK_SIZE*8,&key);
	AES_decrypt(encrypted_msg,msg2,&key);
	printf("%s\n",msg2);

*/
	FILE* fp_plain =NULL;
	FILE* fp_encrypt = NULL;
	unsigned char plain_data[16],encrypt_data[18];
	int ret;
	char user_key[17]="";
	AES_KEY key;

	strcpy(user_key,argv[3]);	
	AES_set_encrypt_key(user_key,128,&key);	

	fp_encrypt = fopen(argv[1],"rb");
	fp_plain = fopen(argv[2],"wb");
	
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
	//	file_size += ret;
	}
	
//	fwrite(&ret,sizeof(int),1,fp_encrypt);

	fclose(fp_plain);
	fclose(fp_encrypt);


	return 0;
}
