/*
 * Copyright (c) 2007, Merit Network, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Merit Network, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY MERIT NETWORK, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL MERIT NETWORK, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _CALEA_H
#define _CALEA_H

#define MAX_CONTENT_ID_LENGTH 128
#define MAX_CASE_ID_LENGTH 128
#define MAX_IAP_SYSTEM_ID_LENGTH 128
#define TS_LENGTH 23  // time in ascii "YYYY-MM-DDThh:mm:ss.sss"

typedef struct {
    char contentID[MAX_CONTENT_ID_LENGTH];
    char ts[TS_LENGTH];
} cmc_header_t; 
#define CmCh cmc_header_t

/* Definition of a Communications Content packet according to the std */
typedef struct {
    CmCh cmch;
    u_char pkt[9000];
} cmc_pkt_t;
#define CmC cmc_pkt_t

/* Definition of a Header Set according to the std */
typedef struct {
    uint32_t streamID;
    uint32_t srcIP;
    uint32_t dstIP;
    uint16_t srcPort;
    uint16_t dstPort;
} header_t;
#define HEADER header_t

typedef struct {
    char caseID[MAX_CASE_ID_LENGTH];
    char IAPSystemID[MAX_IAP_SYSTEM_ID_LENGTH];
    char ts[TS_LENGTH];
    char contentID[MAX_CONTENT_ID_LENGTH];
} cmii_header_t; 
#define CmIIh cmii_header_t

/* the Packet Data Header Report Msg Format from the std */
typedef struct {
    CmIIh cmiih;
    HEADER pkt_header;
} cmii_pkt_t;
#define CmII cmii_pkt_t

int CmCPacketSend ( CmC *packet, int length, int *send_sock, 
                    struct sockaddr_in *send_addr );
int CmIIPacketSend ( CmII *packet, int length, int *send_sock, 
                     struct sockaddr_in *send_addr );

void get_calea_time ( time_t sec, time_t usec, char *buf );

CmC* CmCPacketBuild ( CmCh *header, char *buf, int len );
CmII* CmIIPacketBuild ( CmIIh *header, char *buf, int len );
void CmCPacketFree ( CmC *cmc_pkt );
void CmIIPacketFree ( CmII *cmii_pkt );

#endif
