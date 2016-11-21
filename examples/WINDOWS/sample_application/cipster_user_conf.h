/*******************************************************************************
 * Copyright (c) 2009, Rockwell Automation, Inc.
 * All rights reserved.
 *
 ******************************************************************************/
#ifndef CIPSTER_USER_CONF_H_
#define CIPSTER_USER_CONF_H_

/** @file
 * @brief CIPster configuration setup
 *
 * This file contains the general application specific configuration for CIPster.
 *
 * Furthermore you have to specific platform specific network include files.
 * CIPster needs definitions for the following data-types
 * and functions:
 *    - struct sockaddr_in
 *    - AF_INET
 *    - INADDR_ANY
 *    - htons
 *    - ntohl
 *    - inet_addr
 */
#include <windows.h>
typedef unsigned short in_port_t;

//! Identity configuration of the device
#define CIPSTER_DEVICE_VENDOR_ID            1
#define CIPSTER_DEVICE_TYPE                 12
#define CIPSTER_DEVICE_PRODUCT_CODE         65001
#define CIPSTER_DEVICE_MAJOR_REVISION       1
#define CIPSTER_DEVICE_MINOR_REVISION       2
#define CIPSTER_DEVICE_NAME                 "amphibius goodie"


/** @brief Define the number of supported explicit connections.
 *  According to ODVA's PUB 70 this number should be greater than 6.
 */
#define CIPSTER_CIP_NUM_EXPLICIT_CONNS 6

/** @brief Define the number of supported exclusive owner connections.
 *  Each of these connections has to be configured with the function
 *  void configureExclusiveOwnerConnectionPoint(unsigned pa_unConnNum, unsigned pa_unOutputAssembly, unsigned pa_unInputAssembly, unsigned pa_unConfigAssembly)
 *
 */
#define CIPSTER_CIP_NUM_EXLUSIVE_OWNER_CONNS 5

/** @brief Define the number of supported input only connections.
 *  Each of these connections has to be configured with the function
 *  void configureInputOnlyConnectionPoint(unsigned pa_unConnNum, unsigned pa_unOutputAssembly, unsigned pa_unInputAssembly, unsigned pa_unConfigAssembly)
 *
 */
#define CIPSTER_CIP_NUM_INPUT_ONLY_CONNS 5

/** @brief Define the number of supported input only connections per connection path
 */
#define CIPSTER_CIP_NUM_INPUT_ONLY_CONNS_PER_CON_PATH 3

/** @brief Define the number of supported listen only connections.
 *  Each of these connections has to be configured with the function
 *  void configureListenOnlyConnectionPoint(unsigned pa_unConnNum, unsigned pa_unOutputAssembly, unsigned pa_unInputAssembly, unsigned pa_unConfigAssembly)
 *
 */
#define CIPSTER_CIP_NUM_LISTEN_ONLY_CONNS 5

/** @brief Define the number of supported Listen only connections per connection path
 */
#define CIPSTER_CIP_NUM_LISTEN_ONLY_CONNS_PER_CON_PATH   3

/**
 *  The number of bytes used for the buffer that will be used for generating any
 *  reply data of messages. There are two uses in CIPster:
 *    1. Explicit messages will use this buffer to store the data generated by the request
 *    2. I/O Connections will use this buffer for the produced data
 */
#define CIPSTER_MESSAGE_DATA_REPLY_BUFFER       1000

/**
 * The number of bytes used for the Ethernet message buffer.
 *
 * This buffer size will be used for any received message.
 */
#define CIPSTER_ETHERNET_BUFFER_SIZE            1200


/** @brief Number of sessions that can be handled at the same time
 */
#define CIPSTER_NUMBER_OF_SUPPORTED_SESSIONS 20

 /** @brief  The time in usecs of the timer used in this implementations
 */
static const unsigned kOpenerTimerTickInMicroSeconds = 10000;

/** @brief Define if RUN IDLE data is sent with consumed data
*/
static const int kOpenerConsumedDataHasRunIdleHeader = 1;

/** @brief Define if RUN IDLE data is to be sent with produced data
*
* Per default we don't send run idle headers with produced data
*/
static const int kOpenerProducedDataHasRunIdleHeader = 0;

#ifdef CIPSTER_WITH_TRACES
// If we have tracing enabled provide print tracing macro
#include <stdio.h>

#define LOG_TRACE(...)  fprintf(stderr,__VA_ARGS__)

//#define PRINT_TRACE(args...)  fprintf(stderr,args);

#endif


#ifndef NDEBUG

/** @brief A specialized assertion command that will log the assertion and block
 *  further execution in an while(1) loop.
 */
#define CIPSTER_ASSERT(assertion) \
    do { \
      if(!(assertion)) { \
        LOG_TRACE("Assertion \"%s\" failed: file \"%s\", line %d\n", #assertion, __FILE__, __LINE__); \
        while(1){;} \
      } \
    } while(0)

// else use standard assert()
//#include <assert.h>
//#include <stdio.h>
//#define CIPSTER_ASSERT(assertion) assert(assertion)

#else

// for release builds execute the assertion, but don't test it
#define CIPSTER_ASSERT(assertion) (assertion)

/* the above may result in "statement with no effect" warnings.
 *  If you do not use assert()s to run functions, the an empty
 *  macro can be used as below
 */
//#define CIPSTER_ASSERT(assertion)
// else if you still want assertions to stop execution but without tracing, use the following
//#define CIPSTER_ASSERT(assertion) do { if(!(assertion)) { while(1){;} } } while (0)
// else use standard assert()
//#include <assert.h>
//#include <stdio.h>
//#define CIPSTER_ASSERT(assertion) assert(assertion)

#endif


#endif //CIPSTER_USER_CONF_H_