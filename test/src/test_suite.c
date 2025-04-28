#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "test_suite.h"
#include <stdarg.h>

#ifdef DSLAB
#include "lsim.h"
#include "lsimLogger.h"
#endif

// Wait user key
void waitKey(tAppArguments parameters) {
    if (parameters.wait_on_exit) {
        printf("Press key to continue...");
        getchar();
    }
}

// Display help text
void help(const char* app_name) {
    printf("%s [--help] [--in <input_test_file>] [--out <output_file>] [--progress <progress_file>] [--readme <readme_file>]\n", app_name);
    printf("\t[%s] %s\n", "--help", "Show this help information.");
    printf("\t[%s] %s\n", "--no-wait", "Do not wait user key press on exit.");
    printf("\t[%s] %s\n", "--in", "Provide file with input test data in CSV format.");
    printf("\t[%s] %s\n", "--out", "Write the result of tests in a file in JSON format.");
    printf("\t[%s] %s\n", "--progress", "Write test progress in an output file.");
    printf("\t[%s] %s\n", "--readme", "Path to README.txt file.");
    printf("\t[%s] %s\n", "--hide-results", "Do not show tests results on the standard output.");
}

// Parse application arguments
bool parseArguments(tAppArguments* arguments, int argc, char** argv) {
    int i;

    // Initialize the arguments
    arguments->app_name = NULL;
    arguments->out_file = NULL;
    arguments->in_file = NULL;
    arguments->readme_file = NULL;
    arguments->progress_file = NULL;
    arguments->wait_on_exit = true;
    arguments->print_results_on_stdout = true;

    // Parse input arguments
    arguments->app_name = argv[0];
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            help(argv[0]);
        }
        else if (strcmp(argv[i], "--no-wait") == 0) {
            arguments->wait_on_exit = false;
        }
        else if (strcmp(argv[i], "--in") == 0) {
            if (argc < i + 1) {
                help(argv[0]);
                return false;
            }
            arguments->in_file = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "--out") == 0) {
            if (argc < i + 1) {
                help(argv[0]);
                return false;
            }
            arguments->out_file = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "--progress") == 0) {
            if (argc < i + 1) {
                help(argv[0]);
                return false;
            }
            arguments->progress_file = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "--readme") == 0) {
            if (argc < i + 1) {
                help(argv[0]);
                return false;
            }
            arguments->readme_file = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "--hide-results") == 0) {
            arguments->print_results_on_stdout = false;
        }
    }

    return true;
}

// Initialize a test Suite
void testSuite_init(tTestSuite* object) {
    assert(object != NULL);
    object->learner.email = NULL;
    object->learner.username = NULL;
    object->learner.first_name = NULL;
    object->learner.last_name = NULL;
    object->learner.environment = NULL;
    object->learner.file_exists = false;
    object->numSections = 0;
    object->sections = NULL;
    object->progress_file = NULL;
}

// Set output progress file
void testSuite_set_progress_file(tTestSuite* object, char* progress_file) {
    object->progress_file = progress_file;
}

// Load learner data
bool testSuite_load_learner(tTestSuite* object, const char* file) {
    char buffer[BUFFER_SIZE];
    FILE* fin = NULL;
    int state;
    char* pos;

    assert(object != NULL);
    assert(file != NULL);

    fin = fopen(file, "r");
    if (fin == NULL) {
        object->learner.email = NULL;
        object->learner.username = NULL;
        object->learner.first_name = NULL;
        object->learner.last_name = NULL;
        object->learner.environment = NULL;
        object->learner.file_exists = false;
        return false;
    }

    state = 0;
    while (fgets(buffer, BUFFER_SIZE, fin)) {
        if (state == 0) {
            // Read email
            object->learner.email = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
            memset(object->learner.email, 0, (strlen(buffer) + 1) * sizeof(char));
            strncpy(object->learner.email, buffer, strcspn(buffer, "\n\r"));
        }
        else if (state == 1) {
            // Read Surname, Name
            pos = strchr(buffer, ',');
            if (pos > 0) {
                // Copy the surnames
                object->learner.last_name = (char*)malloc((pos - buffer + 1) * sizeof(char));
                memset(object->learner.last_name, 0, (pos - buffer + 1) * sizeof(char));
                strncpy(object->learner.last_name, buffer, strcspn(buffer, ","));
                // Skip the comma
                pos++;
                // Skip initial blank spaces
                while (pos < &buffer[BUFFER_SIZE] && *pos == ' ') pos++;
                // Copy the first name
                object->learner.first_name = (char*)malloc((strlen(pos) + 1) * sizeof(char));
                memset(object->learner.first_name, 0, (strlen(pos) + 1) * sizeof(char));
                strncpy(object->learner.first_name, pos, strcspn(pos, "\n\r"));
            }
            else {
                object->learner.first_name = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
                memset(object->learner.first_name, 0, (strlen(buffer) + 1) * sizeof(char));
                strncpy(object->learner.first_name, buffer, strlen(buffer));
            }
        }
        else if (state == 2) {
            object->learner.environment = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
            strcpy(object->learner.environment, buffer);
        }
        else if (state > 2) {
            object->learner.environment = (char*)realloc(object->learner.environment, (strlen(object->learner.environment) + strlen(buffer) + 1) * sizeof(char));
            strcat(object->learner.environment, buffer);
        }
        state++;
    }

    object->learner.file_exists = true;

    fclose(fin);
    return true;
}

