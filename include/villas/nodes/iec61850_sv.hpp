/* Node type: IEC 61850-9-2 (Sampled Values).
 *
 * Author: Steffen Vogel <post@steffenvogel.de>
 * SPDX-FileCopyrightText: 2014-2023 Institute for Automation of Complex Power Systems, RWTH Aachen University
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <libiec61850/sv_publisher.h>
#include <libiec61850/sv_subscriber.h>

#include <villas/list.hpp>
#include <villas/nodes/iec61850.hpp>
#include <villas/pool.hpp>
#include <villas/queue_signalled.h>

namespace villas {
namespace node {

// Forward declarations
class NodeCompat;

struct iec61850_sv {
  char *interface;
  int app_id;
  struct ether_addr dst_address;

  struct {
    bool enabled;
    bool check_dst_address;

    SVSubscriber subscriber;
    SVReceiver receiver;

    struct CQueueSignalled queue;
    struct Pool pool;
    struct List signals; // Mappings of type struct iec61850_type_descriptor

    unsigned total_size;
  } in;

  struct {
    bool enabled;

    SVPublisher publisher;
    SVPublisher_ASDU asdu;

    char *sv_id;

    struct {
      bool enabled;
      int priority;
      int id;
    } vlan;

    int smp_mod;
    int smp_synch;
    int smp_rate;
    int conf_rev;

    struct List signals; // Mappings of type struct iec61850_type_descriptor

    unsigned asdu_length;
  } out;
};

int iec61850_sv_type_stop();

int iec61850_sv_parse(NodeCompat *n, json_t *json);

char *iec61850_sv_print(NodeCompat *n);

int iec61850_sv_start(NodeCompat *n);

int iec61850_sv_stop(NodeCompat *n);

int iec61850_sv_init(NodeCompat *n);

int iec61850_sv_destroy(NodeCompat *n);

int iec61850_sv_read(NodeCompat *n, struct Sample *const smps[], unsigned cnt);

int iec61850_sv_write(NodeCompat *n, struct Sample *const smps[], unsigned cnt);

int iec61850_sv_poll_fds(NodeCompat *n, int fds[]);

} // namespace node
} // namespace villas
