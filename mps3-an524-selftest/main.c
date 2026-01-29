/*
 * Copyright:
 * ----------------------------------------------------------------
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 *   (C) COPYRIGHT 2016 ARM Limited
 *       ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 * ----------------------------------------------------------------
 * File:     main.c
 * Release:  Version 2.0
 * ----------------------------------------------------------------
 *
 */

/*
 * --------Included Headers--------
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "SMM_MPS3.h"                   // MPS3 common header
#include "GLCD_MPS3.h"

#include "uart_stdout.h"

#include "../apaaci/apaaci.h"
#include "../apleds/apleds.h"
#include "../apclcd/apclcd.h"
#include "../aptsc/aptsc.h"
#include "../apmem/apmem.h"
#include "../aptimer/aptimer.h"
#include "../aplan/aplan.h"
#include "../apusb/apusb.h"
#include "../apqspi/apqspi.h"
#include "../apgpio/apgpio.h"
#include "../aprtc/aprtc.h"
#include "../apuart/apuart.h"


// Local variables

// Return status
typedef enum sts
{
    TEST_S_UNKNOWN,
    TEST_S_NOTRUN,
    TEST_S_SUCCESS,
    TEST_S_FAILURE,
    MAX_STATUS
} Status_t;

char    *status_str[MAX_STATUS];

typedef struct test
{
    apError     (*test)(void);
    int         auto_run;
    char        *name;
}Test_t;

// Table of available tests
static Test_t tests[] =
{
#ifdef FPGA_IMAGE
    {&apAACI_TEST,          0,  "AACI (Audio CODEC)     "},
    {&apCLCD_TEST,          0,  "CLCD                   "},
    {&apTSC_TEST,           0,  "TSCI (TouchScreen)     "},
    {&apLEDS_TEST,          0,  "LEDs/Switches/Buttons  "},
    {&apLANI_TEST,          0,  "Ethernet               "},
    {&apUSB_TEST,           0,  "USB                    "},
    {&apMEM_TEST,           0,  "Memory                 "},
    {&apTIMER_TEST,         0,  "Timer                  "},
    {&apRTC_TEST,           0,  "Real Time Clock        "},
#endif
    {&apQSPI_TEST,          0,  "QSPI                   "},
#ifdef FPGA_IMAGE
    {&apGPIO_TEST,          0,  "Shield GPIO            "},
    {&apGPIO_TEST_SEQUENCE, 0,  "Shield GPIO sequential "},
#endif
};

static Test_t prod_tests[] =
{
    {&apAACI_TEST,          0,  "AACI (Audio)           "},
    {&apCLCD_TEST,          0,  "CLCD                   "},
    {&apTSC_TEST,           0,  "TSCI (TouchScreen)     "},
    {&apLEDS_TEST,          0,  "LEDs/Switches/Buttons  "},
    {&apLANI_TEST,          0,  "Ethernet               "},
    {&apUSB_TEST,           0,  "USB                    "},
    {&apMEM_TEST,           0,  "SRAM Memory            "},
    {&apTIMER_TEST,         0,  "Timer                  "},
    {&apQSPI_TEST,          0,  "QSPI                   "}
};

#define NO_OF_PROD_TESTS (sizeof(prod_tests) / sizeof(prod_tests[0]))
#define NO_OF_TESTS (sizeof(tests) / sizeof(tests[0]))

Status_t test_status[NO_OF_TESTS];
Status_t prod_test_status[NO_OF_PROD_TESTS];


// Initialisation routines
void Test_Init (void)
{
    int i;

    // Init test status and status strings.
    for (i = 0; i < MAX_STATUS; i++)
        status_str[i]  = "Unknown";

    status_str[TEST_S_NOTRUN]  = "Not Run";
    status_str[TEST_S_SUCCESS] = "PASS";
    status_str[TEST_S_FAILURE] = "FAIL";

    for (i = 0; i < NO_OF_TESTS; i++)
        test_status[i] = TEST_S_NOTRUN;
}

// User interface
char *Get_Status (Status_t status)
{
    if (status >= MAX_STATUS)
        status = TEST_S_UNKNOWN;

    return status_str[status];
}

void Print_Results (void)
{
    int i;
    int counts[MAX_STATUS];

    for (i = 0; i < MAX_STATUS; i++)
        counts[i] = 0;

        printf ("Summary of results\n");
        printf ("====================================\n");

    for (i = 0; i < NO_OF_TESTS; i++) {
        printf ("%2d %-20s : %s\n",(i+1), tests[i].name, Get_Status (test_status[i]));

        if (test_status[i] < MAX_STATUS)
            counts[test_status[i]]++;
    }
}

void Print_Production_Results(void)
{
    int i;
    int counts[MAX_STATUS];

    for (i = 0; i < MAX_STATUS; i++)
        counts[i] = 0;

        printf ("Summary of results\n");
        printf ("====================================\n");

    for (i = 0; i < NO_OF_PROD_TESTS; i++) {
        printf ("%2d %-20s : %s\n",(i+1), (prod_tests[i]).name,
                Get_Status (prod_test_status[i]));

        if (prod_test_status[i] < MAX_STATUS)
            counts[prod_test_status[i]]++;
    }
    
    printf("%2d Repeat Production Tests:\n",NO_OF_PROD_TESTS + 1);
    printf("%2d Back to interactive Selftest:\n",NO_OF_PROD_TESTS + 2);
}

#ifdef SEMIHOST
#define LOG_LINE_MAX                       100
char logfilepath[LOG_LINE_MAX];
FILE *logfile;
#endif

void Run_Production_Test(int test)
{
    apError status;

    test--;
    printf ("\nTesting %s\n", (prod_tests[test]).name);

    status = (*prod_tests[test].test)();

    if (status == apERR_NONE)
        prod_test_status[test] = TEST_S_SUCCESS;
    else
        prod_test_status[test] = TEST_S_FAILURE;

    printf_err("%s    : test result : %s\n\n", (prod_tests[test]).name, Get_Status (prod_test_status[test]));
}

void Run_Test (int test)
{
    apError status;

    test--;
    printf ("\nTesting %s\n", tests[test].name);

    status = (*tests[test].test)();

    if (status == apERR_NONE)
        test_status[test] = TEST_S_SUCCESS;
    else
        test_status[test] = TEST_S_FAILURE;

    printf ("%s    : test result : %s\n\n", tests[test].name, Get_Status (test_status[test]));
}


void Run_All_Tests (void)
{
    int i;
#ifdef SEMIHOST
    char *logbasedir = "c:\\arm\\dspl\\logs\\";
    char *logfiledir = "c:\\arm\\dspl\\logs\\mpb\\";
    char *board_info_path = "c:\\arm\\dspl\\Temp\\functest.txt";
    char *syscommand = "IF NOT EXIST c:\\arm\\dspl\\logs\\mpb "
                       "MKDIR c:\\arm\\dspl\\logs\\mpb\n";
    char serial[LOG_LINE_MAX];
    char date[LOG_LINE_MAX];
    char epoch[LOG_LINE_MAX];
    time_t now;
    int epoch_i;
    FILE *board_info;

    memset(serial, 0, LOG_LINE_MAX);
    memset(date, 0, LOG_LINE_MAX);
    memset(epoch, 0, LOG_LINE_MAX);

    if ((board_info = fopen(board_info_path,"r")) == 0)
        printf("Opening %s failed.\n", board_info_path);
    else
    {
        // Read and check validity of test information file on host
        fgets(epoch, LOG_LINE_MAX, board_info);
        fgets(date, LOG_LINE_MAX, board_info);
        fgets(serial, LOG_LINE_MAX, board_info);
    }
    
    printf("Epoch timestamp: %s\n", epoch);
    printf("Date: %s\n", date);
    printf("Serial no: %s\n", serial);

    time(&now);
    // Convert epoch to integer
    epoch_i = atoi(epoch);

    printf("Creating directory with command: %s\n", syscommand);
    system(syscommand);

    // Timestamp not recent, writing to default file.
    if ((int)now - 300 > epoch_i) {
        memcpy(&serial[0], "0000B00000", 10);
        strcpy(&serial[10], ".txt");
        strcpy(logfilepath, logbasedir);
        strcpy(&logfilepath[strlen(logbasedir)], serial);
    } else {
        strcpy(&serial[strlen(serial)-1], ".txt");
        strcpy(logfilepath, logfiledir);
        strcpy(&logfilepath[strlen(logfiledir)], serial);
    }
    printf("Using log file:%s\n", logfilepath);
    if ((int)(logfile = fopen(logfilepath, "a")) == 0)
        printf("Unable to open %s\n", logfilepath);
    else {
        printf("Opened %s\n", logfilepath);
        fprintf(logfile, "\n-- %s", ctime(&now));
        fclose(logfile);
    }
#endif
    // Make sure all of the test harness is plugged in
    printf("\nStarting Production testing...\n");
    printf("Please plug in the Ethernet, SSP, VGA,\n");
    printf("and Audio cables, \n");
    Wait_For_Enter(TRUE);

    for (i = 0; i < NO_OF_PROD_TESTS; i++) {
        Run_Production_Test(i + 1);
    }
    return;
}

int Select_Test (void)
{
    unsigned int choice;
    char         buffer[8];

    if(RunAllTests == TRUE) {
        printf("\nSelect the test you wish to run. (X - Exit)\n");
        do {
            choice = 0;
            printf ("\nChoice: ");
#ifdef FPGA_IMAGE
            GetLine (buffer, sizeof(buffer));
#endif

            if(toupper(buffer[0]) == 'X')
                return 0;

            sscanf (buffer, "%d", &choice);
        }
        while (!choice  || (choice > NO_OF_PROD_TESTS + 2));

    }
    else {
        printf("\nSelect the test you wish to run. (X - Exit)\n");
        do {
            choice = 0;
            printf ("\nChoice: ");
#ifdef FPGA_IMAGE
            GetLine (buffer, sizeof(buffer));
#endif

            if (toupper(buffer[0]) == 'X')
                return 0;

            sscanf (buffer, "%d", &choice);
        }
        while (!choice  || (choice > (NO_OF_TESTS + 1)));


    }
    return choice;
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
__ASM(" .global __ARM_use_no_argv\n");
#endif
int main (void)
{
    int choice;
#ifdef FPGA_IMAGE    
    unsigned int id, fpgaid, apnote, rev, aid;
#endif
    unsigned int core_clock = MPS3_SCC->CFG_ACLK;
    if(core_clock != 0)
        SystemCoreClockUpdate (core_clock);

    // UART init
    UartStdOutInit();

    Test_Init();

    NVIC_ClearAllPendingIRQ();

#ifdef FPGA_IMAGE    
    // Display the program version
    printf ("\n\n\nArm MPS3 FPGA Prototyping Board Test Suite\n");
    printf ("Version 1.0.4" " Build date: " __DATE__ "\n");
    printf ("Copyright (C) ARM Ltd 2016. All rights reserved.\n\n");

    rev = MPS3_SCC->CFG_REG4;
    
    printf("V2M-MPS3 revision %c\n\n", rev + 'A');
    
    fpgaid = MPS3_SCC->SCC_ID;
    aid = MPS3_SCC->SCC_AID;
    
//    if (rev != EXTRACT_BITS(aid, 23, 20))
//        printf("WARNING: Board revision does not match FPGA target revision\n\n");
    
    apnote = EXTRACT_BITS(fpgaid, 15, 4);
    
    printf("Application Note AN%x, Revision %c, FPGA build %d\n", apnote, EXTRACT_BITS(aid, 23, 20) + 'A', EXTRACT_BITS(aid, 31, 24));
    
    // Display CPU ID
    id = SCB->CPUID;
    if(EXTRACT_BITS(id, 15, 8) == 0xD2)
    {
        if(EXTRACT_BITS(id, 7, 4) == 1)
            printf ("\nCPU: Cortex-M33 r%dp%d\n\n",EXTRACT_BITS(id, 23, 20),EXTRACT_BITS(id, 3, 0));
        else if (EXTRACT_BITS(id, 7, 4) == 0)
            printf ("\nCPU: Cortex-M23 r%dp%d\n\n",EXTRACT_BITS(id, 23, 20),EXTRACT_BITS(id, 3, 0));
        else
            printf ("\nCPU: Cortex-M Class");
    }
    else if(EXTRACT_BITS(id, 15, 8) == 0xC6)
        printf ("\nCPU: Cortex-M%d+ r%dp%d\n\n",EXTRACT_BITS(id, 7, 4),EXTRACT_BITS(id, 23, 20),EXTRACT_BITS(id, 3, 0));
    else
        printf ("\nCPU: Cortex-M%d r%dp%d\n\n",EXTRACT_BITS(id, 7, 4),EXTRACT_BITS(id, 23, 20),EXTRACT_BITS(id, 3, 0));

    // CLCD screen register setup
    GLCD_Initialize();

    // Fill CLCD screen
    //GLCD_Clear(DarkGreen);

    // Draw intro screen image
    GLCD_Bitmap (0, 0, 320, 240, (unsigned short *)introData);

    //GLCD_Bitmap (22, 71, 276, 99, (unsigned short *)introData);
#endif
    // Start Test
    RunAllTests = FALSE;
#ifndef FPGA_IMAGE
        choice = 1;
#endif
    while(1)
    {
#ifdef FPGA_IMAGE
        if(RunAllTests) {
            Print_Production_Results();
        } else {
            Print_Results();
        }

        choice = Select_Test();
#endif
        printf("\nchoice is %d\n", choice);

        if (choice == 0)
            break;

        if(!RunAllTests) {
            if (choice == NO_OF_TESTS + 1) {
                RunAllTests = TRUE;
                Run_All_Tests();
            }
            else {
                Run_Test(choice);
            }
        }
        else 
        {  // Production tests
            if(choice == NO_OF_PROD_TESTS + 2) 
            {
                RunAllTests = FALSE;    // Set Interactive mode
                continue;               // Skip running production and next
                                        // Loop will start in interactive mode.
            }
            else if(choice == NO_OF_PROD_TESTS + 1)
            {
                Run_All_Tests();
            }
            else 
            {
                Run_Production_Test(choice);
            }
        }
#ifndef FPGA_IMAGE
        printf("\nchoice 1 is %d\n", choice);
        if(choice == 2)
        {
            printf("\nchoice 2 is %d\n", choice);
            choice = 7;
            printf("\nchoice changed from 2 to 7\n");
        } else {
            if(choice == 7)
            {
                printf("\nchoice 3 is %d\n", choice);
                choice = 2;
                printf("\nchoice changed from 7 to 2\n");
            } else {
                            choice = choice;
                        }
                        
        }
#endif
    }

    printf("\nProgram terminated.\n");

    return TRUE;
}
