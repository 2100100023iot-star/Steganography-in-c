#include <stdio.h>
#include "encode.h"
#include "types.h"
#include <string.h>

OperationType check_operation_type(char *);

int main(int argc, char *argv[])
{

    int a=check_operation_type(argv[1]);
    if(a==e_encode)
    {
        EncodeInfo encInfo;
        int res=read_and_validate_encode_args(argv,&encInfo);
        {
            if(res==e_success)
            {
                printf("Encoding Sucessifully");
            }
            else{
                printf("Encoding Failure");
            }
        }
    }
    //step1 -> check_operation_type(argv[1])
    //step2 -> check the return value == e_encode
            //declare structure variable EncodeInfo encInfo
            //--> read_and_validate_encode_args(pass command line arg, &encInfo) == e_success or e_failure
            // e_failure -> print error msg and stop the program
            // e_success -> next step.
        // call do_encoding(&encInfo);
            //e_failure -> print error msg and stop the program
            // e_sucess -> print sucess msg and stop the program

    //step3 -> return value == e_decode
            // --
    //step3 -> return value == e_unsupported
            // --> print invalid arg
            // -e -> encode
            // -d  -> decode
}

OperationType check_operation_type(char *symbol)
{
    //step1 -> check it is -e or 
    if(strcmp(symbol, "-e")==0)
    {
        printf("Selected Encoding");
        return e_encode;
    }
    // if it is -e return e_encode
    else if(strcmp(symbol,"-d")==0)
    {
        printf("Selected Decoding");
        return e_decode;
    }
    // else if it is -d rteun e_decode
    else
    {
        printf("Enter valid Operation: ");
        return e_unsupported;
    }
    // else return e_unsuported
}