// Remove a test Suite
void testSuite_free(tTestSuite* object) {
    int i;
    assert(object != NULL);
    // Free learner data
    if (object->learner.email != NULL) {
        free(object->learner.email);
        object->learner.email = NULL;
    }
    if (object->learner.username != NULL) {
        free(object->learner.username);
        object->learner.username = NULL;
    }
    if (object->learner.first_name != NULL) {
        free(object->learner.first_name);
        object->learner.first_name = NULL;
    }
    if (object->learner.last_name != NULL) {
        free(object->learner.last_name);
        object->learner.last_name = NULL;
    }
    if (object->learner.environment != NULL) {
        free(object->learner.environment);
        object->learner.environment = NULL;
    }
    object->learner.file_exists = false;
    // Free test data
    if (object->sections != NULL) {
        for (i = 0; i < object->numSections; i++) {
            testSection_free(&(object->sections[i]));
        }
        free(object->sections);
    }
    object->progress_file = NULL;
}

// Add a test Section
void testSuite_addSection(tTestSuite* object, const char* code, const char* title) {
    assert(object != NULL);
    object->numSections++;
    if (object->sections == NULL) {
        object->sections = (tTestSection*)malloc(object->numSections * sizeof(tTestSection));
    }
    else {
        object->sections = (tTestSection*)realloc(object->sections, object->numSections * sizeof(tTestSection));
    }
    assert(object->sections != NULL);
    testSection_init(&(object->sections[object->numSections - 1]), code, title);
    if (object->progress_file != NULL) {
        object->sections[object->numSections - 1].progress_file = object->progress_file;
    }
}

// Add a test
void testSuite_addTest(tTestSuite* object, const char* section_code, const char* code, const char* description, tTestResult result) {
    tTestSection* section = NULL;
    assert(object != NULL);
    assert(section_code != NULL);
    assert(code != NULL);
    assert(description != NULL);

    section = testSuite_getSection(object, section_code);
    assert(section != NULL);

    testSection_addTest(section, code, description, result);
}

// Update a test result
void testSuite_updateTest(tTestSuite* object, const char* section_code, const char* test_code, tTestResult result) {
    tTestSection* section = NULL;

    assert(object != NULL);
    assert(section_code != NULL);
    assert(test_code != NULL);

    section = testSuite_getSection(object, section_code);
    assert(section != NULL);

    testSection_updateTest(section, test_code, result);
}

// Get a pointer to a section
tTestSection* testSuite_getSection(tTestSuite* object, const char* section_code) {
    int i;

    assert(object != NULL);
    assert(section_code != NULL);
    for (i = 0; i < object->numSections; i++) {
        if (strcmp(object->sections[i].code, section_code) == 0) {
            return &(object->sections[i]);
        }
    }
    return NULL;
}

// Get a pointer to a test
tTest* testSuite_getTest(tTestSuite* object, const char* section_code, const char* test_code) {
    tTestSection* section = NULL;

    assert(object != NULL);
    assert(section_code != NULL);
    assert(test_code != NULL);
    section = testSuite_getSection(object, section_code);
    assert(section != NULL);

    if (section != NULL) {
        return testSection_getTest(section, test_code);
    }

    return NULL;
}

