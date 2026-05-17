#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#define MAGIC_STRING "#*"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

uint get_file_size(FILE *fptr)
{
    fseek(fptr,0,SEEK_END);
  printf("Secret file size is %lu\n",ftell(fptr));
  return ftell(fptr);
    // Find the size of secret file data
}

/*
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    char str[10]=".bmp";
    char *ptr;
    ptr=strstr(argv[2],str);
    if((ptr!=NULL && strcmp(ptr,str)==0) && strlen(ptr)==strlen(str))
    {
        printf("Validation of bmp file is sucessifully");
        return e_success;
    }
    else
    {
        printf("Enter the .bmp file");
        return e_failure;
    }
    
    //step1 -> check source file name having .bmp present or not
            // no -> return e_failure
            // yes -> store source file name into encInfo->src_image_fname
            char str1[10]=".txt";
     char *ptr1;
     ptr1=strstr(argv[3],str1); // Validate .txt
    if((ptr1 != NULL && strcmp(ptr1,".txt")==0)&&strlen(ptr1) == strlen(".txt"))
    {
       printf("---------validation complete--------\n");
       return e_success;
    }
    else 
    printf("Enter the .txt file\n");
    return e_failure;
    //step2 -> check secret file having extn or not
            // no -> return e_failure
            // yes -> store secret file name into encInfo->src_image_fname
    // step3 -> check optional file is passed or not
            // yes -> check the file having .bmp or not
                    // no -> return e_failure
                    //yes -> store the file name into encInfo->stego_image_fname
            // no -> store default name to encInfo->stego_image_fname = "stego.bmp";
    //step4 -> return e_success
}

Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

        return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

        return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

        return e_failure;
    }

    // No failure return e_success
    return e_success;
}

Status check_capacity(EncodeInfo *encInfo)
{
    encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);
     // step1 -> encInfo->image_capacity =get_image_size_for_bmp(source_file_pointer)
    encInfo->size_secret_file= get_file_size(encInfo->fptr_secret);
    // step2 -> find secret file size encInfo -> size_secret_file = get_file_size(secret file pointer)
   if(encInfo->image_capacity>16+32+32+32+(encInfo->size_secret_file*8))
    // step3 -> compare encInfo->image_capacity > 16 + 32 + 32 + 32 + 54 + (encInfo -> size_secret_file * 8)
    return e_success;
    else
    return e_failure;
            //yes -> return e_success
            // no -> return e_failure
}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    char arr[54];
    fseek(fptr_src_image,0,SEEK_SET);
   //step1  ->   rewind file pointer 0th position
   fread(arr,54,1,fptr_src_image);
     // step2 ->   read 54 byter from source file(use fread);
     fwrite(arr,54,1,fptr_dest_image);
     //step3 ->   write the 54 bytes to strgo image file(from buffer)
     printf("Copying the header file is sucessifully");
    //step4 ->  return e_sucess
    return e_success;
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    if(encode_magic_string(strlen(MAGIC_STRING),encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_success)
    {
          printf("Encoding data to image\n");
          return e_success;
    }
    else 
    {
        printf("Encoding data to image failed \n");
        return e_failure;
    }
    //step1  ->   read 8 bytes of buffer form source image
     // step2 ->  call encode_bytes to lsb(magic_string[0],buffer)
     //step3 ->   store the buffer to stego image file
    //Do this upto magic_string size time (step1)
    // return e_sucess
}
Status encode_secret_file_extn_size(int size, EncodeInfo *encInfo)
{
    char buffer[32];

    // Step 1: Read 32 bytes from source image
    if (fread(buffer, 1, 32, encInfo->fptr_src_image) != 32)
    {
        return e_failure;
    }
    encode_size_to_lsb(size, buffer);

    if (fwrite(buffer, 1, 32, encInfo->fptr_stego_image) != 32)
    {
        return e_failure;
    }

    // Step 4: Return success
    return e_success;
}
    //step1 ->  read 32 bytes of buffer from source image
     // step2 -> call encode_size_to_lsb(size,buffer)
     // step -> store the buffer to stego image file
       // return e_sucess

Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    int len = strlen(file_extn);
    if (encode_secret_file_size(len, encInfo) != e_success)
        return e_failure;

    /* Now encode extension characters */
    if (encode_data_to_image(file_extn, len,
            encInfo->fptr_src_image, encInfo->fptr_stego_image) != e_success)
        return e_failure;

    return e_success;
   // step 1 -> read 8 bytes of buffer from source image file
    // step2 -> encode_byte_to_lsd(file_extn[0],buffer)
    // step3 -> store the buffer into stego image file 
            // repeat the upto size of extn size // 

    // return e_sucess
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)

    {
    unsigned char size_buffer[4]; // 4 bytes to store size

    size_buffer[0] = (file_size >> 24) & 0xFF; // Most significant byte
    size_buffer[1] = (file_size >> 16) & 0xFF;
    size_buffer[2] = (file_size >> 8) & 0xFF;
    size_buffer[3] = file_size & 0xFF; // Least significant byte

   if(encode_data_to_image((char*)size_buffer, 4, encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_success)
    {
          printf("Encoding data to image\n");
          return e_success;
    }
    else 
    {
        printf("Encoding data to image failed \n");
        return e_failure;
    }
    //step1 ->  read 32 bytes of buffer from source image
     // step2 -> call encode_size_to_lsb(file_size,buffer)
     // step -> store the buffer to stego image file
       // return e_sucess
}

Status encode_secret_file_data(EncodeInfo *encInfo)
{
    
    char arr[8];
    int ch;
    fseek(encInfo->fptr_secret,0,SEEK_SET); // Start reading secret file
    while ((ch = fgetc(encInfo->fptr_secret)) != EOF)
    {
        fread(arr, 8, 1, encInfo->fptr_src_image);
        if (encode_byte_to_lsb((char)ch, arr) != e_success)
            return e_failure;
        fwrite(arr, 8, 1, encInfo->fptr_stego_image);
    }
    return e_success;
}
    //step1 -> read the secret data into one data buffer
    // step 2 -> read 8 bytes of buffer from source image file
    // step 3-> encode_byte_to_lsd(data_uffer[0],buffer)
    // step 4 -> store the buffer into stego image file 
            // repeat the upto size of secret file 
            // return e_sucess

Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
   char arr[512]; // Buffer for remaining image
   uint var;
    // Continue copying until end of file
    while ((var = fread(arr, 1, sizeof(arr), fptr_src)) > 0)
    {
        fwrite(arr, 1, var, fptr_dest);  // Write remaining bytes
    }
    return e_success;
}
     //run a loop upto reachim=ng the end of file 
      // read uffer from source image file
      // store into stego image file
          // return e_sucess


