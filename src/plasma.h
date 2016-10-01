#ifndef PLASMA_H
#define PLASMA_H

#include <inttypes.h>
#include <stdio.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

#include "common.h"

typedef struct {
  int64_t data_size;
  int64_t metadata_size;
  int64_t create_time;
  int64_t construct_duration;
} plasma_object_info;

enum plasma_message_type {
  /** Create a new object. */
  PLASMA_CREATE = 128,
  /** Get an object. */
  PLASMA_GET,
  /** Check if an object is present. */
  PLASMA_CONTAINS,
  /** Seal an object. */
  PLASMA_SEAL,
  /** Delete an object. */
  PLASMA_DELETE,
  /** Request transfer to another store. */
  PLASMA_TRANSFER,
  /** Header for sending data. */
  PLASMA_DATA,
};

typedef struct {
  /** The ID of the object that the request is about. */
  object_id object_id;
  /** The size of the object's data. */
  int64_t data_size;
  /** The size of the object's metadata. */
  int64_t metadata_size;
  /** In a transfer request, this is the IP address of the Plasma Manager to
   *  transfer the object to. */
  uint8_t addr[4];
  /** In a transfer request, this is the port of the Plasma Manager to transfer
   *  the object to. */
  int port;
} plasma_request;

typedef struct {
  /** The offset in bytes in the memory mapped file of the data. */
  ptrdiff_t data_offset;
  /** The offset in bytes in the memory mapped file of the metadata. */
  ptrdiff_t metadata_offset;
  /** The size in bytes of the memory mapped file. */
  int64_t map_size;
  /** The size in bytesof the data. */
  int64_t data_size;
  /** The size in bytes of the metadata. */
  int64_t metadata_size;
  /** This is used only to respond to requests of type PLASMA_CONTAINS. It is 1
   *  if the object is present and 0 otherwise. Used for plasma_contains. */
  int has_object;
  /** The file descriptor of the memory mapped file in the store. */
  int store_fd_val;
} plasma_reply;

#endif