// Get test statistics
void testSuite_getStats(tTestSuite* object, int* total, int* passed, int* failed, int* not_implemented) {
    int i;
    int s_total, s_passed, s_failed, s_not_implemented;
    assert(object != NULL);
    assert(total != NULL);
    assert(passed != NULL);
    assert(failed != NULL);
    assert(not_implemented != NULL);

    *total = 0;
    *passed = 0;
    *failed = 0;
    *not_implemented = 0;
    for (i = 0; i < object->numSections; i++) {
        testSection_getStats(&(object->sections[i]), &s_total, &s_passed, &s_failed, &s_not_implemented);
        *total += s_total;
        *passed += s_passed;
        *failed += s_failed;
        *not_implemented += s_not_implemented;
    }
}

// Print test suite
void testSuite_print(tTestSuite* object, tAppArguments parameters) {
    int i;
    int total, passed, failed, not_implemented;
    tBuffer* buffer = NULL;

    assert(object != NULL);

    // Reserve memory and open buffer
    buffer = (tBuffer*)malloc(sizeof(tBuffer));
    assert(buffer != NULL);
    open_buffer(buffer);

    // Print the header
    if (object->learner.file_exists) {
        bprintf(buffer, "\n=========================================================================\n");
        if (object->learner.first_name != NULL && object->learner.last_name != NULL) {
            bprintf(buffer, "\t Name: %s %s\n", object->learner.first_name, object->learner.last_name);
        }
        else {
            bprintf(buffer, "\t Name: <not provided>\n");
        }
        if (object->learner.email != NULL) {
            bprintf(buffer, "\t Email: %s\n", object->learner.email);
        }
        else {
            bprintf(buffer, "\t Email: <not provided>\n");
        }
        bprintf(buffer, "=========================================================================\n");
    }
    else {
        bprintf(buffer, "\n=========================================================================\n");
        bprintf(buffer, "\t NO LEARNER DATA\n");
        bprintf(buffer, "=========================================================================\n");
    }

    testSuite_getStats(object, &total, &passed, &failed, &not_implemented);

    bprintf(buffer, "\n=========================================================================\n");
    bprintf(buffer, "\t TEST RESULTS\n");
    bprintf(buffer, "=========================================================================\n");
    if (object->numSections == 0) {
        bprintf(buffer, "NO TEST DEFINED\n");
    }
    else {
        for (i = 0; i < object->numSections; i++) {
            testSection_print(&(object->sections[i]), buffer);
        }
    }
    bprintf(buffer, "\n=========================================================================\n");
    if (total > 0) {
        bprintf(buffer, "Total Tests: %d\n", total);
        bprintf(buffer, "Passed Tests: %d ( %2.02f %% )\n", passed, ((float)passed / (float)total) * 100.0);
        bprintf(buffer, "Failed Tests: %d ( %2.02f %% )\n", failed, ((float)failed / (float)total) * 100.0);
        //fprintf(buffer, "Not Implemented: %d ( %2.02f %% )\n", not_implemented, ((float)not_implemented/(float)total)*100.0);
        bprintf(buffer, "=========================================================================\n");
    }

    if (parameters.print_results_on_stdout)
        printf("%s", buffer->data);

#ifdef DSLAB
    float percent = 0.0;
    char summary[100];
    if (total > 0)
        percent = (float)passed / total * 100.0;
    sprintf(summary, "\tPassed %d of %d [%0.2f%%]\n", passed, total, percent);
    bool is_Ok = ((float)passed / (float)total) == 1.0;
    LSim_sendCorreccio(is_Ok, (char)percent, summary, buffer->data);
#endif

    // Close buffer and free memory
    close_buffer(buffer);
    free(buffer);
}

void write_nullable_field(FILE* fout, const char* value) {
    if (value == NULL) {
        fprintf(fout, "null");
    }
    else {
        fprintf(fout, "\"%s\"", value);
    }
}

