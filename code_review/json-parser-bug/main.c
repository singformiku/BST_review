#include <stdio.h>
#include <sys/stat.h>
#include "string.h"
#include "json.h"

static void process_value(json_value* value, int depth);
static void process_array(json_value* value, int depth)
{
    int length, x;
    if (value == NULL) {
        return;
    }
    length = value->u.array.length;
    printf("[array]\n");
    for (x = 0; x < length; x++) {
        process_value(value->u.array.values[x], depth);
    }
}

static void print_depth_shift(int depth)
{
    for (int j = 0; j < depth; j++) {
        printf(" ");
    }
}
static void process_object(json_value* value, int depth)
{
    int length, x;
    if (value == NULL) {
        return;
    }
    length = value->u.object.length;
    for (x = 0; x < length; x++) {
        print_depth_shift(depth);
        printf("\033[1;30mobject[%d]:\033[m %s\n", x, value->u.object.values[x].name);
        process_value(value->u.object.values[x].value, depth+1);
    }
}

static void process_value(json_value* value, int depth)
{
    int j;
    if (value == NULL) {
        return;
    }
    if (value->type != json_object) {
        print_depth_shift(depth);
    }
    if (value->type == json_none) {
        printf("none\n");
    } else if (value->type == json_object) {
        process_object(value, depth+1);
    } else if (value->type == json_array) {
        process_array(value, depth+1);
    } else if (value->type == json_integer) {
        printf("\033[0;35m(integer): %4" PRId64 "\n\033[m", value->u.integer);
    } else if (value->type == json_double) {
        printf("\033[0;35m(doble): %f\n\033[m", value->u.dbl);
    } else if (value->type == json_string) {
        printf("\033[1;33m(string): %s\n\033[m", value->u.string.ptr);
    } else if (value->type == json_boolean) {
        printf("\033[0;35m(bool): %d\n\033[m", value->u.boolean);
    } 
}

int main()
{
    char *file_name = "example.json";
    FILE *fp = fopen(file_name, "rt");
    struct stat file_status;

    stat(file_name, &file_status);
    int file_size = file_status.st_size;

    char *json_str = (char*) malloc(file_status.st_size);
    fread(json_str, file_size, 1, fp);
    fclose(fp);

    json_value *value = json_parse(json_str, strlen(json_str));
    process_value(value, 0);
}