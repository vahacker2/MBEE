#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


void main(int argc, char *argv[])

{

if (argc !=4) {
printf("\n\n");

printf("\nMBEE - Metric Buttload Encryption Engine\n----\n mbee -c <create> to create keys and keystore.\n mbee -e <source_filename> <encrypted_filename> to encrypt a file.\n mbee -d <source_filename> <encrypted_filename> to decrypt a file.\n\n\n");

exit(1);

}

if (!strcmp(argv[1], "-c"))

{

    FILE *fp, *fp1;


     char password[10];

     printf("Enter password: ");
     scanf("%s",password);

    printf("\n");
    fp1 = fopen("/etc/mbee","r");
      if(fp1 == NULL)
        mkdir("/etc/mbee", 0700);

     mkdir ("/mnt/mbee_ramdisk", 0700);
     system("mount -t tmpfs -o size=3m tmpfs /mnt/mbee_ramdisk");
     sleep(1);
     srand((unsigned int)(time(NULL)));


          fp = fopen("/mnt/mbee_ramdisk/mbee_keystore", "w");

         int i = 0;
         int index = 0;

             //character list to build random passwords
                        char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
             // CAREFUL what special chars you put in here as they could break the engine.
             // Each password is 400 trillion trillion trillion trillion trillion trillion years to BF hack.  I think this is enough.




             //Function to create 4 random password, each 128chars in length for MBEE_Keystore.

         while (i < 4)
    {
              for(index = 0; index < 128; index++)
                {
                  fprintf(fp, "%c", characters[rand() % (sizeof characters - 1)]);
                }
                  printf("\n");
                  fprintf(fp,"\n");
    i++;
   }
          fclose(fp);

          // Encryption of MBEE Keystore in ramdir then copys it to /etc/mbee directory.

      char command[300];

      sprintf(command, "openssl aes-256-cbc -e -salt -in /mnt/mbee_ramdisk/mbee_keystore -out /mnt/mbee_ramdisk/mbee_keystore2 -pass pass:%s\n", password);
      system( command );

      sprintf(command, "openssl bf-ecb -e -salt -in /mnt/mbee_ramdisk/mbee_keystore2 -out /mnt/mbee_ramdisk/mbee_keystore3 -pass pass:%s\n", password);
      system( command );

      sprintf(command, "openssl camellia-256-cfb1 -e -salt -in /mnt/mbee_ramdisk/mbee_keystore3 -out /mnt/mbee_ramdisk/mbee_keystore4 -pass pass:%s\n", password);
      system( command );

      sprintf(command, "openssl aes-192-ecb -e -salt -in /mnt/mbee_ramdisk/mbee_keystore4 -out /mnt/mbee_ramdisk/mbee_keystore1 -pass pass:%s\n", password);
      system( command );



      system("cp /mnt/mbee_ramdisk/mbee_keystore1 /etc/mbee/mbee_keystore");

      system("umount /mnt/mbee_ramdisk/");




}



//
// Encryption Function
//
  if (!strcmp(argv[1], "-e"))
{
      mkdir ("/mnt/mbee_ramdisk", 0700);
      system("mount -t tmpfs -o size=1m tmpfs /mnt/mbee_ramdisk");
      system("cp /etc/mbee/mbee_keystore /mnt/mbee_ramdisk/mbee_keystore");


     char password[10];

     printf("Enter password: ");
     scanf("%s",password);


      char command[300];

      sprintf(command, "openssl aes-192-ecb -d -salt -in /mnt/mbee_ramdisk/mbee_keystore -out /mnt/mbee_ramdisk/mbee_keystore2 -pass pass:%s\n",password);
      system( command );

      sprintf(command, "openssl camellia-256-cfb1 -d -salt -in /mnt/mbee_ramdisk/mbee_keystore2 -out /mnt/mbee_ramdisk/mbee_keystore3 -pass pass:%s\n", password);
      system( command );

      sprintf(command, "openssl bf-ecb -d -salt -in /mnt/mbee_ramdisk/mbee_keystore3 -out /mnt/mbee_ramdisk/mbee_keystore4 -pass pass:%s\n", password);
      system( command );

      sprintf(command, "openssl aes-256-cbc -d -salt -in /mnt/mbee_ramdisk/mbee_keystore4 -out /mnt/mbee_ramdisk/mbee_keystore_decrypt -pass pass:%s\n", password);
      system( command );



#define BUF 175 /* can change the buffer size as well */
#define TOT 10 /* change to accomodate other sizes, change ONCE here */


{

//
// Function to read lines from keystore and put into an array
//

    char line[TOT][BUF];
    FILE *plist = NULL;
    int a = 0;
    int total = 0;

    plist = fopen("/mnt/mbee_ramdisk/mbee_keystore_decrypt", "r");
    while(fgets(line[a], BUF, plist)) {

        /* get rid of ending \n from fgets */
        line[a][strlen(line[a]) - 1] = '\0';
        a++;


}


    total = a;
    for(a = 0; a < total; ++a)
    printf("%s\n", line[a]);
    printf("\n");

   fclose(plist);
   system("umount /mnt/mbee_ramdisk/");



    char command2[300];

    char *in_name=argv[2];
    char *out_name="aaa.enc";
    char *pass="pass:";
    char *fname=argv[3];


    sprintf(command2, "openssl aes-192-ecb -e -salt -in %s -out %s -pass pass:%s\n", in_name, out_name, line[0]);
    system( command2 );
    printf(command2);

    sprintf(command2, "mv  %s tempenc.mbee\n", out_name);
    system( command2 );

    printf("Encrypting with : aes-192-ecb\n");

    sprintf(command2, "openssl bf-ecb  -salt -in tempenc.mbee -out %s  -pass pass:%s\n", out_name, line[1]);
    system( command2 );
    sprintf(command2, "mv  %s tempenc.mbee\n", out_name);
    system( command2 );

    printf("Encrypting with : bf-ecb\n");


    sprintf(command2, "openssl camellia-256-cfb1  -salt -in tempenc.mbee -out %s -pass pass:%s\n", out_name, line[2]);
    system( command2 );
    sprintf(command2, "mv  %s tempenc.mbee\n", out_name);
    system( command2 );

    printf("Encrypting with : camellia-256-cfb1\n");


    sprintf(command2, "openssl aes-256-cbc  -salt -in tempenc.mbee -out %s -pass pass:%s\n", out_name, line[3]);
    system( command2 );

    sprintf(command2, "mv  %s %s\n", out_name, fname);
    system( command2 );
    system(" rm tempenc.mbee");


    printf("Encrypting with : aes-256-cbc\n\n");

}
}


//
// DECRYPTION FUNCTION
//



  if (!strcmp(argv[1], "-d"))
{
      mkdir ("/mnt/mbee_ramdisk", 0700);
      system("mount -t tmpfs -o size=1m tmpfs /mnt/mbee_ramdisk");
      system("cp /etc/mbee/mbee_keystore /mnt/mbee_ramdisk/mbee_keystore");

     char password[10];

     printf("Enter password: ");
     scanf("%s",password);


      char command[300];

      sprintf(command, "openssl aes-192-ecb -d -salt -in /mnt/mbee_ramdisk/mbee_keystore -out /mnt/mbee_ramdisk/mbee_keystore2 -pass pass:%s\n",password);
      system( command );

      sprintf(command, "openssl camellia-256-cfb1 -d -salt -in /mnt/mbee_ramdisk/mbee_keystore2 -out /mnt/mbee_ramdisk/mbee_keystore3 -pass pass:%s\n", password);
      system( command );

      sprintf(command, "openssl bf-ecb -d -salt -in /mnt/mbee_ramdisk/mbee_keystore3 -out /mnt/mbee_ramdisk/mbee_keystore4 -pass pass:%s\n", password);
      system( command );

      sprintf(command, "openssl aes-256-cbc -d -salt -in /mnt/mbee_ramdisk/mbee_keystore4 -out /mnt/mbee_ramdisk/mbee_keystore_decrypt -pass pass:%s\n", password);
      system( command );




#define BUF 175 /* can change the buffer size as well */
#define TOT 10 /* change to accomodate other sizes, change ONCE here */


{

//
// Function to read lines from keystore and put into an array
//

    char line[TOT][BUF];
    FILE *plist = NULL;
    int a = 0;
    int total = 0;

    plist = fopen("/mnt/mbee_ramdisk/mbee_keystore_decrypt", "r");
    while(fgets(line[a], BUF, plist)) {

        /* get rid of ending \n from fgets */
        line[a][strlen(line[a]) - 1] = '\0';
        a++;


}


    total = a;
    for(a = 0; a < total; ++a)
    printf("%s\n", line[a]);
    printf("\n");

   fclose(plist);
   system("umount /mnt/mbee_ramdisk/");



    char command2[300];

    char *in_name=argv[2];
    char *out_name="aaa.enc";
    char *pass="pass:";
    char *fname=argv[3];

    sprintf(command2, "openssl aes-256-cbc -d -salt -in %s -out %s -pass pass:%s\n", in_name, out_name, line[3]);
    system( command2 );
    sprintf(command2, "mv  %s tempenc.mbee\n", out_name);
    system( command2 );

    printf("Round 1\n");

    sprintf(command2, "openssl camellia-256-cfb1 -d  -salt -in tempenc.mbee -out %s -pass pass:%s\n", out_name, line[2]);
    system( command2 );
    sprintf(command2, "mv  %s tempenc.mbee\n", out_name);
    system( command2 );

    printf("Round 2\n");

    sprintf(command2, "openssl bf-ecb -d -salt -in tempenc.mbee -out %s -pass pass:%s\n", out_name, line[1]);
    system( command2 );
    sprintf(command2, "mv  %s tempenc.mbee\n", out_name);
    system( command2 );

    printf("Round 3\n");


    sprintf(command2, "openssl aes-192-ecb -d  -salt -in tempenc.mbee -out %s -pass pass:%s\n", out_name, line[0]);
    system( command2 );

    sprintf(command2, "mv  %s %s\n", out_name, fname);
    system( command2 );
    system(" rm tempenc.mbee");


    printf("Round4\n");



}

// More dev here.


}

else

{

printf("Access denied");

exit(1);

}

// More Dev here.

}