// Export a test suite
void testSuite_export(tTestSuite* object, const char* output) {
    int i;
    int total, passed, failed, not_implemented;
    FILE* fout = NULL;

    assert(object != NULL);
    assert(output != NULL);

    fout = fopen(output, "w");
    assert(fout != NULL);

    fprintf(fout, "{ \"learner\": {\"first_name\": ");
    write_nullable_field(fout, object->learner.first_name);
    fprintf(fout, ", \"last_name\": ");
    write_nullable_field(fout, object->learner.last_name);
    fprintf(fout, ", \"email\": ");
    write_nullable_field(fout, object->learner.email);
    fprintf(fout, ", \"username\": ");
    write_nullable_field(fout, object->learner.username);
    fprintf(fout, ", \"environment\": ");
    write_nullable_field(fout, object->learner.environment);
    fprintf(fout, "}, ");

    testSuite_getStats(object, &total, &passed, &failed, &not_implemented);

    fprintf(fout, " \"total\": %d, \"passed\": %d, \"failed\": %d, \"not_implemented\": %d, \"sections\": [", total, passed, failed, not_implemented);

    for (i = 0; i < object->numSections; i++) {
        if (i > 0) {
            fprintf(fout, ", ");
        }
        testSection_export(&(object->sections[i]), fout);
    }

    fprintf(fout, "]}");
    fclose(fout);
}


// Initialize a test Section
void testSection_init(tTestSection* object, const char* code, const char* title) {
    assert(object != NULL);
    object->code = (char*)malloc((strlen(code) + 1) * sizeof(char));
    assert(object->code != NULL);
    strcpy(object->code, code);
    object->title = (char*)malloc((strlen(title) + 1) * sizeof(char));
    assert(object->title != NULL);
    strcpy(object->title, title);
    object->numTests = 0;
    object->tests = NULL;
    object->progress_file = NULL;
}

// Remove a test Section
void testSection_free(tTestSection* object) {
    int i;
    assert(object != NULL);
    assert(object->code != NULL);

    free(object->code);
    free(object->title);
    if (object->tests != NULL) {
        for (i = 0; i < object->numTests; i++) {
            test_free(&(object->tests[i]));
        }
        free(object->tests);
    }

}

// Add a test to the Section
void testSection_addTest(tTestSection* object, const char* code, const char* description, tTestResult result) {
    assert(object != NULL);
    object->numTests++;
    if (object->tests == NULL) {
        object->tests = (tTest*)malloc(object->numTests * sizeof(tTest));
    }
    else {
        object->tests = (tTest*)realloc(object->tests, object->numTests * sizeof(tTestSection));
    }
    assert(object->tests != NULL);
    test_init(&(object->tests[object->numTests - 1]), code, description, result);
}

// Update a test result
void testSection_updateTest(tTestSection* object, const char* test_code, tTestResult result) {
    tTest* test = NULL;

    assert(object != NULL);
    test = testSection_getTest(object, test_code);

    assert(test != NULL);
    test_updateTest(test, result);
}

// Get a pointer to a test
tTest* testSection_getTest(tTestSection* object, const char* test_code) {
    int i;
    assert(object != NULL);
    assert(test_code != NULL);
    for (i = 0; i < object->numTests; i++) {
        if (strcmp(object->tests[i].code, test_code) == 0) {
            return &(object->tests[i]);
        }
    }
    return NULL;
}

// Get test statistics
void testSection_getStats(tTestSection* object, int* total, int* passed, int* failed, int* not_implemented) {
    int i;
    assert(object != NULL);
    assert(total != NULL);
    assert(passed != NULL);
    assert(failed != NULL);
    assert(not_implemented != NULL);

    *total = object->numTests;
    *passed = 0;
    *failed = 0;
    *not_implemented = 0;
    for (i = 0; i < object->numTests; i++) {
        if (object->tests[i].result == TEST_PASSED) {
            (*passed)++;
        }
        else
            if (object->tests[i].result == TEST_FAILED) {
                (*failed)++;
            }
            else
                if (object->tests[i].result == TEST_FAILED) {
                    (*not_implemented)++;
                }
    }
}

