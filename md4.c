#include <gcrypt.h>
#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
  gcry_md_hd_t md4;
  gcry_error_t error;
  int text_length;
  unsigned char* buffer;
  size_t len;
  int a,i;
/*initialization of gcrypt library*/
/*check if subsystems are intialized, check version.*/
  if (!gcry_check_version (GCRYPT_VERSION)){
    err(1, "%s", "libgcrypt version mismatch\n");
  }
/*turn off warnings*/
  gcry_control (GCRYCTL_SUSPEND_SECMEM_WARN);
/*allocate a pool of 16k for secure memory*/
  gcry_control (GCRYCTL_INIT_SECMEM, 16384, 0);
/*libgcrypt check secure memory*/
  gcry_control (GCRYCTL_RESUME_SECMEM_WARN);
/*initialization has completed. */
  gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);
/*end of initialization*/
  text_length=strlen(argv[1]);
  buffer=(unsigned char*) malloc(text_length*sizeof(char));
  strcpy(buffer,argv[1]);
/*create a message digest object for algorithm GCRY_MD_MD4 - means MD4*/
  error=gcry_md_open(&md4,GCRY_MD_MD4,GCRY_MD_FLAG_SECURE);
  if(error){
    err(1, "Failed opening MD4: %s\n", gpg_strerror(error));
  }
  gcry_md_write( md4, buffer, text_length );
  gcry_md_final( md4 );
  unsigned char *digest=(unsigned char*) malloc(gcry_md_get_algo_dlen( GCRY_MD_MD4 )*sizeof(char));
  digest = gcry_md_read( md4, GCRY_MD_MD4 );
/*print hash*/
  printf("HASH MD4:");
  for ( i=0; i < gcry_md_get_algo_dlen(buffer[i]); i++){
    printf("%X", digest[i]);
  }
  printf("\n");

  /*for (int j = 0; j < gcry_md_get_algo_dlen(hashes[i]); j++) printf("%02x", digest[j]);
      printf("\n\n");*/


/*closing*/
  gcry_md_close(md4);
  return 0;
}