Status encode_byte_to_lsb(char data, char *image_buffer)
{
     //first we clear the lsb bits 
    for(int i=0;i<8;i++) // For each bit
    {
        char bit = (data >> (7 - i)) & 1;  // Extract bit from data
        image_buffer[i]=(image_buffer[i] & 0xFE) | bit; // Set LSB
    }
    return e_success;
   // logic to encode the data.
}

Status encode_size_to_lsb(int size, char *imageBuffer)
{
    for (int i = 0; i < 32; i++)
    {
        // Clear LSB of image byte
        imageBuffer[i] &= 0xFE;

        // Get bit from size (MSB to LSB)
        imageBuffer[i] |= (size >> (31 - i)) & 1;
    }

    return e_success;
}

Status do_encoding(EncodeInfo *encInfo)
{
    if(open_files(encInfo)==e_success) // Open all required files
  {
    printf("Open file is successful\n");
  }
  else
  {
    printf("Open File is failure\n");
    return e_failure;
  }
   if(check_capacity(encInfo)==e_success) // Check if image can hold secret data
   {
    printf("capicity in range\n");
    //return e_success;
   }
   else 
   {
    return e_failure;
   }
   if(copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_success) // copy header
   {
    
       printf("Copying the header file to destination image\n");
      // return e_success;
   }
   else 
   {
    printf("\nCopying not successful\n");
    return e_failure;
   }
    if(encode_magic_string( MAGIC_STRING, encInfo)==e_success)
    {
        printf("Magic string is succesfully matched\n");
    }
    else 
    {
        printf("Magic string is not matched\n");
        return e_failure;
    }
    if(encode_secret_file_extn(".txt",encInfo)==e_success)
    {
        printf("Encoding secret flile extension\n");
    }
    else
    {
        printf("Encoding secret file extension failed");
        return e_failure;
    }
    if( encode_secret_file_size(encInfo->size_secret_file,encInfo)==e_success)
    {
        printf("Encoding secret file size\n");
    }
    else
    {
            printf("Encoding secret file size not done");
            return e_failure;
    }
    if(encode_secret_file_data(encInfo)==e_success)
    {
        printf("Started encoding secret file data\n");

    }
    else 
    {
        printf("encoding secret fiel data failed ");
        return e_failure;
    }
    if(copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image)==e_success) 
    {
        printf("Copying image files\n");
    }
    else
    {
        printf("Copying image not done");
    }
    
return e_success;
}
    //step1 -> call open file(encInfo)
            // e_failure -> print error msg and return e_failure
            // e_success -> print success msg goto next step

    // step2 -> call check_capacity(encInfo)
            // e_failure -> print error msg and return e_failure
            // e_success -> print success msg goto next step

    // step-3; call copy_bmp_header(EncInfo)
    // print sucess message and go to next step

    // step 4-> call encode_magic_string(MAGIC_STRING,encInfo)
              // print sucess message and got to next step

    // step5 -> encode_secret_file_extn_size(strlen(encInfo ->extn_secret_file),encInfo)
                // print sucess msg and goto next step

    // step6 -> call encode_secret_file_extn(encInfo -> extn_secret_file,encInfo)
            // print sucess msg and goto next step
     
    // step 7 -> call ebcode_secret_file_size(encInfo -> size_secret_file,encInfo)
              // print sucess msg and goto next step

    // step8 -> call ebcode_secret_file_data(enInfo)
         // print sucess msg and goto next step
    // step9 -> copy_remaining_img_data(pass two file pointers)
               // print sucess msg and goto next step