// Print test section
void testSection_print(tTestSection* object, tBuffer* buffer) {
    int i;
    int total, passed, failed, not_implemented;

    assert(object != NULL);
    assert(buffer != NULL);

    testSection_getStats(object, &total, &passed, &failed, &not_implemented);

    bprintf(buffer, "\n\t=================================================================\n");
    bprintf(buffer, "\t%s\n", object->title);
    bprintf(buffer, "\t=================================================================\n");
    if (object->numTests == 0) {
        bprintf(buffer, "\tNO TEST DEFINED\n");
    }
    else {
        for (i = 0; i < object->numTests; i++) {
            test_print(&(object->tests[i]), buffer);
        }
    }
    bprintf(buffer, "\t=================================================================\n");
    if (total > 0) {
        bprintf(buffer, "\tTotal Tests: %d\n", total);
        bprintf(buffer, "\tPassed Tests: %d ( %2.2f %% )\n", passed, ((float)passed / (float)total) * 100.0);
        bprintf(buffer, "\tFailed Tests: %d ( %2.2f %%)\n", failed, ((float)failed / (float)total) * 100.0);
        //bprintf(buffer, "\tNot Implemented: %d ( %2.2f %%)\n", not_implemented, ((float)not_implemented/(float)total)*100.0);
        bprintf(buffer, "\t=================================================================\n");
    }
}

// Export a test section
void testSection_export(tTestSection* object, FILE* fout) {
    int i;
    int total, passed, failed, not_implemented;

    assert(object != NULL);
    assert(fout != NULL);

    testSection_getStats(object, &total, &passed, &failed, &not_implemented);

    fprintf(fout, "{ \"code\": \"%s\", \"title\": \"%s\", \"total\": %d, \"passed\": %d, \"failed\": %d, \"not_implemented\": %d, \"tests\": [", object->code, object->title, total, passed, failed, not_implemented);

    for (i = 0; i < object->numTests; i++) {
        if (i > 0) {
            fprintf(fout, ", ");
        }
        test_export(&(object->tests[i]), fout);
    }

    fprintf(fout, "]}");
}


// Initialize a test
void test_init(tTest* object, const char* code, const char* description, tTestResult result) {
    assert(object != NULL);
    object->code = (char*)malloc((strlen(code) + 1) * sizeof(char));
    assert(object->code != NULL);
    object->description = (char*)malloc((strlen(description) + 1) * sizeof(char));
    assert(object->description != NULL);
    strcpy(object->code, code);
    strcpy(object->description, description);
    object->result = TEST_RUNNING;
}

// Remove a test
void test_free(tTest* object) {
    assert(object != NULL);
    assert(object->code != NULL);
    assert(object->description != NULL);
    free(object->code);
    free(object->description);
}

// Update a test result
void test_updateTest(tTest* object, tTestResult result) {
    assert(object != NULL);
    object->result = result;
}

// Print test
void test_print(tTest* object, tBuffer* buffer) {
    assert(object != NULL);
    bprintf(buffer, "\t\t");
    if (object->result == TEST_RUNNING) {
        bprintf(buffer, "[%s]", "RUNNING");
    }
    else
        if (object->result == TEST_NOT_IMPLEMENTED) {
            bprintf(buffer, "[%s]", "NOT IMPLEMENTED");
        }
        else
            if (object->result == TEST_PASSED) {
                bprintf(buffer, "[%s]", "OK");
            }
            else
                if (object->result == TEST_FAILED) {
                    bprintf(buffer, "[%s]", "FAIL");
                }
    bprintf(buffer, ":\t [%s] %s\n", object->code, object->description);
}

// Export a test
void test_export(tTest* object, FILE* fout) {
    assert(object != NULL);
    assert(fout != NULL);

    fprintf(fout, "{ \"code\": \"%s\", \"description\": \"%s\", \"result\": ", object->code, object->description);
    if (object->result == TEST_RUNNING) {
        fprintf(fout, "\"%s\"}", "RUNNING");
    }
    else
        if (object->result == TEST_NOT_IMPLEMENTED) {
            fprintf(fout, "\"%s\"}", "NOT IMPLEMENTED");
        }
        else
            if (object->result == TEST_PASSED) {
                fprintf(fout, "\"%s\"}", "OK");
            }
            else
                if (object->result == TEST_FAILED) {
                    fprintf(fout, "\"%s\"}", "FAIL");
                }
}


// Start a test
void start_test(tTestSection* section, const char* code, const char* description) {

    assert(section != NULL);
    assert(code != NULL);
    assert(description != NULL);

    _save_progress(section, code, NULL);
    _print_progress(TEST_RUNNING, code, description);

    testSection_addTest(section, code, description, TEST_RUNNING);
}

