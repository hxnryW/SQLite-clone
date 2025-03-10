#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdint.h>

// user defined types   
#define COLUMN_USERNAME_SIZE 32
#define COLMUN_EMAIL_SIZE 225
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNMAE_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;





typedef struct 
{
    char* buffer;
    size_t buffer_length;       
    ssize_t input_length;
}InputBuffer;

typedef enum{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
}MetaCommadnresult;

typedef enum {PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT}PrepareResult;

typedef enum {STATEMENT_INSERT, STATEMENT_SELECT}StatementType;

typedef struct 
{
    StatementType type;
    Row row_to_insert;
} Statement;

typedef struct
{
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLMUN_EMAIL_SIZE];
}Row;




// front-end functions

InputBuffer* new_input_buffer(){
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    
    return input_buffer;
}

void print_prompt() {printf("db > ");}

ssize_t getline(char **lineptr, size_t *n , FILE *stream);

void read_input(InputBuffer* input_buffer){
    ssize_t bytes_read = 
        getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0){
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    input_buffer->input_length = bytes_read -1;
    input_buffer->buffer[bytes_read - 1] = 0;    
}


void close_input_buffer(InputBuffer* input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}

MetaCommadnresult do_meta_command(InputBuffer* input_buffer)
{
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}


// SQL Compiler

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
    if (strncmp(input_buffer->buffer, "insert", 6) == 0)
    {
        Statement->type = STATEMENT_INSERT;
        int args_assigned =sscanf(
            input_buffer->buffer, "insert %d %s %s", $(statement->row_to_insert.id),
            statement->row_to_insert.username, statement->row_to_insert.email);
        if (args_assigned < 3){
            return PREPARE_SYNTAX_ERROR;
        }
    }
        
        return PREPARE_SUCCESS;
}

    // updating the insert function 
    


    if (strcmp(input_buffer->buffer, "select") == 0)
    {
        Statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
    

}

void execute_statement(Statement* Statement)
{
    switch (Statement->type)
    {
    case (STATEMENT_INSERT):
        printf("insert?!");
        break;
    case (STATEMENT_SELECT):
        printf("select?!");
    }
}





int main(int argc, char* argv[])
{
    InputBuffer* input_buffer = new_input_buffer();
    while (true)
    {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0){
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS); 
        }else {
            printf("Unrecognized Command '%s' \n", input_buffer->buffer);
        }

        if (input_buffer->buffer[0] == "."){
            switch (do_meta_command(input_buffer))
            {
            case (META_COMMAND_SUCCESS):
                continue;
            case (META_COMMAND_UNRECOGNIZED_COMMAND):
                printf("Unrecognized Commmand %s", input_buffer);
                continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
        case (PREPARE_SUCCESS):
            break;
        case (PREPARE_UNRECOGNIZED_STATEMENT):
        printf("Unrecognized keyword at the start of %s", input_buffer->buffer);        
        continue;
        }
        execute_statement(&statement);
        printf("\n\nExecuted!!\n");



    }
}
    
