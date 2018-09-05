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
	unsigned char plain_data[16],encrypt_data[16];
	int ret,file_size=0;
	char user_key[17]="";
	AES_KEY key;

	strcpy(user_key,argv[3]);	
	AES_set_encrypt_key(user_key,128,&key);	

	fp_plain = fopen(argv[1],"rb");
	fp_encrypt = fopen(argv[2],"wb");
	
	while(ret=fread(plain_data,1,16,fp_plain))
	{
		AES_encrypt(plain_data,encrypt_data,&key);
		fwrite(encrypt_data,1,16,fp_encrypt);
		if(ret < 16) break;
	}
	
	fwrite(&ret,1,1,fp_encrypt);

	fclose(fp_plain);
	fclose(fp_encrypt);


	return 0;
}