// Finish a test
void end_test(tTestSection* section, const char* code, bool passed) {
    tTest* test = NULL;
    assert(section != NULL);
    assert(code != NULL);

    test = testSection_getTest(section, code);
    assert(test != NULL);

    if (passed) {
        _print_progress(TEST_PASSED, test->code, test->description);
        _save_progress(section, test->code, "OK");
        test_updateTest(test, TEST_PASSED);
    }
    else {
        _print_progress(TEST_FAILED, test->code, test->description);
        _save_progress(section, test->code, "FAIL");
        test_updateTest(test, TEST_FAILED);
    }
}

// Set output progress file
void _save_progress(tTestSection* section, const char* test_code, const char* test_result) {
    FILE* f_progress = NULL;
    if (section->progress_file == NULL) {
        return;
    }
    // Open the file
    f_progress = fopen(section->progress_file, "a");
    if (f_progress == NULL) {
        return;
    }

    if (test_result == NULL) {
        fprintf(f_progress, "TEST:START:{\"section_code\": \"%s\", \"test_code\": \"%s\"}\n", section->code, test_code);
    }
    else {
        fprintf(f_progress, "TEST:END:{\"section_code\": \"%s\", \"test_code\": \"%s\", \"result\": \"%s\"}\n", section->code, test_code, test_result);
    }

    // Close the file
    fclose(f_progress);
}

// Output test progress
void _print_progress(tTestResult result, const char* code, const char* description)
{
#if defined(PRINT_TEST_PROGRESS) || defined(DSLAB)
    tBuffer* buffer = NULL;

    // Reserve memory and open buffer
    buffer = (tBuffer*)malloc(sizeof(tBuffer));
    assert(buffer != NULL);
    open_buffer(buffer);

    switch (result) {
    case TEST_RUNNING: bprintf(buffer, "\n[START] ==> Running test [%s] - %s\n", code, description); break;
    case TEST_PASSED: bprintf(buffer, "\n[OK] ==> Finished test [%s] - %s\n", code, description); break;
    case TEST_FAILED: bprintf(buffer, "\n[FAIL] ==> Finished test [%s] - %s\n", code, description); break;
    case TEST_NOT_IMPLEMENTED: bprintf(buffer, "\n[FAIL] ==> Not implemented test [%s] - %s\n", code, description); break;
    }

#ifdef PRINT_TEST_PROGRESS
    printf("%s", buffer->data);
#endif
#ifdef DSLAB
    LSimLogger_log("INFO", buffer->data);
#endif

    // Close buffer and free memory
    close_buffer(buffer);
    free(buffer);
#endif
}

// Open and initializes a buffer
void open_buffer(tBuffer* buffer)
{
    assert(buffer != NULL);

    // Reserve memory for 1 char to store NULL at last position
    buffer->data = (char*)malloc(sizeof(char));
    assert(buffer->data != NULL);

    // Initialize values
    memset(buffer->data, 0, sizeof(char));
    buffer->count = 0;
}

// Close a buffer and free its internal string
void close_buffer(tBuffer* buffer) {
    free(buffer->data);
    buffer->data = NULL;
    buffer->count = 0;
}

// Clear a buffer, reset to empty string
void clear_buffer(tBuffer* buffer)
{
    // Reserve memory for 1 char to store NULL at last position
    buffer->data = (char*)realloc(buffer->data, sizeof(char));
    assert(buffer->data != NULL);

    // Initialize values
    memset(buffer->data, 0, sizeof(char));
    buffer->count = 0;
}

// Add a formated string to a buffer. Analog to functions like sprintf or fprintf
void bprintf(tBuffer* buffer, const char* pString, ...) {
    const int MAX_LENGTH = 2048;
    int size; //, length;
    va_list args;
    char tmp[MAX_LENGTH];

    // Read parameters
    va_start(args, pString);

    // Determine the size of new string using temporary string
    size = vsnprintf(tmp, MAX_LENGTH, pString, args);

    // Allocate memory for buffer. Add extra space for NULL termination
    buffer->count += size;
    buffer->data = (char*)realloc(buffer->data, (buffer->count + 1) * sizeof(char));

    // Update buffer
    strncat(buffer->data, tmp, size);

    // Close parameter's read
    va_end(args);
}
